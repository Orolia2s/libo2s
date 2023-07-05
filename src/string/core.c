/* ************************************************************************** */
/*      ____    _    _____ ____     _    _   _   _____ _  _   ____  ____      */
/*     / ___|  / \  |  ___|  _ \   / \  | \ | | |_   _| || | |  _ \/ ___|     */
/*     \___ \ / _ \ | |_  | |_) | / _ \ |  \| |   | | | || |_| | | \___ \     */
/*      ___) / ___ \|  _| |  _ < / ___ \| |\  |   | | |__   _| |_| |___) |    */
/*     |____/_/   \_|_|   |_| \_/_/   \_|_| \_|   |_|    |_| |____/|____/     */
/*                                                                            */
/* Copyright 2023, SAFRAN T4DS, ALL RIGHTS RESERVED                           */
/*                                                                            */
/* @file string.c                                                             */
/* @author Hugo FOLCHER                                                       */
/*                                                                            */
/* ************************************************************************** */

#include "o2s/array.h"
#include "o2s/string.h"

/**
 * Contructs a string.
 */
string_t string_new(void)
{
	return (string_t)array_new(sizeof(char));
}

/**
 * Adds one element at the end of the string.
 * @return false if allocation failed.
 */
bool string_append(string_t* self, char* element)
{
	return array_push_back((array_t*)self, (void*)element);
}

/**
 * Adds one n elements at the end of the string.
 * @return false if allocation failed.
 */
bool string_append_n(string_t* self, char* element, size_t count)
{
	return array_push_back_n((array_t*)self, (void*)element, count);
}

/**
 * Moves to destination the last element of the string.
 * @return false if the string is empty.
 */
bool string_pop(string_t* self, char* destination)
{
	return array_pop_back((array_t*)self, (void*)destination);
}

/**
 * Moves to destination the n last elements of the string.
 * Destination can be NULL to just discard the elements.
 * @return false if not enough element in the string.
 */
bool string_pop_n(string_t* self, char* destination, size_t count)
{
	return array_pop_back_n((array_t*)self, (void*)destination, count);
}

/**
 * Pointer of the element at position 'index' of the string.
 * @return NULL if invalid index.
 */
void* string_get(string_t* self, size_t index)
{
	return array_get((array_t*)self, index);
}

/**
 * True if the string contains no element.
 */
bool string_is_empty(string_t* self)
{
	return array_is_empty((array_t*)self);
}

/**
 * Forces allocation to handle 'count' new elements.
 * @return false if allocation failed.
 */
bool string_reserve(string_t* self, size_t count)
{
	return array_reserve((array_t*)self, count);
}

/**
 * Clears properly the string.
 */
void string_clear(string_t* self)
{
	return array_clear((array_t*)self);
}

/**
 * Resizes the underlying storage to match current elements count.
 * @return false if allocation failed.
 */
bool string_trim(string_t* self)
{
	return array_trim((array_t*)self);
}