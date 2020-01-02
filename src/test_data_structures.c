/*
 * test_data_structures.c
 *
 *  Created on: Dec 24, 2019
 *      Author: diegomtassis
 */

#include <genesis.h>

#include "../inc/fwk/lists.h"
#include "../inc/fwk/printer.h"

static void testFixedList();
static void printFixedListState(FixedList* fixedList);

void testDataStructures() {

	KLog("testing data structures");

	testFixedList();
}

static void testFixedList() {

	VDP_setTextPalette(PAL2);

	turnPrinterOn();


	println("Test FixedList");
	println("");
	printerWait(3000);

	FixedList fixedList;

	fixedlist_init(&fixedList, 10);
	println("Created fixed list");
	printFixedListState(&fixedList);
	printerWait(500);

	char* foo = "foo";
	fixedlist_add(&fixedList, foo);
	println("Added \"foo\"");
	printFixedListState(&fixedList);
	println("");
	printerWait(1500);

	char* bar = "bar";
	fixedlist_add(&fixedList, bar);
	println("Added \"bar\"");
	printFixedListState(&fixedList);
	println("");
	printerWait(1500);

	s16 found = fixedlist_find(&fixedList, foo);
	print("Looking for \"foo\". Found in pos: ");
	char value[5];
	sprintf(value, "%d", found);
	println(value);
	printFixedListState(&fixedList);
	println("");
	printerWait(1500);

	found = fixedlist_find_empty(&fixedList);
	print("Looking for first empty element. Found position: ");
	sprintf(value, "%d", found);
	println(value);
	printFixedListState(&fixedList);
	println("");
	printerWait(1500);

	fixedlist_remove_at(&fixedList, 0);
	println("Removed element at position 0");
	printFixedListState(&fixedList);
	println("");
	printerWait(1500);

	char* foobar = "foobar";
	fixedlist_add(&fixedList, foobar);
	println("Added \"foobar\"");
	printFixedListState(&fixedList);
	println("");
	printerWait(1500);

	fixedlist_release(&fixedList);
	println("Released list");
	printFixedListState(&fixedList);

	printerWait(5000);

	turnPrinterOff();
}

static void printFixedListState(FixedList* fixedList) {

	char value[2];

	println("FixedList state: ");
	print("size: ");
	sprintf(value, "%02u", fixedList->size);
	print(value);

	print(", count: ");
	sprintf(value, "%02u", fixedList->count);
	print(value);

	print(", elements:");
	if (fixedList->e) {
		print("[");
		for (u8 idx = 0; idx < fixedList->size; idx++) {
			if (idx > 0) {
				print(", ");
			}
			if (fixedList->e[idx]) {
				print("\"");
				print(fixedList->e[idx]);
				print("\"");
			} else {
				print("0");
			}
		}
		println("]");
	} else {
		println("0");
	}

	println("");
}
