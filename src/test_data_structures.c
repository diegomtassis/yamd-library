/*
 * test_data_structures.c
 *
 *  Created on: Dec 24, 2019
 *      Author: diegomtassis
 */

#include <genesis.h>

#include "../inc/fwk/array_fixed_list.h"
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
	printFixedListState(&arrayList);
	printerWait(500);

	char* foo = "foo";
	arrayFixedListAdd(&arrayList, foo);
	println("Added \"foo\"");
	printFixedListState(&arrayList);
	println("");
	printerWait(1500);

	char* bar = "bar";
	arrayFixedListAdd(&arrayList, bar);
	println("Added \"bar\"");
	printFixedListState(&arrayList);
	println("");
	printerWait(1500);

	s16 found = arrayFixedListFind(&arrayList, foo);
	print("Looking for \"foo\". Found in pos: ");
	char value[5];
	sprintf(value, "%d", found);
	println(value);
	printFixedListState(&arrayList);
	println("");
	printerWait(1500);

	found = arrayFixedListFindEmpty(&arrayList);
	print("Looking for first empty element. Found position: ");
	sprintf(value, "%d", found);
	println(value);
	printFixedListState(&arrayList);
	println("");
	printerWait(1500);

	arrayFixedListRemoveAt(&arrayList, 0);
	println("Removed element at position 0");
	printFixedListState(&arrayList);
	println("");
	printerWait(1500);

	char* foobar = "foobar";
	arrayFixedListAdd(&arrayList, foobar);
	println("Added \"foobar\"");
	printFixedListState(&arrayList);
	println("");
	printerWait(1500);

	arrayFixedListRelease(&arrayList);
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
	println("Created doubly linked list");
	printDoublyLinkedListState(&doublyLinkedList);
	println("");
	printerWait(1500);

	char* foo = "foo";
	doublyLinkedListAdd(&doublyLinkedList, foo);
	println("Added \"foo\"");
	printDoublyLinkedListState(&doublyLinkedList);
	println("");
	printerWait(1500);

	char* bar = "bar";
	doublyLinkedListAdd(&doublyLinkedList, bar);
	println("Added \"bar\"");
	printDoublyLinkedListState(&doublyLinkedList);
	println("");
	printerWait(1500);

	DoublyLinkedListNode* found = doublyLinkedListFind(&doublyLinkedList, foo);
	println("Looking for \"foo\" and found");
	printDoublyLinkedListState(&doublyLinkedList);
	println("");
	printerWait(1500);

	doublyLinkedListRemove(&doublyLinkedList, found);
	println("Removed element successfully");
	printDoublyLinkedListState(&doublyLinkedList);
	println("");
	printerWait(1500);

	char* foobar = "foobar";
	doublyLinkedListAdd(&doublyLinkedList, foobar);
	println("Added \"foobar\"");
	printDoublyLinkedListState(&doublyLinkedList);
	println("");
	printerWait(1500);

	doublyLinkedListRelease(&doublyLinkedList);
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
