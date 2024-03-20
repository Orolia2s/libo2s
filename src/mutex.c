/* ************************************************************************** */
/*      ____    _    _____ ____     _    _   _   _____ _  _   ____  ____      */
/*     / ___|  / \  |  ___|  _ \   / \  | \ | | |_   _| || | |  _ \/ ___|     */
/*     \___ \ / _ \ | |_  | |_) | / _ \ |  \| |   | | | || |_| | | \___ \     */
/*      ___) / ___ \|  _| |  _ < / ___ \| |\  |   | | |__   _| |_| |___) |    */
/*     |____/_/   \_|_|   |_| \_/_/   \_|_| \_|   |_|    |_| |____/|____/     */
/*                                                                            */
/**
 * @copyright 2024, SAFRAN T4DS, ALL RIGHTS RESERVED
 * @file mutex.c
 * @author Antoine GAGNIERE
 * @brief Provide a convenient RAII-style mechanism to access mutex-protected resources
 */
/* ************************************************************************** */

#include "o2s/mutex.h"

#include "o2s/log.h" // log_*

#include <pthread.h> // pthread_*

#include <string.h> // strerror

/** Lock the mutex, logging any error. */
pthread_mutex_t* o2s_mutex_lock(pthread_mutex_t* mutex)
{
	int error = pthread_mutex_lock(mutex);

	if (error != 0)
		log_error("Unable to lock mutex: %s", strerror(error));
	return mutex;
}

/** Unlock the mutex, logging any error. */
void o2s_mutex_unlock(pthread_mutex_t* const* mutex)
{
	int error = pthread_mutex_unlock(*mutex);

	if (error != 0)
		log_error("Unable to unlock mutex: %s", strerror(error));
}
