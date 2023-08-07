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
 * @file log.h
 * @author Antoine GAGNIERE
 * @author Hugo FOLCHER
 * @brief Simplistic logging utilities
 */
/* ************************************************************************** */

#include <stdio.h> // fprintf, stdout, stderr

#define LOG_LEVEL_NONE    0
#define LOG_LEVEL_FATAL   1
#define LOG_LEVEL_ERROR   2
#define LOG_LEVEL_WARNING 3
#define LOG_LEVEL_INFO    4
#define LOG_LEVEL_DEBUG   5
#define LOG_LEVEL_TRACE   6

#ifndef LOG_LEVEL
/** Set this value to control the logs verbosity */
#	define LOG_LEVEL LOG_LEVEL_INFO
#endif

#define log_log(FILE, LEVEL, COLOR, FORMAT, ...) \
	fprintf(FILE, \
	        "[\e[" COLOR "m" LEVEL "\e[0m]\e[2m " __FILE__ ":%s:%02i: \e[0m" FORMAT "\n", \
	        __FUNCTION__, \
	        __LINE__, \
	        ##__VA_ARGS__)

#if LOG_LEVEL >= LOG_LEVEL_TRACE
#	define log_trace(...) log_log(stdout, "TRACE", "0", __VA_ARGS__)
#else
/** Report information of the lowest importance */
#	define log_trace(...)
#endif

#if LOG_LEVEL >= LOG_LEVEL_DEBUG
#	define log_debug(...) log_log(stdout, "DEBUG", "34", __VA_ARGS__)
#else
/** Report information useful to the developer */
#	define log_debug(...)
#endif

#if LOG_LEVEL >= LOG_LEVEL_INFO
/** Report a significant event */
#	define log_info(...) log_log(stdout, "INFO ", "1;32", __VA_ARGS__)
#else
#	define log_info(...)
#endif

#if LOG_LEVEL >= LOG_LEVEL_WARNING
/** Report an usual condition, not significant enough to abort the current operation */
#	define log_warning(...) log_log(stderr, "WARN ", "1;33", __VA_ARGS__)
#else
#	define log_warning(...)
#endif

#if LOG_LEVEL >= LOG_LEVEL_ERROR
/** Report a condition causing the current operation to abort */
#	define log_error(...) log_log(stderr, "ERROR", "1;31", __VA_ARGS__)
#else
#	define log_error(...)
#endif

#if LOG_LEVEL >= LOG_LEVEL_FATAL
/** Report a condition causing the program to halt */
#	define log_fatal(...) log_log(stderr, "FATAL", "1;97;41", __VA_ARGS__)
#else
#	define log_fatal(...)
#endif
