/* ************************************************************************** */
/*      ____    _    _____ ____     _    _   _   _____ _  _   ____  ____      */
/*     / ___|  / \  |  ___|  _ \   / \  | \ | | |_   _| || | |  _ \/ ___|     */
/*     \___ \ / _ \ | |_  | |_) | / _ \ |  \| |   | | | || |_| | | \___ \     */
/*      ___) / ___ \|  _| |  _ < / ___ \| |\  |   | | |__   _| |_| |___) |    */
/*     |____/_/   \_|_|   |_| \_/_/   \_|_| \_|   |_|    |_| |____/|____/     */
/*                                                                            */
/* Copyright 2023, SAFRAN T4DS, ALL RIGHTS RESERVED                           */
/*                                                                            */
/* @file core.c                                                               */
/* @author Hugo FOLCHER                                                       */
/*                                                                            */
/* ************************************************************************** */

#include "o2s/deque.h"
#include "private.h"

#include <stdlib.h> //free

/**
 * Contructs an deque.
 * note that:
 * - 'first' points the start of the first element i.e where next element will
 * be popped by pop_front.
 * - 'end' points the end of the last element i.e where next element will be
 * inserted by push_back.
 */
deque_t deque_new(void* p, size_t type_size, size_t capacity)
{
	return (deque_t){.data        = p,
	                 .first       = p,
	                 .end         = p,
	                 .first_index = 0,
	                 .end_index   = 0,
	                 .count       = 0,
	                 .type_size   = type_size,
	                 .capacity    = capacity};
}

/**
 * Shift the start pointer ('first') consistently i.e shifting the index in accordance.
 */
bool deque_front_shift(deque_t* self, int shift)
{
	size_t new_index = deque_index_shift(self, self->first_index, shift);
	void*  element   = deque_get_element_from_index(self, new_index);
	if (element == NULL)
		return false;
	self->first       = element;
	self->first_index = new_index;
	return true;
}

/**
 * Shift the end pointer ('end') consistently i.e shifting the index in accordance.
 */
bool deque_back_shift(deque_t* self, int shift)
{
	size_t new_index = deque_index_shift(self, self->end_index, shift);
	void*  element   = deque_get_element_from_index(self, new_index);
	if (element == NULL)
		return false;
	self->end       = element;
	self->end_index = new_index;
	return true;
}

/**
 * Clears properly the deque.
 */
void deque_clear(deque_t* self)
{
	self->first       = self->data;
	self->end         = self->data;
	self->first_index = 0;
	self->end_index   = 0;
	self->count       = 0;
}

/**
 * Frees properly the deque.
 */
void deque_free(deque_t* self)
{
	free(self->data);
	self->data = NULL;
}
