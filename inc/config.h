/*
 * config.h
 *
 *  Created on: Dec 24, 2019
 *      Author: diegomtassis
 */

#ifndef INC_CONFIG_H_
#define INC_CONFIG_H_

#include "elements.h"

typedef enum {
	COLLISIONS, //
	LISTS, //
} Utility;

void initConfig();
const Config* setUpTest();

#endif /* INC_CONFIG_H_ */
