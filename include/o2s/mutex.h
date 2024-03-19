#pragma once

/* ************************************************************************** */
/*      ____    _    _____ ____     _    _   _   _____ _  _   ____  ____      */
/*     / ___|  / \  |  ___|  _ \   / \  | \ | | |_   _| || | |  _ \/ ___|     */
/*     \___ \ / _ \ | |_  | |_) | / _ \ |  \| |   | | | || |_| | | \___ \     */
/*      ___) / ___ \|  _| |  _ < / ___ \| |\  |   | | |__   _| |_| |___) |    */
/*     |____/_/   \_|_|   |_| \_/_/   \_|_| \_|   |_|    |_| |____/|____/     */
/*                                                                            */
/**
 * @copyright 2024, SAFRAN T4DS, ALL RIGHTS RESERVED
 * @file mutex.h
 * @author Antoine GAGNIERE
 * @brief Provide a convenient RAII-style mechanism to access mutex-protected resources
 */
/* ************************************************************************** */

#include <pthread.h> // pthread_mutex_t

pthread_mutex_t* o2s_mutex_lock(pthread_mutex_t* mutex);
void             o2s_mutex_unlock(pthread_mutex_t* const* mutex);

/**
 * Automatically unlock the mutex at the end of the current scope.
 *
 * In a situation where one wants to declare a mutex in a local scope,
 * this "typedef" can be used for that mutex to be unlocked
 * automatically when the variable goes out of scope.
 *
 * It means this "typedef" can only be used like this:
 * @code{.c}
 * {
 *     O2sLockGuard my_mutex = o2s_mutex_lock(...);
 *     ...
 * } // <- the mutex will be unlocked at that point
 * @endcode
 */
#define O2sLockGuard   __attribute__((cleanup(o2s_mutex_unlock))) pthread_mutex_t*
