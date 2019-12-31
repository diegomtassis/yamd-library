/*
 * main.c
 *
 *  Created on: Apr 06, 2019
 *      Author: diegomtassis
 */

#include <genesis.h>

#include "../inc/config.h"
#include "../inc/elements.h"
#include "../inc/fwk/printer.h"
#include "../inc/fwk/vdp_utils.h"
#include "../inc/test_suite.h"
#include "../inc/yamdl_file.h"

//#include "../inc/fwk/logger.h"

#define LOADING_TIME	3000

int main(u16 hard) {

	VDP_setScreenWidth320();
	VDP_setScreenHeight224();

	initPrinter();

	if (hard) {
		printDisclaimer();
		JOY_waitPress(JOY_1, BUTTON_BTN);
		clearDisclaimer();
		waitMs(50);
	}

	resetTileMemory();

	initConfig();

	while (1) {

		// log_memory();
		waitMs(250);
		const Config* config = setUpTest();
		runTest(config);

		VDP_waitVSync();
	}

	return 0;
}
