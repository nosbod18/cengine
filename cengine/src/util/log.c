#include "cengine/util/log.h"
#include "cengine/util/timer.h"

#include <stdio.h>
#include <stdarg.h>

static unsigned char level_mask = CE_LOG_LEVEL_max;

static const char* ce__logLevelName(int level)
{
    switch (level)
    {
        case CE_LOG_LEVEL_trace: return "TRACE";
        case CE_LOG_LEVEL_debug: return "DEBUG";
        case CE_LOG_LEVEL_info:  return "INFO";
        case CE_LOG_LEVEL_warn:  return "WARN";
        case CE_LOG_LEVEL_error: return "ERROR";
        case CE_LOG_LEVEL_fatal: return "FATAL";
    };

    return "";
}

static const char* ce_logLevelColor(int level)
{
    switch (level)
    {
        case CE_LOG_LEVEL_trace: return "\033[35m";
        case CE_LOG_LEVEL_debug: return "\033[36m";
        case CE_LOG_LEVEL_info:  return "\033[32m";
        case CE_LOG_LEVEL_warn:  return "\033[33m";
        case CE_LOG_LEVEL_error: return "\033[91m";
        case CE_LOG_LEVEL_fatal: return "\033[31;1m";
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
ce__log(int level, const char* func, const char* file, int line, const char* fmt, ...)
{
    if (!(level_mask & level))
        return;

    va_list ap;

    char now[32];
    ce_timeStamp(now);

    va_start(ap, fmt);
    fprintf(stderr,
            "[%s] [%s%-5s%s] [%s:%s:%d] ",
            now,
            ce_logLevelColor(level),
            ce__logLevelName(level),
            "\033[0m",
            func,
            file,
            line);
    vfprintf(stderr, fmt, ap);
    fprintf(stderr, "\n");
    va_end(ap);
}
