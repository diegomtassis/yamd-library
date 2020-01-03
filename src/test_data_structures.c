/*
 * test_data_structures.c
 *
 *  Created on: Dec 24, 2019
 *      Author: diegomtassis
 */

#include <genesis.h>

#include "../inc/fwk/doubly_linked_list.h"
#include "../inc/fwk/fixed_list.h"
#include "../inc/fwk/printer.h"

static void testFixedList();
static void testDoublyLinkedList();

static void printFixedListState(FixedList* fixedList);
static void printDoublyLinkedListState(DoublyLinkedList* doublyLinkedList);

void testDataStructures() {

	KLog("testing data structures");

	VDP_setTextPalette(PAL2);

	testFixedList();
	testDoublyLinkedList();
}

static void testFixedList() {

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

static void testDoublyLinkedList() {

	turnPrinterOn();

	println("Test DoublyLinkedList");
	println("");
	printerWait(3000);

	DoublyLinkedList doublyLinkedList;

	doubly_linked_list_init(&doublyLinkedList);
	println("Created doubly linked list");
	printDoublyLinkedListState(&doublyLinkedList);
	println("");
	printerWait(1500);

	char* foo = "foo";
	doubly_linked_list_add(&doublyLinkedList, foo);
	println("Added \"foo\"");
	printDoublyLinkedListState(&doublyLinkedList);
	println("");
	printerWait(1500);

	char* bar = "bar";
	doubly_linked_list_add(&doublyLinkedList, bar);
	println("Added \"bar\"");
	printDoublyLinkedListState(&doublyLinkedList);
	println("");
	printerWait(1500);

	DoublyLinkedListNode* found = doubly_linked_list_find(&doublyLinkedList, foo);
	println("Looking for \"foo\" and found");
	printDoublyLinkedListState(&doublyLinkedList);
	println("");
	printerWait(1500);

	doubly_linked_list_remove(&doublyLinkedList, found);
	println("Removed element successfully");
	printDoublyLinkedListState(&doublyLinkedList);
	println("");
	printerWait(1500);

	char* foobar = "foobar";
	doubly_linked_list_add(&doublyLinkedList, foobar);
	println("Added \"foobar\"");
	printDoublyLinkedListState(&doublyLinkedList);
	println("");
	printerWait(1500);

	doubly_linked_list_release(&doublyLinkedList);
	println("Released list");
	printDoublyLinkedListState(&doublyLinkedList);

	printerWait(5000);

	turnPrinterOff();
}

static void printFixedListState(FixedList* fixedList) {

	char value[5];

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
