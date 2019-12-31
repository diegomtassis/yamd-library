/*
 * test_printer.c
 *
 *  Created on: Dec 29, 2019
 *      Author: diegomtassis
 */

#include "../inc/test_suite.h"

#include "../inc/fwk/printer.h"

#include <genesis.h>

static const int COMMA_WAIT = 500;
static const int MIDDLE_DOT_WAIT = 900;
static const int PARAGRAPH_DOT_WAIT = 1250;
static const int FULL_STOP_WAIT = 3000;

static void printFlynnTheGridSpeech();
static void printLoremIpsum();
static void printArchitectSpeech();

void testPrinter() {

	KLog("testing printer");

	VDP_setTextPalette(PAL2);
	VDP_clearPlan(VDP_getTextPlan(), TRUE);

	printerOn();

	clearScreen();
	waitMs(WAIT_1100);

	printFlynnTheGridSpeech();

	clearScreen();
	waitMs(WAIT_1100);

	printArchitectSpeech();

	clearScreen();
	waitMs(WAIT_1100);

	printLoremIpsum();

	printerOff();
}

static void printFlynnTheGridSpeech() {

	clearScreen();
	printerOn();
	waitMs(WAIT_1100);

	print("The Grid.");
	waitMs(MIDDLE_DOT_WAIT);
	print(" A digital frontier.");
	waitMs(MIDDLE_DOT_WAIT);
	println("");
	print("I tried to picture clusters of information as they moved through the computer.");
	waitMs(MIDDLE_DOT_WAIT);
	println("");
	println("");
	print("What did they look like?");
	waitMs(COMMA_WAIT);
	print(" Ships?");
	waitMs(COMMA_WAIT);
	print(" Motorcycles?");
	waitMs(COMMA_WAIT);
	print(" Were the circuits like freeways?");
	waitMs(MIDDLE_DOT_WAIT);
	println("");
	println("");
	print("I kept dreaming of a world I thought I'd never see.");
	waitMs(MIDDLE_DOT_WAIT);
	println("");
	println("");
	print("And then,");
	waitMs(COMMA_WAIT);
	print(" one day");
	waitMs(COMMA_WAIT);
	print(".");
	waitMs(COMMA_WAIT);
	print(".");
	waitMs(COMMA_WAIT);
	print(".");
	waitMs(COMMA_WAIT);
	print(" I");
	waitMs(MIDDLE_DOT_WAIT);
	print(" got");
	waitMs(MIDDLE_DOT_WAIT);
	print(" in");

	waitMs(FULL_STOP_WAIT);
}

static void printArchitectSpeech() {

	clearScreen();
	printerOn();
	waitMs(WAIT_1100);

	print("Your life is the sum of a remainder of an unbalanced equation inherent to the programming of the matrix.");
	waitMs(MIDDLE_DOT_WAIT);
	print(" You are the eventuality of an anomaly,");
	waitMs(COMMA_WAIT);
	print(
			" which despite my sincerest efforts I have been unable to eliminate from what is otherwise a harmony of mathematical precision.");
	waitMs(MIDDLE_DOT_WAIT);
	print(" While it remains a burden to sedulously avoid it,");
	waitMs(COMMA_WAIT);
	print(" it is not unexpected,");
	waitMs(COMMA_WAIT);
	print(" and thus not beyond a measure of control.");
	waitMs(MIDDLE_DOT_WAIT);
	print(" Which has led you,");
	waitMs(COMMA_WAIT);
	print(" inexorably,");
	waitMs(COMMA_WAIT);
	print(" here.");

	waitMs(FULL_STOP_WAIT);

	printerOff();
}

static void printLoremIpsum() {

	clearScreen();
	printerOn();
	waitMs(WAIT_1100);

	print("Lorem ipsum dolor sit amet,");
	waitMs(COMMA_WAIT);
	print(" consectetur adipiscing elit,");
	waitMs(COMMA_WAIT);
	print(" sed do eiusmod tempor incididunt ut labore et dolore magna aliqua.");
	waitMs(MIDDLE_DOT_WAIT);
	print(" Ut enim ad minim veniam,");
	waitMs(COMMA_WAIT);
	print(" quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat.");
	waitMs(MIDDLE_DOT_WAIT);
	print(" Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur.");
	waitMs(MIDDLE_DOT_WAIT);
	print("Excepteur sint occaecat cupidatat non proident,");
	waitMs(COMMA_WAIT);
	print(" sunt in culpa qui officia deserunt mollit anim id est laborum.");
	waitMs(FULL_STOP_WAIT);

	printerOff();
}
