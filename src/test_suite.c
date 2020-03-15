/*
 * test_suite.c
 *
 *  Created on: Dec 24, 2019
 *      Author: diegomtassis
 */

#include "../inc/test_suite.h"

#include <genesis.h>

#include "../inc/config.h"
#include "../inc/fwk/assert.h"

void runTest(const Config* config) {

	assert(config->test, "No test set");

	switch (config->test) {
	case DATA_STRUCTURES:
		testDataStructures();
		break;

	case PHYSICS:
		testPhysics();
		break;

	case SPATIAL_GRID:
		testSpatialGrid();
		break;

	case PRINTER:
		testPrinter();
		break;

	case PERFORMACE_C:
		testPerformanceC();
		break;

	default:
		assert(FALSE, "Invalid test ");
		break;
	}
}
