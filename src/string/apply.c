/* ************************************************************************** */
/*      ____    _    _____ ____     _    _   _   _____ _  _   ____  ____      */
/*     / ___|  / \  |  ___|  _ \   / \  | \ | | |_   _| || | |  _ \/ ___|     */
/*     \___ \ / _ \ | |_  | |_) | / _ \ |  \| |   | | | || |_| | | \___ \     */
/*      ___) / ___ \|  _| |  _ < / ___ \| |\  |   | | |__   _| |_| |___) |    */
/*     |____/_/   \_|_|   |_| \_/_/   \_|_| \_|   |_|    |_| |____/|____/     */
/*                                                                            */
/* Copyright 2023, SAFRAN T4DS, ALL RIGHTS RESERVED                           */
/*                                                                            */
/* @file apply.c                                                              */
/* @author Antoine GAGNIERE                                                   */
/*                                                                            */
/* ************************************************************************** */

#include "o2s/string.h"

#include <ctype.h> // tolower, toupper

/**
 * Replace each character by its image through the provided function.
 * Possible implementation in GNU C :
 * @code{.c}
 *	void local(char* c)
 *	{
 *		*c = function(*c);
 *	}
 *
 *	array_iter(self, local);
 * @endcode
 */
void string_apply_inplace(string_t* self, char (*function)(char))
{
	for (char*c = self->start; c < (char*)self->start + self->capacity * self->type_size; c++)
		*c = function(*c);
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wcast-function-type"

/** Replace each alphabetic character by its lower case equivalent */
void string_tolower_inplace(string_t* self)
{
	string_apply_inplace(self, (char (*)(char))tolower);
}

/** Replace each alphabetic character by its upper case equivalent */
void string_toupper_inplace(string_t* self)
{
	string_apply_inplace(self, (char (*)(char))toupper);
}

#pragma GCC diagnostic pop
