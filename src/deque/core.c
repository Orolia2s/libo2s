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
	return (deque_t){.first       = p + 0,
	                 .end         = p + 0,
	                 .first_index = 0,
	                 .end_index   = 0,
	                 .type_size   = type_size,
	                 .capacity    = capacity};
}

/**
 * Gives allocation size of given count.
 */
size_t deque_offset(deque_t* self, size_t count)
{
	return (count * self->type_size);
}

/**
 * Gives the current count of elements in the deque.
 */
size_t deque_count(deque_t* self)
{
	return ((self->capacity + self->end_index - self->first_index) % self->capacity);
}

/**
 * Gives the remaining available capacity in the deque.
 */
size_t deque_remaining_capacity(deque_t* self)
{
	return (self->capacity - deque_count(self));
}

/**
 * Gives the between the given index and the right border of allocated space.
 */
size_t deque_right_distance(deque_t* self, size_t index)
{
	return (self->capacity - index);
}

/**
 * Getter for element in the deque.
 * @return pointer to the element requested if index is valid, NULL instead.
 */
void* deque_get_element_from_index(deque_t* self, size_t index)
{
	if (index >= self->capacity)
		return NULL;
	int offset = deque_offset(self, index - self->first_index);
	return ((void*)(self->first + offset));
}

/**
 * Shift a given index consistently i.e applying the correct modulo.
 * @return new index after the shift.
 */
size_t deque_index_shift(deque_t* self, size_t index, int shift)
{
	return ((self->capacity + index + shift) % self->capacity);
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
bool deque_clear(deque_t* self)
{
	return deque_front_shift(self, deque_count(self));
}