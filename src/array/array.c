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

bool _realloc(void* start, size_t content_size, size_t allocation_size)
{
	void* p = malloc(allocation_size);
	if (p != NULL)
	{
		memcpy(p, start, content_size);
		free(start);
		start = p;
		return true;
	}
	else
		return false;
}

size_t _array_offset(array_t* self, size_t count)
{
	return(self->type_size * count);
}

size_t _array_end(array_t* self)
{
	return((void*)self->start + _array_offset(self, self->count));
}


bool _array_realloc(array_t* self, size_t capacity_to_alloc)
{
	if (_realloc(self->start, _array_offset(self, self->count), _array_offset(self, capacity_to_alloc)))
	{
		self->capacity = capacity_to_alloc;
		return true;
	}
	else
		return false;
}

bool _array_grow(array_t* self, size_t grow_count)
{
	size_t next_count = (self->count + grow_count);
	if (next_count > self->capacity)
	{
		size_t required_capacity =
		    MAX(INITIAL_SIZE, self->capacity - (self->capacity % INITIAL_SIZE)); // avoid cases with invalid capacity due to trim
		while (required_capacity < next_count)
		{
			required_capacity = required_capacity * REALLOC_FACTOR;
		}
		return _array_realloc(self, _array_offset(self, required_capacity));
	}
	else
		return true;
}

bool array_push_back_n(array_t* self, void* elements, size_t count)
{
	if (_array_grow(self, count))
	{
		memcpy(_array_end(self), elements, _array_offset(self, count));
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
		void* source = (void*)self->start + _array_offset(self, self->count - count);
		memcpy(destination, source, _array_offset(self, count));
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
		return self->start + _array_offset(self, self->count - 1);
	}
	else
		return NULL;
}

void* array_get(array_t* self, size_t index)
{
	if (index + 1 <= self->count)
	{
		return self->start + _array_offset(self, index);
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
	return _array_realloc(self, self->count);
}