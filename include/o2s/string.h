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
 * @file string.h
 * @author Hugo FOLCHER
 * @author Antoine GAGNIERE
 * @brief Dynamic string implementation
 */
/* ************************************************************************** */

#include "o2s/array.h"

#include <stdbool.h> // bool
#include <stddef.h>  // size_t
#include <string.h>  // strlen

/**
 * A string is an array of `char`.
 * Note that it means that a string owns the memory.
 */
typedef array_t string_t;

string_t        string_new();
string_t        string_from(const char* cstring, size_t length);
void            string_clear(string_t* self);

/**
 * Allocates a string, copying the content from a C string.
 * Note that `strlen` of a literal can be computed at compile-time.
 * This function can technically also be used with run-time C string,
 * it's just better not to rely on null-termination too much.
 */
#define string_from_literal(StringLiteral) \
	string_from(StringLiteral, strlen(StringLiteral))

/**
 * Automatically free the allocated storage when going out of scope.
 *
 * In a situation where one wants to declare a string in a local scope,
 * this "typedef" can be used for that string to release the allocated memory
 * automatically when the variable goes out of scope.
 *
 * It means this "typedef" can only be used like this:
 * @code{.c}
 * {
 *     String my_string = string_new();
 *     ...
 * } // <- the underlying storage will be freed at that point
 * @endcode
 */
#define String __attribute__((cleanup(string_clear))) string_t

bool string_append_char(string_t* self, char character);
bool string_append_cstring(string_t* self, const char* cstring, size_t length);
bool string_append(string_t* self, const string_t* other);

/**
 * Copy the content of a C string to the end of this string.
 * Note that `strlen` of a literal can be computed at compile-time.
 * This function can technically also be used with run-time C string,
 * it's just better not to rely on null-termination too much.
 */
#define string_append_literal(Self, StringLiteral) \
	string_append_cstring(Self, StringLiteral, strlen(StringLiteral))

bool     string_pop(string_t* self, char* destination);
bool     string_pop_n(string_t* self, char* destination, size_t count);
string_t string_pop_as_string(string_t* self, size_t count);

size_t   string_length(const string_t* self);
char*    string_get(const string_t* self, size_t index);
bool     string_is_empty(const string_t* self);

bool     string_reserve(string_t* self, size_t count);
bool     string_trim(string_t* self);

string_t string_map(const string_t* self, char (*function)(char));
string_t string_tolower(const string_t* self);
string_t string_toupper(const string_t* self);

void     string_apply_inplace(string_t* self, char (*function)(char));
void     string_tolower_inplace(string_t* self);
void     string_toupper_inplace(string_t* self);

bool     string_is_equal(const string_t* self, const string_t* other);

char*    string_to_cstring(string_t* self);

/** Iterate over each character of the string */
#define string_foreach(STRING, Element) array_foreach (char, STRING, Element)

/** Iterate over each character of the string with its index */
#define string_enumerate(STRING, Element, Index) \
	array_enumerate (char, STRING, Element, Index)
