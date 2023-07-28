/* ************************************************************************** */
/*      ____    _    _____ ____     _    _   _   _____ _  _   ____  ____      */
/*     / ___|  / \  |  ___|  _ \   / \  | \ | | |_   _| || | |  _ \/ ___|     */
/*     \___ \ / _ \ | |_  | |_) | / _ \ |  \| |   | | | || |_| | | \___ \     */
/*      ___) / ___ \|  _| |  _ < / ___ \| |\  |   | | |__   _| |_| |___) |    */
/*     |____/_/   \_|_|   |_| \_/_/   \_|_| \_|   |_|    |_| |____/|____/     */
/*                                                                            */
/* Copyright 2023, SAFRAN T4DS, ALL RIGHTS RESERVED                           */
/*                                                                            */
/* @file map.c                                                                */
/* @author Antoine GAGNIERE                                                   */
/*                                                                            */
/* ************************************************************************** */

#include "o2s/string.h"

#include <ctype.h> // tolower, toupper

/**
 * Creates a copy of the string, where each character is the image
 * through the provided function
*/
string_t string_map(const string_t* self, char (*function)(char))
{
	string_t result = string_new();
	char     c;

	string_reserve(&result, string_length(self));
	string_foreach(self, &c)
	{
		string_append_char(&result, function(c));
	}
	return result;
}

/** Creates a copy of the string, with all alphabetic characters to lower-case */
string_t string_tolower(const string_t* self)
{
	return string_map(self, (char (*)(char))tolower);
}

/** Creates a copy of the string, with all alphabetic characters to upper-case */
string_t string_toupper(const string_t* self)
{
	return string_map(self, (char (*)(char))toupper);
}
