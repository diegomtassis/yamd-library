/*
 * test_physics.c
 *
 *  Created on: Dec 24, 2019
 *      Author: diegomtassis
 */

#include <genesis.h>

#include "../inc/fwk/physics.h"
#include "../inc/fwk/printer.h"
#include "../res/gfx.h"
#include "../res/sprite.h"

static void runPhysicsSanbox();

static void handleInput();
static void joyEvent(u16 joy, u16 changed, u16 state);

static volatile bool exit;

static Sprite* cross_spr;
static Sprite* blue_block_spr;
static Sprite* green_block_spr;

static Object_f16 cross;
static V2s16 order;

static Object_f16 blue_block;
static Object_f16 green_block;

static const fix16 SPEED = FIX16(1);

void testPhysics() {

	KLog("testing physics");

	VDP_setTextPalette(PAL2);

	turnPrinterOn();

	println("Move the target to interact with other objects in the screen.");
	println("");
	printerWait(500);

	println("Blue objects turn red when the target overlaps them.");
	println("");
	printerWait(500);

	println("Green objects can not be gone through.");

	printerWait(3000);
	turnPrinterOff();

	runPhysicsSanbox();
}

static void runPhysicsSanbox() {

	JOY_setEventHandler(joyEvent);
	exit = FALSE;

	VDP_setPalette(0, game_palette.data);

	// initialize the cross: object and sprite
	cross.pos.x = FIX16(150);
	cross.pos.y = FIX16(100);
	cross.size.x = 16;
	cross.size.y = 16;
	cross.box.w = 16;
	cross.box.h = 16;
	updateBox(&cross);
	cross_spr = SPR_addSprite(&cross_sprite, 150, 100, TILE_ATTR(PAL0, TRUE, FALSE, FALSE));

	// initialize the blue block: object and sprite
	blue_block.pos.x = FIX16(70);
	blue_block.pos.y = FIX16(100);
	blue_block.size.x = 32;
	blue_block.size.y = 32;
	blue_block.box.w = 32;
	blue_block.box.h = 32;
	updateBox(&blue_block);
	blue_block_spr = SPR_addSprite(&blue_block_sprite, 70, 100, TILE_ATTR(PAL0, TRUE, FALSE, FALSE));

	// initialize the green block: object and sprite
	green_block.pos.x = FIX16(210);
	green_block.pos.y = FIX16(100);
	green_block.size.x = 32;
	green_block.size.y = 32;
	green_block.box.w = 32;
	green_block.box.h = 32;
	updateBox(&green_block);
	green_block_spr = SPR_addSprite(&green_block_sprite, 210, 100, TILE_ATTR(PAL0, TRUE, FALSE, FALSE));

	while (!exit) {

		// handle the movement of the cross
		handleInput();

		if (!order.x) {
			cross.mov.x = 0;
		} else if (order.x > 0) {
			cross.mov.x = SPEED;
		} else {
			cross.mov.x = -SPEED;
		}

		if (!order.y) {
			cross.mov.y = 0;
		} else if (order.y > 0) {
			cross.mov.y = SPEED;
		} else {
			cross.mov.y = -SPEED;
		}

		// handle collision with green box
		Box_s16 target_h_box = targetHBox(cross);
		if (hitRight(target_h_box, green_block.box)) {
			cross.pos.x = FIX16(adjacentXOnTheRight(target_h_box, green_block.box));
			cross.mov.x = 0;

		} else if (hitLeft(target_h_box, green_block.box)) {
			cross.pos.x = FIX16(adjacentXOnTheLeft(target_h_box, green_block.box));
			cross.mov.x = 0;

		} else {
			cross.pos.x += cross.mov.x;
		}

		Box_s16 target_v_box = targetVBox(cross);
		if (hitAbove(target_v_box, green_block.box)) {
			cross.pos.y = FIX16(adjacentYAbove(target_v_box, green_block.box));
			cross.mov.y = 0;

		} else if (hitUnder(target_v_box, green_block.box)) {

			cross.pos.y = FIX16(adjacentYUnder(target_v_box, green_block.box));
			cross.mov.y = 0;

		} else {
			cross.pos.y += cross.mov.y;
		}

		updateBox(&cross);

		SPR_setPosition(cross_spr, fix16ToInt(cross.pos.x), fix16ToInt(cross.pos.y));

		// handle overlapping with blue box
		if (overlap(cross.box, blue_block.box)) {
			SPR_setFrame(blue_block_spr, 1);
		} else {
			SPR_setFrame(blue_block_spr, 0);
		}

		SPR_update();
		VDP_waitVInt();
	}

	SPR_reset();
	SPR_update();

	JOY_setEventHandler(0);
}

static void handleInput() {

	u16 value = JOY_readJoypad(JOY_1);

	if (value & BUTTON_UP) {
		order.y = -1;
	} else if (value & BUTTON_DOWN) {
		order.y = 1;
	} else {
		order.y = 0;
	}

	if (value & BUTTON_LEFT) {
		order.x = -1;
	} else if (value & BUTTON_RIGHT) {
		order.x = 1;
	} else {
		order.x = 0;
	}
}

static void joyEvent(u16 joy, u16 changed, u16 state) {

	if (BUTTON_START & changed & ~state) {
		exit = TRUE;
	}
}
