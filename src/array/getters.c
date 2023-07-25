/* ************************************************************************** */
/*      ____    _    _____ ____     _    _   _   _____ _  _   ____  ____      */
/*     / ___|  / \  |  ___|  _ \   / \  | \ | | |_   _| || | |  _ \/ ___|     */
/*     \___ \ / _ \ | |_  | |_) | / _ \ |  \| |   | | | || |_| | | \___ \     */
/*      ___) / ___ \|  _| |  _ < / ___ \| |\  |   | | |__   _| |_| |___) |    */
/*     |____/_/   \_|_|   |_| \_/_/   \_|_| \_|   |_|    |_| |____/|____/     */
/*                                                                            */
/* Copyright 2023, SAFRAN T4DS, ALL RIGHTS RESERVED                           */
/*                                                                            */
/* @file getters.c                                                            */
/* @author Hugo FOLCHER                                                       */
/*                                                                            */
/* ************************************************************************** */

#include "o2s/array.h"
#include "private.h"

/** One-past-the-end pointer of the array */
void* array_end(const array_t* self)
{
	return ((void*)self->start + array_offset(self, self->count));
}

/**
 * Pointer to the first element of the array.
 * @return NULL if the array is empty.
 */
void* array_first(const array_t* self)
{
	return array_get(self, 0);
}

/**
 * Pointer of the last element of the array.
 * @return NULL if the array is empty.
 */
void* array_last(const array_t* self)
{
	if (array_is_empty(self))
		return NULL;
	return array_get(self, self->count - 1);
}

/**
 * Pointer of the element at position @p index of the array.
 * @return NULL if invalid index.
 */
void* array_get(const array_t* self, size_t index)
{
	if (index >= self->count)
		return NULL;
	return self->start + array_offset(self, index);
}

/** True if the array contains no element. */
bool array_is_empty(const array_t* self)
{
	return self->count == 0;
}
