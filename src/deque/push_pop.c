/* ************************************************************************** */
/*      ____    _    _____ ____     _    _   _   _____ _  _   ____  ____      */
/*     / ___|  / \  |  ___|  _ \   / \  | \ | | |_   _| || | |  _ \/ ___|     */
/*     \___ \ / _ \ | |_  | |_) | / _ \ |  \| |   | | | || |_| | | \___ \     */
/*      ___) / ___ \|  _| |  _ < / ___ \| |\  |   | | |__   _| |_| |___) |    */
/*     |____/_/   \_|_|   |_| \_/_/   \_|_| \_|   |_|    |_| |____/|____/     */
/*                                                                            */
/* Copyright 2023, SAFRAN T4DS, ALL RIGHTS RESERVED                           */
/*                                                                            */
/* @file core.c                                                               */
/* @author Hugo FOLCHER                                                       */
/*                                                                            */
/* ************************************************************************** */

#include "o2s/deque.h"
#include "private.h"

#include <string.h> // memcpy

void deque_push_front_n(deque_t* self, void* elements, size_t count)
{
	for (size_t i = 0; i < count; i++)
	{
		deque_push_front(self, elements + deque_offset(self, i));
	}
}

void deque_push_front(deque_t* self, void* element)
{
	deque_front_shift(self, 1);
	memcpy(self->first, element, deque_offset(self, 1));
}

bool deque_push_back_n(deque_t* self, void* elements, size_t count)
{
	if (deque_remaining_capacity(self) < count)
		return false;
	size_t remaining_back_capacity = deque_remaining_back_capacity(self);
	if (remaining_back_capacity >= count)
	{
		memcpy(deque_end(self), elements, deque_offset(self, count));
	}
	else
	{
		memcpy(deque_end(self), elements, deque_offset(self, remaining_back_capacity));
		deque_back_shift(self, remaining_back_capacity);
		memcpy(deque_end(self), elements, deque_offset(self, count - remaining_back_capacity));
		deque_back_shift(self, count - remaining_back_capacity);
	}
	memcpy(deque_end(self), elements, deque_offset(self, count));
	deque_back_shift(self, count + 1);
}

void deque_push_back(deque_t* self, void* element)
{
	deque_push_back_n(self, element, 1);
}