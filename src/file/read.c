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

#include <unistd.h> // read
#include <stdio.h> //printf

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

	printf("[DEQUE] Inserting %d elements ", result);
    printf("[ ");
    for (size_t i = 0; i < result; i++)
    {
        printf("%02x ", buffer[i]);
    }
    printf("]\n");
	if (result > 0)
	{
		if (deque_push_back_n(queue, buffer, result))
		{
			printf("[DEQUE] Inserted %d elements ", result);
			printf("[ ");
			for (size_t i = 0; i < deque_count(queue); i++)
			{
				printf("%02x ", *((uint8_t*) deque_first(queue) + i));
			}
			printf("]\n");
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
