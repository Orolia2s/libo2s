/* ************************************************************************** */
/*      ____    _    _____ ____     _    _   _   _____ _  _   ____  ____      */
/*     / ___|  / \  |  ___|  _ \   / \  | \ | | |_   _| || | |  _ \/ ___|     */
/*     \___ \ / _ \ | |_  | |_) | / _ \ |  \| |   | | | || |_| | | \___ \     */
/*      ___) / ___ \|  _| |  _ < / ___ \| |\  |   | | |__   _| |_| |___) |    */
/*     |____/_/   \_|_|   |_| \_/_/   \_|_| \_|   |_|    |_| |____/|____/     */
/*                                                                            */
/* Copyright 2023, SAFRAN T4DS, ALL RIGHTS RESERVED                           */
/*                                                                            */
/* @file getters.c                                                            */
/* @author Antoine GAGNIERE                                                   */
/*                                                                            */
/* ************************************************************************** */

#include "o2s/string.h"

/** Number of characters in the string */
size_t string_length(const string_t* self)
{
	return array_count(self);
}

/**
 * The address of the character at the requested index
 * @return NULL if the index is not valid
 */
char* string_get(const string_t* self, size_t index)
{
	return (char*)array_get(self, index);
}

/** True if the string has a length of zero */
bool string_is_empty(const string_t* self)
{
	return array_is_empty(self);
}
