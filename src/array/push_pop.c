/* ************************************************************************** */
/*      ____    _    _____ ____     _    _   _   _____ _  _   ____  ____      */
/*     / ___|  / \  |  ___|  _ \   / \  | \ | | |_   _| || | |  _ \/ ___|     */
/*     \___ \ / _ \ | |_  | |_) | / _ \ |  \| |   | | | || |_| | | \___ \     */
/*      ___) / ___ \|  _| |  _ < / ___ \| |\  |   | | |__   _| |_| |___) |    */
/*     |____/_/   \_|_|   |_| \_/_/   \_|_| \_|   |_|    |_| |____/|____/     */
/*                                                                            */
/**
 * @copyright 2023, SAFRAN T4DS, ALL RIGHTS RESERVED
 * @file push_pop.c
 * @author Hugo FOLCHER
 * @author Antoine GAGNIERE
 * @brief Add and remove elements from dynamic arrays
 */
/* ************************************************************************** */

#include "private.h"

#include "o2s/array.h"

#include <iso646.h> // not
#include <string.h> // memcpy

/**
 * Adds @p count elements at the end of the array.
 * @return false if allocation failed.
 */
bool array_push_back_n(array_t* self, const void* elements, size_t count)
{
	if (count == 0)
		return true;
	if (not array_reserve(self, count))
		return false;
	memcpy(array_end(self), elements, array_offset(self, count));
	self->count += count;
	return true;
}

/**
 * Adds one element at the end of the array.
 * @return false if allocation failed.
 */
bool array_push_back(array_t* self, const void* element)
{
	return array_push_back_n(self, element, 1);
}

/**
 * Moves to destination the n last elements of the array.
 * Destination can be NULL to just discard the elements.
 * @return false if not enough element in the array.
 */
bool array_pop_back_n(array_t* self, void* destination, size_t count)
{
	if (count > self->count)
		return false;
	const void* source = array_get(self, self->count - count);
	if (destination != NULL)
		memcpy(destination, source, array_offset(self, count));
	self->count -= count;
	return true;
}

/**
 * Moves to destination the last element of the array.
 * @return false if the array is empty.
 */
bool array_pop_back(array_t* self, void* destination)
{
	return array_pop_back_n(self, destination, 1);
}

/**
 * Moves to @p destination the @p count first elements of @p self
 * @return false if there are not enough elements in the array
 */
bool array_pop_front_n(array_t* self, void* destination, size_t count)
{
	if (count > self->count)
		return false;
	size_t remaining = self->count - count;
	if (destination)
		memcpy(destination, self->start, array_offset(self, count));
	memmove(self->start, array_get(self, count), array_offset(self, remaining));
	self->count -= count;
	return true;
}

/**
 * Moves to @p destination the first element of @p self
 * @return false if the array is empty
 */
bool array_pop_front(array_t* self, void* destination)
{
	return array_pop_front_n(self, destination, 1);
}
