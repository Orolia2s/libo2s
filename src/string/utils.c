/* ************************************************************************** */
/*      ____    _    _____ ____     _    _   _   _____ _  _   ____  ____      */
/*     / ___|  / \  |  ___|  _ \   / \  | \ | | |_   _| || | |  _ \/ ___|     */
/*     \___ \ / _ \ | |_  | |_) | / _ \ |  \| |   | | | || |_| | | \___ \     */
/*      ___) / ___ \|  _| |  _ < / ___ \| |\  |   | | |__   _| |_| |___) |    */
/*     |____/_/   \_|_|   |_| \_/_/   \_|_| \_|   |_|    |_| |____/|____/     */
/*                                                                            */
/* Copyright 2023, SAFRAN T4DS, ALL RIGHTS RESERVED                           */
/*                                                                            */
/* @file utils.c                                                              */
/* @author Antoine GAGNIERE                                                   */
/*                                                                            */
/* ************************************************************************** */

#include "o2s/string.h"

#include <iso646.h> // not

/**
 * Provide compatibility with legacy string functions.
 * Ensure the string is null-terminated, without impacting the length.
 * @return NULL if a reallocation was necessary and failed
 */
char* string_to_cstring(string_t* self)
{
	if (not string_reserve(self, 1))
		return NULL;
	*(self->count + (char*)self->start) = '\0';
	return self->start;
}

/** Ensure the underlying storage can accomodate @p count more characters. */
bool string_reserve(string_t* self, size_t count)
{
	return array_reserve(self, count);
}

/** Resize the underlying storage, for it not to take any more room that needed */
bool string_trim(string_t* self)
{
	return array_trim(self);
}
