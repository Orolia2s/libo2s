/* ************************************************************************** */
/*      ____    _    _____ ____     _    _   _   _____ _  _   ____  ____      */
/*     / ___|  / \  |  ___|  _ \   / \  | \ | | |_   _| || | |  _ \/ ___|     */
/*     \___ \ / _ \ | |_  | |_) | / _ \ |  \| |   | | | || |_| | | \___ \     */
/*      ___) / ___ \|  _| |  _ < / ___ \| |\  |   | | |__   _| |_| |___) |    */
/*     |____/_/   \_|_|   |_| \_/_/   \_|_| \_|   |_|    |_| |____/|____/     */
/*                                                                            */
/**
 * @copyright 2024, SAFRAN T4DS, ALL RIGHTS RESERVED
 * @file write.c
 * @author Antoine GAGNIERE
 * @brief Wrapper around the write system call
 */
/* ************************************************************************** */

#include "o2s/write.h"

#include "o2s/log.h" // log_*

#include <sys/types.h> // size_t, ssize_t

#include <errno.h>   // errno
#include <iso646.h>  // and
#include <stdbool.h> // bool
#include <string.h>  // strerror
#include <unistd.h>  // write

/** Keep calling write, untill all bytes are written, or write returns an error */
bool write_all(int file_descriptor, const char* memory, size_t length)
{
	ssize_t returned;
	size_t written = 0;

	while (written < length and (returned = write(file_descriptor, memory + written, length - written)) > 0)
		written += returned;
	if (written == length)
		return true;
	log_error("Unable to write the last %zu bytes out of %zu to file descriptor %i: %s",
	          length - written, length, file_descriptor, strerror(errno));
	return false;
}
