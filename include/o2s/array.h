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

/** O2S array implemantation */
typedef struct array
{
	void*  start;
	size_t type_size;
	size_t count;
	size_t capacity;
} array_t;

array_t array_new(size_t type_size);
void    array_clear(array_t* self);

/** Convenient constructor wrapper */
#define ArrayNew(Type) array_new(sizeof(Type))

bool    array_push_back(array_t* self, void* element);
bool    array_push_back_n(array_t* self, void* elements, size_t count);

bool    array_pop_back(array_t* self, void* destination);
bool    array_pop_back_n(array_t* self, void* destination, size_t count);

void*   array_first(const array_t* self);
void*   array_last(const array_t* self);
void*   array_get(const array_t* self, size_t index);

bool    array_is_empty(const array_t* self);

bool    array_reserve(array_t* self, size_t count);
bool    array_trim(array_t* self);

/**
 * Iterate over the elements of the array.
 * To be used like a for loop
 */
#define array_foreach(T, A, E) \
	for (char* _pointer = (char*)array_first(A); \
	     _pointer <= (char*)array_last(A) && ((*(E) = *(T*)_pointer) || true); \
	     _pointer += (A)->type_size)

/**
 * Iterate over the elements of the array, with the index.
 * To be used like a for loop
 */
#define array_enumerate(T, A, E, I) \
	for (*(I) = 0; \
	     *(I) < (A)->count && ((*(E) = *(T*)array_get(A, *(I))) || true); \
	     (*(I))++)
