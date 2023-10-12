/* ************************************************************************** */
/*      ____    _    _____ ____     _    _   _   _____ _  _   ____  ____      */
/*     / ___|  / \  |  ___|  _ \   / \  | \ | | |_   _| || | |  _ \/ ___|     */
/*     \___ \ / _ \ | |_  | |_) | / _ \ |  \| |   | | | || |_| | | \___ \     */
/*      ___) / ___ \|  _| |  _ < / ___ \| |\  |   | | |__   _| |_| |___) |    */
/*     |____/_/   \_|_|   |_| \_/_/   \_|_| \_|   |_|    |_| |____/|____/     */
/*                                                                            */
/* Copyright 2023, SAFRAN T4DS, ALL RIGHTS RESERVED                           */
/*                                                                            */
/* @file pop.c                                                                */
/* @author Antoine GAGNIERE                                                   */
/*                                                                            */
/* ************************************************************************** */

#include "o2s/string.h"

/** Pop the last character */
bool string_pop(string_t* self, char* destination)
{
	return array_pop_back(self, destination);
}

/** Pop the @p count last characters */
bool string_pop_n(string_t* self, char* destination, size_t count)
{
	return array_pop_back_n(self, destination, count);
}

/** Create a string from the @p count last characters */
string_t string_pop_as_string(string_t* self, size_t count)
{
	if (count > string_length(self))
		return string_new();
	string_t result = string_from(string_get(self, string_length(self) - count), count);
	array_pop_back_n(self, NULL, count);
	return result;
}

/** Pop the first character */
bool string_pop_front(string_t* self, char* destination)
{
	return array_pop_front(self, destination);
}

/** Pop the first @p count characters */
bool string_pop_front_n(string_t* self, char* destination, size_t count)
{
	return array_pop_front_n(self, destination, count);
}
