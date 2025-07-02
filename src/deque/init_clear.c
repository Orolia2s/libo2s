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
 * @brief Create and empty deques
 */
/* ************************************************************************** */

#include "o2s/deque.h"

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

/** Discard all elements, but retain the capacity */
void deque_clear(deque_t* self)
{
	self->front = self->storage;
	self->back  = self->storage;
	self->count = 0;
}
