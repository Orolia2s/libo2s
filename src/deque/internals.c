/* ************************************************************************** */
/*      ____    _    _____ ____     _    _   _   _____ _  _   ____  ____      */
/*     / ___|  / \  |  ___|  _ \   / \  | \ | | |_   _| || | |  _ \/ ___|     */
/*     \___ \ / _ \ | |_  | |_) | / _ \ |  \| |   | | | || |_| | | \___ \     */
/*      ___) / ___ \|  _| |  _ < / ___ \| |\  |   | | |__   _| |_| |___) |    */
/*     |____/_/   \_|_|   |_| \_/_/   \_|_| \_|   |_|    |_| |____/|____/     */
/*                                                                            */
/* Copyright 2023, SAFRAN T4DS, ALL RIGHTS RESERVED                           */
/*                                                                            */
/* @file internals.c                                                          */
/* @author Antoine GAGNIERE                                                   */
/*                                                                            */
/* ************************************************************************** */

#include "o2s/deque.h"
#include "private.h"

/** The size in memory of @p count elements */
size_t deque_offset(const deque_t* self, size_t count)
{
	return (count * self->type_size);
}

/** The remaining number of elements that can be added */
size_t deque_room(const deque_t* self)
{
	return deque_capacity(self) - deque_count(self);
}

/** Pointer to the start of the underlying storage */
void* deque_begin(const deque_t* self)
{
	return self->storage;
}

/** Pointer one-past-the-end of the underlying storage */
void* deque_end(const deque_t* self)
{
	return deque_begin(self) + deque_offset(self, deque_capacity(self));
}

/** The next slot */
void* deque_pointer_after(const deque_t* self, void* pointer)
{
	pointer += deque_offset(self, 1);
	if (pointer == deque_end(self))
		pointer = deque_begin(self);
	return pointer;
}

/** The previous slot */
void* deque_pointer_before(const deque_t* self, void* pointer)
{
	if (pointer == deque_begin(self))
		pointer = deque_end(self);
	return pointer - deque_offset(self, 1);
}

/** Number of elements in the range delimited by the two provided elements */
size_t deque_distance(const deque_t* self, void* one, void* two)
{
	return (one > two ? one - two : two - one) / self->type_size;
}
