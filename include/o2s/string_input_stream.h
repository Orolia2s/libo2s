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
 * @file string_input_stream.h
 * @author Antoine GAGNIERE
 * @brief Create input streams from strings
 */
/* ************************************************************************** */

#include "o2s/input_stream.h"
#include "o2s/string.h"

#include <stddef.h> // size_t

istream_t string_input_stream(const string_t* value);
istream_t cstring_input_stream(const char* value, size_t length);

/**
 * Create an input stream with the content of a C string.
 * @note strlen() of a literal can be computed at compile time.
 */
#define string_literal_input_stream(Value) cstring_input_stream(Value, strlen(Value));

/**
 * Use the RAII idiom with a string input stream.
 *
 * In a situation where one wants to declare an istream variable
 * on the stack in the local scope, this "typedef" can be used for
 * the file to be closed automatically when the variable goes out
 * of scope.
 *
 * It means this "typedef" can only be used like this :
 * @code{.c}
 * {
 *     StringInputStream file = string_input_string(...);
 *     ...
 * } // <- The stream will be closed at that point
 * @endcode
 */
#define StringInputStream __attribute__((cleanup(istream_close))) istream_t
