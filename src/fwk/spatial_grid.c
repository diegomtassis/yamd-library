/*
 * spatial_grid.c
 *
 *  Created on: Jan 3, 2020
 *      Author: diegomtassis
 */

#include "../../inc/fwk/spatial_grid.h"

#include <genesis.h>

#include "../../inc/fwk/commons.h"
#include "../../inc/fwk/doubly_linked_list.h"

void spatialGridInit(SpatialGrid* grid, u8 dim_x, u8 dim_y) {

	grid->dimension.x = dim_x;
	grid->dimension.y = dim_y;

	u16 cell_width = VDP_getScreenWidth() / dim_x;
	u16 cell_height = VDP_getScreenHeight() / dim_y;

	grid->cells = MEM_calloc((sizeof(SpatialGridCell*)) * dim_x);

	Box_s16* box;
	for (int x = 0; x < dim_x; x++) {

		grid->cells[x] = MEM_calloc((sizeof(SpatialGridCell)) * dim_y);

		for (int y = 0; y < dim_y; y++) {

			box = &grid->cells[x][y].aabb;

			setV2s16(&box->min, cell_width * x, cell_height * y);
			box->w = cell_width;
			box->h = cell_height;
			updateBoxMax(box);

			doublyLinkedListInit(&grid->cells[x][y].e);
		}
	}
}

void spatialGridRelease(SpatialGrid* grid) {

	if (!grid) {
		return;
	}

	if (grid->cells) {
		for (int x = 0; x < grid->dimension.x; x++) {
			for (int y = 0; y < grid->dimension.y; y++) {
				doublyLinkedListRelease(&grid->cells[x][y].e);
			}
			MEM_free(grid->cells[x]);
		}

		MEM_free(grid->cells);
		grid->cells = 0;
	}

	grid->dimension.x = 0;
	grid->dimension.y = 0;
}

void spatialGridIndex(SpatialGrid* grid, Box_s16 object) {

	if (!grid) {
		return;
	}

	if (grid->cells) {
		for (int x = 0; x < grid->dimension.x; x++) {
			for (int y = 0; y < grid->dimension.y; y++) {

				SpatialGridCell cell = grid->cells[x][y];
				KLog_S4_("Attempting to index box [", object.min.x, "-", object.max.x, ", ", object.min.y, "-",
						object.max.y, "]");
				KLog_S4_("in cell [", object.min.x, "-", object.max.x, ", ", object.min.y, "-", object.max.y, "]");

				if (overlap(cell.aabb, object)) {

					doublyLinkedListAdd(&cell.e, &object);
					KLog("Indexed");
				} else {
					KLog("Not indexed");
				}
			}
		}
	}
}
