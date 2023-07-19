#pragma once

#include <stdio.h> // fprintf, stdout, stderr

#define log_log(FILE, LEVEL, COLOR, FORMAT, ...) fprintf(FILE, "[\e[" COLOR "m" LEVEL "\e[0m] " FORMAT "\n" , ## __VA_ARGS__ )

#define log_trace(...) log_log(stdout, "TRACE", "0", __VA_ARGS__)
#define log_debug(...) log_log(stdout, "DEBUG", "34", __VA_ARGS__)
#define log_info(...)  log_log(stdout, "INFO ", "1;35", __VA_ARGS__)
#define log_warning(...) log_log(stderr, "WARN ", "1;33", __VA_ARGS__)
#define log_error(...) log_log(stderr, "ERROR", "1;31", __VA_ARGS__)
#define log_fatal(...) log_log(stderr, "FATAL", "1;97;41", __VA_ARGS__)
