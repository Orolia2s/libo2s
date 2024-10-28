/* ************************************************************************** */
/*      ____    _    _____ ____     _    _   _   _____ _  _   ____  ____      */
/*     / ___|  / \  |  ___|  _ \   / \  | \ | | |_   _| || | |  _ \/ ___|     */
/*     \___ \ / _ \ | |_  | |_) | / _ \ |  \| |   | | | || |_| | | \___ \     */
/*      ___) / ___ \|  _| |  _ < / ___ \| |\  |   | | |__   _| |_| |___) |    */
/*     |____/_/   \_|_|   |_| \_/_/   \_|_| \_|   |_|    |_| |____/|____/     */
/*                                                                            */
/**
 * @copyright 2023-2024, SAFRAN T4DS, ALL RIGHTS RESERVED
 * @file timer.c
 * @author Antoine GAGNIERE
 * @brief Use timeouts backed by signals and realtime clock
 */
/* ************************************************************************** */

#define _GNU_SOURCE

#include "o2s/timer.h"

#include "o2s/log.h"

#include <errno.h>  // errno
#include <iso646.h> // not
#include <signal.h> // sigaction
#include <string.h> // strerror
#include <time.h>   // timer_*
#include <unistd.h> // gettid

/** Milli-seconds expressed in nano-seconds */
#define MS_IN_NS 1000000UL

/** Number of milli-seconds in a second */
#define MS_PER_S 1000

/**
 * Prepare the process for timeouts.
 * Needed to be called only once, preferably before creating the threads.
 * @return true if successful, false otherwise
 */
bool o2s_timer_setup_process(void (*handle)(int, siginfo_t*, void*))
{
	struct sigaction signal_action;

	sigemptyset(&signal_action.sa_mask);
	signal_action.sa_sigaction = handle;
	signal_action.sa_flags = SA_SIGINFO;
	if (sigaction(SIGALRM, &signal_action, NULL) == 0)
		return true;
	log_error("Unable to set signal action: %s", strerror(errno));
	return false;
}

/**
 * Initialize a timer, that will create a SIGALRM in the current thread when
 * timing out. This needs to be done once per thread, as the goal is for the
 * timer to interrupt the system calls of the current thread.
 * @return a timer object whose member created is false if it was unable to create the timer
 */
o2s_timer_t o2s_timer_create()
{
	o2s_timer_t     timer;
	struct sigevent event = {
	    .sigev_notify   = SIGEV_THREAD_ID,
	    .sigev_signo    = SIGALRM,
	    ._sigev_un._tid = gettid(),
	};

	timer.created = (timer_create(CLOCK_REALTIME, &event, &timer.timer_id) == 0);
	if (not timer.created)
		log_error("Unable to create a timer: %s", strerror(errno));
	return timer;
}

/**
 * Arm timer for the specified duration, in milliseconds.
 * @return another timer object whose member armed is false if unable to start
 */
o2s_timer_t o2s_timer_start(o2s_timer_t timer, unsigned milliseconds)
{
	struct itimerspec duration = {
	    .it_value.tv_nsec = MS_IN_NS * (milliseconds % MS_PER_S),
	    .it_value.tv_sec  = milliseconds / MS_PER_S,
	};

	timer.armed = (timer_settime(timer.timer_id, 0, &duration, NULL) == 0);
	if (not timer.armed)
		log_error("Unable to arm timer: %s", strerror(errno));
	return timer;
}

/** Disarm timer */
void o2s_timer_stop(o2s_timer_t* timer)
{
	struct itimerspec duration = {0};

	if (not timer->armed)
	{
		log_debug("No need to disarm a disarmed timer");
		return;
	}
	if (timer_settime(timer->timer_id, 0, &duration, NULL) == 0)
		return;
	log_error("Unable to disarm timer: %s", strerror(errno));
}

/** Destructor */
void o2s_timer_delete(o2s_timer_t* timer)
{
	if (not timer->created)
	{
		log_debug("No need to delete a non-created timer");
		return;
	}
	if (timer_delete(timer->timer_id) == 0)
		return;
	log_error("Unable to delete timer: %s", strerror(errno));
}
