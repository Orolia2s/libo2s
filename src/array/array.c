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
#include <string.h> //enable use of 'memcpy'
#include <stdlib.h> //enable use of 'malloc' and 'free'

#define INITIAL_SIZE   16
#define REALLOC_FACTOR 2

#define MIN(i, j)      (((i) < (j)) ? (i) : (j))
#define MAX(i, j)      (((i) > (j)) ? (i) : (j))

array_t array_new(size_t type_size)
{
	return (array_t){.start = NULL, .type_size = type_size, .count = 0, .capacity = 0};
}

bool _array_realloc(array_t* self, size_t allocation_size)
{
	void* p = malloc(allocation_size);
	if (p != NULL)
	{
		memcpy(p, self->start, self->count * self->type_size);
		self->capacity = allocation_size;
		free(self->start);
		self->start = p;
		return true;
	}
	else
		return false;
}

bool _array_grow(array_t* self, size_t grow_count)
{
	size_t next_real_size = (self->count + grow_count) * sizeof(self->type_size);
	if (next_real_size > self->capacity)
	{
		size_t allocation_chunk_size =
		    MAX(INITIAL_SIZE, self->capacity - (self->capacity % INITIAL_SIZE)); // avoid cases with invalid capacity due to trim
		while (allocation_chunk_size < next_real_size)
		{
			allocation_chunk_size = allocation_chunk_size * REALLOC_FACTOR;
		}
		return _array_realloc(self, allocation_chunk_size);
	}
	else
		return true;
}

bool array_push_back_n(array_t* self, void* elements, size_t count)
// What if user send wrong type ?
// if too large a troncated part of this elt will be copied but will be probably
// unusable if too small could end by a core dumped
{
	if (_array_grow(self, count))
	{
		void* end = (void*)self->start + (self->count * self->type_size);
		memcpy(end, elements, count * self->type_size);
		self->count = self->count + count;
		return true;
	}
	return false;
}

bool array_push_back(array_t* self, void* element)
{
	return array_push_back_n(self, element, 1);
}

bool array_pop_back_n(array_t* self, void* destination, size_t count)
{
	if (count <= self->count)
	{
		void* source = (void*)self->start + (self->count - count) * self->type_size;
		memcpy(destination, source, count * self->type_size);
		self->count = self->count - count;
		return true;
	}
	return false;
}

bool array_pop_back(array_t* self, void* destination)
{
	return array_pop_back_n(self, destination, 1);
}

void* array_first(array_t* self)
{
	return array_get(self, 0);
}

void* array_last(array_t* self)
{
	if (self->count > 0)
	{
		return self->start + (self->count - 1) * self->type_size;
	}
	else
		return NULL;
}

void* array_get(array_t* self, size_t index)
{
	if (index + 1 <= self->count)
	{
		return self->start + index * self->type_size;
	}
	else
		return NULL;
}

bool array_reserve(array_t* self, size_t count)
{
	return _array_grow(self, count);
}

bool array_clear(array_t* self)
{
	free(self->start);
	self->count    = 0;
	self->capacity = 0;
	return true;
}

bool array_trim(array_t* self)
{
	return _array_realloc(self, self->count * self->type_size);
}