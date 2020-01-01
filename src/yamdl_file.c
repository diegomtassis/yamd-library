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

	turnPrinterOn();
	printerWait(WAIT_1100);

	print("Program: YaMDl test suite");
	printerWait(WAIT_750);

	println("");
	println("");
	print("Written by Diego Martin, 2019");
	printerWait(WAIT_750);

	println("");
	println("");
	print("Work in progress");
	printerWait(WAIT_750);

	println("");
	println("");
	print("This information priority one");
	printerWait(WAIT_750);

	println("");
	println("");
	print("End of Line");
}

void clearDisclaimer() {

	turnPrinterOff();
}
