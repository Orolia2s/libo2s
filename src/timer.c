/* ************************************************************************** */
/*      ____    _    _____ ____     _    _   _   _____ _  _   ____  ____      */
/*     / ___|  / \  |  ___|  _ \   / \  | \ | | |_   _| || | |  _ \/ ___|     */
/*     \___ \ / _ \ | |_  | |_) | / _ \ |  \| |   | | | || |_| | | \___ \     */
/*      ___) / ___ \|  _| |  _ < / ___ \| |\  |   | | |__   _| |_| |___) |    */
/*     |____/_/   \_|_|   |_| \_/_/   \_|_| \_|   |_|    |_| |____/|____/     */
/*                                                                            */
/**
 * @copyright 2023, SAFRAN T4DS, ALL RIGHTS RESERVED
 * @file timer.c
 * @author Antoine GAGNIERE
 * @brief Use timeouts backed by signals and realtime clock
 */
/* ************************************************************************** */

#define _GNU_SOURCE

#include "o2s/timer.h"

#include "o2s/log.h"

#include <errno.h>
#include <signal.h> // sigaction
#include <string.h> // strerror
#include <time.h>   // timer_*
#include <unistd.h> // gettid

/**
 * Prepare the process for timeouts.
 * Needed to be called only once, preferably before creating the threads.
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
 */
timer_t o2s_timer_create(void)
{
	timer_t         timer;
	struct sigevent event = {.sigev_notify   = SIGEV_THREAD_ID,
	                         .sigev_signo    = SIGALRM,
	                         ._sigev_un._tid = gettid()};

	if (timer_create(CLOCK_REALTIME, &event, &timer) == 0)
		return timer;
	log_error("Unable to create a timer: %s", strerror(errno));
	return NULL;
}

/** Arm timer for the specified duration, in milliseconds */
timer_t o2s_timer_start(timer_t timer, unsigned milliseconds)
{
	struct itimerspec duration = {.it_value.tv_nsec = 1000000UL * (milliseconds % 1000),
	                              .it_value.tv_sec = milliseconds / 1000};

	if (timer_settime(timer, 0, &duration, NULL) == 0)
		return timer;
	log_error("Unable to arm timer: %s", strerror(errno));
	return NULL;
}

/** Disarm timer */
void o2s_timer_stop(timer_t* timer)
{
	struct itimerspec duration = {0};

	if (timer_settime(*timer, 0, &duration, NULL) == 0)
		return;
	log_error("Unable to disarm timer: %s", strerror(errno));
}

/** Destructor */
void o2s_timer_delete(timer_t* timer)
{
	if (timer_delete(*timer) == 0)
		return;
	log_error("Unable to delete timer: %s", strerror(errno));
}
