/* ************************************************************************** */
/*      ____    _    _____ ____     _    _   _   _____ _  _   ____  ____      */
/*     / ___|  / \  |  ___|  _ \   / \  | \ | | |_   _| || | |  _ \/ ___|     */
/*     \___ \ / _ \ | |_  | |_) | / _ \ |  \| |   | | | || |_| | | \___ \     */
/*      ___) / ___ \|  _| |  _ < / ___ \| |\  |   | | |__   _| |_| |___) |    */
/*     |____/_/   \_|_|   |_| \_/_/   \_|_| \_|   |_|    |_| |____/|____/     */
/*                                                                            */
/* Copyright 2023, SAFRAN T4DS, ALL RIGHTS RESERVED                           */
/*                                                                            */
/* @file constructors_destructors.c                                           */
/* @author Hugo FOLCHER                                                       */
/*                                                                            */
/* ************************************************************************** */

#include "o2s/deque.h"
#include "private.h"

#include <stdlib.h> //free

/**
 * Contructs an deque, using externally owned memory.
 * note that:
 * - 'first' points the start of the first element i.e where next element will
 * be popped by pop_front.
 * - 'end' points the end of the last element i.e where next element will be
 * inserted by push_back.
 */
deque_t deque_new(void* storage, size_t capacity, size_t type_size)
{
	return (deque_t){.storage   = storage,
	                 .front     = storage,
	                 .back      = storage,
	                 .count     = 0,
	                 .type_size = type_size,
	                 .capacity  = capacity};
}

/**
 * Constructs a deque, allocating the needed memory.
 * If the allocation failed, the capacity will be set to zero.
 */
deque_t deque_allocate(size_t capacity, size_t type_size)
{
	void* storage = calloc(capacity, type_size);

	if (storage == NULL)
		capacity = 0;
	return deque_new(storage, capacity, type_size);
}

/** Clears properly the deque */
void deque_clear(deque_t* self)
{
	self->front = self->storage;
	self->back  = self->storage;
	self->count = 0;
}

/** Frees properly the deque */
void deque_free(deque_t* self)
{
	if (self->storage != NULL)
		free(self->storage);
	self->storage = NULL;
	deque_clear(self);
	self->capacity = 0;
}
