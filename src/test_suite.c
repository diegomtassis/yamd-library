/*
 * testsuite.c
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
	case LISTS:
		testLists();
		break;

	case PHYSICS:
		testPhysics();
		break;

	case SPATIAL_GRID:
		testSpatialGrid();
		break;

	default:
		assert(FALSE, "Invalid test ");
		break;
	}
}
