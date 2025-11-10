/*
 * elements.h
 *
 *  Created on: Dec 24, 2019
 *      Author: diegomtassis
 */

#ifndef INC_ELEMENTS_H_
#define INC_ELEMENTS_H_

#include <genesis.h>

typedef enum {
	DATA_STRUCTURES = 1, //
	PHYSICS, //
	SPATIAL_GRID, //
	PRINTER, //
} Utility;

typedef struct Config Config;

struct Config {
	Utility test;
};

#endif /* INC_ELEMENTS_H_ */
