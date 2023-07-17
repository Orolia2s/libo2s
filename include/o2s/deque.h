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
/* @author Hugo FOLCHER                                                   */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h> // bool
#include <stddef.h>  // size_t

/**
 * O2S deque implemantation.
 */
typedef struct deque
{
	void*  data;
	void*  first;
	size_t first_index;
	void*  end;
	size_t end_index;
	size_t count;
	size_t type_size;
	size_t capacity;
} deque_t;

#define Deque(Pointer, Type, Capacity) \
	deque_new(Pointer, sizeof(Type), Capacity)

deque_t deque_new(void* p, size_t type_size, size_t capacity);
size_t  deque_count(deque_t* self);
void*  deque_first(deque_t* self);
bool    deque_is_empty(deque_t* self);
size_t  deque_capacity(deque_t* self);
size_t  deque_room(deque_t* self);
bool    deque_push_front(deque_t* self, void* element);
bool    deque_push_front_n(deque_t* self, void* elements, size_t count);
bool    deque_pop_front(deque_t* self, void* element);
bool    deque_pop_front_n(deque_t* self, void* destination, size_t count);
bool    deque_push_back(deque_t* self, void* destination);
bool    deque_push_back_n(deque_t* self, void* elements, size_t count);
bool    deque_pop_back(deque_t* self, void* destination);
bool    deque_pop_back_n(deque_t* self, void* destination, size_t count);
bool    deque_intent(deque_t* self, char intent);
void    deque_clear(deque_t* self);
void    deque_free(deque_t* self);
void deque_iter(deque_t* self, void (*f)());