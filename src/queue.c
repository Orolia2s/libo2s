/* ************************************************************************** */
/*      ____    _    _____ ____     _    _   _   _____ _  _   ____  ____      */
/*     / ___|  / \  |  ___|  _ \   / \  | \ | | |_   _| || | |  _ \/ ___|     */
/*     \___ \ / _ \ | |_  | |_) | / _ \ |  \| |   | | | || |_| | | \___ \     */
/*      ___) / ___ \|  _| |  _ < / ___ \| |\  |   | | |__   _| |_| |___) |    */
/*     |____/_/   \_|_|   |_| \_/_/   \_|_| \_|   |_|    |_| |____/|____/     */
/*                                                                            */
/*
 * @copyright 2023, SAFRAN T4DS, ALL RIGHTS RESERVED
 * @file queue.c
 * @author Antoine GAGNIERE
 * @brief Realtime FIFO buffer
 */
/* ************************************************************************** */

#include "o2s/queue.h"

/** Release the allocated memory @see deque_free */
void queue_free(queue_t* self)
{
	deque_free(self);
}

/** Add a single element to the queue @see deque_push_back */
bool queue_push(queue_t* self, const void* element)
{
	return deque_push_back(self, element);
}

/** Add @p count elements to the queue @see deque_push_back_n */
bool queue_push_n(queue_t* self, const void* elements, size_t count)
{
	return deque_push_back_n(self, elements, count);
}

/** Pop the first element of the queue @see deque_pop_front */
bool queue_pop(queue_t* self, void* destination)
{
	return deque_pop_front(self, destination);
}

/** Pop the first @p count elements of the queue @see deque_pop_front_n */
bool queue_pop_n(queue_t* self, void* destination, size_t count)
{
	return deque_pop_front_n(self, destination, count);
}

/** Number of elements that can be added @see deque_room */
size_t queue_room(const queue_t* self)
{
	return deque_room(self);
}

/** Number of elements currently in the queue @see deque_count */
size_t queue_count(const queue_t* self)
{
	return deque_count(self);
}

/** Next element to be popped @see deque_first */
void* queue_first(const queue_t* self)
{
	return deque_first(self);
}

/** Access an arbitrary queue element @see deque_get */
void* queue_get(const queue_t* self, size_t index)
{
	return deque_get(self, index);
}
