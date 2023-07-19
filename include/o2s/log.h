#pragma once

#include <stdio.h> // fprintf, stdout, stderr

/*
#define LOG_LEVEL_FATAL   0
#define LOG_LEVEL_ERROR   1
*/
#define LOG_LEVEL_WARNING 2
#define LOG_LEVEL_INFO    3
#define LOG_LEVEL_DEBUG   4
#define LOG_LEVEL_TRACE   5

#ifndef LOG_LEVEL
# define LOG_LEVEL LOG_LEVEL_INFO
#endif

#define log_log(FILE, LEVEL, COLOR, FORMAT, ...) fprintf(FILE, "[\e[" COLOR "m" LEVEL "\e[0m]\e[2m %s@%s:%03i \e[0m" FORMAT "\n", __FILE__, __FUNCTION__, __LINE__ , ## __VA_ARGS__ )

#if LOG_LEVEL >= LOG_LEVEL_TRACE
# define log_trace(...) log_log(stdout, "TRACE", "0", __VA_ARGS__)
#else
# define log_trace(...)
#endif

#if LOG_LEVEL >= LOG_LEVEL_DEBUG
#define log_debug(...) log_log(stdout, "DEBUG", "34", __VA_ARGS__)
#else
#define log_debug(...)
#endif

#if LOG_LEVEL >= LOG_LEVEL_INFO
# define log_info(...)  log_log(stdout, "INFO ", "1;32", __VA_ARGS__)
#else
# define log_info(...)
#endif

#define log_warning(...) log_log(stderr, "WARN ", "1;33", __VA_ARGS__)
#define log_error(...) log_log(stderr, "ERROR", "1;31", __VA_ARGS__)
#define log_fatal(...) log_log(stderr, "FATAL", "1;97;41", __VA_ARGS__)
