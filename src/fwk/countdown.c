/*
 * countdown.c
 *
 *  Created on: Dec 24, 2019
 *      Author: diegomtassis
 */

#include "../../inc/fwk/countdown.h"

#include <timer.h>
#include <types.h>

#include "../../inc/fwk/commons.h"

static u32 countdowns[MAXTIMER];

void startCountDown(u16 numTimer, u32 subticks) {

	startTimer(numTimer);
	countdowns[numTimer] = subticks;
}

void startCountDownRandom(u16 numTimer, u32 minSubticks, u32 maxSubticks) {

	startCountDown(numTimer, randomInRangeU32(minSubticks, maxSubticks));
}

bool isCountDownFinished(u16 numTimer, bool restart) {

	u32 countdown = countdowns[numTimer];
	bool isFinished = getTimer(numTimer, FALSE) > countdown;

	if (isFinished && restart) {
		startCountDown(numTimer, countdown);
	}

	return isFinished;
}

