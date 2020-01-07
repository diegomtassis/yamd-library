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

void testSpatialGrid() {

	KLog("testing spatial grid");

	VDP_setTextPalette(PAL2);

	turnPrinterOn();

	println("Test SpatialGrid");
	println("");
	printerWait(3000);

	// create the grid
	SpatialGrid spatial_grid;
	u8 dim_x = 2;
	u8 dim_y = 2;
	spatialGridInit(&spatial_grid, dim_x, dim_y);

	assert(spatial_grid.dimension.x == dim_x, "wrong size");
	assert(spatial_grid.dimension.y == dim_y, "wrong size");
	assert(spatial_grid.cells != 0, "memory for lists not allocated");
	println("Initialized spatial grid");
	printSpatialGridLayout(&spatial_grid);
	println("");
	printSpatialGridState(&spatial_grid);
	println("");
	printerWait(1500);

	// create some objects
	u8 num_objects = 3;
	Box_s16 objects[num_objects];

	// put the objects somewhere in the screen
	// TODO do it randomly
	objects[0].min.x = 50;
	objects[0].min.y = 50;
	objects[0].h = 24;
	objects[0].w = 16;
	updateBoxMax(&objects[0]); // to be in [0][0]
	objects[1].min.x = 200;
	objects[1].min.y = 150;
	objects[1].h = 24;
	objects[1].w = 16;
	updateBoxMax(&objects[1]); // to be in [0][0]
	objects[2].min.x = 150;
	objects[2].min.y = 105;
	objects[2].h = 20;
	objects[2].w = 20;
	updateBoxMax(&objects[2]); // to be in all the cells

	println("Created AABBs");
	println("");
	printerWait(1500);

	// index the objects
	for (int idx = 0; idx < num_objects; idx++) {
		spatialGridIndex(&spatial_grid, &objects[idx]);
	}
	assert(2 == spatial_grid.cells[0][0].e.count, "wrong count for cell [0][0]");
	assert(1 == spatial_grid.cells[0][1].e.count, "wrong count for cell [0][1]");
	assert(1 == spatial_grid.cells[1][0].e.count, "wrong count for cell [1][0]");
	assert(2 == spatial_grid.cells[1][1].e.count, "wrong count for cell [1][1]");
	println("AABBs successfully indexed");
	printSpatialGridState(&spatial_grid);
	println("");
	printerWait(1500);

	// release the grid
	spatialGridRelease(&spatial_grid);
	assert(spatial_grid.dimension.x == 0, "wrong size");
	assert(spatial_grid.dimension.y == 0, "wrong size");
	assert(!spatial_grid.cells, "memory for lists not released");
	println("Released spatial grid");
	printSpatialGridState(&spatial_grid);
	println("");

	printerWait(5000);
	turnPrinterOff();
}

static void printSpatialGridLayout(SpatialGrid* grid) {

	char value[5];

	u8 dim_x = grid->dimension.x;
	u8 dim_y = grid->dimension.y;

	println("SpatialGrid layout:");

	print("dim x=");
	sprintf(value, "%01u", dim_x);
	print(value);
	print(", dim y=");
	sprintf(value, "%01u", dim_y);
	println(value);

	if (grid->cells) {

		Box_s16* box;
		for (int x = 0; x < dim_x; x++) {
			for (int y = 0; y < dim_y; y++) {

				box = &grid->cells[x][y].aabb;

				print("Cell [");
				sprintf(value, "%01u", x);
				print(value);
				print(",");
				sprintf(value, "%01u", y);
				print(value);
				print("]: [");
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
		}
	} else {
		println(", no cells");
	}
}

static void printSpatialGridState(SpatialGrid* grid) {

	char value[5];

	u8 dim_x = grid->dimension.x;
	u8 dim_y = grid->dimension.y;

	print("SpatialGrid state:");
	if (grid->cells) {
		println("");
		for (int x = 0; x < dim_x; x++) {
			for (int y = 0; y < dim_y; y++) {
				print("Cell [");
				sprintf(value, "%01u", x);
				print(value);
				print(",");
				sprintf(value, "%01u", y);
				print(value);
				print("]: count = ");
				sprintf(value, "%02u", grid->cells[x][y].e.count);
				println(value);
			}
		}
	} else {
		println(" no cells");
	}
}
