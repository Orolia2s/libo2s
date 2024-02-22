/* ************************************************************************** */
/*      ____    _    _____ ____     _    _   _   _____ _  _   ____  ____      */
/*     / ___|  / \  |  ___|  _ \   / \  | \ | | |_   _| || | |  _ \/ ___|     */
/*     \___ \ / _ \ | |_  | |_) | / _ \ |  \| |   | | | || |_| | | \___ \     */
/*      ___) / ___ \|  _| |  _ < / ___ \| |\  |   | | |__   _| |_| |___) |    */
/*     |____/_/   \_|_|   |_| \_/_/   \_|_| \_|   |_|    |_| |____/|____/     */
/*                                                                            */
/**
 * @copyright 2023-2024, SAFRAN T4DS, ALL RIGHTS RESERVED
 * @file to_string.c
 * @author Antoine GAGNIERE
 * @brief Convert numbers to string
 */
/* ************************************************************************** */

#include "o2s/to_string.h"

#include "o2s/preprocessing.h"

#include <ctype.h>    // isprint
#include <inttypes.h> // PRIi32
#include <iso646.h>   // not
#include <limits.h>   // INT_MAX
#include <stdio.h>    // snprintf
#include <string.h>   // strlen

/** Create a sring from a float */
string_t float_to_string(const float* value)
{
	string_t     result  = string_new();

	if (not string_reserve(&result, 20))
		return result;
	const int size = snprintf(result.start, result.capacity, "%g", *value);
	if (size > 0)
		result.count = (unsigned)size;
	return result;
}

/** Create a string from a double */
string_t double_to_string(const double* value)
{
	string_t     result  = string_new();

	if (not string_reserve(&result, 20))
		return result;
	const int size = snprintf(result.start, result.capacity, "%lg", *value);
	if (size > 0)
		result.count = (unsigned)size;
	return result;
}

/** Create a string from an integer */
string_t int_to_string(const int* value)
{
	string_t     result  = string_new();
	const size_t maxsize = strlen(LIBO2S_PREPRO_STRING(INT_MIN)) + 1;

	if (not string_reserve(&result, maxsize))
		return result;
	const int size = snprintf(result.start, maxsize, "%" PRIi32, *value);
	if (size > 0)
		result.count = (unsigned)size;
	return result;
}

/** Create a string from a short integer */
string_t short_to_string(const short* value)
{
	string_t     result  = string_new();
	const size_t maxsize = strlen(LIBO2S_PREPRO_STRING(SHORT_MIN)) + 1;

	if (not string_reserve(&result, maxsize))
		return result;
	const int size = snprintf(result.start, maxsize, "%" PRIi16, *value);
	if (size > 0)
		result.count = (unsigned)size;
	return result;
}

/** Create a string from a long integer */
string_t long_to_string(const long* value)
{
	string_t     result  = string_new();
	const size_t maxsize = strlen(LIBO2S_PREPRO_STRING(LONG_MIN)) + 1;

	if (not string_reserve(&result, maxsize))
		return result;
	const int size = snprintf(result.start, maxsize, "%" PRIi64, *value);
	if (size > 0)
		result.count = (unsigned)size;
	return result;
}

/** Create a string from an unsigned integer */
string_t unsigned_to_string(const unsigned* value)
{
	string_t     result  = string_new();
	const size_t maxsize = strlen(LIBO2S_PREPRO_STRING(UNSIGNED_MAX)) + 1;

	if (not string_reserve(&result, maxsize))
		return result;
	const int size = snprintf(result.start, maxsize, "%" PRIu32, *value);
	if (size > 0)
		result.count = (unsigned)size;
	return result;
}

/**
 * Create a string from a null-terminated character string.
 * If the parameter is the NULL pointer, the returned string
 * is `"(null)"`.
 */
string_t cstring_to_string(const char* const* value)
{
	if (*value == NULL)
		return string_from_literal("(null)");
	return string_from(*value, strlen(*value));
}

/**
 * Creates a string to represent the char pointed to by @p value.
 * If @p value is printable, it will be included directly, else a escape
 * sequence. In both cases surrounded by single quotes
 */
string_t char_to_string(const char* value)
{
	string_t result = string_from_literal("'");

	if (isprint(*value))
		string_append_char(&result, *value);
	else
	{
		string_append_char(&result, '\\');
		switch (*value)
		{
		case 0:
			string_append_char(&result, '0');
			break;
		case '\t':
			string_append_char(&result, 't');
			break;
		case '\n':
			string_append_char(&result, 'n');
			break;
		case '\r':
			string_append_char(&result, 'r');
			break;
		default:
			string_append_char(&result, 'x');
			if (*value >= 16)
				string_append_char(&result, "0123456789abcdef"[*value >> 4]);
			string_append_char(&result, "0123456789abcdef"[*value & 0xf]);
		}
	}
	string_append_char(&result, '\'');
	return result;
}

/**
 * Null-temrminated string from a boolean
 * @return
 * - `"true"` if the parameter is `true`
 * - `"false"` otherwise
 */
const char* boolean_to_cstring(bool value)
{
	return value ? "true" : "false";
}
