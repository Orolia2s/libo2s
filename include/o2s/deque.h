#pragma once

/* ************************************************************************** */
/*      ____    _    _____ ____     _    _   _   _____ _  _   ____  ____      */
/*     / ___|  / \  |  ___|  _ \   / \  | \ | | |_   _| || | |  _ \/ ___|     */
/*     \___ \ / _ \ | |_  | |_) | / _ \ |  \| |   | | | || |_| | | \___ \     */
/*      ___) / ___ \|  _| |  _ < / ___ \| |\  |   | | |__   _| |_| |___) |    */
/*     |____/_/   \_|_|   |_| \_/_/   \_|_| \_|   |_|    |_| |____/|____/     */
/*                                                                            */
/* Copyright 2023, SAFRAN T4DS, ALL RIGHTS RESERVED                           */
/*                                                                            */
/* @file deque.h                                                              */
/* @author Hugo FOLCHER                                                       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h> // bool
#include <stddef.h>  // size_t

/** Double-ended queue */
typedef struct deque
{
	void*  storage;   /**< Memory area */
	void*  front;     /**< Pointer to the front of the queue */
	void*  back;      /**< Pointer past-the-end of the queue */
	size_t count;     /**< Number of elements currently stored */
	size_t capacity;  /**< Maximum number of elements that can be stored */
	size_t type_size; /**< Size in bytes of a single element */
} deque_t;

deque_t deque_new(void* storage, size_t capacity, size_t type_size);
void    deque_clear(deque_t* self);
void    deque_clear_f(deque_t* self, void (*cleanup)());

/** Wrapper arround the non-owning constructor */
#define DequeNew(Storage, Capacity, Type) \
	deque_new(Storage, Capacity, sizeof(Type))

deque_t deque_allocate(size_t capacity, size_t type_size);
void    deque_free(deque_t* self);
void    deque_free_f(deque_t* self, void (*cleanup)());

/** Wrapper around the owning constructor */
#define DequeAllocate(Capacity, Type) deque_allocate(Capacity, sizeof(Type))

/**
 * Automatically free the alloacted storage when going out of scope.
 *
 * In a situation where one wants to declare a Deque in a local scope,
 * this "typedef" can be used for that Deque to release the allocated memory
 * automatically when the variable goes out of scope.
 *
 * It means this "typedef" can only be used like this:
 * @code{.c}
 * {
 *     Deque my_deque = DequeAllocate(512, float);
 *     ...
 * } // <- the underlying storage will be freed at that point
 * @endcode
 */
#define Deque                         __attribute__((cleanup(deque_free))) deque_t

void*  deque_first(const deque_t* self);
void*  deque_last(const deque_t* self);
void*  deque_get(const deque_t* self, size_t index);

bool   deque_is_empty(const deque_t* self);
bool   deque_is_full(const deque_t* self);

size_t deque_count(const deque_t* self);
size_t deque_capacity(const deque_t* self);
size_t deque_room(const deque_t* self);

bool   deque_push_front(deque_t* self, const void* element);
bool   deque_push_front_n(deque_t* self, const void* elements, size_t count);
bool   deque_pop_front(deque_t* self, void* element);
bool   deque_pop_front_n(deque_t* self, void* destination, size_t count);

bool   deque_push_back(deque_t* self, const void* destination);
bool   deque_push_back_n(deque_t* self, const void* elements, size_t count);
bool   deque_pop_back(deque_t* self, void* destination);
bool   deque_pop_back_n(deque_t* self, void* destination, size_t count);

void   deque_iter(const deque_t* self, void (*f)());
void   deque_iter1(const deque_t* self, void (*f)(), void* ext);
void   deque_iter2(const deque_t* self, void (*f)(), void* ext1, void* ext2);

/**
 * Iterate over the elements of the queue.
 * To be used like a for loop
 */
#define deque_foreach(T, A, E) \
	for (unsigned _i = 0; _i < deque_count(A) && ((*(E) = *(T*)deque_get(A, _i)) || true); _i++)

/**
 * Iterate over the elements of the queue, with the index.
 * To be used like a for loop
 */
#define deque_enumerate(T, A, E, I) \
	for (*(I) = 0; *(I) < deque_count(A) && ((*(E) = *(T*)deque_get(A, *(I))) || true); \
	     (*(I))++)
