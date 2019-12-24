/*
 * main.c
 *
 *  Created on: Apr 06, 2019
 *      Author: diegomtassis
 */

#include <genesis.h>

#include "../inc/yamdl_file.h"

//#include "../inc/fwk/logger.h"

#define LOADING_TIME	3000

int main(u16 hard) {

	VDP_setScreenWidth320();
	VDP_setScreenHeight224();

	if (hard) {
		printDisclaimer();
		JOY_waitPress(JOY_1, BUTTON_BTN);
		clearDisclaimer();

		waitMs(50);
	}

	while (1) {

		VDP_waitVSync();
	}

	return 0;
}
