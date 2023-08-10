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
 * @file file_input_stream.h
 * @author Antoine GAGNIERE
 * @brief Buffered file reader
 */
/*                                                                            */
/* ************************************************************************** */

#include "o2s/input_stream.h"

#include <sys/types.h> // ssize_t

#include <stdbool.h> // bool
#include <stdint.h>  // uint*_t

/** File Input Stream @todo store the name for debug purposes ? */
typedef struct file_input_stream
{
	istream_t stream;      /**< Inherit from input stream */
	int       descriptor; /**< Underlying file */
	uint8_t   opened :1;  /**< Is this file still open ? */
} ifstream_t;

ifstream_t file_open(const char* file_name, int flags);
void       file_close(ifstream_t* file);

ssize_t    file_single_read(ifstream_t* file);
bool       file_accumulate(ifstream_t* file, size_t count);

/**
 * Use the RAII idiom with a file input stream.
 *
 * In a situation where one wants to declare an ifstream variable
 * on the stack in the local scope, this "typedef" can be used for
 * the file to be closed automatically when the variable goes out
 * of scope.
 *
 * It means this "typedef" can only be used like this :
 * @code{.c}
 * {
 *     FileInputStream file = file_open(...);
 *     ...
 * } // <- The file will be closed at that point
 * @endcode
 */
#define FileInputStream __attribute__((cleanup(file_close))) ifstream_t
