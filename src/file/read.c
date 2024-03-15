/* ************************************************************************** */
/*      ____    _    _____ ____     _    _   _   _____ _  _   ____  ____      */
/*     / ___|  / \  |  ___|  _ \   / \  | \ | | |_   _| || | |  _ \/ ___|     */
/*     \___ \ / _ \ | |_  | |_) | / _ \ |  \| |   | | | || |_| | | \___ \     */
/*      ___) / ___ \|  _| |  _ < / ___ \| |\  |   | | |__   _| |_| |___) |    */
/*     |____/_/   \_|_|   |_| \_/_/   \_|_| \_|   |_|    |_| |____/|____/     */
/*                                                                            */
/**
 * @copyright 2023, SAFRAN T4DS, ALL RIGHTS RESERVED
 * @file read.c
 * @author Antoine GAGNIERE
 * @brief Read from buffered input streams
 */
/* ************************************************************************** */

#include "o2s/file_input_stream.h"
#include "o2s/log.h"

#include <errno.h>
#include <iso646.h> // not, and
#include <string.h> // strerror
#include <unistd.h> // read
#include <stdbool.h>

#if !defined(__STDC_VERSION__) || __STDC_VERSION__ < 202300L
#	warning including threads.h to have thread_local before C23
#	include <threads.h> // thread_local
#endif

/** Flag used to prevent blocking reads */
static thread_local bool keep_reading = true;

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
	{ /* This branch is impossible to reach if this thread has exclusive access to the queue, which it should */
		log_error("cannot add %li characters to the queue, %zu / %zu bytes used", result, queue_count(queue), queue_capacity(queue));
		return -1;
	}
	return result;
}

/**
 * If possible, accumulate @p count bytes before returning.
 *
 * This alternative keeps trying upon reaching the end of the file,
 * waiting for new data to be written.
 * It is suitable when reading pipes, serial ports and such infinite streams.
 *
 * To set a timeout, create a timer that emits a signal with @ref file_stop_reading as a signal handler,
 * for the current read call to be interrupted and to break out of the loop.
 *
 * @return a boolean
 *  - `true` if n bytes were successfully accumulated
 *  - `false` otherwise
 */
bool file_accumulate_infinite(ifstream_t* file, size_t count)
{
	while (not istream_has_at_least(&file->stream, count))
		if (not keep_reading or file_single_read(file) < 0)
			return false;
	return true;
}

/**
 * If possible, accumulate @p count bytes before returning.
 *
 * This alternative exits upon reaching the end of the file.
 * It is suitable when reading regular files
 *
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

/**
 * Prevent the accumulate function from calling read in this thread.
 * This allows setting a thread specific timeout, that interrupts the current read, and exits the accumulating loop.
 * The effect is thread_local, so multiple files can have their own timeouts in parallel.
 */
void file_stop_reading(void)
{
	keep_reading = false;
}

/** Resume calling read in this thread */
void file_resume_reading(void)
{
	keep_reading = true;
}

/** Default signal handler */
void file_default_signal_handler(int, siginfo_t*, void*)
{
	file_stop_reading();
}
