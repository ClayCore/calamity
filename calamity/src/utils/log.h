#pragma once

#include "common.h"

// different colors for printing log messages
typedef enum { RESET = 0, RED = 31, GREEN, YELLOW, BLUE, MAGENTA, CYAN } log_colors;

// used internally for checking what log level we're printing on.
enum log_levels_t { TRACE, INFO, DEBUG, WARN, ERROR };
internal enum log_levels_t log_levels;

void log_helper(enum log_levels_t level, i8 color, const char* format, ...);

void log_trace(const char* format, ...);
void log_info(const char* format, ...);
void log_debug(const char* format, ...);
void log_warn(const char* format, ...);
void log_error(const char* format, ...);
