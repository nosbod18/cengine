#include "cengine/core/log.h"
#include "cengine/core/timer.h"

#include <stdio.h>
#include <stdarg.h>

static unsigned char level_mask = CE_LOG_LEVEL_max;

static const char* ce__logLevelName(int level)
{
    switch (level)
    {
        case CE_LOG_LEVEL_trace:  return "TRACE";
        case CE_LOG_LEVEL_debug:  return "DEBUG";
        case CE_LOG_LEVEL_info:   return "INFO";
        case CE_LOG_LEVEL_warn:   return "WARN";
        case CE_LOG_LEVEL_error:  return "ERROR";
        case CE_LOG_LEVEL_fatal:  return "FATAL";
        case CE_LOG_LEVEL_assert: return "ASSERT";
    };

    return "";
}

static const char* ce_logLevelColor(int level)
{
    switch (level)
    {
        case CE_LOG_LEVEL_trace:  return "\033[35m";
        case CE_LOG_LEVEL_debug:  return "\033[36m";
        case CE_LOG_LEVEL_info:   return "\033[32m";
        case CE_LOG_LEVEL_warn:   return "\033[33m";
        case CE_LOG_LEVEL_error:  return "\033[91m";

        case CE_LOG_LEVEL_fatal:
        case CE_LOG_LEVEL_assert: return "\033[31;1m";
    }

    return "";
}

void
ce_logEnable(unsigned char mask)
{
    level_mask |= mask;
}

void
ce_logDisable(unsigned char mask)
{
    level_mask &= ~mask;
}

void
ce__log(int level, const char* file, int line, const char* func, const char* fmt, ...)
{
    if (!(level_mask & level))
        return;

    va_list ap;

    va_start(ap, fmt);
    fprintf(stderr,
            "[%s:%3d] [%s%-5s%s] %s(): ",
            file,
            line,
            ce_logLevelColor(level),
            ce__logLevelName(level),
            "\033[0m",
            func);
    vfprintf(stderr, fmt, ap);
    fprintf(stderr, "\n");
    va_end(ap);
}
