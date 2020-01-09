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

static bool indexedInPosition(u8 columns, u8 rows, u8 column, u8 row, bool indexed_cells[columns][rows]);

void spatialGridInit(SpatialGrid* grid, u8 rows, u8 columns) {

	grid->dimension.y = rows;
	grid->dimension.x = columns;

	u16 cell_width = VDP_getScreenWidth() / columns;
	u16 cell_height = VDP_getScreenHeight() / rows;

	grid->cells = MEM_calloc((sizeof(SpatialGridCell*)) * rows);

	Box_s16* box;
	for (int row = 0; row < rows; row++) {

		grid->cells[row] = MEM_calloc((sizeof(SpatialGridCell)) * columns);

		for (int column = 0; column < columns; column++) {

			box = &grid->cells[row][column].aabb;

			setV2s16(&box->min, cell_width * column, cell_height * row);
			box->w = cell_width;
			box->h = cell_height;
			updateBoxMax(box);

			doublyLinkedListInit(&grid->cells[row][column].e);
		}
	}
}

void spatialGridRelease(SpatialGrid* grid) {

	if (!grid) {
		return;
	}

	if (grid->cells) {
		for (int row = 0; row < grid->dimension.y; row++) {
			for (int column = 0; column < grid->dimension.x; column++) {
				doublyLinkedListRelease(&grid->cells[row][column].e);
			}
			MEM_free(grid->cells[row]);
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

	if (grid->cells) {

		u8 rows = grid->dimension.y;
		u8 columns = grid->dimension.x;

		bool indexed_cells[rows][columns];
		bool already_indexed = FALSE;

		for (int row = 0; row < rows; row++) {
			for (int column = 0; column < columns; column++) {

				SpatialGridCell cell = grid->cells[row][column];

				// some scenarios allow shortcuts
				if (already_indexed) {

					u8 combined_adjacents = indexedInPosition(rows, columns, row - 1, column - 1, indexed_cells)
							+ indexedInPosition(rows, columns, row, column - 1, indexed_cells)
							+ indexedInPosition(rows, columns, row - 1, column, indexed_cells);
					if (combined_adjacents == 3) {
						doublyLinkedListAdd(&grid->cells[column][row].e, object); // somehow using &cell.e passes a wrong address for the list
						already_indexed = TRUE;
						indexed_cells[column][row] = TRUE;
						continue;

					} else if (combined_adjacents == 2
							|| indexedInPosition(rows, columns, row - 1, column - 1, indexed_cells)) {
						return;
					}
				}

				if (overlap(&cell.aabb, object)) {
					doublyLinkedListAdd(&grid->cells[row][column].e, object); // somehow using &cell.e passes a wrong address for the list
					already_indexed = TRUE;
					indexed_cells[row][column] = TRUE;
				}
			}
		}
	}
}

static bool indexedInPosition(u8 rows, u8 columns, u8 row, u8 column, bool indexed_cells[rows][columns]) {

	if (column < 0 || row < 0 || column >= columns || row >= rows) {
		return FALSE;
	}

	return indexed_cells[row][column];
}
