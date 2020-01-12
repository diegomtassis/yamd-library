/*
 * spatial_grid.h
 *
 *  Created on: Jan 3, 2020
 *      Author: diegomtassis
 */

#ifndef INC_FWK_SPATIAL_GRID_H_
#define INC_FWK_SPATIAL_GRID_H_

#include <genesis.h>

#include "array_fixed_list.h"
#include "physics.h"

typedef struct SpatialGrid SpatialGrid;
typedef struct SpatialGridCell SpatialGridCell;

struct SpatialGridCell {
	Box_s16 aabb;
	ArrayFixedList e;
};

struct SpatialGrid {
	u8 rows, columns;
	SpatialGridCell** cells;
};

void spatialGridInit(SpatialGrid* grid, u8 rows, u8 columns, u8 max_num_boxes);
void spatialGridRelease(SpatialGrid* grid);

void spatialGridIndex(SpatialGrid* grid, const Box_s16* object);

#endif /* INC_FWK_SPATIAL_GRID_H_ */
