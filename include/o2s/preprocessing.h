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
 * @file preprocessing.h
 * @author Antoine GAGNIERE
 * @brief Compile-time utilities
 */
/* ************************************************************************** */

#include "o2s/private_prepro.h"

/** @name Token manipulation */
///@{

/** Changes token type to string literal */
#define LIBO2S_PREPRO_STRING_DIRECT(TEXT) #TEXT

/** Create a string literal from the evaluation of its argument */
#define LIBO2S_PREPRO_STRING(EXPRESSION)  LIBO2S_PREPRO_STRING_DIRECT(EXPRESSION)

/** Evaluates as a single identifier token, that is @p TEXT1 concatenated with @p TEXT2 */
#define LIBO2S_PREPRO_CONCAT_DIRECT(TEXT1, TEXT2) TEXT1 ## TEXT2

/**
 * Evaluates as a single identifier token,
 * that is the evaluation of @p EXPRESSION1 concatenated with the evaluation of @p EXPRESSION2
 */
#define LIBO2S_PREPRO_CONCAT(EXPRESSION1, EXPRESSION2) LIBO2S_PREPRO_CONCAT_DIRECT(EXPRESSION1, EXPRESSION2)

///@}

/** @name Numbers manipulation */
///@{

/** Evaluates as the biggest of the two parameters */
#define max(a, b) \
	({ \
		__typeof__(a) _a = (a); \
		__typeof__(b) _b = (b); \
		_a > _b ? _a : _b; \
	})

/** Evaluates as the smallest of the two parameters */
#define min(a, b) \
	({ \
		__typeof__(a) _a = (a); \
		__typeof__(b) _b = (b); \
		_a < _b ? _a : _b; \
	})

///@}

/** Number of elements in a C array (on the stack) */
#define C_ARRAY_LENGTH(ARRAY) (sizeof(ARRAY) / sizeof(*ARRAY))

/** Evaluates as the number of arguments, up to 39 */
#define LIBO2S_PREPRO_ARGUMENT_COUNT(...) O2SPP_ARGCNT1(__VA_ARGS__)

/**
 * Fowler–Noll–Vo hash function, at compile-time.
 * Evaluates as an expression that will be computed at compile-time,
 * representing the hash of the sequence of characters passed as arguments.
 */
#define FNV1A(...) FNV1A_N(__VA_ARGS__)
