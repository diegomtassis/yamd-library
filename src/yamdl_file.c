/*
 * yamdl_file.c
 *
 *  Created on: Apr 06, 2019
 *      Author: diegomtassis
 */

#include <genesis.h>

#include "../inc/fwk/printer.h"

void printDisclaimer() {

	VDP_setScreenWidth320();
	VDP_setScreenHeight224();

	VDP_setTextPalette(PAL2);

	printerOn();
	waitMs(WAIT_1100);

	print("Program: YAMD-library test");
	waitMs(WAIT_750);

	println("");
	println("");
	print("Written by Diego Martin, 2019");
	waitMs(WAIT_750);

	println("");
	println("");
	print("Work in progress");
	waitMs(WAIT_750);

	println("");
	println("");
	print("This information priority one");
	waitMs(WAIT_750);

	println("");
	println("");
	print("End of Line");
}

void clearDisclaimer() {

	printerOff();
}
