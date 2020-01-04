/*
 * spatial_grid.h
 *
 *  Created on: Jan 3, 2020
 *      Author: diegomtassis
 */

#ifndef INC_FWK_SPATIAL_GRID_H_
#define INC_FWK_SPATIAL_GRID_H_

#include <genesis.h>

#include "doubly_linked_list.h"
#include "physics.h"

typedef struct SpatialGrid SpatialGrid;
typedef struct SpatialGridCell SpatialGridCell;

struct SpatialGridCell {
	Box_s16 aabb;
	DoublyLinkedList e;
};

struct SpatialGrid {
	V2s16 dimension;
	SpatialGridCell** cells;
};

void spatialGridInit(SpatialGrid* grid, u8 dim_x, u8 dim_y);
void spatialGridRelease(SpatialGrid* grid);

void spatialGridIndex(SpatialGrid* grid, Box_s16 object);

#endif /* INC_FWK_SPATIAL_GRID_H_ */
