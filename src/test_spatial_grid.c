/*
 * test_spatial_grid.c
 *
 *  Created on: Dec 24, 2019
 *      Author: diegomtassis
 */

#include <genesis.h>

#include "../inc/fwk/array_fixed_list.h"
#include "../inc/fwk/assert.h"
#include "../inc/fwk/commons.h"
#include "../inc/fwk/doubly_linked_list.h"
#include "../inc/fwk/physics.h"
#include "../inc/fwk/printer.h"
#include "../inc/fwk/spatial_grid.h"

static void testPerformance();

void testSpatialGrid() {

	KLog("testing spatial grid");

	VDP_setTextPalette(PAL2);

	// test performance
	testPerformance();
}

static void testPerformance() {

	u8 num_boxes = 50;

	u8 rows = 1;
	u8 columns = 1;

	turnPrinterOn();

	println("Performance test");
	println("");

	char value[10];
	print("Boxes: ");
	sprintf(value, "%02u", num_boxes);
	println(value);
	println("");

	u32 spatial_grid_collisions_time = 0;
	u32 grid_overlaps = 0;

	Box_s16 boxes[num_boxes];
	Box_s16* box;

	V2u16 screen_max = { .x = VDP_getScreenWidth() - 1, .y = VDP_getScreenHeight() - 1 };

	// prepare boxes
	for (u8 idx = 0; idx < num_boxes; idx++) {
		box = &boxes[idx];
		box->min.x = randomInRangeU16(0, screen_max.x);
		box->min.y = randomInRangeU16(0, screen_max.y);
		box->w = randomInRangeU16(0, 32);
		box->h = randomInRangeU16(0, 32);
		updateBoxMax(box);
	}

	// spatial grid
	SpatialGrid spatial_grid;
	spatialGridInit(&spatial_grid, rows, columns, num_boxes);

	// index the boxes
	for (u16 idx = 0; idx < num_boxes; idx++) {
		spatialGridIndex(&spatial_grid, &boxes[idx]);
	}

	// collisions
	ArrayFixedList* list = &spatial_grid.cells[0][0].e;



	//// BEGIN SCENARIO

	// u8 size = num_boxes; // elapsed time: 30
	u8 size = list->size;  // elapsed time: 330 approx.

	assert(num_boxes == size, "wrong size");

	startTimer(3);

	for (u8 outer_idx = 0; outer_idx < size; outer_idx++) {
		for (u8 inner_idx = outer_idx + 1; inner_idx < size; inner_idx++) {
			grid_overlaps++;
		}
	}

	spatial_grid_collisions_time += getTimer(3, FALSE);


	//// END SCENARIO



	// release the grid
	spatialGridRelease(&spatial_grid);

	println("Time spent");
	println("Spatial grid collisions time: ");
	sprintf(value, "%010lu", spatial_grid_collisions_time);
	println(value);
	println("Grid collisions overlaps: ");
	sprintf(value, "%010lu", grid_overlaps);
	println(value);
	println("");

	printerWait(5000);
	turnPrinterOff();
}
