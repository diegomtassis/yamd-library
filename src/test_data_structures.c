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
	assert(arrayList.size == 5, "wrong size");
	assert(arrayList.count == 0, "wrong count");
	assert(arrayList.e != 0, "array not initialized");
	println("Created array fixed list");
	printFixedListState(&arrayList);
	printerWait(1500);

	char* foo = "foo";
	arrayFixedListAdd(&arrayList, foo);
	assert(arrayList.count == 1, "wrong size");
	assert(arrayList.e[0] == foo, "element not added");
	println("Added \"foo\"");
	printFixedListState(&arrayList);
	printerWait(1500);

	char* bar = "bar";
	arrayFixedListAdd(&arrayList, bar);
	assert(arrayList.count == 2, "wrong size");
	assert(arrayList.e[1] == bar, "element not added");
	println("Added \"bar\"");
	printFixedListState(&arrayList);
	printerWait(1500);

	s16 found = arrayFixedListFind(&arrayList, foo);
	assert(found == 0, "wrong element found");
	print("Found \"foo\" in index: ");
	char value[5];
	sprintf(value, "%d", found);
	println(value);
	printFixedListState(&arrayList);
	printerWait(1500);

	found = arrayFixedListFind(&arrayList, "foobar");
	assert(found == -1, "element found");
	println("Looking for \"foobar\". Not found");
	printFixedListState(&arrayList);
	printerWait(1500);

	found = arrayFixedListFindEmpty(&arrayList);
	assert(2 == found, "wrong index");
	print("Looking for first empty element. Found at position: ");
	sprintf(value, "%d", found);
	println(value);
	printFixedListState(&arrayList);
	printerWait(1500);

	arrayFixedListRemoveAt(&arrayList, 0);
	assert(arrayList.count == 1, "wrong size");
	assert(!arrayList.e[0], "element not removed");
	println("Removed element at position 0");
	printFixedListState(&arrayList);
	printerWait(1500);

	char* foobar = "foobar";
	arrayFixedListAdd(&arrayList, foobar);
	assert(arrayList.count == 2, "wrong size");
	assert(arrayList.e[0] == foobar, "element not added");
	println("Added \"foobar\"");
	printFixedListState(&arrayList);
	printerWait(1500);

	arrayFixedListRelease(&arrayList);
	assert(arrayList.size == 0, "wrong size");
	assert(arrayList.count == 0, "wrong count");
	assert(!arrayList.e, "array not released");
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
	assert(doublyLinkedList.count == 0, "wrong count");
	assert(!doublyLinkedList.first, "wrong first");
	assert(!doublyLinkedList.last, "wrong last");
	println("Created doubly linked list");
	printDoublyLinkedListState(&doublyLinkedList);
	println("");
	printerWait(1500);

	DoublyLinkedListNode* node;
	char* foo = "foo";
	node = doublyLinkedListAdd(&doublyLinkedList, foo);
	assert(doublyLinkedList.count == 1, "wrong count");
	assert(doublyLinkedList.first == node, "wrong first");
	assert(doublyLinkedList.last == node, "wrong last");
	assert(node->e == foo, "wrong element");
	assert(!node->prev, "wrong prev");
	assert(!node->next, "wrong next");
	println("Added \"foo\"");
	printDoublyLinkedListState(&doublyLinkedList);
	println("");
	printerWait(1500);

	char* bar = "bar";
	node = doublyLinkedListAdd(&doublyLinkedList, bar);
	assert(node->e == bar, "wrong element");
	assert(node->prev && node->prev->e == foo, "wrong prev");
	assert(!node->next, "wrong next");
	assert(doublyLinkedList.count == 2, "wrong count");
	assert(doublyLinkedList.last == node, "wrong last");
	assert(doublyLinkedList.first->e == foo, "wrong first");
	println("Added \"bar\"");
	printDoublyLinkedListState(&doublyLinkedList);
	println("");
	printerWait(1500);

	DoublyLinkedListNode* found = doublyLinkedListFind(&doublyLinkedList, foo);
	assert(found != 0, "not found");
	assert(found->e == foo, "found wrong node");
	println("Found \"foo\"");
	printDoublyLinkedListState(&doublyLinkedList);
	println("");
	printerWait(1500);

	doublyLinkedListRemove(&doublyLinkedList, found);
	assert(doublyLinkedList.count == 1, "wrong count");
	assert(doublyLinkedList.first->e == bar, "wrong first");
	assert(doublyLinkedList.last->e == bar, "wrong last");
	assert(!doublyLinkedList.first->prev, "wrong bar prev");
	assert(!doublyLinkedList.first->next, "wrong bar next");
	println("Removed element successfully");
	printDoublyLinkedListState(&doublyLinkedList);
	println("");
	printerWait(1500);

	char* foobar = "foobar";
	node = doublyLinkedListAdd(&doublyLinkedList, foobar);
	assert(node->e == foobar, "wrong element");
	assert(node->prev && node->prev->e == bar, "wrong prev");
	assert(!node->next, "wrong next");
	assert(doublyLinkedList.count == 2, "wrong count");
	assert(doublyLinkedList.last == node, "wrong last");
	assert(doublyLinkedList.first->e == bar, "wrong first");
	println("Added \"foobar\"");
	printDoublyLinkedListState(&doublyLinkedList);
	println("");
	printerWait(1500);

	doublyLinkedListRelease(&doublyLinkedList);
	assert(doublyLinkedList.count == 0, "wrong count");
	assert(!doublyLinkedList.first, "wrong first");
	assert(!doublyLinkedList.last, "wrong last");
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
