/* ************************************************************************** */
/*      ____    _    _____ ____     _    _   _   _____ _  _   ____  ____      */
/*     / ___|  / \  |  ___|  _ \   / \  | \ | | |_   _| || | |  _ \/ ___|     */
/*     \___ \ / _ \ | |_  | |_) | / _ \ |  \| |   | | | || |_| | | \___ \     */
/*      ___) / ___ \|  _| |  _ < / ___ \| |\  |   | | |__   _| |_| |___) |    */
/*     |____/_/   \_|_|   |_| \_/_/   \_|_| \_|   |_|    |_| |____/|____/     */
/*                                                                            */
/**
 * @copyright 2023-2024, SAFRAN T4DS, ALL RIGHTS RESERVED
 * @file getters.c
 * @author Hugo FOLCHER
 * @author Antoine GAGNIERE
 * @brief Expose the state of a deque
 */
/* ************************************************************************** */

#include "private.h"

#include "o2s/deque.h"
#include "o2s/preprocessing.h" // min

#include <iso646.h>            // or
#include <string.h>            // memcpy

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

/**
 * Peeks the @p count elements of the queue, starting with @p start.
 * @return false if there is less than @p start or @p start + @p count elements stored
 */
bool deque_get_n(const deque_t* self, void* destination, size_t start, size_t count)
{
	const void* begin;
	size_t      first_pass;
	size_t      first_pass_size;

	if (count == 0 or destination == NULL)
		return true;
	if ((begin = deque_get(self, start)) == NULL)
		return false;
	if (deque_count(self) < start + count)
		return false;

	first_pass = min(count, deque_distance(self, begin, deque_end(self)));
	first_pass_size = deque_offset(self, first_pass);
	memcpy(destination, begin, first_pass_size);

	if (first_pass < count)
		return deque_get_n(self, destination + first_pass_size, start + first_pass, count - first_pass);
	return true;
}
