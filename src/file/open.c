/* ************************************************************************** */
/*      ____    _    _____ ____     _    _   _   _____ _  _   ____  ____      */
/*     / ___|  / \  |  ___|  _ \   / \  | \ | | |_   _| || | |  _ \/ ___|     */
/*     \___ \ / _ \ | |_  | |_) | / _ \ |  \| |   | | | || |_| | | \___ \     */
/*      ___) / ___ \|  _| |  _ < / ___ \| |\  |   | | |__   _| |_| |___) |    */
/*     |____/_/   \_|_|   |_| \_/_/   \_|_| \_|   |_|    |_| |____/|____/     */
/*                                                                            */
/* Copyright 2023, SAFRAN T4DS, ALL RIGHTS RESERVED                           */
/*                                                                            */
/* @file open.c                                                              */
/* @author Antoine GAGNIERE                                                   */
/*                                                                            */
/* ************************************************************************** */

#include "o2s/file_input_stream.h"
#include "o2s/log.h"

#include <fcntl.h> // open

#include <errno.h>
#include <stdbool.h>
#include <stdlib.h> // malloc
#include <string.h> // strerror
#include <unistd.h> // close

#define BUFFER_SIZE 4096 // TODO: configure in a better way

/**
 * Construct a file input stream :
 * Open the file and allocate the buffer.
 */
ifstream_t file_open(const char* file_name, int flags)
{
	ifstream_t file = {.descriptor = -1, .opened = false};
	void*      buffer;

	log_trace("%s(\"%s\")", __FUNCTION__, file_name);
	if ((file.descriptor = open(file_name, flags)) < 0)
	{
		log_error("Unable to open \"%s\": %s", file_name, strerror(errno));
		return file;
	}
	if ((buffer = malloc(BUFFER_SIZE * sizeof(char))) == NULL)
	{
		log_error("malloc failed: %s", strerror(errno));
		close(file.descriptor);
		file.descriptor = -1;
		return file;
	}
	file.opened = true;
	file.buffer = DequeNew(buffer, char, BUFFER_SIZE);
	return file;
}
