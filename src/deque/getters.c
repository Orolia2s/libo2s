/* ************************************************************************** */
/*      ____    _    _____ ____     _    _   _   _____ _  _   ____  ____      */
/*     / ___|  / \  |  ___|  _ \   / \  | \ | | |_   _| || | |  _ \/ ___|     */
/*     \___ \ / _ \ | |_  | |_) | / _ \ |  \| |   | | | || |_| | | \___ \     */
/*      ___) / ___ \|  _| |  _ < / ___ \| |\  |   | | |__   _| |_| |___) |    */
/*     |____/_/   \_|_|   |_| \_/_/   \_|_| \_|   |_|    |_| |____/|____/     */
/*                                                                            */
/* Copyright 2023, SAFRAN T4DS, ALL RIGHTS RESERVED                           */
/*                                                                            */
/* @file getters.c                                                            */
/* @author Hugo FOLCHER                                                       */
/*                                                                            */
/* ************************************************************************** */

#include "private.h"

#include "o2s/deque.h"

/** The number of elements currently held in the queue */
size_t deque_count(const deque_t* self)
{
	return self->count;
}

/** The maximum number of elements that can be stored */
size_t deque_capacity(const deque_t* self)
{
	return self->capacity;
}

/**
 * The current first element in the queue.
 * @return NULL if the queue is empty
 */
void* deque_first(const deque_t* self)
{
	if (deque_is_empty(self))
		return NULL;
	return self->front;
}

/**
 * The current last element in the queue.
 * @return NULL if the queue is empty
 */
void* deque_last(const deque_t* self)
{
	if (deque_is_empty(self))
		return NULL;
	return (self->back == deque_begin(self) ? deque_end(self) : self->back)
	       - deque_offset(self, 1);
}

/** True if no elements are currently stored */
bool deque_is_empty(const deque_t* self)
{
	return deque_count(self) == 0;
}

/** True if the queue reached its maximum capacity */
bool deque_is_full(const deque_t* self)
{
	return deque_count(self) == deque_capacity(self);
}

/**
 * The element of the element at an arbitrary index
 * @return NULL if the @p index is not a valid one
 */
void* deque_get(const deque_t* self, size_t index)
{
	if (index >= deque_count(self))
		return NULL;
	void* result = self->front + deque_offset(self, index);
	if (result >= deque_end(self))
		result -= deque_offset(self, deque_capacity(self));
	return result;
}
