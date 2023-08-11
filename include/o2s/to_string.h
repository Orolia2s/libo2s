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
 * @file to_string.h
 * @author Antoine GAGNIERE
 * @brief Create strings from data structures
 */
/* ************************************************************************** */

#include "o2s/array.h"
#include "o2s/deque.h"
#include "o2s/queue.h"
#include "o2s/stack.h"
#include "o2s/string.h"

/** @name Integers */
///@{
string_t int_to_string(const int* value);
string_t unsigned_to_string(const unsigned* value);
string_t short_to_string(const short* value);
string_t long_to_string(const long* value);
///@}

/** @name Floating point numbers */
///@{
string_t float_to_string(const float* value);
string_t double_to_string(const double* value);
///@}

/** @name Strings */
///@{
string_t cstring_to_string(const char* const* value);
string_t char_to_string(const char* value);
///@}

/** @name Structures */
///@{
string_t array_to_string(const array_t* self, string_t (*function)(const void* element));
string_t deque_to_string(const deque_t* self, string_t (*function)(const void* element));
inline string_t queue_to_string(const queue_t* self, string_t (*function)(const void* element)) { return deque_to_string(self, function); }
inline string_t stack_to_string(const stack_t* self, string_t (*function)(const void* element)) { return deque_to_string(self, function); }
///@}
