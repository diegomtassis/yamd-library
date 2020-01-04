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
	println("Created array fixed list");
	assert(arrayList.size == 5, "wrong size");
	assert(arrayList.count == 0, "wrong count");
	assert(arrayList.e, "array not initialized");
	printFixedListState(&arrayList);
	printerWait(500);

	char* foo = "foo";
	arrayFixedListAdd(&arrayList, foo);
	println("Added \"foo\"");
	assert(arrayList.count == 1, "wrong size");
	assert(arrayList.e[0] == foo, "element not added");
	printFixedListState(&arrayList);
	printerWait(1500);

	char* bar = "bar";
	arrayFixedListAdd(&arrayList, bar);
	println("Added \"bar\"");
	assert(arrayList.count == 2, "wrong size");
	assert(arrayList.e[1] == bar, "element not added");
	printFixedListState(&arrayList);
	printerWait(1500);

	s16 found = arrayFixedListFind(&arrayList, foo);
	print("Looking for \"foo\". Found in pos: ");
	char value[5];
	sprintf(value, "%d", found);
	println(value);
	assert(found == 0, "wrong element found");
	printFixedListState(&arrayList);
	printerWait(1500);

	found = arrayFixedListFind(&arrayList, "foobar");
	println("Looking for \"foobar\". Not found");
	assert(found == -1, "element found");
	printFixedListState(&arrayList);
	printerWait(1500);

	found = arrayFixedListFindEmpty(&arrayList);
	print("Looking for first empty element. Found position: ");
	sprintf(value, "%d", found);
	println(value);
	assert(2 == found, "wrong index");
	printFixedListState(&arrayList);
	printerWait(1500);

	arrayFixedListRemoveAt(&arrayList, 0);
	println("Removed element at position 0");
	assert(arrayList.count == 1, "wrong size");
	assert(!arrayList.e[0], "element not removed");
	printFixedListState(&arrayList);
	printerWait(1500);

	char* foobar = "foobar";
	arrayFixedListAdd(&arrayList, foobar);
	println("Added \"foobar\"");
	assert(arrayList.count == 2, "wrong size");
	assert(arrayList.e[0] == foobar, "element not added");
	printFixedListState(&arrayList);
	printerWait(1500);

	arrayFixedListRelease(&arrayList);
	println("Released list");
	assert(arrayList.size == 0, "wrong size");
	assert(arrayList.count == 0, "wrong count");
	assert(!arrayList.e, "array not released");
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
	println("Created doubly linked list");
	assert(doublyLinkedList.count == 0, "wrong count");
	assert(!doublyLinkedList.first, "wrong first");
	assert(!doublyLinkedList.last, "wrong last");
	printDoublyLinkedListState(&doublyLinkedList);
	println("");
	printerWait(1500);

	DoublyLinkedListNode* node;
	char* foo = "foo";
	node = doublyLinkedListAdd(&doublyLinkedList, foo);
	println("Added \"foo\"");
	assert(doublyLinkedList.count == 1, "wrong count");
	assert(doublyLinkedList.first == node, "wrong first");
	assert(doublyLinkedList.last == node, "wrong last");
	assert(node->e == foo, "wrong element");
	assert(!node->prev, "wrong prev");
	assert(!node->next, "wrong next");
	printDoublyLinkedListState(&doublyLinkedList);
	println("");
	printerWait(1500);

	char* bar = "bar";
	node = doublyLinkedListAdd(&doublyLinkedList, bar);
	println("Added \"bar\"");
	assert(node->e == bar, "wrong element");
	assert(node->prev && node->prev->e == foo, "wrong prev");
	assert(!node->next, "wrong next");
	assert(doublyLinkedList.count == 2, "wrong count");
	assert(doublyLinkedList.last == node, "wrong last");
	assert(doublyLinkedList.first->e == foo, "wrong first");
	printDoublyLinkedListState(&doublyLinkedList);
	println("");
	printerWait(1500);

	DoublyLinkedListNode* found = doublyLinkedListFind(&doublyLinkedList, foo);
	println("Looking for \"foo\" and found");
	assert(found, "not found");
	assert(found->e == foo, "found wrong node");
	printDoublyLinkedListState(&doublyLinkedList);
	println("");
	printerWait(1500);

	doublyLinkedListRemove(&doublyLinkedList, found);
	println("Removed element successfully");
	assert(doublyLinkedList.count == 1, "wrong count");
	assert(doublyLinkedList.first->e == bar, "wrong first");
	assert(doublyLinkedList.last->e == bar, "wrong last");
	assert(!doublyLinkedList.first->prev, "wrong bar prev");
	assert(!doublyLinkedList.first->next, "wrong bar next");
	printDoublyLinkedListState(&doublyLinkedList);
	println("");
	printerWait(1500);

	char* foobar = "foobar";
	node = doublyLinkedListAdd(&doublyLinkedList, foobar);
	println("Added \"foobar\"");
	assert(node->e == foobar, "wrong element");
	assert(node->prev && node->prev->e == bar, "wrong prev");
	assert(!node->next, "wrong next");
	assert(doublyLinkedList.count == 2, "wrong count");
	assert(doublyLinkedList.last == node, "wrong last");
	assert(doublyLinkedList.first->e == bar, "wrong first");
	printDoublyLinkedListState(&doublyLinkedList);
	println("");
	printerWait(1500);

	doublyLinkedListRelease(&doublyLinkedList);
	println("Released list");
	assert(doublyLinkedList.count == 0, "wrong count");
	assert(!doublyLinkedList.first, "wrong first");
	assert(!doublyLinkedList.last, "wrong last");
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
