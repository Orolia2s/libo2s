/* ************************************************************************** */
/*      ____    _    _____ ____     _    _   _   _____ _  _   ____  ____      */
/*     / ___|  / \  |  ___|  _ \   / \  | \ | | |_   _| || | |  _ \/ ___|     */
/*     \___ \ / _ \ | |_  | |_) | / _ \ |  \| |   | | | || |_| | | \___ \     */
/*      ___) / ___ \|  _| |  _ < / ___ \| |\  |   | | |__   _| |_| |___) |    */
/*     |____/_/   \_|_|   |_| \_/_/   \_|_| \_|   |_|    |_| |____/|____/     */
/*                                                                            */
/**
 * @copyright 2023-2025, SAFRAN T4DS, ALL RIGHTS RESERVED
 * @file
 * @author Hugo FOLCHER
 * @author Antoine GAGNIERE
 * @brief Create and destroy deques on the heap
 */
/* ************************************************************************** */

#include "o2s/deque.h"

#include <stdlib.h> // free

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

/** Frees properly the deque */
void deque_free(deque_t* self)
{
	if (self->storage != NULL)
		free(self->storage);
	self->storage = NULL;
	deque_clear(self);
	self->capacity = 0;
}
