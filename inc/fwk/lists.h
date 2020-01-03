/*
 * lists.h
 *
 *  Created on: Dec 23, 2019
 *      Author: diegomtassis
 */

#ifndef INC_FWK_LISTS_H_
#define INC_FWK_LISTS_H_

#include <types.h>

typedef struct List {
	u8 count;
	u8 size;
	void** e;
} FixedList;

/**
 * @brief initializes the size and reserves memory for the elements
 *
 * @param list
 * @param size
 */
void fixedlist_init(FixedList* list, u8 size);

/**
 * @brief releases the list, setting count to 0 and releasing the memory for the elements
 *
 * @param list
 */
void fixedlist_release(FixedList* list);

/**
 * @brief adds an element in the first empty position
 *
 * @param list
 * @param e
 * @return pos where the element has been added, -1 otherwise
 */
s16 fixedlist_add(FixedList* list, void* e);

/**
 * @brief removes the element at a given position
 *
 * @param list
 * @param idx
 */
void fixedlist_remove_at(FixedList* list, u16 idx);

/**
 * @brief looks for the first empty position
 *
 * @param list
 * @return first empty position in case it exists, -1 otherwise
 */
s16 fixedlist_find_empty(FixedList* list);

/**
 * @brief finds whether a given element exists in the list
 *
 * @param list
 * @param e
 * @return position of the given element, -1 if it does not exist in the list
 */
s16 fixedlist_find(FixedList* list, void* e);

#endif /* INC_FWK_LISTS_H_ */
