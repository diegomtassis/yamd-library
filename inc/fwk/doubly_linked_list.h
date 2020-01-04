/*
 * doubly_linked_list.h
 *
 *  Created on: Jan 3, 2020
 *      Author: diegomtassis
 */

#ifndef INC_FWK_DOUBLY_LINKED_LIST_H_
#define INC_FWK_DOUBLY_LINKED_LIST_H_

#include <types.h>

typedef struct DoublyLinkedList DoublyLinkedList;
typedef struct DoublyLinkedListNode DoublyLinkedListNode;

struct DoublyLinkedListNode {
	void* e;
	DoublyLinkedListNode* prev;
	DoublyLinkedListNode* next;
	DoublyLinkedList* list;
};

struct DoublyLinkedList {
	DoublyLinkedListNode* first;
	DoublyLinkedListNode* last;
	u8 count;
};

/**
 * @brief initializes the list
 *
 * @param list
 */
void doublyLinkedListInit(DoublyLinkedList* list);

/**
 * @brief releases the list, removing all the nodes
 *
 * @param list
 */
void doublyLinkedListRelease(DoublyLinkedList* list);

/**
 * @brief adds an element at the end
 *
 * @param list
 * @param e
 * @return the node containing the element
 */
DoublyLinkedListNode* doublyLinkedListAdd(DoublyLinkedList* list, void* e);

/**
 * @brief finds whether a given element exists in a list
 *
 * @param list
 * @param e
 * @return the node containing the element
 */
DoublyLinkedListNode* doublyLinkedListFind(DoublyLinkedList* list, void* e);

/**
 * @brief removes a node form a list
 *
 * @param list
 * @param node
 */
void doublyLinkedListRemove(DoublyLinkedList* list, DoublyLinkedListNode* node);

#endif /* INC_FWK_DOUBLY_LINKED_LIST_H_ */
