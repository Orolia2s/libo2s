#pragma once

/* ************************************************************************** */
/*      ____    _    _____ ____     _    _   _   _____ _  _   ____  ____      */
/*     / ___|  / \  |  ___|  _ \   / \  | \ | | |_   _| || | |  _ \/ ___|     */
/*     \___ \ / _ \ | |_  | |_) | / _ \ |  \| |   | | | || |_| | | \___ \     */
/*      ___) / ___ \|  _| |  _ < / ___ \| |\  |   | | |__   _| |_| |___) |    */
/*     |____/_/   \_|_|   |_| \_/_/   \_|_| \_|   |_|    |_| |____/|____/     */
/*                                                                            */
/**
 * @copyright 2023, SAFRAN T4DS, ALL RIGHTS RESERVED
 * @file array.h
 * @author Antoine GAGNIERE
 * @author Hugo FOLCHER
 * @brief Dynamic array
 */
/* ************************************************************************** */

#include <stdbool.h> // bool
#include <stddef.h>  // size_t

/** O2S array implementation */
typedef struct array
{
	void*  start;     /**< Underlying storage */
	size_t type_size; /**< Size in bytes of a single element */
	size_t count;     /**< Number of elements currently stored */
	size_t capacity;  /**< Number of elements that can fit in the storage */
} array_t;

/** @name Initializing and destroying */
///@{
array_t array_new(size_t type_size);
void    array_clear(array_t* self);
void    array_clear_f(array_t* self, void (*cleanup)());

/** Convenient constructor wrapper */
#define ArrayNew(Type) array_new(sizeof(Type))

/**
 * Automatically free the allocated storage when going out of scope.
 *
 * In a situation where one wants to declare an array in a local scope,
 * this "typedef" can be used for that array to release the allocated memory
 * automatically when the variable goes out of scope.
 *
 * It means this "typedef" can only be used like this:
 * @code{.c}
 * {
 *     Array my_array = ArrayNew(float);
 *     ...
 * } // <- the underlying storage will be freed at that point
 * @endcode
 */
#define Array          __attribute__((cleanup(array_clear))) array_t
///@}

/** @name Modifiers */
///@{
bool   array_push_back(array_t* self, const void* element);
bool   array_push_back_n(array_t* self, const void* elements, size_t count);

bool   array_pop_back(array_t* self, void* destination);
bool   array_pop_back_n(array_t* self, void* destination, size_t count);

bool   array_pop_front(array_t* self, void* destination);
bool   array_pop_front_n(array_t* self, void* destination, size_t count);
///@}

/** @name Element access */
///@{
void*  array_first(const array_t* self);
void*  array_last(const array_t* self);
void*  array_get(const array_t* self, size_t index);
void*  array_end(const array_t* self);
///@}

/** @name Capacity */
///@{
bool   array_is_empty(const array_t* self);

size_t array_count(const array_t* self);
bool   array_reserve(array_t* self, size_t count);
bool   array_trim(array_t* self);
///@}

/** @name Iterators */
///@{
void   array_iter(const array_t* self, void (*function)());

/**
 * Iterate over the elements of the array.
 * To be used like a for loop
 */
#define array_foreach(TYPE, ARRAY, ELEMENT) \
	for (char* _pointer = (char*)array_first(ARRAY); \
	     _pointer <= (char*)array_last(ARRAY) && ((*(ELEMENT) = *(TYPE*)_pointer), true); \
	     _pointer += (ARRAY)->type_size)

/**
 * Iterate over the elements of the array, with the index.
 * To be used like a for loop
 */
#define array_enumerate(TYPE, ARRAY, ELEMENT, INDEX) \
	for (*(INDEX) = 0; *(INDEX) < array_count(ARRAY) \
	                   && ((*(ELEMENT) = *(TYPE*)array_get(ARRAY, *(INDEX))), true); \
	     (*(INDEX))++)
///@}
