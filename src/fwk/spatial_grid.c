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

	grid->rows = rows;
	grid->columns = columns;

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
		for (int row = 0; row < grid->rows; row++) {
			for (int column = 0; column < grid->columns; column++) {
				doublyLinkedListRelease(&grid->cells[row][column].e);
			}
			MEM_free(grid->cells[row]);
		}

		MEM_free(grid->cells);
		grid->cells = 0;
	}

	grid->rows = 0;
	grid->columns = 0;
}

void spatialGridIndex(SpatialGrid* grid, const Box_s16* object) {

	if (!grid) {
		return;
	}

	if (grid->cells) {

		u8 rows = grid->rows;
		u8 columns = grid->columns;

		bool indexed_cells[rows][columns];
		bool already_indexed = FALSE;
		u8 overlaps_count = 0;

		u8 row = 0;
		bool keep_exploring_rows = TRUE;
		do {
			u8 column = 0;
			bool keep_exploring_columns_per_row = TRUE;
			do {
				SpatialGridCell cell = grid->cells[row][column];

				// some scenarios allow shortcuts
				if (already_indexed) {

					u8 combined_adjacents = indexedInPosition(rows, columns, row - 1, column - 1, indexed_cells)
							+ indexedInPosition(rows, columns, row, column - 1, indexed_cells)
							+ indexedInPosition(rows, columns, row - 1, column, indexed_cells);
					if (combined_adjacents == 3) {

						// easiest scenario, the box is present in 3 surrounding cell, hence also in this one
						doublyLinkedListAdd(&grid->cells[row][column].e, object); // somehow using &cell.e passes a wrong address for the list
						already_indexed = TRUE;
						indexed_cells[row][column] = TRUE;

					} else if (combined_adjacents == 2) {
						// if it's present only in two surrounding cells then it can't be in this one
						keep_exploring_columns_per_row = FALSE;
						break;

					} else if (combined_adjacents == 1) {
						if (indexedInPosition(rows, columns, row - 1, column - 1, indexed_cells)) {
							keep_exploring_columns_per_row = FALSE;
							keep_exploring_rows = FALSE;
							break;

						} else {
							overlaps_count++;
							if (overlap(&cell.aabb, object)) {
								doublyLinkedListAdd(&grid->cells[row][column].e, object); // somehow using &cell.e passes a wrong address for the list
								already_indexed = TRUE;
								indexed_cells[row][column] = TRUE;
							}
						}
					} else { // combined_adjacents == 0
						// not in this cell, but maybe in one in this row
						break;
					}
				} else {
					overlaps_count++;
					if (overlap(&cell.aabb, object)) {
						doublyLinkedListAdd(&grid->cells[row][column].e, object); // somehow using &cell.e passes a wrong address for the list
						already_indexed = TRUE;
						indexed_cells[row][column] = TRUE;
					}
				}

				column++;
			} while (column < columns && keep_exploring_columns_per_row);

			row++;
		} while (row < rows && keep_exploring_rows);

		KLog_U1("overlap invocations: ", overlaps_count);
	}
}

static bool indexedInPosition(u8 rows, u8 columns, u8 row, u8 column, bool indexed_cells[rows][columns]) {

	if (column < 0 || row < 0 || column >= columns || row >= rows) {
		return FALSE;
	}

	return indexed_cells[row][column];
}
