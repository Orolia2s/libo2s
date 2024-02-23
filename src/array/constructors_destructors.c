/* ************************************************************************** */
/*      ____    _    _____ ____     _    _   _   _____ _  _   ____  ____      */
/*     / ___|  / \  |  ___|  _ \   / \  | \ | | |_   _| || | |  _ \/ ___|     */
/*     \___ \ / _ \ | |_  | |_) | / _ \ |  \| |   | | | || |_| | | \___ \     */
/*      ___) / ___ \|  _| |  _ < / ___ \| |\  |   | | |__   _| |_| |___) |    */
/*     |____/_/   \_|_|   |_| \_/_/   \_|_| \_|   |_|    |_| |____/|____/     */
/*                                                                            */
/**
 * @copyright 2023, SAFRAN T4DS, ALL RIGHTS RESERVED
 * @file constructors_destructors.c
 * @author Antoine GAGNIERE
 * @brief Create and destroy dynamic arrays
 */
/* ************************************************************************** */

#include "private.h"

#include "o2s/array.h"

#include <stdlib.h> // free

/** Contructs an empty array, no memory is allocated */
array_t array_new(size_t type_size)
{
	return (array_t){.start = NULL, .type_size = type_size, .count = 0, .capacity = 0};
}

/**
 * Clears properly the array.
 * Frees the underlying storage,
 * and leaves the array in a usable state
 */
void array_clear(array_t* self)
{
	if (self->start)
		free(self->start);
	self->count    = 0;
	self->capacity = 0;
	self->start    = NULL;
}

/**
 * Release the resources of each elements before clearing the array.
 * In the case of an array storing elements that own resources,
 * each element should be cleaned up before the array is emptied.
 */
void array_clear_f(array_t* self, void (*cleanup)(void*))
{
	array_iter(self, cleanup);
	array_clear(self);
}
