#pragma once

#include <stdio.h> //printf

#define log_trace(...) \
	do \
	{ \
		printf("[TRACE] "); \
		printf(__VA_ARGS__); \
		printf("\n"); \
	} while (0)
#define log_debug(...) \
	do \
	{ \
		printf("[DEBUG] "); \
		printf(__VA_ARGS__); \
		printf("\n"); \
	} while (0)
#define log_info(...) \
	do \
	{ \
		printf("[INFO] "); \
		printf(__VA_ARGS__); \
		printf("\n"); \
	} while (0)
#define log_warn(...) \
	do \
	{ \
		printf("[WARN] "); \
		printf(__VA_ARGS__); \
		printf("\n"); \
	} while (0)
#define log_error(...) \
	do \
	{ \
		printf("[ERROR] "); \
		printf(__VA_ARGS__); \
		printf("\n"); \
	} while (0)
#define log_fatal(...) \
	do \
	{ \
		printf("[FATAL] "); \
		printf(__VA_ARGS__); \
		printf("\n"); \
	} while (0)