/* ************************************************************************** */
/*      ____    _    _____ ____     _    _   _   _____ _  _   ____  ____      */
/*     / ___|  / \  |  ___|  _ \   / \  | \ | | |_   _| || | |  _ \/ ___|     */
/*     \___ \ / _ \ | |_  | |_) | / _ \ |  \| |   | | | || |_| | | \___ \     */
/*      ___) / ___ \|  _| |  _ < / ___ \| |\  |   | | |__   _| |_| |___) |    */
/*     |____/_/   \_|_|   |_| \_/_/   \_|_| \_|   |_|    |_| |____/|____/     */
/*                                                                            */
/* Copyright 2023, SAFRAN T4DS, ALL RIGHTS RESERVED                           */
/*                                                                            */
/* @file new.c                                                                */
/* @author Hugo FOLCHER                                                       */
/*                                                                            */
/* ************************************************************************** */

#include "o2s/array.h"
#include "private.h"

#include <iso646.h> // not

#include <string.h> // memcpy

/**
 * Adds one n elements at the end of the array.
 * @return false if allocation failed.
 */
bool array_push_back_n(array_t* self, void* elements, size_t count)
{
	if (not array_grow(self, count))
		return false;
	memcpy(array_end(self), elements, array_offset(self, count));
	self->count = self->count + count;
	return true;
}

/**
 * Adds one element at the end of the array.
 * @return false if allocation failed.
 */
bool array_push_back(array_t* self, void* element)
{
	return array_push_back_n(self, element, 1);
}

/**
 * Moves to destination the n last elements of the array.
 * @return false if not enough element in the array.
 */
bool array_pop_back_n(array_t* self, void* destination, size_t count)
{
	if (count > self->count)
		return false;
	void* source = (void*)self->start + array_offset(self, self->count - count);
	memcpy(destination, source, array_offset(self, count));
	self->count = self->count - count;
	return true;
}

/**
 * Moves to destination the last element of the array.
 * @return false if the array is empty.
 */
bool array_pop_back(array_t* self, void* destination)
{
	return array_pop_back_n(self, destination, 1);
}
