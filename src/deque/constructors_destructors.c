/* ************************************************************************** */
/*      ____    _    _____ ____     _    _   _   _____ _  _   ____  ____      */
/*     / ___|  / \  |  ___|  _ \   / \  | \ | | |_   _| || | |  _ \/ ___|     */
/*     \___ \ / _ \ | |_  | |_) | / _ \ |  \| |   | | | || |_| | | \___ \     */
/*      ___) / ___ \|  _| |  _ < / ___ \| |\  |   | | |__   _| |_| |___) |    */
/*     |____/_/   \_|_|   |_| \_/_/   \_|_| \_|   |_|    |_| |____/|____/     */
/*                                                                            */
/**
 * @copyright 2023-2024, SAFRAN T4DS, ALL RIGHTS RESERVED
 * @file constructors_destructors.c
 * @author Hugo FOLCHER
 * @author Antoine GAGNIERE
 * @brief Create and destroy deques
 */
/* ************************************************************************** */

#include "o2s/deque.h"

#include <stdlib.h> //free

/** Contructs an deque, using externally owned memory */
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
