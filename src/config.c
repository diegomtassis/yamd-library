/*
 * config.c
 *
 *  Created on: May 5, 2019
 *      Author: diegomtassis
 */

#include "../inc/config.h"
#include "../inc/elements.h"

#include <genesis.h>

#include "../inc/fwk/assert.h"
#include "../inc/fwk/commons.h"

static const char *TEXT_YAMDL = "Yet another MegaDrive library";
static const char *TEXT_TEST_SUITE = "YaMDl test suite";
static const char *TEXT_DATA_STRUCTURES = "Data structures";
static const char *TEXT_PHYSICS = "2D physics";
static const char *TEXT_SPATIAL_GRID = "Spatial grid";
static const char *TEXT_PRINTER = "Printer";

static void setUpDefaults();

static void initConfigScreen();
static void clearConfigScreen();

static void displayConfig(Config config, V2u16 pos);
static void displayOption(const char *option, const char *value, u8 highlighted, u16 x, u16 y);

static void changeTest(Config config[static 1]);

static void joyEvent(u16 joy, u16 changed, u16 state);

volatile enum option {
    OPTION_DATA_STRUCTURES, //
    OPTION_PHYSICS,         //
    OPTION_SPATIAL_GRID,    //
    OPTION_PRINTER,         //
} current_option;

static Config *current_config;

volatile bool start = FALSE;
volatile bool refresh = TRUE;

const V2u16 pos_init = {.x = 2, .y = 2};

void initConfig() {

    // whatever is the current config, it is trash, no need to free
    current_config = 0;
}

const Config *setUpTest() {

    setUpDefaults();

    u8 prev_priority = VDP_getTextPriority();

    if (!current_config) {
        current_config = MEM_calloc(sizeof(*current_config));
        current_config->test = DATA_STRUCTURES;
    }

    initConfigScreen();

    start = FALSE;
    refresh = TRUE;

    JOY_setEventHandler(joyEvent);

    do {
        displayConfig(*current_config, pos_init);
		SYS_doVBlankProcess();
    } while (!start);

    JOY_setEventHandler(0);

    setRandomSeed(getTick());

    clearConfigScreen();
    VDP_setTextPriority(prev_priority);

    return current_config;
}

static void setUpDefaults() {}

static void initConfigScreen() {

    PAL_setPalette(PAL1, palette_grey, DMA);
    VDP_setTextPalette(PAL1);
    VDP_setTextPriority(0);

    VDP_setHilightShadow(TRUE);
}

static void clearConfigScreen() {

    VDP_clearTextAreaBG(VDP_BG_A, 0, 5, 32, 25); // don't clear the HUD
    VDP_setHilightShadow(FALSE);
}

static void displayConfig(Config config, V2u16 pos) {

    if (refresh) {

        VDP_drawText(TEXT_YAMDL, pos.x, pos.y);

        pos.y += 4;
        VDP_drawText(TEXT_TEST_SUITE, pos.x, pos.y);

        pos.y += 4;
        displayOption(TEXT_DATA_STRUCTURES, 0, current_option == OPTION_DATA_STRUCTURES, pos.x, pos.y);
        pos.y += 2;
        displayOption(TEXT_PHYSICS, 0, current_option == OPTION_PHYSICS, pos.x, pos.y);
        pos.y += 2;
        displayOption(TEXT_SPATIAL_GRID, 0, current_option == OPTION_SPATIAL_GRID, pos.x, pos.y);
        pos.y += 2;
        displayOption(TEXT_PRINTER, 0, current_option == OPTION_PRINTER, pos.x, pos.y);

        refresh = FALSE;
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

static void changeTest(Config config[static 1]) {

    switch (current_option) {
    case OPTION_DATA_STRUCTURES:
        config->test = DATA_STRUCTURES;
        break;

    case OPTION_PHYSICS:
        config->test = PHYSICS;
        break;

    case OPTION_SPATIAL_GRID:
        config->test = SPATIAL_GRID;
        break;

    case OPTION_PRINTER:
        config->test = PRINTER;
        break;

    default:
        yamdl_assert(FALSE, "Invalid test ");
        break;
    }
}

static void joyEvent(u16 joy, u16 changed, u16 state) {

    if (BUTTON_DOWN & changed & ~state) {

        if (current_option == OPTION_PRINTER) {
            current_option = OPTION_DATA_STRUCTURES;
        } else {
            current_option++;
        }
        changeTest(current_config);
        refresh = TRUE;
    }

    if (BUTTON_UP & changed & ~state) {

        if (current_option == OPTION_DATA_STRUCTURES) {
            current_option = OPTION_PRINTER;
        } else {
            current_option--;
        }
        changeTest(current_config);
        refresh = TRUE;
    }

    if (BUTTON_START & changed & ~state) {

        start = TRUE;
    }
}
