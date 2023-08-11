/* ************************************************************************** */
/*      ____    _    _____ ____     _    _   _   _____ _  _   ____  ____      */
/*     / ___|  / \  |  ___|  _ \   / \  | \ | | |_   _| || | |  _ \/ ___|     */
/*     \___ \ / _ \ | |_  | |_) | / _ \ |  \| |   | | | || |_| | | \___ \     */
/*      ___) / ___ \|  _| |  _ < / ___ \| |\  |   | | |__   _| |_| |___) |    */
/*     |____/_/   \_|_|   |_| \_/_/   \_|_| \_|   |_|    |_| |____/|____/     */
/*                                                                            */
/* Copyright 2023, SAFRAN T4DS, ALL RIGHTS RESERVED                           */
/*                                                                            */
/* @file open.c                                                               */
/* @author Antoine GAGNIERE                                                   */
/*                                                                            */
/* ************************************************************************** */

#include "o2s/file_input_stream.h"
#include "o2s/log.h"

#include <fcntl.h> // open

#include <errno.h>
#include <stdbool.h>
#include <string.h> // strerror
#include <unistd.h> // close

#ifndef FILE_STREAM_BUFFER_SIZE
#	define FILE_STREAM_BUFFER_SIZE 4096 /// @todo configure in a better way
#endif

/**
 * Construct a file input stream :
 * Open the file and allocate the buffer.
 */
ifstream_t file_open(const char* file_name, int flags)
{
	ifstream_t file = {.descriptor = -1, .opened = false};

	if ((file.descriptor = open(file_name, flags)) < 0)
	{
		log_error("Unable to open \"%s\": %s", file_name, strerror(errno));
		return file;
	}
	file.stream = InputStreamInit(FILE_STREAM_BUFFER_SIZE, file_accumulate);
	if (file.stream.buffer.capacity == 0)
	{
		log_error("malloc failed: %s", strerror(errno));
		close(file.descriptor);
		file.descriptor = -1;
		return file;
	}
	file.opened = true;
	return file;
}
