/*
 * test_data_structures.c
 *
 *  Created on: Dec 24, 2019
 *      Author: diegomtassis
 */

#include <genesis.h>

#include "../inc/fwk/printer.h"

void testLists() {

	KLog("testing data structures");

	VDP_setTextPalette(PAL2);
	VDP_clearPlan(VDP_getTextPlan(), TRUE);

	clearScreen();
	printerOn();

	print("Data structures test scenario not implemented yet.");

	waitMs(3000);
	printerOff();
}
