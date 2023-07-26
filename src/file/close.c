/* ************************************************************************** */
/*      ____    _    _____ ____     _    _   _   _____ _  _   ____  ____      */
/*     / ___|  / \  |  ___|  _ \   / \  | \ | | |_   _| || | |  _ \/ ___|     */
/*     \___ \ / _ \ | |_  | |_) | / _ \ |  \| |   | | | || |_| | | \___ \     */
/*      ___) / ___ \|  _| |  _ < / ___ \| |\  |   | | |__   _| |_| |___) |    */
/*     |____/_/   \_|_|   |_| \_/_/   \_|_| \_|   |_|    |_| |____/|____/     */
/*                                                                            */
/* Copyright 2023, SAFRAN T4DS, ALL RIGHTS RESERVED                           */
/*                                                                            */
/* @file close.c                                                              */
/* @author Antoine GAGNIERE                                                   */
/*                                                                            */
/* ************************************************************************** */

#include "o2s/file_input_stream.h"
#include "o2s/log.h"

#include <errno.h>
#include <stdlib.h> // free
#include <string.h> // strerror
#include <unistd.h> // close

/**
 * Release resources to the system
 *
 * In case of error when calling close, there is absolutely nothing interesting
 * that can be done beyond reporting it, so it is not propagated.
 */
void file_close(ifstream_t* file)
{
	log_trace("%s(%i)", __FUNCTION__, file->descriptor);
	if (file->buffer.storage)
	{
		deque_free(&file->buffer);
	}
	if (!file->opened)
	{
		log_warning("Attempting to close a file that isn't open.");
		return;
	}
	if (close(file->descriptor) != 0)
	{
		log_error("Unable to close the file: %s", strerror(errno));
		return;
	}
	file->opened = false;
}
