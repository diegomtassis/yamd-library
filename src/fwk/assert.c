/*
 * assert.c
 *
 *  Created on: Dec 24, 2019
 *      Author: diegomtassis
 */

#include "../inc/fwk/assert.h"

#include <sys.h>
#include <tools.h>

void assert(bool clause, const char* message) {

	if (!clause) {
		KLog(message);
		SYS_die(message);
	}
}
