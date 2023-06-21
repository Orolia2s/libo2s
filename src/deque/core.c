/* ************************************************************************** */
/*      ____    _    _____ ____     _    _   _   _____ _  _   ____  ____      */
/*     / ___|  / \  |  ___|  _ \   / \  | \ | | |_   _| || | |  _ \/ ___|     */
/*     \___ \ / _ \ | |_  | |_) | / _ \ |  \| |   | | | || |_| | | \___ \     */
/*      ___) / ___ \|  _| |  _ < / ___ \| |\  |   | | |__   _| |_| |___) |    */
/*     |____/_/   \_|_|   |_| \_/_/   \_|_| \_|   |_|    |_| |____/|____/     */
/*                                                                            */
/* Copyright 2023, SAFRAN T4DS, ALL RIGHTS RESERVED                           */
/*                                                                            */
/* @file core.c                                                                */
/* @author Hugo FOLCHER                                                   */
/*                                                                            */
/* ************************************************************************** */

#include "o2s/deque.h"
#include "private.h"

#include <stdlib.h> // malloc, free
#include <string.h> // memcpy

/**
 * Contructs an deque.
 */
deque_t deque_new(size_t type_size, size_t capacity)
{
	void* p = malloc(type_size * capacity);
	if (p == NULL)
		return (deque_t){.first = NULL, .last = NULL, .first_index = 0, .last_index = 0, .type_size = type_size, .capacity = 0};
	return (deque_t){.first = p, .last = p, .first_index = 0, .last_index = 0, .type_size = type_size, .capacity = capacity};
}

size_t  deque_offset(deque_t* self, size_t count)
{
	return (count * self->type_size);
}

size_t  deque_count(deque_t* self)
{
	return ((self->last_index - self->first_index) % self->capacity);
}

void*  front_shift(void* p, size_t old_index, size_t shift, size_t capacity)
{
	size_t new_index = (old_index - shift) % capacity;
	return p + new_index - old_index;
}

void*  back_shift(void* p, size_t old_index, size_t shift, size_t capacity)
{
	size_t new_index = (old_index + shift) % capacity;
	return p + new_index - old_index;
}

void    deque_push_front_n(deque_t* self, void* elements, size_t count)
{
    self->first = front_shift(self->first, self->first_index, count, self->capacity);
	memcpy(self->first, elements, deque_offset(self, count));
}

void    deque_push_front(deque_t* self, void* element)
{
    deque_push_front_n(self, element, 1);
}

bool    deque_push_back_n(deque_t* self, void* elements, size_t count)
{
	memcpy(self->last + deque_offset(self, 1), elements, deque_offset(self, count));
    self->last = back_shift(self->last, self->last_index, count + 1, self->capacity);
}

void    deque_push_back(deque_t* self, void* element)
{
    deque_push_back_n(self, element, 1);
}

// if (not array_grow(self, count))
// 	return false;
// memcpy(array_last(self), elements, array_offset(self, count));
// self->count = self->count + count;
// return true;