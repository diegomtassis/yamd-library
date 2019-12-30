/*
 * test_printer.c
 *
 *  Created on: Dec 29, 2019
 *      Author: diegomtassis
 */

#include "../inc/test_suite.h"

#include "../inc/fwk/printer.h"

#include <genesis.h>

void testPrinter() {

	KLog("testing printer");

	VDP_setTextPalette(PAL2);
	VDP_clearPlan(VDP_getTextPlan(), TRUE);

	clearScreen();
	printerOn();
	waitMs(WAIT_1100);

	print("The Grid.");
	waitMs(WAIT_1100);
	print(" A digital frontier.");
	waitMs(WAIT_1100);
	println("");
	print("I tried to picture clusters of information as they moved through the computer.");
	waitMs(WAIT_1100);
	println("");
	println("");
	print("What did they look like?");
	waitMs(WAIT_750);
	print(" Ships?");
	waitMs(WAIT_750);
	print(" Motorcycles?");
	waitMs(WAIT_750);
	print(" Were the circuits like freeways?");
	waitMs(WAIT_1100);
	println("");
	println("");
	print("I kept dreaming of a world I thought I'd never see.");
	waitMs(WAIT_750);
	println("");
	println("");
	print("And then,");
	waitMs(500);
	print(" one day");
	waitMs(WAIT_750);
	print(".");
	waitMs(250);
	print(".");
	waitMs(250);
	print(".");
	waitMs(250);
	print(".");
	waitMs(WAIT_750);
	print(" I");
	waitMs(500);
	print(" got");
	waitMs(500);
	print(" in");

	waitMs(3000);

	printerOff();
}
