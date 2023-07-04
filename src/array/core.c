/* ************************************************************************** */
/*      ____    _    _____ ____     _    _   _   _____ _  _   ____  ____      */
/*     / ___|  / \  |  ___|  _ \   / \  | \ | | |_   _| || | |  _ \/ ___|     */
/*     \___ \ / _ \ | |_  | |_) | / _ \ |  \| |   | | | || |_| | | \___ \     */
/*      ___) / ___ \|  _| |  _ < / ___ \| |\  |   | | |__   _| |_| |___) |    */
/*     |____/_/   \_|_|   |_| \_/_/   \_|_| \_|   |_|    |_| |____/|____/     */
/*                                                                            */
/* Copyright 2023, SAFRAN T4DS, ALL RIGHTS RESERVED                           */
/*                                                                            */
/* @file new.c                                                                */
/* @author Antoine GAGNIERE                                                   */
/*                                                                            */
/* ************************************************************************** */

#include "o2s/array.h"
#include "private.h"

#include <stdlib.h> // malloc, free
#include <string.h> // memcpy

/**
 * Contructs an array.
 */
array_t array_new(size_t type_size)
{
	return (array_t){.start = NULL, .type_size = type_size, .count = 0, .capacity = 0};
}

/**
 * Gives allocation size of given count.
 */
size_t array_offset(array_t* self, size_t count)
{
	return (count * self->type_size);
}

/**
 * Adds one n elements at the end of the array.
 * @return false if allocation failed.
 */
bool array_realloc(array_t* self, size_t capacity_to_alloc)
{
	void* p = reallocarray(self->start, capacity_to_alloc, self->type_size);
	if (p == NULL)
		return false;
	self->start    = p;
	self->capacity = capacity_to_alloc;
	return true;
}

/**
 * Checks if the array can handle 'grow_count' new elements and reallocate if not.
 * @return false if allocation was needed and failed.
 */
bool array_grow(array_t* self, size_t grow_count)
{
	size_t next_count = (self->count + grow_count);
	if (next_count <= self->capacity)
		return true;
	size_t required_capacity =
	    MAX(INITIAL_SIZE, self->capacity - (self->capacity % INITIAL_SIZE));
	while (required_capacity < next_count)
	{
		required_capacity = required_capacity * REALLOC_FACTOR;
	}
	return array_realloc(self, required_capacity);
}

/**
 * Forces allocation to handle 'count' new elements.
 * @return false if allocation failed.
 */
bool array_reserve(array_t* self, size_t count)
{
	return array_grow(self, count);
}

/**
 * Clears properly the array.
 */
void array_clear(array_t* self)
{
	free(self->start);
	self->count    = 0;
	self->capacity = 0;
}

/**
 * Resizes the underlying storage to match current elements count.
 * @return false if allocation failed.
 */
bool array_trim(array_t* self)
{
	return array_realloc(self, self->count);
}