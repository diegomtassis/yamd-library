/*
 * printer.c
 *
 *  Created on: Apr 18, 2019
 *      Author: diegomtassis
 */

#include "../../inc/fwk/printer.h"

#include <genesis.h>

#include "../../inc/fwk/commons.h"
#include "../../res/sprite.h"

static void printChar(const char* text, u16 pos, int is_last, V2u16* offset);

static void moveForward(V2u16* offset);
static void moveToNextLine(V2u16* offset);
static void normalizeOffset(V2u16* offset);

static void cursorOn();
static void cursorOff();
static void cursorUpdate();

static u16 tilesToPx(u8);

static Sprite* cursor;

static V2u16 min_screen = { .x = 1, .y = 1 };
static V2u16 max_screen = { .x = 38, .y = 28 };

static V2u16* pos;

void printerOn() {

	max_screen.x = VDP_getScreenWidth() == 320 ? 38 : 30;
	max_screen.y = VDP_getScreenHeight() == 240 ? 28 : 26;

	pos = MEM_calloc(sizeof(*pos));
	setV2u16(pos, min_screen.x, min_screen.y);

	SPR_init(5, 16, 64);

	cursor = SPR_addSprite(&cursor_sprite, tilesToPx(pos->x), tilesToPx(pos->y),
			TILE_ATTR(VDP_getTextPalette(), TRUE, FALSE, FALSE));
	cursorOn();
}

void printerOff() {

	clearScreen();
	SPR_reset();
	SPR_update();
	MEM_free(pos);
}

void clearScreen() {

	VDP_clearPlan(VDP_getTextPlan(), TRUE);
	setV2u16(pos, min_screen.x, min_screen.y);
	cursorOn();
}

void println(const char* text) {

	print(text);
	if (pos->x != min_screen.x) {
		moveToNextLine(pos);
	}
	moveToNextLine(pos);

	cursorUpdate();
}

void print(const char* text) {

	normalizeOffset(pos);

	u16 rest = strlen(text);
	u16 current = 0;

	cursorOff();

	while (rest--) {

		printChar(text, current++, rest == 1, pos);
		waitMs(WAIT_50);
	}

	cursorUpdate();
}

static void printChar(const char* text, u16 pos, int is_last, V2u16* offset) {

	char current = text[pos];
	char str[1];
	str[0] = current;

	char prev = ' ';
	if (pos > 0) {
		prev = text[pos - 1];
	}

	char next = ' ';
	if (!is_last) {
		next = text[pos + 1];
	}

	if (current != ' ') {
		if (offset->x == max_screen.x && next != ' ') {
			if (prev != ' ') {
				VDP_drawText("-", offset->x, offset->y);
				moveForward(offset);
			} else {
				// first letter of a word in the last position, start in the next line
				moveForward(offset);
			}
		}

		VDP_drawText(str, offset->x, offset->y);
		moveForward(offset);

	} else {
		// ignore spaces in the first pos
		if (offset->x) {
			moveForward(offset);
		}
	}
}

static void normalizeOffset(V2u16* offset) {

	if (offset->x < min_screen.x) {
		offset->x = min_screen.x;
	}

	if (offset->y < min_screen.y) {
		offset->y = min_screen.y;
	}
}

static void moveForward(V2u16* offset) {

	if (offset->x == max_screen.x) {
		moveToNextLine(offset);
		moveToNextLine(offset);
	} else {
		offset->x++;
	}

	SPR_setPosition(cursor, offset->x, offset->y);
}

static void moveToNextLine(V2u16* offset) {

	offset->x = min_screen.x;
	offset->y++;

	SPR_setPosition(cursor, offset->x, offset->y);
}

static void cursorOn() {

	cursorUpdate();
}

static void cursorOff() {

	SPR_setVisibility(cursor, HIDDEN);
	SPR_update();
}

static void cursorUpdate() {

	SPR_setVisibility(cursor, VISIBLE);
	SPR_setPosition(cursor, tilesToPx(pos->x), tilesToPx(pos->y));
	SPR_update();
}

static u16 tilesToPx(u8 tiles) {
	return tiles * 8;
}
