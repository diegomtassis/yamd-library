/*
 * doubly_linked_list.c
 *
 *  Created on: Jan 3, 2020
 *      Author: diegomtassis
 */

#include "../../inc/fwk/doubly_linked_list.h"

#include <genesis.h>

#include "../../inc/fwk/commons.h"

void doubly_linked_list_init(DoublyLinkedList* list) {

	list->first = 0;
	list->last = 0;
	list->count = 0;
}

void doubly_linked_list_release(DoublyLinkedList* list) {

	while (list->first) {
		doubly_linked_list_remove(list, list->first);
	}

	list->first = 0;
	list->last = 0;
	list->count = 0;
}

DoublyLinkedListNode* doubly_linked_list_add(DoublyLinkedList* list, void* e) {

	DoublyLinkedListNode* node = MEM_calloc(sizeof(*node));
	node->e = e;

	if (list->first) {
		node->prev = list->last;
		list->last = node;

	} else {
		list->first = node;
		list->last = node;
	}

	list->count++;

	return node;
}

DoublyLinkedListNode* doubly_linked_list_find(DoublyLinkedList* list, void* e) {

	if (!list || !e) {
		return 0;
	}

	DoublyLinkedListNode* node = list->first;

	while (node) {
		if (node->e == e) {
			return node;
		}
		node = node->next;
	}

	return 0;
}

void doubly_linked_list_remove(DoublyLinkedList* list, DoublyLinkedListNode* node) {

	if (!node) {
		return;
	}

	if (list->first == node) {
		list->first = node->next;
	}

	if (list->last == node) {
		list->last = node->prev;
	}

	node->e = 0;
	node->prev = 0;
	node->next = 0;

	MEM_free(node);

	list->count--;
}

