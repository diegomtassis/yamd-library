/*
 * config.c
 *
 *  Created on: May 5, 2019
 *      Author: diegomtassis
 */

#include "../inc/config.h"

#include <genesis.h>

#include "../inc/fwk/assert.h"
#include "../inc/fwk/commons.h"

static const char* TEXT_YAMDL = "Yet Another MegaDrive Library";
static const char* TEXT_SELECTION = "Test Suite";
static const char* TEXT_UTILITY = "Utility";
static const char* TEXT_PHYSICS = "2D Physics";
static const char* TEXT_LISTS = "Lists";
static const char* TEXT_SPATIAL_GRID = "Spatial grid";
static const char* PRESS_RUN_TESTS = "Run test scenarios";

static const u16 BUTTON_ABC = BUTTON_A | BUTTON_B | BUTTON_C;

static void setUpDefaults();

static void initConfigScreen();
static void clearConfigScreen();

static void displayConfig(Config config, V2u16 pos);
static void displayOption(const char *option, const char *value, u8 highlighted, u16 x, u16 y);

static const char* printableTest(Config config);

static void changeMode(Config config[static 1]);

static void joyEvent(u16 joy, u16 changed, u16 state);

volatile enum option {
	OPTION_TEST, //
	OPTION_START,
} current_option;

static Config* current_config;

volatile bool start = FALSE;
volatile bool refresh = TRUE;

const V2u16 pos_init = { .x = 2, .y = 2 };

void initConfig() {

	// whatever is the current config is trash, no need to free
	current_config = 0;
}

const Config* setUpTest() {

	setUpDefaults();

	u8 prev_priority = VDP_getTextPriority();

	if (!current_config) {
		current_config = MEM_calloc(sizeof(*current_config));
		current_config->test = COLLISIONS;
	}

	current_option = OPTION_TEST;

	initConfigScreen();

	start = FALSE;
	refresh = TRUE;

	JOY_setEventHandler(joyEvent);

	do {
		displayConfig(*current_config, pos_init);
		VDP_waitVSync();
	} while (!start);

	setRandomSeed(getTick());

	clearConfigScreen();
	VDP_setTextPriority(prev_priority);

	return current_config;
}

static void setUpDefaults() {

}

static void initConfigScreen() {

	VDP_setPalette(PAL1, palette_grey);
	VDP_setTextPalette(PAL1);
	VDP_setTextPriority(0);

	VDP_setHilightShadow(TRUE);
}

static void clearConfigScreen() {

	VDP_clearTextAreaBG(PLAN_A, 0, 5, 32, 25); // don't clear the HUD
	VDP_setHilightShadow(FALSE);
}

static void displayConfig(Config config, V2u16 pos) {

	if (refresh) {

		VDP_drawText(TEXT_YAMDL, pos.x, pos.y);

		pos.y += 4;
		VDP_drawText(TEXT_SELECTION, pos.x, pos.y);

		pos.y += 4;
		displayOption(TEXT_UTILITY, printableTest(config), current_option == OPTION_TEST, pos.x, pos.y);

		pos.y += 4;
		displayOption(PRESS_RUN_TESTS, 0, current_option == OPTION_START, pos.x, pos.y);

		refresh = FALSE;
	}
}

static const char* printableTest(Config config) {

	switch (config.test) {
	case COLLISIONS:
		return TEXT_PHYSICS;
	case LISTS:
		return TEXT_LISTS;
	case SPATIAL_GRID:
		return TEXT_SPATIAL_GRID;
	default:
		assert(FALSE, "Invalid test");
		return 0;
	}
}

static void changeMode(Config config[static 1]) {

	if (config->test == SPATIAL_GRID) {
		config->test = COLLISIONS;
	} else {
		config->test++;
	}
}

static void displayOption(const char *option, const char *value, u8 highlighted, u16 x, u16 y) {

	VDP_clearTextLine(y);
	VDP_setTextPriority(highlighted);
	VDP_drawText(option, x, y);
	if (value) {
		VDP_drawText(value, x + 15, y);
	}
	VDP_setTextPriority(0);
}

static void joyEvent(u16 joy, u16 changed, u16 state) {

	if (BUTTON_DOWN & changed & ~state) {

		if (current_option == OPTION_START) {
			current_option = OPTION_TEST;
		} else {
			current_option++;
		}
		refresh = TRUE;
	}

	if (BUTTON_UP & changed & ~state) {
		if (current_option == OPTION_TEST) {
			current_option = OPTION_START;
		} else {
			current_option--;
		}
		refresh = TRUE;
	}

	if (BUTTON_ABC & changed & ~state) {

		if (current_option == OPTION_TEST) {
			changeMode(current_config);
			refresh = TRUE;

		}
	}

	if (BUTTON_START & changed & ~state) {
		if (current_option == OPTION_START) {
			start = TRUE;
		}
	}
}
