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
