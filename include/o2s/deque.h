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
	void*        first;
	size_t       first_index;
	void*        last;
	size_t       last_index;
	const size_t type_size;
	const size_t capacity;
} deque_t;

#define Deque(Type, Capacity) deque_new(sizeof(Type), Capacity)

deque_t deque_new(size_t type_size, size_t capacity);

void    deque_push_front(deque_t* self, void* element);
void    deque_push_front_n(deque_t* self, void* elements, size_t count);

void    deque_push_back(deque_t* self, void* element);
bool    deque_push_back_n(deque_t* self, void* elements, size_t count);

// void    deque_pop_front(deque_t* self, void* destination);
// void    deque_pop_front_n(deque_t* self, void* destination, size_t count);

// void    deque_pop_back(deque_t* self, void* destination);
// void    deque_pop_back_n(deque_t* self, void* destination, size_t count);

// void    deque_clear(deque_t* self);
