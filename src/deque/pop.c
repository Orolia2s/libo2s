/* ************************************************************************** */
/*      ____    _    _____ ____     _    _   _   _____ _  _   ____  ____      */
/*     / ___|  / \  |  ___|  _ \   / \  | \ | | |_   _| || | |  _ \/ ___|     */
/*     \___ \ / _ \ | |_  | |_) | / _ \ |  \| |   | | | || |_| | | \___ \     */
/*      ___) / ___ \|  _| |  _ < / ___ \| |\  |   | | |__   _| |_| |___) |    */
/*     |____/_/   \_|_|   |_| \_/_/   \_|_| \_|   |_|    |_| |____/|____/     */
/*                                                                            */
/**
 * @copyright 2023-2024, SAFRAN T4DS, ALL RIGHTS RESERVED
 * @file pop.c
 * @author Hugo FOLCHER
 * @author Antoine GAGNIERE
 * @brief Remove elements from deques
 */
/* ************************************************************************** */

#include "private.h"

#include "o2s/deque.h"
#include "o2s/preprocessing.h" // min

#include <string.h>            // memcpy

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
 * If destination is `NULL`, they will be discarded
 * @return false if there is less than @p count elements stored
 */
bool deque_pop_front_n(deque_t* self, void* destination, size_t count)
{
	size_t first_pass;
	size_t first_pass_size;

	if (count == 0)
		return true;
	if (deque_count(self) < count)
		return false;

	first_pass = min(count, deque_distance(self, self->front, deque_end(self)));
	first_pass_size = deque_offset(self, first_pass);
	if (destination != NULL)
	{
		memcpy(destination, self->front, first_pass_size);
		destination += first_pass_size;
	}
	self->front += first_pass_size;
	self->count -= first_pass;

	if (self->front == deque_end(self))
		self->front = deque_begin(self);
	if (first_pass < count)
		return deque_pop_front_n(self, destination, count - first_pass);
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
 * @return false if the queue contains less than @p count elements
 */
bool deque_pop_back_n(deque_t* self, void* destination, size_t count)
{
	if (deque_count(self) < count)
		return false;
	while (count-- > 0)
	{
		deque_pop_back(self, destination);
		destination += deque_offset(self, 1);
	}
	return true;
}
