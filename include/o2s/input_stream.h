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
/* ************************************************************************** */

#include "o2s/queue.h"

#include <stdbool.h> // bool
#include <stddef.h>  // size_t

/**
 * Input Stream.
 * Abstraction layer hiding either a file input stream of a string input stream
 */
typedef struct input_stream
{
	queue_t buffer; /**< Circular buffer of bytes */
	/** Ask if the stream can provide at least @p count bytes to read */
	bool (*accumulate)(struct input_stream* self, size_t count);
} istream_t;

/** Convenient wrapper around @ref istream_init that casts @p Accumulate */
#define InputStreamInit(Size, Accumulate) \
	istream_init(Size, ((bool (*)(istream_t*, size_t))(Accumulate)))

istream_t istream_init(size_t buffer_size, bool (*accumulate)(istream_t*, size_t));
void istream_close(istream_t* self);

bool istream_has_at_least(const istream_t* self, size_t count);

/** @name Calling a virtual member function */
///@{
/** Convenient way to call the input stream's accumulate member function */
#define istream_accumulate(Stream, Count) \
	((istream_t*)(Stream))->accumulate((istream_t*)Stream, Count)
///@}
