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

#include "o2s/file_input_stream.h"
#include "o2s/log.h"

#include <errno.h>
#include <string.h> // strerror
#include <iso646.h> // not, and
#include <unistd.h> // read

/**
 * Read as much as possible.
 *
 * Attempt to fill the buffer
 */
ssize_t file_single_read(ifstream_t* file)
{
	queue_t*      queue = &file->stream.buffer;
	const size_t  room  = queue_room(queue);
	uint8_t       buffer[room];
	const ssize_t result = read(file->descriptor, buffer, room);

	if (result < 0)
		log_error("read returned %li: %s", result, strerror(errno));
	else if (result > 0 and not queue_push_n(queue, buffer, result))
	{ /* This branch is impossible to reach if this thread has exclusive access to the queue */
		log_error("cannot add %li characters to the queue, %zu / %zu bytes used", result, queue_count(queue), queue_capacity(queue));
		return -1;
	}
	return result;
}

/**
 * If possible, accumulate @p count bytes before returning.
 * @return a boolean
 *  - `true` if n bytes were successfully accumulated
 *  - `false` otherwise
 */
bool file_accumulate(ifstream_t* file, size_t count)
{
	while (not istream_has_at_least(&file->stream, count))
		if (file_single_read(file) <= 0)
			return false;
	return true;
}
