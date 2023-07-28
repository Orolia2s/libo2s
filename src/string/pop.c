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

bool string_pop(string_t* self, char* character)
{
	return array_pop_back(self, character);
}

bool string_pop_n(string_t* self, char* character, size_t count)
{
	return array_pop_back_n(self, character, count);
}

string_t string_pop_as_string(string_t* self, size_t count)
{
	if (count > string_length(self))
		return string_new();
	string_t result = string_from(string_get(self, string_length(self) - count), count);
	array_pop_back_n(self, NULL, count);
	return result;
}
