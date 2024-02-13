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

#include <stdbool.h>
#include <time.h> // timer_t

bool    o2s_timer_setup_process(void);
timer_t o2s_timer_create(void);
timer_t o2s_timer_start(timer_t timer, unsigned milliseconds);
void    o2s_timer_stop(timer_t* timer);
void    o2s_timer_delete(timer_t* timer);

#define O2sTimer   __attribute__((cleanup(o2s_timer_delete))) timer_t
#define ArmedTimer __attribute__((cleanup(o2s_timer_stop))) timer_t
