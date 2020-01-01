/*
 * test_printer.c
 *
 *  Created on: Dec 29, 2019
 *      Author: diegomtassis
 */

#include "../inc/test_suite.h"

#include "../inc/fwk/printer.h"

#include <genesis.h>

static void printFlynnSpeech();
static void printArchitectSpeech();

void testPrinter() {

	KLog("testing printer");

	VDP_setTextPalette(PAL2);

	turnPrinterOn();
	printerWait(WAIT_1100);

	printArchitectSpeech();
	printerWait(WAIT_1100);

	printFlynnSpeech();

	turnPrinterOff();
}

static void printFlynnSpeech() {

	clearScreen();
	printerWait(WAIT_1100);

	print("The Grid.");
	printerWait(MIDDLE_DOT_WAIT);
	println(" A digital frontier.");
	printerWait(MIDDLE_DOT_WAIT);

	println("I tried to picture clusters of information as they moved through the computer.");
	printerWait(MIDDLE_DOT_WAIT);

	println("");
	print("What did they look like?");
	printerWait(COMMA_WAIT);
	print(" Ships?");
	printerWait(COMMA_WAIT);
	print(" Motorcycles?");
	printerWait(COMMA_WAIT);
	println(" Were the circuits like freeways?");
	printerWait(MIDDLE_DOT_WAIT);

	println("");
	println("I kept dreaming of a world I thought I'd never see.");
	printerWait(MIDDLE_DOT_WAIT);

	println("");
	print("And then,");
	printerWait(COMMA_WAIT);
	print(" one day");
	printerWait(COMMA_WAIT);
	print(".");
	printerWait(COMMA_WAIT);
	print(".");
	printerWait(COMMA_WAIT);
	print(".");
	printerWait(COMMA_WAIT);
	print(" I");
	printerWait(MIDDLE_DOT_WAIT);
	print(" got");
	printerWait(MIDDLE_DOT_WAIT);
	print(" in");

	printerWait(FULL_STOP_WAIT);
}

static void printArchitectSpeech() {

	clearScreen();
	printerWait(WAIT_1100);

	print("I am the Architect.");
	printerWait(PARAGRAPH_DOT_WAIT);
	println("");
	println("");
	print("I created the matrix.");
	printerWait(PARAGRAPH_DOT_WAIT);
	println("");
	println("");
	print("I've been waiting for you.");
	printerWait(PARAGRAPH_DOT_WAIT);
	println("");
	println("");
	print("You have many questions,");
	printerWait(COMMA_WAIT);
	print(" and although the process has altered your consciousness,");
	printerWait(COMMA_WAIT);
	print(" you remain irrevocably human.");
	printerWait(PARAGRAPH_DOT_WAIT);
	println("");
	println("");
	print("Ergo,");
	printerWait(COMMA_WAIT);
	print(" some of my answers you will understand,");
	printerWait(COMMA_WAIT);
	print(" and some of them you will not.");
	printerWait(PARAGRAPH_DOT_WAIT);
	println("");
	println("");
	print("Concordantly,");
	printerWait(COMMA_WAIT);
	print(" while your first question may be the most pertinent,");
	printerWait(COMMA_WAIT);
	print(" you may or may not realize it is also irrelevant.");

	printerWait(FULL_STOP_WAIT);
	println("");
	println("");

	print("Your life is the sum of a remainder of an unbalanced equation inherent to the programming of the matrix.");
	printerWait(MIDDLE_DOT_WAIT);
	print(" You are the eventuality of an anomaly,");
	printerWait(COMMA_WAIT);
	print(
			" which despite my sincerest efforts I have been unable to eliminate from what is otherwise a harmony of mathematical precision.");
	printerWait(MIDDLE_DOT_WAIT);
	print(" While it remains a burden to sedulously avoid it,");
	printerWait(COMMA_WAIT);
	print(" it is not unexpected,");
	printerWait(COMMA_WAIT);
	print(" and thus not beyond a measure of control.");
	printerWait(MIDDLE_DOT_WAIT);
	print(" Which has led you,");
	printerWait(COMMA_WAIT);
	print(" inexorably,");
	printerWait(COMMA_WAIT);
	print(" here.");

	printerWait(FULL_STOP_WAIT);
}
