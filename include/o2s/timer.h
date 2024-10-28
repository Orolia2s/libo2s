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
 * @file timer.h
 * @author Antoine GAGNIERE
 * @brief Use timeouts backed by signals and realtime clock
 */
/* ************************************************************************** */

#include <signal.h>  // sigaction
#include <stdbool.h> // bool
#include <time.h>    // timer_t

typedef struct o2s_timer
{
	timer_t timer_id;
	bool    created;
	bool    armed;
} o2s_timer_t;

bool        o2s_timer_setup_process(void (*handle)(int, siginfo_t*, void*));
o2s_timer_t o2s_timer_create(void);
o2s_timer_t o2s_timer_start(o2s_timer_t timer, unsigned milliseconds);
void        o2s_timer_stop(o2s_timer_t* timer);
void        o2s_timer_delete(o2s_timer_t* timer);

/**
 * Automatically delete the timer when going out of scope.
 *
 * In a situation where one wants to declare a timer in a local scope,
 * this "typedef" can be used for that timer to be deleted
 * automatically when the variable goes out of scope.
 *
 * It means this "typedef" can only be used like this:
 * @code{.c}
 * {
 *     O2sTimer my_timer = o2s_timer_create(...);
 *     ...
 * } // <- the timer will be deleted at that point
 * @endcode
 */
#define O2sTimer   __attribute__((cleanup(o2s_timer_delete))) o2s_timer_t

/**
 * Automatically disarm the timer when going out of scope.
 *
 * In a situation where one wants to declare a timer in a local scope,
 * this "typedef" can be used for that timer to be disarmed
 * automatically when the variable goes out of scope.
 *
 * It means this "typedef" can only be used like this:
 * @code{.c}
 * {
 *     ArmedTimer copy = o2s_timer_start(my_timer, ...);
 *     ...
 * } // <- the timer will be disarmed at that point
 * @endcode
 */
#define ArmedTimer __attribute__((cleanup(o2s_timer_stop))) o2s_timer_t
