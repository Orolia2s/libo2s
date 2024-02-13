/* ************************************************************************** */
/*      ____    _    _____ ____     _    _   _   _____ _  _   ____  ____      */
/*     / ___|  / \  |  ___|  _ \   / \  | \ | | |_   _| || | |  _ \/ ___|     */
/*     \___ \ / _ \ | |_  | |_) | / _ \ |  \| |   | | | || |_| | | \___ \     */
/*      ___) / ___ \|  _| |  _ < / ___ \| |\  |   | | |__   _| |_| |___) |    */
/*     |____/_/   \_|_|   |_| \_/_/   \_|_| \_|   |_|    |_| |____/|____/     */
/*                                                                            */
/* Copyright 2023, SAFRAN T4DS, ALL RIGHTS RESERVED                           */
/*                                                                            */
/* @file constructors_destructors.c                                           */
/* @author Antoine GAGNIERE                                                   */
/*                                                                            */
/* ************************************************************************** */

#include "o2s/string.h"

/** Constructs an empty string */
string_t string_new(void)
{
	return ArrayNew(char);
}

/** Construct a string with an initial value */
string_t string_from(const char* cstring, size_t length)
{
	string_t result = string_new();

	string_append_cstring(&result, cstring, length);
	return result;
}

void string_clear(string_t* self)
{
	array_clear(self);
}
