/* ************************************************************************** */
/*      ____    _    _____ ____     _    _   _   _____ _  _   ____  ____      */
/*     / ___|  / \  |  ___|  _ \   / \  | \ | | |_   _| || | |  _ \/ ___|     */
/*     \___ \ / _ \ | |_  | |_) | / _ \ |  \| |   | | | || |_| | | \___ \     */
/*      ___) / ___ \|  _| |  _ < / ___ \| |\  |   | | |__   _| |_| |___) |    */
/*     |____/_/   \_|_|   |_| \_/_/   \_|_| \_|   |_|    |_| |____/|____/     */
/*                                                                            */
/**
 * @copyright 2023, SAFRAN T4DS, ALL RIGHTS RESERVED
 * @file stream/string.c
 * @author Antoine GAGNIERE
 * @brief Create input streams from strings
 */
/* ************************************************************************** */

#include "o2s/string_input_stream.h"

/** Create an input stream with the content of a string */
istream_t string_input_stream(const string_t* value)
{
	return cstring_input_stream(value->start, value->count);
}

/** Create an input stream with the content of a C string */
istream_t cstring_input_stream(const char* value, size_t length)
{
	istream_t result = InputStreamInit(length, istream_has_at_least);

	queue_push_n(&result.buffer, value, length);
	return result;
}
