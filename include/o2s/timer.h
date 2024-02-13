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

Here is the intended usage of timers:
@code{.c}
// In a given process
if (not o2s_timer_setup_process(some_signal_handler_that_tells_the_operation_to_exit))
    error();

{ // in a given thread
    O2sTimer timer = o2s_timer_create();
    if (timer == NULL)
        error();

    { // Where a timeout is wanted
        ArmedTimer copy = o2s_timer_start();
        if (copy == NULL)
            error();

        some_operation_that_can_hang();
    } // <- the timer is disarmed here

    tell_the_operation_to_not_exit();
} // <- the timer is deleted here
@endcode
 */
/* ************************************************************************** */

#include <signal.h>  // sigaction
#include <stdbool.h> // bool
#include <time.h>    // timer_t

bool    o2s_timer_setup_process(void (*handle)(int, siginfo_t*, void*));
timer_t o2s_timer_create(void);
timer_t o2s_timer_start(timer_t timer, unsigned milliseconds);
void    o2s_timer_stop(timer_t* timer);
void    o2s_timer_delete(timer_t* timer);

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
#define O2sTimer   __attribute__((cleanup(o2s_timer_delete))) timer_t

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
#define ArmedTimer __attribute__((cleanup(o2s_timer_stop))) timer_t
