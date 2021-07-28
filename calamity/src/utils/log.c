#include "log.h"

// Prints a format string with a specific color.
void log_helper(enum log_levels_t level, i8 color, const char* format, ...) {
    printf("\x1b[%" PRId8 "m", color);

    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);

    log_colors reset = RESET;
    switch (level) {
        case TRACE:
        case DEBUG:
        case INFO:
            printf("\x1b[%" PRId8 "m", reset);
            break;
        case WARN:
        case ERROR:
            fprintf(stderr, "\x1b[%" PRId8 "m", reset);
            break;
    }
}

void log_trace(const char* format, ...) {
    log_colors color = BLUE;

    va_list args;
    va_start(args, format);
    log_helper(0, color, format, args);
    va_end(args);
}

void log_debug(const char* format, ...) {
    log_colors color = CYAN;

    va_list args;
    va_start(args, format);
    log_helper(1, color, format, args);
    va_end(args);
}

void log_info(const char* format, ...) {
    log_colors color = GREEN;

    va_list args;
    va_start(args, format);
    log_helper(2, color, format, args);
    va_end(args);
}

void log_warn(const char* format, ...) {
    log_colors color = YELLOW;

    va_list args;
    va_start(args, format);
    log_helper(3, color, format, args);
    va_end(args);
}

void log_error(const char* format, ...) {
    log_colors color = RED;

    va_list args;
    va_start(args, format);
    log_helper(4, color, format, args);
    va_end(args);
}
