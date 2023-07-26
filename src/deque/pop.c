/* ************************************************************************** */
/*      ____    _    _____ ____     _    _   _   _____ _  _   ____  ____      */
/*     / ___|  / \  |  ___|  _ \   / \  | \ | | |_   _| || | |  _ \/ ___|     */
/*     \___ \ / _ \ | |_  | |_) | / _ \ |  \| |   | | | || |_| | | \___ \     */
/*      ___) / ___ \|  _| |  _ < / ___ \| |\  |   | | |__   _| |_| |___) |    */
/*     |____/_/   \_|_|   |_| \_/_/   \_|_| \_|   |_|    |_| |____/|____/     */
/*                                                                            */
/* Copyright 2023, SAFRAN T4DS, ALL RIGHTS RESERVED                           */
/*                                                                            */
/* @file pop.c                                                                */
/* @author Hugo FOLCHER                                                       */
/*                                                                            */
/* ************************************************************************** */

#include "o2s/deque.h"
#include "o2s/preprocessing.h" // min
#include "private.h"

#include <iso646.h> // not

#include <stdint.h> //uint8_t
#include <string.h> // memcpy

/**
 * Pops the front-most element of the queue, copying it to destination.
 * If destination is `NULL`, it will be discarded
 * @return false if the queue is empty
 */
bool deque_pop_front(deque_t* self, void* destination)
{
	if (deque_is_empty(self))
		return false;
	if (destination != NULL)
		memcpy(destination, self->front, deque_offset(self, 1));
	self->front = deque_pointer_after(self, self->front);
	self->count -= 1;
	return true;
}

/**
 * Pops the @p count first elements of the queue.
 * @return false if there is less than @p count elements stored
 */
bool deque_pop_front_n(deque_t* self, void* destination, size_t count)
{
	size_t first_pass;
	size_t first_pass_size;

	if (deque_count(self) < count)
		return false;
	first_pass = min(count, deque_distance(self, self->front, deque_end(self)));
	first_pass_size = deque_offset(self, first_pass);
	memcpy(destination, self->front, first_pass_size);
	self->front += first_pass_size;
	self->count -= first_pass;
	if (first_pass < count)
	{
		self->front = deque_begin(self);
		deque_pop_front_n(self, destination + first_pass_size, count - first_pass);
	}
	return true;
}

/**
 * Pops the last element in the queue.
 * @return false if the queue is empty
 */
bool deque_pop_back(deque_t* self, void* destination)
{
	if (deque_is_empty(self))
		return false;
	self->back = deque_pointer_before(self, self->back);
	if (destination != NULL)
		memcpy(destination, self->back, deque_offset(self, 1));
	self->count -= 1;
	return true;
}

/**
 * Pops the @p count last elements in the queue.
 */
bool deque_pop_back_n(deque_t* self, void* destination, size_t count)
{
	if (deque_count(self) < count)
		return false;
	while (count --> 0)
	{
		deque_pop_back(self, destination);
		destination += deque_offset(self, 1);
	}
	return true;
}
