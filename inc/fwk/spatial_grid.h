/*
 * spatial_grid.h
 *
 *  Created on: Jan 3, 2020
 *      Author: diegomtassis
 */

#ifndef INC_FWK_SPATIAL_GRID_H_
#define INC_FWK_SPATIAL_GRID_H_

#include <genesis.h>

typedef struct {
	V2s16 dimension;
	void** e;
} SpatialGrid;

void index();

#endif /* INC_FWK_SPATIAL_GRID_H_ */
