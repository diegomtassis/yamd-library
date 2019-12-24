/*
 * testsuite.c
 *
 *  Created on: Dec 24, 2019
 *      Author: diegomtassis
 */

#include "../inc/testsuite.h"

#include <tools.h>

#include "../inc/fwk/assert.h"

void runTest(const Config* config) {

	KLog_U1("Test ", config->mode);
	assert(config->mode == 0, "Invalid mode");
}
