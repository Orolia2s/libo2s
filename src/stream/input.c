/* ************************************************************************** */
/*      ____    _    _____ ____     _    _   _   _____ _  _   ____  ____      */
/*     / ___|  / \  |  ___|  _ \   / \  | \ | | |_   _| || | |  _ \/ ___|     */
/*     \___ \ / _ \ | |_  | |_) | / _ \ |  \| |   | | | || |_| | | \___ \     */
/*      ___) / ___ \|  _| |  _ < / ___ \| |\  |   | | |__   _| |_| |___) |    */
/*     |____/_/   \_|_|   |_| \_/_/   \_|_| \_|   |_|    |_| |____/|____/     */
/*                                                                            */
/**
 * @copyright 2023, SAFRAN T4DS, ALL RIGHTS RESERVED
 * @file input.c
 * @author Antoine GAGNIERE
 * @brief Functions common to all input streams
 */
/* ************************************************************************** */

#include "o2s/input_stream.h"

/**
 * Allocate a buffer and set the member function
 * @warning Input stream is an abstact type and is not meant to be created by an end user
 */
istream_t istream_init(size_t buffer_size, bool (*accumulate)(istream_t*, size_t))
{
	return (istream_t){.buffer = QueueAllocate(buffer_size, char), .accumulate = accumulate};
}

/** Free the buffer */
void istream_close(istream_t* self)
{
	queue_free(&self->buffer);
}

/**
 * Test if enough characters are available
 * @return true if the buffer contains at least @p count bytes
 */
bool istream_has_at_least(const istream_t* self, size_t count)
{
	return queue_count(&self->buffer) >= count;
}
