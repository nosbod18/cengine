#include "engine/core/log.h"
#include "engine/core/timer.h"

#include <stdio.h>
#include <stdarg.h>

static unsigned char level_mask = LOG_LEVEL_MAX;

static const char* log_level_name__(int level)
{
    switch (level)
    {
        case LOG_LEVEL_TRACE:  return "TRACE";
        case LOG_LEVEL_DEBUG:  return "DEBUG";
        case LOG_LEVEL_INFO:   return "INFO";
        case LOG_LEVEL_WARN:   return "WARN";
        case LOG_LEVEL_ERROR:  return "ERROR";
        case LOG_LEVEL_FATAL:  return "FATAL";
        case LOG_LEVEL_ASSERT: return "ASSERT";
    };

    return "";
}

static const char* log_level_color__(int level)
{
    switch (level)
    {
        case LOG_LEVEL_TRACE:  return "\033[35m";
        case LOG_LEVEL_DEBUG:  return "\033[36m";
        case LOG_LEVEL_INFO:   return "\033[32m";
        case LOG_LEVEL_WARN:   return "\033[33m";
        case LOG_LEVEL_ERROR:  return "\033[91m";

        case LOG_LEVEL_FATAL:
        case LOG_LEVEL_ASSERT: return "\033[31;1m";
    }

    return "";
}

void
log_enable(unsigned char mask)
{
    level_mask |= mask;
}

void
log_disable(unsigned char mask)
{
    level_mask &= ~mask;
}

void
log__log(int level,
         const char* file,
         int line,
         const char* func,
         const char* fmt,
         ...)
{
    if (!(level_mask & level))
        return;

    va_list ap;

    va_start(ap, fmt);
    fprintf(stderr,
            "[%8s:%3d] [%s%-5s%s] %s(): ",
            file,
            line,
            log_level_color__(level),
            log_level_name__(level),
            "\033[0m",
            func);
    vfprintf(stderr, fmt, ap);
    fprintf(stderr, "\n");
    va_end(ap);
}
