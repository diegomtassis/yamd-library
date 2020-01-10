/*
 * test_spatial_grid.c
 *
 *  Created on: Dec 24, 2019
 *      Author: diegomtassis
 */

#include <genesis.h>

#include "../inc/fwk/assert.h"
#include "../inc/fwk/commons.h"
#include "../inc/fwk/physics.h"
#include "../inc/fwk/printer.h"
#include "../inc/fwk/spatial_grid.h"

static void printSpatialGridLayout(SpatialGrid* grid);
static void printSpatialGridState(SpatialGrid* grid);
static void printBoxBounds(const Box_s16* box);

static void testForBox(const Box_s16* object, u8 columns, u8 rows, bool expected[columns][rows], const char* scenario);
static void testPerformance();

void testSpatialGrid() {

	KLog("testing spatial grid");

	VDP_setTextPalette(PAL2);

	/*

	 u8 rows = 2;
	 u8 columns = 3;

	 Box_s16 box;

	 // box in first cell only
	 defineBox(&box, 1, 1, 10, 10);
	 updateBoxMax(&box);
	 bool test1[2][3] = { { 1, 0, 0 }, { 0, 0, 0 } };
	 testForBox(&box, rows, columns, test1, "box in first cell only");

	 // box spans the whole first row
	 defineBox(&box, 1, 1, 310, 10);
	 updateBoxMax(&box);
	 bool test2[2][3] = { { 1, 1, 1 }, { 0, 0, 0 } };
	 testForBox(&box, rows, columns, test2, "box spans the whole first row");

	 // box spans the whole first column
	 defineBox(&box, 1, 1, 10, 210);
	 updateBoxMax(&box);
	 bool test3[2][3] = { { 1, 0, 0 }, { 1, 0, 0 } };
	 testForBox(&box, rows, columns, test3, "box spans the whole first column");

	 // box spans all the cells
	 defineBox(&box, 1, 1, 315, 220);
	 updateBoxMax(&box);
	 bool test4[2][3] = { { 1, 1, 1 }, { 1, 1, 1 } };
	 testForBox(&box, rows, columns, test4, "box spans all the cells");

	 // box in the last cell
	 defineBox(&box, 310, 210, 5, 5);
	 updateBoxMax(&box);
	 bool test5[2][3] = { { 0, 0, 0 }, { 0, 0, 1 } };
	 testForBox(&box, rows, columns, test5, "box in the last cell");

	 */

	// test performance
	testPerformance();
}

static void testForBox(const Box_s16* object, u8 rows, u8 columns, bool expected[rows][columns], const char* scenario) {

	turnPrinterOn();

	println("Test SpatialGrid for Box:");
	println(scenario);
	printBoxBounds(object);
	println("");
	printerWait(3000);

	// create the grid
	SpatialGrid spatial_grid;
	spatialGridInit(&spatial_grid, rows, columns);

	assert(spatial_grid.rows == rows, "wrong size");
	assert(spatial_grid.columns == columns, "wrong size");
	assert(spatial_grid.cells != 0, "memory for lists not allocated");
	println("Initialized spatial grid");
	printSpatialGridLayout(&spatial_grid);
	println("");
	printerWait(1500);

	// index the object
	spatialGridIndex(&spatial_grid, object);

	for (int row = 0; row < rows; row++) {
		for (int column = 0; column < columns; column++) {
			assert(expected[row][column] == spatial_grid.cells[row][column].e.count, "wrong count for cell");
		}
	}

	println("AABBs successfully indexed");
	printSpatialGridState(&spatial_grid);
	println("");
	printerWait(1500);

	// release the grid
	spatialGridRelease(&spatial_grid);
	assert(spatial_grid.rows == 0, "wrong size");
	assert(spatial_grid.columns == 0, "wrong size");
	assert(!spatial_grid.cells, "memory for lists not released");
	println("Released spatial grid");

	printerWait(5000);
	turnPrinterOff();
}

static void testPerformance() {

	u8 iterations = 25;
	u16 num_boxes = 100;

	turnPrinterOn();

	println("Performance test");
	println("brute force vs spatial grid");
	println("");

	char value[10];
	print("Boxes: ");
	sprintf(value, "%02u", num_boxes);
	println(value);
	print("Iterations: ");
	sprintf(value, "%02u", iterations);
	println(value);
	println("");

	u32 brute_force_time = 0;
	u32 spatial_grid_time = 0;

	Box_s16 boxes[num_boxes];
	Box_s16* box;

	V2u16 screen_max = { .x = VDP_getScreenWidth() - 1, .y = VDP_getScreenHeight() - 1 };

	for (u8 i = 0; i < iterations; i++) {

		// prepare boxes
		for (u16 idx = 0; idx < num_boxes; idx++) {
			box = &boxes[idx];
			box->min.x = randomInRangeU16(0, screen_max.x);
			box->min.y = randomInRangeU16(0, screen_max.y);
			box->w = randomInRangeU16(0, 32);
			box->h = randomInRangeU16(0, 32);
			updateBoxMax(box);
		}

		// brute force
		startTimer(1);
		for (u16 left_box = 0; left_box < num_boxes; left_box++) {
			for (u16 right_box = left_box + 1; right_box < num_boxes; right_box++) {
				overlap(&boxes[left_box], &boxes[right_box]);
			}
		}

		brute_force_time += getTimer(1, FALSE);

		// spatial grid
		startTimer(1);

		u8 rows = 3;
		u8 columns = 3;
		SpatialGrid spatial_grid;
		spatialGridInit(&spatial_grid, rows, columns);

		// index the boxes
		for (u16 idx = 0; idx < num_boxes; idx++) {
			spatialGridIndex(&spatial_grid, &boxes[idx]);
		}

		// collisions
		for (int row = 0; row < rows; row++) {
			for (int column = 0; column < columns; column++) {
				DoublyLinkedListNode* outer_node = spatial_grid.cells[row][column].e.first;
				while (outer_node) {
					DoublyLinkedListNode* inner_node = outer_node->next;
					while (inner_node) {
						overlap(&outer_node->e, &inner_node->e);
						inner_node = inner_node->next;
					}
					outer_node = outer_node->next;
				}
			}
		}

		spatial_grid_time += getTimer(1, FALSE);

		// release the grid
		spatialGridRelease(&spatial_grid);

		// release boxes
	}

	println("Time spent");
	print("Brute force: ");
	sprintf(value, "%010lu", brute_force_time);
	println(value);
	print("Spatial grid: ");
	sprintf(value, "%010lu", spatial_grid_time);
	println(value);

	print("Ratio: ");
	sprintf(value, "%010lu", brute_force_time / spatial_grid_time);
	println(value);

	printerWait(5000);
	turnPrinterOff();
}

static void printSpatialGridLayout(SpatialGrid* grid) {

	char value[5];

	u8 rows = grid->rows;
	u8 columns = grid->columns;

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

	print("SpatialGrid state:");
	if (grid->cells) {
		println("");
		for (int row = 0; row < grid->rows; row++) {
			for (int column = 0; column < grid->columns; column++) {
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
