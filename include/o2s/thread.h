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
 * @file thread.h
 * @author Antoine GAGNIERE
 * @brief Thread-specific global and its setter
 */
/* ************************************************************************** */

#if !defined(__STDC_VERSION__) || __STDC_VERSION__ < 202300L
/* # warning including threads.h to have thread_local before C23 */
#	include <threads.h> // thread_local
#endif

void o2s_thread_set_name(const char* name);

thread_local extern char o2s_thread_name[8];
