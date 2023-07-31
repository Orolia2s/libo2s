/* ************************************************************************** */
/*      ____    _    _____ ____     _    _   _   _____ _  _   ____  ____      */
/*     / ___|  / \  |  ___|  _ \   / \  | \ | | |_   _| || | |  _ \/ ___|     */
/*     \___ \ / _ \ | |_  | |_) | / _ \ |  \| |   | | | || |_| | | \___ \     */
/*      ___) / ___ \|  _| |  _ < / ___ \| |\  |   | | |__   _| |_| |___) |    */
/*     |____/_/   \_|_|   |_| \_/_/   \_|_| \_|   |_|    |_| |____/|____/     */
/*                                                                            */
/* Copyright 2023, SAFRAN T4DS, ALL RIGHTS RESERVED                           */
/*                                                                            */
/* @file memory.c                                                             */
/* @author Antoine GAGNIERE                                                   */
/*                                                                            */
/* ************************************************************************** */

#include "private.h"

#include "o2s/array.h"

#include <stdlib.h> // reallocarray

/** The size in memory of @p count elements */
size_t array_offset(const array_t* self, size_t count)
{
	return (count * self->type_size);
}

/**
 * Re-allocate the storage to a new capacity.
 * @return false if allocation failed.
 */
bool array_realloc(array_t* self, size_t capacity_to_alloc)
{
	void* new_storage = reallocarray(self->start, capacity_to_alloc, self->type_size);
	if (new_storage == NULL)
		return false;
	self->start    = new_storage;
	self->capacity = capacity_to_alloc;
	return true;
}

/**
 * Ensures the array has enough capacity to fit @p count new elements,
 * reallocating if needed.
 * @return false if allocation was needed and failed.
 */
bool array_reserve(array_t* self, size_t count)
{
	const size_t wanted   = self->count + count;
	size_t       required = self->capacity;

	if (wanted <= self->capacity)
		return true;
	if (required == 0)
		required = ARRAY_INITIAL_SIZE;
	while (required < wanted)
		required *= ARRAY_GROWTH_FACTOR;
	return array_realloc(self, required);
}

/**
 * Resizes the underlying storage to fit exactly the current elements count.
 * @return false if allocation failed.
 */
bool array_trim(array_t* self)
{
	return array_realloc(self, self->count);
}
