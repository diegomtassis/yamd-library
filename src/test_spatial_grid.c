/*
 * test_spatial_grid.c
 *
 *  Created on: Dec 24, 2019
 *      Author: diegomtassis
 */

#include <genesis.h>

#include "../inc/fwk/assert.h"
#include "../inc/fwk/physics.h"
#include "../inc/fwk/printer.h"
#include "../inc/fwk/spatial_grid.h"

static void printSpatialGridLayout(SpatialGrid* grid);
static void printSpatialGridState(SpatialGrid* grid);
static void printBoxBounds(const Box_s16* box);

static void testForBox(const Box_s16* object, u8 columns, u8 rows, bool expected[columns][rows]);

void testSpatialGrid() {

	KLog("testing spatial grid");

	VDP_setTextPalette(PAL2);

	u8 rows = 2;
	u8 columns = 3;

	Box_s16 box;

	defineBox(&box, 50, 50, 24, 16);
	updateBoxMax(&box);

	bool test0[2][3] = { { 1, 0, 0 }, { 0, 0, 0 } };
	testForBox(&box, rows, columns, test0);

	defineBox(&box, 1, 50, 310, 10);
	updateBoxMax(&box);

	bool test1[2][3] = { { 1, 1, 1 }, { 0, 0, 0 } };
	testForBox(&box, rows, columns, test1);
}

static void testForBox(const Box_s16* object, u8 rows, u8 columns, bool expected[rows][columns]) {

	turnPrinterOn();

	println("Test SpatialGrid for Box:");
	printBoxBounds(object);
	println("");
	printerWait(3000);

	// create the grid
	SpatialGrid spatial_grid;
	spatialGridInit(&spatial_grid, rows, columns);

	assert(spatial_grid.dimension.y == rows, "wrong size");
	assert(spatial_grid.dimension.x == columns, "wrong size");
	assert(spatial_grid.cells != 0, "memory for lists not allocated");
	println("Initialized spatial grid");
	printSpatialGridLayout(&spatial_grid);
	println("");
	printerWait(1500);

	// index the object
	spatialGridIndex(&spatial_grid, object);

	for (int row = 0; row < 3; row++) {
		for (int column = 0; column < 3; column++) {
			assert(expected[row][column] == spatial_grid.cells[row][column].e.count, "wrong count for cell");
		}
	}

	println("AABBs successfully indexed");
	printSpatialGridState(&spatial_grid);
	println("");
	printerWait(1500);

	// release the grid
	spatialGridRelease(&spatial_grid);
	assert(spatial_grid.dimension.y == 0, "wrong size");
	assert(spatial_grid.dimension.x == 0, "wrong size");
	assert(!spatial_grid.cells, "memory for lists not released");
	println("Released spatial grid");

	printerWait(5000);
	turnPrinterOff();
}

static void printSpatialGridLayout(SpatialGrid* grid) {

	char value[5];

	u8 rows = grid->dimension.y;
	u8 columns = grid->dimension.x;

	println("SpatialGrid layout:");

	print("rows=");
	sprintf(value, "%01u", rows);
	print(value);
	print(", columns=");
	sprintf(value, "%01u", columns);
	println(value);

	if (grid->cells) {

		Box_s16* box;
		for (int row = 0; row < rows; row++) {
			for (int column = 0; column < columns; column++) {

				box = &grid->cells[row][column].aabb;

				print("Cell [");
				sprintf(value, "%01u", row);
				print(value);
				print(",");
				sprintf(value, "%01u", column);
				print(value);
				print("]: ");
				printBoxBounds(box);
			}
		}
	} else {
		println(", no cells");
	}
}

static void printSpatialGridState(SpatialGrid* grid) {

	char value[5];

	u8 rows = grid->dimension.y;
	u8 columns = grid->dimension.x;

	print("SpatialGrid state:");
	if (grid->cells) {
		println("");
		for (int row = 0; row < rows; row++) {
			for (int column = 0; column < columns; column++) {
				print("Cell [");
				sprintf(value, "%01u", row);
				print(value);
				print(",");
				sprintf(value, "%01u", column);
				print(value);
				print("]: count = ");
				sprintf(value, "%02u", grid->cells[row][column].e.count);
				println(value);
			}
		}
	} else {
		println(" no cells");
	}
}

static void printBoxBounds(const Box_s16* box) {

	char value[5];

	print("[");
	sprintf(value, "%03d", box->min.x);
	print(value);
	print("-");
	sprintf(value, "%03d", box->max.x);
	print(value);
	print(", ");
	sprintf(value, "%03d", box->min.y);
	print(value);
	print("-");
	sprintf(value, "%03d", box->max.y);
	print(value);
	println("]");
}
