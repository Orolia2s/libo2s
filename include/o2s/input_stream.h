#pragma once

/* ************************************************************************** */
/*      ____    _    _____ ____     _    _   _   _____ _  _   ____  ____      */
/*     / ___|  / \  |  ___|  _ \   / \  | \ | | |_   _| || | |  _ \/ ___|     */
/*     \___ \ / _ \ | |_  | |_) | / _ \ |  \| |   | | | || |_| | | \___ \     */
/*      ___) / ___ \|  _| |  _ < / ___ \| |\  |   | | |__   _| |_| |___) |    */
/*     |____/_/   \_|_|   |_| \_/_/   \_|_| \_|   |_|    |_| |____/|____/     */
/*                                                                            */
/**
 * @copyright 2023, SAFRAN T4DS, ALL RIGHTS RESERVED
 * @file input_stream.h
 * @author Antoine GAGNIERE
 * @brief Buffered input streams
 */
/*                                                                            */
/* ************************************************************************** */

#include "o2s/queue.h"

#include <stdbool.h> // bool
#include <stddef.h>  // size_t

/** Input Stream */
typedef struct input_stream istream_t;

/** Abstraction layer hiding either a file input stream of a string input stream */
struct input_stream
{
	queue_t buffer; /**< Cirecular buffer of bytes */
	/** Ask if the stream can provide at least @p count bytes to read */
	bool (*accumulate)(istream_t* self, size_t count);
};

istream_t istream_new(bool (*accumulate)(istream_t*, size_t));
void      istream_close(istream_t* self);

bool      istream_has_at_least(istream_t* self, size_t count);
