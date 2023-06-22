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

#include <stdlib.h> // malloc, free
#include <string.h> // memcpy

/**
 * Contructs an deque.
 */
deque_t deque_new(size_t type_size, size_t capacity)
{
	void* p = malloc(type_size * capacity);
	if (p == NULL)
		return (deque_t){.first       = NULL,
		                 .last        = NULL,
		                 .first_index = 0,
		                 .last_index  = 0,
		                 .type_size   = type_size,
		                 .capacity    = 0};
	return (deque_t){.first       = p,
	                 .last        = p,
	                 .first_index = 0,
	                 .last_index  = 0,
	                 .type_size   = type_size,
	                 .capacity    = capacity};
}

size_t deque_offset(deque_t* self, size_t count)
{
	return (count * self->type_size);
}

size_t deque_count(deque_t* self)
{
	return ((self->capacity + self->last_index - self->first_index + 1) % self->capacity);
}

size_t deque_remaining_capacity(deque_t* self)
{
	return (self->capacity - deque_count(self));
}

size_t deque_remaining_back_capacity(deque_t* self)
{
	size_t end_index = self->last_index + 1;
	return (self->capacity - (end_index + 1));
}

void* deque_end(deque_t* self)
{
	return ((self->last_index + 1) % self->capacity);
}

void deque_front_shift(deque_t* self, size_t shift)
{
	size_t new_index = (2 * self->capacity + self->first_index - shift) % self->capacity;
	self->first       = self->first + new_index - self->first_index;
	self->first_index = new_index;
}

void deque_back_shift(deque_t* self, size_t shift)
{
	size_t new_index = (2 * self->capacity + self->last_index + shift) % self->capacity;
	self->last       = self->last + new_index - self->last_index;
	self->last_index = new_index;
}