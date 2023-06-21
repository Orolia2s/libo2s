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
/* @file array.h                                                              */
/* @author Antoine GAGNIERE                                                   */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h> // bool
#include <stddef.h>  // size_t

/**
 * O2S array implemantation.
 */
typedef struct array
{
	void*        start;
	const size_t type_size;
	size_t       count;
	size_t       capacity;
} array_t;

#define Array(T) array_new(sizeof(T))

array_t array_new(size_t type_size);

bool    array_push_back(array_t* self, void* element);
bool    array_push_back_n(array_t* self, void* elements, size_t count);

bool    array_pop_back(array_t* self, void* destination);
bool    array_pop_back_n(array_t* self, void* destination, size_t count);

void*   array_first(array_t* self);
void*   array_last(array_t* self);
void*   array_get(array_t* self, size_t index);

bool    array_reserve(array_t* self, size_t count);
void    array_clear(array_t* self);
bool    array_trim(array_t* self);

#define array_foreach(T, A, E) \
	for (size_t _i = 0; \
	     *E = *(T*)((char*)(A)->start + _i * (A)->type_size), _i < (A)->count; \
	     _i++)
#define array_enumerate(T, A, E, I) \
	for (size_t _i = 0; \
	     *E = *(T*)((char*)(A)->start + _i * (A)->type_size), *I = _i, _i < (A)->count; \
	     _i++)
