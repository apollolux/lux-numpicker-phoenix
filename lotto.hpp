#include <nall/platform.hpp>
#include <nall/array.hpp>
#include <nall/random.hpp>
#include <nall/sort.hpp>
#include <nall/string.hpp>
#include <phoenix.hpp>
#include <ctime>

using namespace nall;
using namespace phoenix;

struct NR {
	random_lfsr rng;
	unsigned n;
	unsigned r;
	NR():n(0),r(0) { seed(); }
	NR(unsigned _n, unsigned _r):n(_n),r(_r) { seed(); }
	void set(unsigned _n, unsigned _r) { n = _n; r = _r; }
	void seed() { seed((unsigned)time(NULL)); }
	void seed(unsigned s) { rng.seed(s); }
	array<unsigned> permute() { return combine(true); }
	array<unsigned> combine(bool isOrdered=false) {
		array<unsigned> ret;
		if (r<=n) {
			unsigned q, _r = r;
			// TODO: compute combinations
			while (_r--) {
				do { q = rng()%n; } while (ret.find(q));
				ret.append(q);
			}
			if (!isOrdered) sort(ret.begin(), ret.size());
		}
		return ret;
	};
};

/**
 * "Fake" status bar class
 **/
struct StatusLayout : HorizontalLayout {
	Timer tmPrg;
	uint8_t prgVal;
	ProgressBar prg;
	Label status;
	//Window parentWin;
	void create(const string &s="Done.", bool hasTimer = false) {
		prgVal = 0;
		prg.setPosition(prgVal);
		setMargin(2);
		setText(s);
		append(prg, {100, 12}, 4);
		append(status, {~0, 12});
		if (hasTimer) tmPrg.onTimeout = [this]() {
			if (prgVal<101) {
				prg.setPosition(prgVal);
				status.setText({"(",prgVal,")"});
				++prgVal;
			}
			else {
				tmPrg.setEnabled(false);
				MessageWindow::information(Window::None, "Done!");
			}
		};
	}
	void start(uint8_t st=0) {
		prgVal = st;
		tmPrg.setEnabled(true);
		tmPrg.setInterval(50);
	}
	void setText(const string &s) { status.setText(s); }
	void set(uint8_t n) { if (n<101) prg.setPosition(prgVal=n); }
	void reset() {
		prgVal = 0;
		tmPrg.setEnabled(true);
	}
};

struct Fieldset : VerticalLayout {
	Label label;
	void setText(string l) { label.setText(l); }
	void create(const string &s="Label") {
		setText(s);
		append(label, {~0, 0}, 4);
	}
};

struct TextField : HorizontalLayout {
	Label label;
	LineEdit field;
	void setText(string l) { label.setText(l); field.setText(l); }
	void setValue(string l) { field.setText(l); }
	string text() { return field.text(); }
	void create(const string &s="Label") {
		setText(s);
		//setAlignment(0.5);
		//field.setWordWrap(false);
		append(label, {0, 0}, 2);
		append(field, {~0, 0});
	}
	//Geometry minimumGeometry() {}
};

struct App : public Window {
	NR brng, xrng;
	//function<void (const string &t)> setStatusSimpleText;
	static const uint32_t MAXDRAWS = 255;
	string title;
	// MENU
	Menu mFile, mHelp;
	Menu mFile_Prefill_Lotto, mFile_Prefill_Deck;
	Separator msFile[2], msFile_Prefill;
	Item mFile_Prefill_Lotto_Mega, mFile_Prefill_Lotto_Power;
	Item mFile_Prefill_Deck_THE;
	Item mFile_Draw, mFile_Quit, mHelp_About;
	//CheckItem mFile_Chk;
	// WINDOW
	Geometry G;
	StatusLayout stBar;
	VerticalLayout layout;
	HorizontalLayout layMain;
	Widget spM, spB, spD;
	// FIELDS
	Fieldset layBalls, layOut, layStats;
	VerticalLayout layBase, layPower, layAct;
	//HorizontalLayout layBalls;
	Label lBase, lPower, lCost;
	TextField fDraws, fPrice, fCost;
	TextField fBaseN, fBaseR;
	TextField fPowerN, fPowerR;
	TextEdit tOutput;
	ListView lvOutput, lvStats;
	Button bProcess;
	App(int argc, char** argv);
	void create();
	void prefill(int bn, int br, int pn, int pr, float cost);
};
