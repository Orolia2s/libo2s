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

/**
 * Double-ended queue
 */
typedef struct deque
{
	void*  data;        /**< Memory area */
	void*  first;       /**< Pointer to the front of the queue */
	size_t first_index; /**/
	void*  end;         /**< Pointer past-the-end of the queue */
	size_t end_index;   /**/
	size_t count;       /**< Number of elements currently stored */
	size_t type_size;   /**< Size in bytes of a single element */
	size_t capacity;    /**< Maximum number of elements that can be stored */
} deque_t;

deque_t deque_new(void* p, size_t type_size, size_t capacity);
void    deque_clear(deque_t* self);

#define DequeNew(Pointer, Type, Capacity) \
	deque_new(Pointer, sizeof(Type), Capacity)

deque_t deque_allocate(size_t type_size, size_t capacity);
void    deque_free(deque_t* self);

void*   deque_first(const deque_t* self);
void*   deque_last(const deque_t* self);

bool    deque_is_empty(const deque_t* self);
size_t  deque_count(const deque_t* self);
size_t  deque_capacity(const deque_t* self);
size_t  deque_room(const deque_t* self);

bool    deque_push_front(deque_t* self, void* element);
bool    deque_push_front_n(deque_t* self, void* elements, size_t count);
bool    deque_pop_front(deque_t* self, void* element);
bool    deque_pop_front_n(deque_t* self, void* destination, size_t count);

bool    deque_push_back(deque_t* self, void* destination);
bool    deque_push_back_n(deque_t* self, void* elements, size_t count);
bool    deque_pop_back(deque_t* self, void* destination);
bool    deque_pop_back_n(deque_t* self, void* destination, size_t count);

void    deque_iter(deque_t* self, void (*f)());
void    deque_iter1(deque_t* self, void (*f)(), void* ext);
void    deque_iter2(deque_t* self, void (*f)(), void* ext1, void* ext2);
