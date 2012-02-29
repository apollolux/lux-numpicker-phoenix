#include "lotto.hpp"

using namespace nall;
using namespace phoenix;

App::App(int argc, char** argv) {
	// MAIN
	G = {128,128,400,300}; title = "Number Pick";
	setTitle(title);
	setGeometry(G);
	setResizable(false);
	// MENU STUFF
	mFile.setText("File");
	mFile_Prefill_Lotto.setText("Prefill from lottery...");
		mFile_Prefill_Lotto_Mega.setText("NY::Mega Millions");// mFile_Hello.setEnabled(false);
		mFile_Prefill_Lotto_Power.setText("NY::Powerball");
	mFile_Prefill_Deck.setText("Prefill from deck...");
		mFile_Prefill_Deck_THE.setText("52-Card::Texas Hold 'em");
	mFile_Draw.setText("Draw!");
	mFile_Quit.setText("Quit");
	mHelp.setText("Help");
	mHelp_About.setText("About...");
	append(mFile);
		mFile_Prefill_Lotto.append(mFile_Prefill_Lotto_Mega);
		mFile_Prefill_Lotto.append(mFile_Prefill_Lotto_Power);
		mFile.append(mFile_Prefill_Lotto);
		mFile_Prefill_Deck.append(mFile_Prefill_Deck_THE);
		//mFile.append(mFile_Prefill_Deck);
		mFile.append(msFile[0]);
		mFile.append(mFile_Draw);
		mFile.append(msFile[1]);
		mFile.append(mFile_Quit);
	append(mHelp);
		mHelp.append(mHelp_About);
	setMenuVisible();
	// "STATUSBAR"
	setStatusText({title," by lux"});
	setStatusVisible();
	stBar.create({title," by lux"});
	// MAIN PANEL
	layOut.create("Output");
	layOut.append(lvOutput, {~0, ~0});
	//layOut.append(tOutput, {~0, ~0});
	layStats.create("Statistics");
	layStats.append(lvStats, {~0, ~0});
	bProcess.setText("Draw!");
	fDraws.create("Draws"); fDraws.setValue(1);
	fPrice.create("Price"); fPrice.setValue("1.00");
	fCost.create("Cost"); fCost.field.setEditable(false);
		layAct.append(fDraws, {~0, 0}, 4); layAct.append(fPrice, {~0, 0}, 4);
		layAct.append(fCost, {~0, 0}, 4); layAct.append(bProcess, {~0, 24});
	lBase.setText("Base Field"); fBaseN.create("N"); fBaseR.create("R");
		layBase.append(lBase, {~0, 0}, 4); layBase.append(fBaseN, {~0, 0}, 2); layBase.append(fBaseR, {~0, 0});
	lPower.setText("Extra Ball"); fPowerN.create("N"); fPowerR.create("R");
		layPower.append(lPower, {~0, 0}, 4); layPower.append(fPowerN, {~0, 0}, 2); layPower.append(fPowerR, {~0, 0});
	tOutput.setText(""); tOutput.setEditable(false); tOutput.setVisible(false); tOutput.setWordWrap(true);
	lvOutput.setHeaderText("Base", "EX"); lvOutput.setHeaderVisible(true); lvOutput.setVisible(true);
	lvStats.setHeaderText("Number", "F"); lvStats.setHeaderVisible(true);
	layBalls.create("Settings");
	layBalls.setAlignment(0.0);
	layBalls.append(layAct, {~0, 0}, 4);
	layBalls.append(layBase, {~0, 0}, 4);
	layBalls.append(layPower, {~0, 0}, 4);
	layBalls.append(spB, {~0, ~0});
	layMain.setMargin(4);
	layMain.append(layBalls, {G.width>>2, ~0}, 4);
	layMain.append(layOut, {~0, ~0}, 4);
	layMain.append(layStats, {~0, ~0});
	// WINDOW
	//layMain.append(spM, {2, ~0});
	layout.append(layMain, {~0, ~0});
	//layout.append(stBar, {~0, 0});
	append(layout);
	// PROC
	brng.seed(); xrng.seed();
	bProcess.onActivate = mFile_Draw.onActivate = [&]() {
		unsigned bn = integer(fBaseN.text()), br = integer(fBaseR.text());
		unsigned pn = integer(fPowerN.text()), pr = integer(fPowerR.text());
		unsigned d = integer(fDraws.text());
		float p = fp(fPrice.text());
		string outp = "", tmpb, tmpp;
		array<unsigned> bncr, pncr;
		unsigned* bnums = new unsigned[bn];
		unsigned* pnums = new unsigned[pn];
		//memset(bnums, 0, bn);
		//memset(&pnums, 0, pn);
		unsigned i, j;
		lvOutput.reset(); lvStats.reset();
		fCost.setValue(p*(float)d);
		//MessageWindow::information(*this, {"TODO:\n{",bn,"c",br," + ",pn,"c",pr,"} * ",d});
		brng.set(bn, br); xrng.set(pn, pr);
		if (d<=MAXDRAWS&&br>=0) {
			float _d = 100.0f/(float)d;
			for (i = 0; i < bn; ++i) bnums[i] = 0;
			for (i = 0; i < pn; ++i) pnums[i] = 0;
			//string hdr;
			//for (i = 0; i < br; ++i) hdr.append((string){i>0?",":"","B",i+1});
			//lvOutput.setHeaderText(hdr);
			for (i = 0; i < d; ++i) {
				tmpb = ""; tmpp = "";
				bncr = brng.combine();
				pncr = xrng.combine();
				if (bncr.size()) {
					for (j = 0; j < bncr.size(); ++j) {
						tmpb.append((string){j>0?", ":"", 1+bncr[j]});
						//if (bnums[bncr[j]]>d) bnums[bncr[j]] = 0;
						(bnums[bncr[j]])++;
					}
					if (pncr.size()) {
						for (j = 0; j < pncr.size(); ++j) {
							tmpp.append((string){j>0?", ":"", 1+pncr[j]});
							//if (pnums[pncr[j]]>d) pnums[pncr[j]] = 0;
							(pnums[pncr[j]])++;
						}
					}
					lvOutput.append(tmpb, tmpp);
					outp.append((string){"\n",tmpb,tmpp.length()?" + ":"",tmpp});
				}
				else stBar.setText({"Error, couldn't ",brng.n,"c",brng.r," (",i+1,")"});
				stBar.set((unsigned)(_d*(float)i));
			}
			if (outp.length()==0) {
				outp = "Something went wrong! Fix your values and try again, please.";
				lvOutput.setVisible(false);
				tOutput.setVisible(true);
				layOut.remove(lvOutput);
				layOut.append(tOutput, {~0, ~0});
			}
			else {
				outp = (string){"Results:\n", outp};
				for (i = 0; i < bn; ++i) if (bnums[i]>0) lvStats.append(i+1, bnums[i]);
				lvOutput.setVisible(true);
				tOutput.setVisible(false);
				layOut.remove(tOutput);
				layOut.append(lvOutput, {~0, ~0});
			}
			stBar.set(100);
		}
		else {
			outp = {"Too many draws! Please enter ",MAXDRAWS," or fewer draws and try again."};
			lvOutput.setVisible(false);
			tOutput.setVisible(true);
			layOut.remove(lvOutput);
			layOut.append(tOutput, {~0, ~0});
		}
		tOutput.setEditable(true); tOutput.setText(outp); tOutput.setEditable(false);
		lvOutput.autoSizeColumns(); lvStats.autoSizeColumns();
		if (bnums) delete[] bnums;
		if (pnums) delete[] pnums;
	};
	mFile_Prefill_Lotto_Mega.onActivate = [&]() { prefill(56, 5, 46, 1, 1.00); };
	mFile_Prefill_Lotto_Power.onActivate = [&]() { prefill(59, 5, 39, 1, 2.00); };
	mFile_Prefill_Deck_THE.onActivate = [&]() { prefill(52, 2, 0, 0, 1.00); };
	mHelp_About.onActivate = [&]() { MessageWindow::information(*this, {title,"\n(c)2012 Apollolux Digital Designs"}); };
	onClose = mFile_Quit.onActivate = [&]() {
		OS::quit();
	};
	/* setStatusSimpleText = [this](const string &t) {
		//SendMessage((&p)->hstatus, SB_SIMPLE, (WPARAM)true, 0);
		setStatusText(t);
		//SendMessage((&p)->hstatus, SB_SIMPLE, (WPARAM)false, 0);
	}; */
}
void App::create() {
	setVisible();
	//stBar.start(0);
}
void App::prefill(int bn, int br, int pn, int pr, float cost) {
	fBaseN.setValue(bn); fBaseR.setValue(br);
	fPowerN.setValue(pn); fPowerR.setValue(pr);
	fPrice.setValue(cost);
}


int main(int argc, char** argv) {
	App app(argc, argv);
	app.create();
	OS::main();
	return 0;
}
