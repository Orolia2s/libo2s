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

#include "o2s/deque.h"
#include "private.h"

/** The size in memory of @p count elements */
size_t deque_offset(const deque_t* self, size_t count)
{
	return (count * self->type_size);
}

/** The number of elements currently held in the queue */
size_t deque_count(const deque_t* self)
{
	return self->count;
}

/**
 * Gives the current first element in the queue.
 * @return NULL if the queue is empty
 */
void* deque_first(const deque_t* self)
{
	if (deque_is_empty(self))
		return NULL;
	return (self->first);
}

/** Tells if deque is empty or not. */
bool deque_is_empty(const deque_t* self)
{
	return (deque_count(self) == 0);
}

/** The maximum number of elements that can be stored */
size_t deque_capacity(const deque_t* self)
{
	return self->capacity;
}

/** The remaining number of elements that can be added */
size_t deque_room(const deque_t* self)
{
	return (self->capacity - deque_count(self));
}

/** The number of slots between the given index and the right border of allocated space */
size_t deque_right_distance(const deque_t* self, size_t index)
{
	return (self->capacity - index);
}

/**
 * Shift a given index consistently i.e applying the correct modulo.
 * @return new index after the shift.
 */
size_t deque_index_shift(const deque_t* self, size_t index, int shift)
{
	return ((self->capacity + index + shift) % self->capacity);
}
