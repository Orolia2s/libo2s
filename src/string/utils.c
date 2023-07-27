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

/**
 * Provide compatibility with legacy string functions.
 * Ensure the string is null-terminated, without impacting the length.
 */
char* string_to_cstring(string_t* self)
{
	string_reserve(self, 1);
	*(self->count + (char*)self->start) = '\0';
	return self->start;
}

/** Ensure the underlying storage can accomodate @p count more characters. */
bool string_reserve(string_t* self, size_t count)
{
	return array_reserve(self, count);
}
