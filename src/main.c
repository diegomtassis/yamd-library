/*
 * main.c
 *
 *  Created on: Apr 06, 2019
 *      Author: diegomtassis
 */

#include <genesis.h>

#include "../inc/fwk/vdp_utils.h"

//#include "../inc/fwk/logger.h"

#define LOADING_TIME	3000

int main(u16 hard) {

	// default resolution
	VDP_setScreenWidth256();
	VDP_setScreenHeight224();

	if (hard) {

	}


	while (1) {

		VDP_waitVSync();
	}

	return 0;
}
