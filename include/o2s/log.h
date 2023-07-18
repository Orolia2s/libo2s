#pragma once

#include <stdio.h> //printf

#define log_log(LEVEL, FORMAT, ...) printf("[" LEVEL "]" FORMAT "\n" , ## __VA_ARGS__ )

#define log_trace(...) log_log("TRACE", __VA_ARGS__)
#define log_debug(...) log_log("DEBUG", __VA_ARGS__)
#define log_info(...)  log_log("INFO", __VA_ARGS__)
#define log_warn(...)  log_log("WARN", __VA_ARGS__)
#define log_error(...) log_log("ERROR", __VA_ARGS__)
#define log_fatal(...) log_log("FATAL", __VA_ARGS__)
