/*
 * test_data_structures.c
 *
 *  Created on: Dec 24, 2019
 *      Author: diegomtassis
 */

#include <genesis.h>

#include "../inc/fwk/array_fixed_list.h"
#include "../inc/fwk/assert.h"
#include "../inc/fwk/doubly_linked_list.h"
#include "../inc/fwk/printer.h"

static void testFixedList();
static void testDoublyLinkedList();

static void printFixedListState(ArrayFixedList* fixedList);
static void printDoublyLinkedListState(DoublyLinkedList* doublyLinkedList);

void testDataStructures() {

	KLog("testing data structures");

	VDP_setTextPalette(PAL2);

	testFixedList();
	testDoublyLinkedList();
}

static void testFixedList() {

	turnPrinterOn();

	println("Test ArrayFixedList");
	println("");
	printerWait(3000);

	ArrayFixedList arrayList;

	arrayFixedListInit(&arrayList, 5);
	yamdl_assert(arrayList.size == 5, "wrong size");
	yamdl_assert(arrayList.count == 0, "wrong count");
	yamdl_assert(arrayList.e != 0, "array not initialized");
	println("Created array fixed list");
	printFixedListState(&arrayList);
	printerWait(1500);

	char* foo = "foo";
	arrayFixedListAdd(&arrayList, foo);
	yamdl_assert(arrayList.count == 1, "wrong size");
	yamdl_assert(arrayList.e[0] == foo, "element not added");
	println("Added \"foo\"");
	printFixedListState(&arrayList);
	printerWait(1500);

	char* bar = "bar";
	arrayFixedListAdd(&arrayList, bar);
	yamdl_assert(arrayList.count == 2, "wrong size");
	yamdl_assert(arrayList.e[1] == bar, "element not added");
	println("Added \"bar\"");
	printFixedListState(&arrayList);
	printerWait(1500);

	s16 found = arrayFixedListFind(&arrayList, foo);
	yamdl_assert(found == 0, "wrong element found");
	print("Found \"foo\" in index: ");
	char value[5];
	sprintf(value, "%d", found);
	println(value);
	printFixedListState(&arrayList);
	printerWait(1500);

	found = arrayFixedListFind(&arrayList, "foobar");
	yamdl_assert(found == -1, "element found");
	println("Looking for \"foobar\". Not found");
	printFixedListState(&arrayList);
	printerWait(1500);

	found = arrayFixedListFindEmpty(&arrayList);
	yamdl_assert(2 == found, "wrong index");
	print("Looking for first empty element. Found at position: ");
	sprintf(value, "%d", found);
	println(value);
	printFixedListState(&arrayList);
	printerWait(1500);

	arrayFixedListRemoveAt(&arrayList, 0);
	yamdl_assert(arrayList.count == 1, "wrong size");
	yamdl_assert(!arrayList.e[0], "element not removed");
	println("Removed element at position 0");
	printFixedListState(&arrayList);
	printerWait(1500);

	char* foobar = "foobar";
	arrayFixedListAdd(&arrayList, foobar);
	yamdl_assert(arrayList.count == 2, "wrong size");
	yamdl_assert(arrayList.e[0] == foobar, "element not added");
	println("Added \"foobar\"");
	printFixedListState(&arrayList);
	printerWait(1500);

	arrayFixedListRelease(&arrayList);
	yamdl_assert(arrayList.size == 0, "wrong size");
	yamdl_assert(arrayList.count == 0, "wrong count");
	yamdl_assert(!arrayList.e, "array not released");
	println("Released list");
	printFixedListState(&arrayList);

	printerWait(5000);

	turnPrinterOff();
}

static void testDoublyLinkedList() {

	turnPrinterOn();

	println("Test DoublyLinkedList");
	println("");
	printerWait(3000);

	DoublyLinkedList doublyLinkedList;

	doublyLinkedListInit(&doublyLinkedList);
	yamdl_assert(doublyLinkedList.count == 0, "wrong count");
	yamdl_assert(!doublyLinkedList.first, "wrong first");
	yamdl_assert(!doublyLinkedList.last, "wrong last");
	println("Created doubly linked list");
	printDoublyLinkedListState(&doublyLinkedList);
	println("");
	printerWait(1500);

	DoublyLinkedListNode* node;
	char* foo = "foo";
	node = doublyLinkedListAdd(&doublyLinkedList, foo);
	yamdl_assert(doublyLinkedList.count == 1, "wrong count");
	yamdl_assert(doublyLinkedList.first == node, "wrong first");
	yamdl_assert(doublyLinkedList.last == node, "wrong last");
	yamdl_assert(node->e == foo, "wrong element");
	yamdl_assert(!node->prev, "wrong prev");
	yamdl_assert(!node->next, "wrong next");
	println("Added \"foo\"");
	printDoublyLinkedListState(&doublyLinkedList);
	println("");
	printerWait(1500);

	char* bar = "bar";
	node = doublyLinkedListAdd(&doublyLinkedList, bar);
	yamdl_assert(node->e == bar, "wrong element");
	yamdl_assert(node->prev && node->prev->e == foo, "wrong prev");
	yamdl_assert(!node->next, "wrong next");
	yamdl_assert(doublyLinkedList.count == 2, "wrong count");
	yamdl_assert(doublyLinkedList.last == node, "wrong last");
	yamdl_assert(doublyLinkedList.first->e == foo, "wrong first");
	println("Added \"bar\"");
	printDoublyLinkedListState(&doublyLinkedList);
	println("");
	printerWait(1500);

	DoublyLinkedListNode* found = doublyLinkedListFind(&doublyLinkedList, foo);
	yamdl_assert(found != 0, "not found");
	yamdl_assert(found->e == foo, "found wrong node");
	println("Found \"foo\"");
	printDoublyLinkedListState(&doublyLinkedList);
	println("");
	printerWait(1500);

	doublyLinkedListRemove(&doublyLinkedList, found);
	yamdl_assert(doublyLinkedList.count == 1, "wrong count");
	yamdl_assert(doublyLinkedList.first->e == bar, "wrong first");
	yamdl_assert(doublyLinkedList.last->e == bar, "wrong last");
	yamdl_assert(!doublyLinkedList.first->prev, "wrong bar prev");
	yamdl_assert(!doublyLinkedList.first->next, "wrong bar next");
	println("Removed element successfully");
	printDoublyLinkedListState(&doublyLinkedList);
	println("");
	printerWait(1500);

	char* foobar = "foobar";
	node = doublyLinkedListAdd(&doublyLinkedList, foobar);
	yamdl_assert(node->e == foobar, "wrong element");
	yamdl_assert(node->prev && node->prev->e == bar, "wrong prev");
	yamdl_assert(!node->next, "wrong next");
	yamdl_assert(doublyLinkedList.count == 2, "wrong count");
	yamdl_assert(doublyLinkedList.last == node, "wrong last");
	yamdl_assert(doublyLinkedList.first->e == bar, "wrong first");
	println("Added \"foobar\"");
	printDoublyLinkedListState(&doublyLinkedList);
	println("");
	printerWait(1500);

	doublyLinkedListRelease(&doublyLinkedList);
	yamdl_assert(doublyLinkedList.count == 0, "wrong count");
	yamdl_assert(!doublyLinkedList.first, "wrong first");
	yamdl_assert(!doublyLinkedList.last, "wrong last");
	println("Released list");
	printDoublyLinkedListState(&doublyLinkedList);

	printerWait(5000);

	turnPrinterOff();
}

static void printFixedListState(ArrayFixedList* fixedList) {

	char value[5];

	println("ArrayFixedList state: ");
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

static void printDoublyLinkedListState(DoublyLinkedList* doublyLinkedList) {

	char value[5];

	println("DoublyLinkedList state: ");
	print("count: ");
	sprintf(value, "%02u", doublyLinkedList->count);
	print(value);

	print(", first: ");
	if (doublyLinkedList->first) {
		print("\"");
		print(doublyLinkedList->first->e);
		print("\"");
	} else {
		print("0");
	}

	print(", last: ");
	if (doublyLinkedList->last) {
		print("\"");
		print(doublyLinkedList->last->e);
		print("\"");
	} else {
		print("0");
	}

	println("");
}
