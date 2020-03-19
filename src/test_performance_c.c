/*
 * test_performance_c.c
 *
 *  Created on: Dec 24, 2019
 *      Author: diegomtassis
 */

#include <genesis.h>

#include "../inc/fwk/assert.h"
#include "../inc/fwk/commons.h"
#include "../inc/fwk/printer.h"

static void testPerformanceRolledVsUnrolledLoops();
static void testMemoryAccessUnrolled();

void testPerformanceC() {

	VDP_setTextPalette(PAL2);

	testMemoryAccessUnrolled();
}

static void testPerformanceRolledVsUnrolledLoops() {

	u16 dim_size = 25;
	u16 unrolled = dim_size * dim_size * dim_size * dim_size;

	u16* elements = MEM_calloc((sizeof(u16)) * unrolled);

	turnPrinterOn();

	println("C Performance test");
	println("");

	char value[10];
	print("Dimension: ");
	sprintf(value, "%02u", dim_size);
	println(value);
	println("");

	u32 rolled_time = 0;
	u32 unrolled_time = 0;

	// rolled
	startTimer(1);
	u16 idx = 0;
	for (u16 dim_1 = 0; dim_1 < dim_size; dim_1++) {
		for (u16 dim_2 = 0; dim_2 < dim_size; dim_2++) {
			for (u16 dim_3 = 0; dim_3 < dim_size; dim_3++) {
				for (u16 dim_4 = 0; dim_4 < dim_size; dim_4++) {
					elements[idx++] = dim_1 + dim_2 + dim_3 + dim_4;
				}
			}
		}
	}
	rolled_time += getTimer(1, FALSE);

	// unrolled
	startTimer(2);
	for (u16 idx = 0; idx < unrolled; idx++) {
		elements[idx] = idx + dim_size + idx + dim_size;
	}
	unrolled_time += getTimer(2, FALSE);

	// release the list
	MEM_free(elements);

	println("Time spent");
	println("Rolled: ");
	sprintf(value, "%010lu", rolled_time);
	println(value);
	println("");
	println("Unrolled: ");
	sprintf(value, "%010lu", unrolled_time);
	println(value);
	println("");

	printerWait(5000);
	turnPrinterOff();
}

static void testMemoryAccessUnrolled() {

	u16 rows = 2;
	u16 columns = 3;

	turnPrinterOn();

	println("C Matrix rolled/unrolled test");
	println("");

	char value[10];
	/*
	 *
	 print("Dimension: ");
	 sprintf(value, "%02u", dim_size);
	 println(value);
	 println("");
	 */

	u16** matrix = MEM_calloc((sizeof(u16*)) * rows);

	u16 offset = 0;
	for (u16 row = 0; row < rows; row++) {
		matrix[row] = MEM_calloc((sizeof(u16)) * columns);
		for (u16 column = 0; column < columns; column++) {
			matrix[row][column] = offset++;
		}
	}

	char error[25];

	offset = 0;
	u16 current = 0;

	// test 1
	u16* ptr;
	for (ptr = &matrix[0][0]; ptr <= &matrix[rows][columns]; ptr++) {

		u16 expected = offset++;
		current = *ptr;
		sprintf(error, "exp %02u current  %02u", expected, current);
		assert(expected == current, error);
	}

	// test 2
	offset = 0;
	for (u16 row = 0; row < rows; row++) {
		for (u16 column = 0; column < columns; column++) {

			u16 expected = matrix[row][column];
			current = *(&matrix[0][0] + offset);
			offset += 1;
			sprintf(error, "exp %02u current  %02u", expected, current);
			assert(expected == current, error);
		}
	}

	// release matrix
	for (u16 row = 0; row < rows; row++) {
		MEM_free(matrix[row]);
	}
	MEM_free(matrix);

	println("Success");
	println("");

	printerWait(5000);
	turnPrinterOff();
}
