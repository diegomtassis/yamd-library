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

	printerOn();
	waitMs(WAIT_1100);

	print("Testing printer");
	waitMs(WAIT_750);

	println("");
	print("Testing printer br");
	waitMs(WAIT_750);

	println("");
	println("");
	print("End of Line");
	waitMs(WAIT_1100);

	printerOff();
}
