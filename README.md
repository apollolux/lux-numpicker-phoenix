# Preamble

This is a small app made to draw a set of (pseudo-)random numbers from a field of numbers. The order in which the numbers are picked doesn't matter, so this type of number picker is known as a "combination" (instead of a "permutation," where order matters).

# Compilation

Compiling this app requires the [phoenix GUI wrapper by byuu](http://byuu.org/phoenix); future versions of this code may include phoenix, but I haven't yet decided. Please be aware that the compilation process has only been confirmed to work on a MinGW-based environment.

1. Download this code into some directory.
2. Download [phoenix](http://byuu.org/phoenix) and unpack it to the parent directory of this code (ie, if this code is in somefolder/numpicker put phoenix in somefolder). If you put phoenix somewhere else please remember to modify the makefile to point to the right location.
3. Navigate to this code's directory and run <tt>make</tt>

# Installation

So far there's no installation; the compiled lux-numpicker is a standalone executable and can be run from anywhere. The pre-compiled binary has only been tested on Windows 7 64-bit, so if it doesn't work for you please either compile your own or wait for a 32-bit binary. So far it's only been tested on Windows, but there will eventually be a makefile that works on Linux.

# Usage

Run the executable! lux-numpicker offers the following functionality:

* Generate a set of numbers from a user-defined field of numbers
	* Change N in the Base Field section to the group of numbers from which to pick
	* Change R in the Base Field section to the set of numbers you want to pick
* Generate a set of numbers from a second user-defined field of numbers (eg, picking a "Power Ball" or "Mega Ball")
	* Change N in the Extra Ball section to the group of numbers from which to pick
	* Change R in the Extra Ball section to the set of numbers you want to pick
* Calculate the cost of playing a user-defined amount of games at a user-defined price
	* Change Draws to the number of times to pick numbers
	* Change Price to the price per game

The File menu has a "Prefill" option that allows you to fill the text fields with predefined values; so far only two lotteries (NY Mega Millions and NY Powerball) are available, but more can be added on request or you can edit the source yourself to add them. Future versions of this app will allow drawing cards from a standard 52-card deck.

Once the text fields have been properly filled, click "Draw!" to generate your numbers.

# Disclaimer

This program is for personal use only; I, Alex Rosario, am not responsible for any losses incurred through the use of this program. If you choose to play numbers picked during the use of this program, it is solely at the user's discretion and the user shall not hold Alex responsible for any outcomes.
