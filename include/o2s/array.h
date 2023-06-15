#pragma once

#include <stdbool.h>
#include <stddef.h>

typedef struct array
{
} array_t;

#define Array(T) array_new(sizeof(T))

array_t array_new(size_t type_size);

bool array_push_back(array_t* self, void* element);
bool array_push_back_n(array_t* self, void* elements, size_t count);

bool array_pop_back(array_t* self, void* destination);
bool array_pop_back_n(array_t* self, void* destination, size_t count);

bool array_reserve(array_t* self, size_t count);
bool array_clear(array_t* self);
