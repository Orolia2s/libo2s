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
/* ************************************************************************** */

#include "o2s/input_stream.h"

#include <signal.h>  // siginfo_t
#include <stdbool.h> // bool
#include <stdint.h>  // uint*_t
#include <stdio.h>   // ssize_t

/** File Input Stream @todo store the name for debug purposes ? */
typedef struct file_input_stream
{
	istream_t stream;     /**< Inherit from input stream */
	int       descriptor; /**< Underlying file */
	bool      opened;     /**< Is this file still open ? */
} ifstream_t;

/** @name Contructors and destructor */
///@{
ifstream_t file_open(const char* file_name, int flags);
ifstream_t file_from_descriptor(int descriptor);
void       file_close(ifstream_t* file);
///@}

/** @name Reading */
///@{
ssize_t    file_single_read(ifstream_t* file);
bool       file_accumulate(ifstream_t* file, size_t count);
bool       file_accumulate_infinite(ifstream_t* file, size_t count);

void       file_stop_reading(void);
void       file_resume_reading(void);
///@}

void       file_default_signal_handler(int, siginfo_t*, void*);

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
