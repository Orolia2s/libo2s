#pragma once

#include <stddef.h> // size_t

void* memcpy(void* dest, const void* src, size_t n);
int   memcmp(const void* a, const void* b, size_t n);
