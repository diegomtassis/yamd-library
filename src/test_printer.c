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

static void printFlynnSpeech();
static void printArchitectSpeech();

void testPrinter() {

	KLog("testing printer");

	VDP_setTextPalette(PAL2);

	turnPrinterOn();
	waitMs(WAIT_1100);

	printArchitectSpeech();
	waitMs(WAIT_1100);

	printFlynnSpeech();

	turnPrinterOff();
}

static void printFlynnSpeech() {

	clearScreen();
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
	waitMs(WAIT_1100);

	print("I am the Architect.");
	waitMs(PARAGRAPH_DOT_WAIT);
	println("");
	println("");
	print("I created the matrix.");
	waitMs(PARAGRAPH_DOT_WAIT);
	println("");
	println("");
	print("I've been waiting for you.");
	waitMs(PARAGRAPH_DOT_WAIT);
	println("");
	println("");
	print("You have many questions,");
	waitMs(COMMA_WAIT);
	print(" and although the process has altered your consciousness,");
	waitMs(COMMA_WAIT);
	print(" you remain irrevocably human.");
	waitMs(PARAGRAPH_DOT_WAIT);
	println("");
	println("");
	print("Ergo,");
	waitMs(COMMA_WAIT);
	print(" some of my answers you will understand,");
	waitMs(COMMA_WAIT);
	print(" and some of them you will not.");
	waitMs(PARAGRAPH_DOT_WAIT);
	println("");
	println("");
	print("Concordantly,");
	waitMs(COMMA_WAIT);
	print(" while your first question may be the most pertinent,");
	waitMs(COMMA_WAIT);
	print(" you may or may not realize it is also irrelevant.");

	waitMs(FULL_STOP_WAIT);
	println("");
	println("");

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
}
