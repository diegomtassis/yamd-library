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

	SpatialGrid spatial_grid;

	println("Test SpatialGrid");
	println("");
	printerWait(3000);

	spatialGridInit(&spatial_grid, 2, 2);

	/*
	assert(spatial_grid.dimension.x == 2, "wrong size");
	assert(spatial_grid.dimension.y == 2, "wrong size");
	assert(spatial_grid.cells != 0, "memory for lists not allocated");
	println("Initialized spatial grid");
	printSpatialGridLayout(&spatial_grid);
	println("");
//	printSpatialGridState(&spatial_grid);
	println("");
	printerWait(1500);

	u8 num_objects = 2;
	Box_s16 objects[num_objects];

	// initialize the objects boxes
	for (int idx = 0; idx < num_objects; idx++) {
		objects[idx].h = 24;
		objects[idx].w = 16;
	}
	println("Created AABBs");
	println("");
	printerWait(1500);

	// put the objects somewhere in the screen
	// TODO do it randomly
	objects[0].min.x = 50;
	objects[0].min.y = 50;
	updateBoxMax(&objects[0]);
	objects[1].min.x = 200;
	objects[1].min.y = 150;
	updateBoxMax(&objects[1]);

	// index the objects
	for (int idx = 0; idx < num_objects; idx++) {
		spatialGridIndex(&spatial_grid, objects[idx]);
	}
	println("AABBs successfully indexed");
//	printSpatialGridState(&spatial_grid);
	println("");
	printSpatialGridLayout(&spatial_grid);
	println("");
	printerWait(1500);

	spatialGridRelease(&spatial_grid);
	assert(spatial_grid.dimension.x == 0, "wrong size");
	assert(spatial_grid.dimension.y == 0, "wrong size");
	assert(!spatial_grid.cells, "memory for lists not released");
	println("Released spatial grid");
//	printSpatialGridState(&spatial_grid);
	println("");

*/

	printerWait(5000);
	turnPrinterOff();
}

static void printSpatialGridLayout(SpatialGrid* grid) {

	char value[5];

	u8 dim_x = grid->dimension.x;
	u8 dim_y = grid->dimension.y;

	println("SpatialGrid layout: ");

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

				KLog_S4_("Cell  [", box->min.x, "-", box->max.x, ", ", box->min.y, "-", box->max.y, "]");
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

	println("SpatialGrid state: ");
	if (grid->cells) {
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
		println(", no cells");
	}
}
