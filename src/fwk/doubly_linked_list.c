/*
 * doubly_linked_list.c
 *
 *  Created on: Jan 3, 2020
 *      Author: diegomtassis
 */

#include "../../inc/fwk/doubly_linked_list.h"

#include <genesis.h>

#include "../../inc/fwk/commons.h"

void doublyLinkedListInit(DoublyLinkedList* list) {

	list->first = 0;
	list->last = 0;
	list->count = 0;
}

void doublyLinkedListRelease(DoublyLinkedList* list) {

	while (list->first) {
		doublyLinkedListRemove(list, list->first);
	}

	list->first = 0;
	list->last = 0;
	list->count = 0;
}

DoublyLinkedListNode* doublyLinkedListAdd(DoublyLinkedList* list, const void* e) {

	DoublyLinkedListNode* node = MEM_calloc(sizeof(*node));
	node->e = e;
	node->list = list;

	if (list->first) {
		list->last->next = node;
		node->prev = list->last;
		list->last = node;

	} else {
		list->first = node;
		list->last = node;
	}

	list->count++;

	return node;
}

DoublyLinkedListNode* doublyLinkedListFind(DoublyLinkedList* list, const void* e) {

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

void doublyLinkedListRemove(DoublyLinkedList* list, DoublyLinkedListNode* node) {

	if (!list || !node || !list->count || node->list != list) {
		return;
	}

	if (list->first == node) {
		list->first = node->next;
		if (list->first) {
			list->first->prev = 0;
		}
	}

	if (list->last == node) {
		list->last = node->prev;
		if (list->last) {
			list->last->next = 0;
		}
	}

	node->e = 0;
	node->list = 0;
	node->prev = 0;
	node->next = 0;

	MEM_free(node);

	list->count--;
}

