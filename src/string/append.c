/* ************************************************************************** */
/*      ____    _    _____ ____     _    _   _   _____ _  _   ____  ____      */
/*     / ___|  / \  |  ___|  _ \   / \  | \ | | |_   _| || | |  _ \/ ___|     */
/*     \___ \ / _ \ | |_  | |_) | / _ \ |  \| |   | | | || |_| | | \___ \     */
/*      ___) / ___ \|  _| |  _ < / ___ \| |\  |   | | |__   _| |_| |___) |    */
/*     |____/_/   \_|_|   |_| \_/_/   \_|_| \_|   |_|    |_| |____/|____/     */
/*                                                                            */
/* Copyright 2023, SAFRAN T4DS, ALL RIGHTS RESERVED                           */
/*                                                                            */
/* @file append.c                                                             */
/* @author Antoine GAGNIERE                                                   */
/*                                                                            */
/* ************************************************************************** */

#include "o2s/string.h"

#include <stdarg.h> // va_*
#include <stdio.h>  // vsnprintf

/** Add a single character to the back of the string */
bool string_append_char(string_t* self, char character)
{
	return array_push_back(self, &character);
}

/** Add a raw character string to the back of the string */
bool string_append_cstring(string_t* self, const char* cstring, size_t length)
{
	return array_push_back_n(self, cstring, length);
}

/** Concatenate two strings */
bool string_append(string_t* self, const string_t* other)
{
	return array_push_back_n(self, other->start, other->count);
}

/** Append a string formed in a similar manner as printf */
bool string_append_format(string_t* self, const char* format, ...)
{
	va_list args1, args2;
	int     length;

	va_start(args1, format);
	va_copy(args2, args1);
	length = vsnprintf(NULL, 0, format, args1);
	va_end(args1);
	if (length > 0)
	{
		string_reserve(self, length + 1);
		self->count += vsnprintf(array_end(self), length + 1, format, args2);
	}
	va_end(args2);
	return length >= 0;
}
