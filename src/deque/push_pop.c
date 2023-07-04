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

#include <iso646.h> // not

#include <string.h> // memcpy

/**
 * Inserts an element in the deque on the front side.
 */
bool deque_push_front(deque_t* self, void* element)
{
	if (not deque_front_shift(self, -1))
		return false;
	memcpy(self->first, element, self->type_size);
	return true;
}

/**
 * Inserts n elements in the deque on the front side.
 */
bool deque_push_front_n(deque_t* self, void* elements, size_t count)
{
	for (size_t i = 0; i < count; i++)
	{
		if (not deque_push_front(self, elements + deque_offset(self, i)))
			return false;
	}
	return true;
}

/**
 * Pops the first element in the deque.
 */
bool deque_pop_front(deque_t* self, void* element)
{
	if (element == NULL)
	{
		return false;
	}
	memcpy(element, self->first, deque_offset(self, 1));
	if (not deque_front_shift(self, 1))
		return false;
	return true;
}

/**
 * Pops the n first element in the deque.
 */
bool deque_pop_front_n(deque_t* self, void* destination, size_t count)
{
	if (deque_remaining_capacity(self) < count)
		return false;

	size_t distance_from_right = deque_right_distance(self, self->first_index);
	if (distance_from_right >= count)
	{
		memcpy(destination, self->first, deque_offset(self, count));
		if (not deque_front_shift(self, count))
			return false;
	}
	else
	{
		memcpy(destination, self->first, deque_offset(self, distance_from_right));
		if (not deque_front_shift(self, distance_from_right))
			return false;
		memcpy(destination + deque_offset(self, distance_from_right),
		       self->first,
		       deque_offset(self, count - distance_from_right));
		if (not deque_front_shift(self, count - distance_from_right))
			return false;
	}
	return true;
}

/**
 * Inserts n elements in the deque on the back side.
 */
bool deque_push_back_n(deque_t* self, void* elements, size_t count)
{
	if (deque_remaining_capacity(self) < count)
		return false;

	size_t distance_from_right = deque_right_distance(self, self->end_index);
	if (distance_from_right >= count)
	{
		memcpy(self->end, elements, deque_offset(self, count));
		if (not deque_back_shift(self, count))
			return false;
	}
	else
	{
		memcpy(self->end, elements, deque_offset(self, distance_from_right));
		if (not deque_back_shift(self, distance_from_right))
			return false;
		memcpy(self->end,
		       elements + deque_offset(self, distance_from_right),
		       deque_offset(self, count - distance_from_right));
		if (not deque_back_shift(self, count - distance_from_right))
			return false;
	}
	return true;
}

/**
 * Inserts an element in the deque on the back side.
 */
bool deque_push_back(deque_t* self, void* destination)
{
	return deque_push_back_n(self, destination, 1);
}

/**
 * Pops the last element in the deque.
 */
bool deque_pop_back(deque_t* self, void* destination)
{
	if (destination == NULL || deque_count(self) == 0)
		return false;
	size_t last_index = deque_index_shift(self, self->end_index, -1);
	void*  element    = deque_get_element_from_index(self, last_index);
	if (element == NULL)
		return false;
	memcpy(destination, element, deque_offset(self, 1));
	if (not deque_back_shift(self, -1))
		return false;
	return true;
}

/**
 * Pops the n last element in the deque.
 */
bool deque_pop_back_n(deque_t* self, void* destination, size_t count)
{
	if (deque_count(self) < count)
		return false;

	for (size_t i = 0; i < count; i++)
	{
		if (not deque_pop_back(self, destination + deque_offset(self, i)))
			return false;
	}
	return true;
}