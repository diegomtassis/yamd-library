/*
 * testsuite.h
 *
 *  Created on: Dec 24, 2019
 *      Author: diegomtassis
 */

#ifndef INC_TEST_SUITE_H_
#define INC_TEST_SUITE_H_

#include "elements.h"

void runTest(const Config* config);

void testDataStructures();
void testPhysics();
void testSpatialGrid();
void testPrinter();
void testPerformanceC();

#endif /* INC_TEST_SUITE_H_ */
