/* ************************************************************************** */
/*      ____    _    _____ ____     _    _   _   _____ _  _   ____  ____      */
/*     / ___|  / \  |  ___|  _ \   / \  | \ | | |_   _| || | |  _ \/ ___|     */
/*     \___ \ / _ \ | |_  | |_) | / _ \ |  \| |   | | | || |_| | | \___ \     */
/*      ___) / ___ \|  _| |  _ < / ___ \| |\  |   | | |__   _| |_| |___) |    */
/*     |____/_/   \_|_|   |_| \_/_/   \_|_| \_|   |_|    |_| |____/|____/     */
/*                                                                            */
/**
 * @copyright 2024, SAFRAN T4DS, ALL RIGHTS RESERVED
 * @file thread.c
 * @author Antoine GAGNIERE
 * @brief Thread-specific global and function
 */
/* ************************************************************************** */

#define _GNU_SOURCE  // pthread_*_np

#include "o2s/thread.h"

#include <pthread.h> // pthread_*

#include <string.h> // strncpy

/** Thread name, used when logging. The name can be 8 characters long at most */
thread_local char o2s_thread_name[8] = {};

/**
 * Sets both the O2S thread name and the POSIX thread name (`/proc/self/task/tid/comm`).
 * The name will be visible in GDB, htop, etc
 * @param name must be a null-terminated character string, preferably a string literal
 */
void o2s_thread_set_name(const char* name)
{
	strncpy(o2s_thread_name, name, sizeof(o2s_thread_name));
	pthread_setname_np(pthread_self(), name);
}
