/* ************************************************************************** */
/*      ____    _    _____ ____     _    _   _   _____ _  _   ____  ____      */
/*     / ___|  / \  |  ___|  _ \   / \  | \ | | |_   _| || | |  _ \/ ___|     */
/*     \___ \ / _ \ | |_  | |_) | / _ \ |  \| |   | | | || |_| | | \___ \     */
/*      ___) / ___ \|  _| |  _ < / ___ \| |\  |   | | |__   _| |_| |___) |    */
/*     |____/_/   \_|_|   |_| \_/_/   \_|_| \_|   |_|    |_| |____/|____/     */
/*                                                                            */
/* Copyright 2023, SAFRAN T4DS, ALL RIGHTS RESERVED                           */
/*                                                                            */
/* @file integers.c                                                           */
/* @author Antoine GAGNIERE                                                   */
/*                                                                            */
/* ************************************************************************** */

#include "o2s/preprocessing.h"
#include "o2s/to_string.h"

#include <inttypes.h> // PRIi32
#include <iso646.h>   // not
#include <limits.h>   // INT_MAX
#include <stdio.h>    // snprintf
#include <string.h>   // strlen

string_t int_to_string(const int* value)
{
	string_t       result  = string_new();
	const size_t   maxsize = strlen(LIBO2S_PREPRO_STRING(INT_MIN)) + 1;

	if (not string_reserve(&result, maxsize)) return result;
	const int size = snprintf(result.start, maxsize, "%" PRIi32, *value);
	if (size > 0)
		result.count = (unsigned)size;
	return result;
}

string_t short_to_string(const short* value)
{
	string_t       result  = string_new();
	const size_t   maxsize = strlen(LIBO2S_PREPRO_STRING(SHORT_MIN)) + 1;

	if (not string_reserve(&result, maxsize)) return result;
	const int size = snprintf(result.start, maxsize, "%" PRIi16, *value);
	if (size > 0)
		result.count = (unsigned)size;
	return result;
}

string_t long_to_string(const long* value)
{
	string_t       result  = string_new();
	const size_t   maxsize = strlen(LIBO2S_PREPRO_STRING(LONG_MIN)) + 1;

	if (not string_reserve(&result, maxsize)) return result;
	const int size = snprintf(result.start, maxsize, "%" PRIi64, *value);
	if (size > 0)
		result.count = (unsigned)size;
	return result;
}

string_t unsigned_to_string(const unsigned* value)
{
	string_t       result  = string_new();
	const size_t   maxsize = strlen(LIBO2S_PREPRO_STRING(UNSIGNED_MAX)) + 1;

	if (not string_reserve(&result, maxsize)) return result;
	const int size = snprintf(result.start, maxsize, "%" PRIu32, *value);
	if (size > 0)
		result.count = (unsigned)size;
	return result;
}

string_t cstring_to_string(const char* const* value)
{
	if (*value == NULL)
		return string_from_literal("(null)");
	return string_from(*value, strlen(*value));
}
