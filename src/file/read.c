/* ************************************************************************** */
/*      ____    _    _____ ____     _    _   _   _____ _  _   ____  ____      */
/*     / ___|  / \  |  ___|  _ \   / \  | \ | | |_   _| || | |  _ \/ ___|     */
/*     \___ \ / _ \ | |_  | |_) | / _ \ |  \| |   | | | || |_| | | \___ \     */
/*      ___) / ___ \|  _| |  _ < / ___ \| |\  |   | | |__   _| |_| |___) |    */
/*     |____/_/   \_|_|   |_| \_/_/   \_|_| \_|   |_|    |_| |____/|____/     */
/*                                                                            */
/* Copyright 2023, SAFRAN T4DS, ALL RIGHTS RESERVED                           */
/*                                                                            */
/* @file read.c                                                               */
/* @author Antoine GAGNIERE                                                   */
/*                                                                            */
/* ************************************************************************** */

#include "o2s/deque.h"
#include "o2s/file_input_stream.h"

#include <stdio.h>  //printf
#include <unistd.h> // read

/**
 * Read as much as possible.
 *
 * Attempt to fill the buffer
 */
ssize_t file_single_read(ifstream_t* file)
{
	deque_t* queue = &file->buffer;
	size_t   room  = deque_room(queue);
	uint8_t  buffer[room];
	ssize_t  result = read(file->descriptor, buffer, room);
	if (result > 0)
	{
		if (deque_push_back_n(queue, buffer, result))
		{
			return result;
		}
		else
			return 0;
	}
	return result;
}

/**
 * If possible, accumulate @p n bytes before returning
 * @return a boolean
 *  - `true` if n bytes were successfully accumulated
 *  - `false` otherwise
 */
bool file_accumulate(ifstream_t* file, size_t n)
{
	while (deque_count(&file->buffer) < n)
		if (file_single_read(file) <= 0)
			return false;
	return true;
}
