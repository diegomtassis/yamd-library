/*
 * test_physics.c
 *
 *  Created on: Dec 24, 2019
 *      Author: diegomtassis
 */

#include "../inc/test_suite.h"

#include <genesis.h>

#include "../inc/fwk/printer.h"

void testPhysics() {

	KLog("testing physics");

	VDP_setTextPalette(PAL2);
	VDP_clearPlan(VDP_getTextPlan(), TRUE);

	clearScreen();
	turnPrinterOn();

	print("Physics test scenario not implemented yet.");

	waitMs(3000);
	turnPrinterOff();
}
