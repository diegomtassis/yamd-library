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

static bool indexedInPosition(u8 dim_x, u8 dim_y, u8 x, u8 y, bool cell_indexed[dim_x][dim_y]);

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

void spatialGridIndex(SpatialGrid* grid, const Box_s16* object) {

	if (!grid) {
		return;
	}

	u8 dim_x = grid->dimension.x;
	u8 dim_y = grid->dimension.y;

	bool cell_indexed[dim_x][dim_y];
	bool already_indexed = FALSE;

	if (grid->cells) {
		for (int x = 0; x < dim_x; x++) {
			for (int y = 0; y < dim_y; y++) {

				SpatialGridCell cell = grid->cells[x][y];

				// in some scenarios there makes no sense to keep exploring
				if (already_indexed) {

					u8 combined_adjacents = indexedInPosition(dim_x, dim_y, x - 1, y - 1, cell_indexed)
							+ indexedInPosition(dim_x, dim_y, x, y - 1, cell_indexed)
							+ indexedInPosition(dim_x, dim_y, x - 1, y, cell_indexed);
					if (combined_adjacents == 3) {
						doublyLinkedListAdd(&grid->cells[x][y].e, object); // somehow using &cell.e passes a wrong address for the list
						already_indexed = TRUE;
						cell_indexed[x][y] = TRUE;
						continue;

					} else if (combined_adjacents == 2 || indexedInPosition(dim_x, dim_y, x - 1, y - 1, cell_indexed)) {
						return;
					}
				}

				if (overlap(&cell.aabb, object)) {
					doublyLinkedListAdd(&grid->cells[x][y].e, object); // somehow using &cell.e passes a wrong address for the list
					already_indexed = TRUE;
					cell_indexed[x][y] = TRUE;
				}
			}
		}
	}
}

static bool indexedInPosition(u8 dim_x, u8 dim_y, u8 x, u8 y, bool cell_indexed[dim_x][dim_y]) {

	if (x < 0 || y < 0 || x >= dim_x || y >= dim_y) {
		return FALSE;
	}

	return cell_indexed[x][y];
}
