/* ************************************************************************** */
/*      ____    _    _____ ____     _    _   _   _____ _  _   ____  ____      */
/*     / ___|  / \  |  ___|  _ \   / \  | \ | | |_   _| || | |  _ \/ ___|     */
/*     \___ \ / _ \ | |_  | |_) | / _ \ |  \| |   | | | || |_| | | \___ \     */
/*      ___) / ___ \|  _| |  _ < / ___ \| |\  |   | | |__   _| |_| |___) |    */
/*     |____/_/   \_|_|   |_| \_/_/   \_|_| \_|   |_|    |_| |____/|____/     */
/*                                                                            */
/* Copyright 2023, SAFRAN T4DS, ALL RIGHTS RESERVED                           */
/*                                                                            */
/* @file structures.c                                                         */
/* @author Antoine GAGNIERE                                                   */
/*                                                                            */
/* ************************************************************************** */

#include "../array/private.h"

#include "o2s/log.h"
#include "o2s/to_string.h"

#include <iso646.h> // not

string_t array_to_string(const array_t* self, string_t (*function)(const void*))
{
	string_t result  = string_from_literal("[");
	void*    element = self->start;

	while (element < array_end(self))
	{
		String single = function(element);

		string_append(&result, &single);
		string_append_literal(&result, ", ");
		element += array_offset(self, 1);
	}
	if (not array_is_empty(self))
		string_pop_n(&result, NULL, 2);
	string_append_literal(&result, "]");
	return result;
}

string_t deque_to_string(const deque_t* self, string_t (*function)(const void*))
{
	string_t result = string_from_literal("[");

	for (unsigned i = 0; i < deque_count(self); i++)
	{
		String single = function(deque_get(self, i));

		string_append(&result, &single);
		string_append_literal(&result, ", ");
		log_info("[%u] %u %s", i, *(unsigned*)deque_get(self, i), string_to_cstring(&single));
	}
	if (not deque_is_empty(self))
		string_pop_n(&result, NULL, 2);
	string_append_literal(&result, "]");
	return result;
}
