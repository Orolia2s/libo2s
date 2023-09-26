/* ************************************************************************** */
/*      ____    _    _____ ____     _    _   _   _____ _  _   ____  ____      */
/*     / ___|  / \  |  ___|  _ \   / \  | \ | | |_   _| || | |  _ \/ ___|     */
/*     \___ \ / _ \ | |_  | |_) | / _ \ |  \| |   | | | || |_| | | \___ \     */
/*      ___) / ___ \|  _| |  _ < / ___ \| |\  |   | | |__   _| |_| |___) |    */
/*     |____/_/   \_|_|   |_| \_/_/   \_|_| \_|   |_|    |_| |____/|____/     */
/*                                                                            */
/* Copyright 2023, SAFRAN T4DS, ALL RIGHTS RESERVED                           */
/*                                                                            */
/* @file reserve.c                                                            */
/* @author Tanguy BERTHOUD                                                    */
/*                                                                            */
/* ************************************************************************** */

#include "o2s/deque.h"

#include <stdlib.h> // reallocarray

/**
 * Reallocates the deque if @p count elements cannot fit in the current
 * allocation. If the reallocation failed, the capacity will be set to zero.
 */
void deque_reserve(deque_t* self, size_t count)
{
	size_t room = deque_room(self);
	if (room < count)
	{
		size_t new_capacity = self->capacity + count;
		self->storage = reallocarray(self->storage, new_capacity, self->type_size);
		if (self->storage == NULL)
			new_capacity = 0;
		self->capacity = new_capacity;
	}
}