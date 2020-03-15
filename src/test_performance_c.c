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

void testPerformanceC() {

	VDP_setTextPalette(PAL2);

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
