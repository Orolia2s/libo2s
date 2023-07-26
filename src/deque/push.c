/* ************************************************************************** */
/*      ____    _    _____ ____     _    _   _   _____ _  _   ____  ____      */
/*     / ___|  / \  |  ___|  _ \   / \  | \ | | |_   _| || | |  _ \/ ___|     */
/*     \___ \ / _ \ | |_  | |_) | / _ \ |  \| |   | | | || |_| | | \___ \     */
/*      ___) / ___ \|  _| |  _ < / ___ \| |\  |   | | |__   _| |_| |___) |    */
/*     |____/_/   \_|_|   |_| \_/_/   \_|_| \_|   |_|    |_| |____/|____/     */
/*                                                                            */
/* Copyright 2023, SAFRAN T4DS, ALL RIGHTS RESERVED                           */
/*                                                                            */
/* @file push.c                                                               */
/* @author Hugo FOLCHER                                                       */
/*                                                                            */
/* ************************************************************************** */

#include "o2s/deque.h"
#include "o2s/preprocessing.h" // min
#include "private.h"

#include <iso646.h> // not

#include <stdint.h> // uint8_t
#include <string.h> // memcpy

/**
 * Inserts an element to the front of the queue.
 * @return false if the queue is already full
 */
bool deque_push_front(deque_t* self, const void* element)
{
	if (deque_is_full(self))
		return false;
	self->front = deque_pointer_before(self, self->front);
	memcpy(self->front, element, deque_offset(self, 1));
	self->count += 1;
	return true;
}

/**
 * Inserts @p count elements to the front of the queue.
 * @return false if there isn't enough capacity to fit @p count more elements
 */
bool deque_push_front_n(deque_t* self, const void* elements, size_t count)
{
	if (count > deque_room(self))
		return false;
	while (count --> 0)
	{
		deque_push_front(self, elements);
		elements += deque_offset(self, 1);
	}
	return true;
}

/**
 * Inserts an element to the back of the queue.
 * @return false if the queue is already full
 */
bool deque_push_back(deque_t* self, const void* element)
{
	return deque_push_back_n(self, element, 1);
}

/**
 * Inserts @p count elements to the back of the queue.
 * @return false if there isn't enough capacity to fit @p count more elements
 */
bool deque_push_back_n(deque_t* self, const void* elements, size_t count)
{
	size_t first_pass;
	size_t first_pass_size;

	if (count > deque_room(self))
		return false;
	first_pass = min(count, deque_distance(self, self->back, deque_end(self)));
	first_pass_size = deque_offset(self, first_pass);
	memcpy(self->back, elements, first_pass_size);
	self->back += first_pass_size;
	self->count += first_pass;
	if (first_pass < count)
	{
		self->back = deque_begin(self);
		deque_push_back_n(self, elements + first_pass_size, count - first_pass);
	}
	return true;
}
