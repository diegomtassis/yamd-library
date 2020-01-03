/*
 * fixed_list.c
 *
 *  Created on: Dec 23, 2019
 *      Author: diegomtassis
 */

#include <genesis.h>

#include "../../inc/fwk/commons.h"
#include "../../inc/fwk/fixed_list.h"

void fixedlist_init(FixedList* list, u8 size) {

	if (!list) {
		return;
	}

	list->e = MEM_calloc(sizeof(void*) * size);
	list->size = size;
	list->count = 0;
}

void fixedlist_release(FixedList* list) {

	if (!list) {
		return;
	}

	memset(list->e, 0, list->size);
	MEM_free(list->e);
	list->e = 0;
	list->count = 0;
}

s16 fixedlist_add(FixedList* list, void* e) {

	if (!list) {
		return -1;
	}

	s16 empty_pos = fixedlist_find_empty(list);
	if (empty_pos >= 0) {
		list->e[empty_pos] = e;
		list->count++;
	}

	return empty_pos;
}

s16 fixedlist_find_empty(FixedList* list) {

	if (!list) {
		return -1;
	}

	for (s16 idx = 0; idx < list->size; idx++) {
		if (!list->e[idx]) {
			return idx;
		}
	}

	return -1;
}

s16 fixedlist_find(FixedList* list, void* e) {

	if (!list) {
		return -1;
	}

	for (s16 idx = 0; idx < list->size; idx++) {
		if (list->e[idx] == e) {
			return idx;
		}
	}

	return -1;
}

void fixedlist_remove_at(FixedList* list, u16 pos) {

	if (!list || list->count <= 0 || pos >= list->size || !list->e[pos]) {
		return;
	}

	list->e[pos] = 0;
	list->count--;
}
