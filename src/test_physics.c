/*
 * test_physics.c
 *
 *  Created on: Dec 24, 2019
 *      Author: diegomtassis
 */

#include "../inc/test_suite.h"

#include <genesis.h>

#include "../inc/fwk/printer.h"

static void runPhysicsSanbox();

void testPhysics() {

	KLog("testing physics");

	VDP_setTextPalette(PAL2);

	turnPrinterOn();

	println("Move the target to interact with other objects in the screen.");
	println("");
	printerWait(500);

	println("Blue objects turn red when the target overlaps them.");
	println("");
	printerWait(500);

	println("Green objects can not be gone through.");

	printerWait(3000);
	turnPrinterOff();

	runPhysicsSanbox();
}

static void runPhysicsSanbox() {

}
