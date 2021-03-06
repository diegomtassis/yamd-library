/*
 * countdwon.h
 *
 *  Created on: May 4, 2019
 *      Author: diegomtassis
 */

#ifndef INC_COUNTDOWN_H_
#define INC_COUNTDOWN_H_

#include <genesis.h>

void startCountDown(u16 numTimer, u32 subticks);

void startCountDownRandom(u16 numTimer, u32 minSubticks, u32 maxSubticks);

bool isCountDownFinished(u16 numTimer, bool restart);

#endif /* INC_COUNTDOWN_H_ */
