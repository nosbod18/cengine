#ifndef __CORE_LOG_H__
#define __CORE_LOG_H__

#include "cengine/core/base.h"

#if COMPILER_MSVC
    #define DEBUG_BREAK __debugbreak()
#else
    #include <signal.h>
    #define DEBUG_BREAK raise(SIGTRAP)
#endif

enum
{
    LOG_LEVEL_TRACE  = BIT(0),
    LOG_LEVEL_DEBUG  = BIT(1),
    LOG_LEVEL_INFO   = BIT(2),
    LOG_LEVEL_WARN   = BIT(3),
    LOG_LEVEL_ERROR  = BIT(4),
    LOG_LEVEL_FATAL  = BIT(5),
    LOG_LEVEL_ASSERT = BIT(6),

    LOG_LEVEL_MAX = BIT(8) - 1
};

#define log_trace(...)\
    log__log(LOG_LEVEL_TRACE, FILENAME, __LINE__, __func__, __VA_ARGS__)

#define log_debug(...)\
    log__log(LOG_LEVEL_DEBUG, FILENAME, __LINE__, __func__, __VA_ARGS__)

#define log_info(...)\
    log__log(LOG_LEVEL_INFO,  FILENAME, __LINE__, __func__, __VA_ARGS__)

#define log_warn(...)\
    log__log(LOG_LEVEL_WARN,  FILENAME, __LINE__, __func__, __VA_ARGS__)

#define log_error(...)\
    log__log(LOG_LEVEL_ERROR, FILENAME, __LINE__, __func__, __VA_ARGS__)

#define log_fatal(...)                                                          \
    do {                                                                        \
        log__log(LOG_LEVEL_FATAL, FILENAME, __LINE__, __func__, __VA_ARGS__);   \
        DEBUG_BREAK;                                                            \
    } while (0)

#define log_assert(x_, ...)\
    do {                                                                            \
        if (!(x_)) {                                                                \
            log__log(LOG_LEVEL_ASSERT, FILENAME, __LINE__, __func__, __VA_ARGS__);  \
            DEBUG_BREAK;                                                            \
        }                                                                           \
    } while (0)

#define logt(...)     log_trace(__VA_ARGS__)
#define logd(...)     log_debug(__VA_ARGS__)
#define logi(...)     log_info(__VA_ARGS__)
#define logw(...)     log_warn(__VA_ARGS__)
#define loge(...)     log_error(__VA_ARGS__)
#define logf(...)     log_fatal(__VA_ARGS__)
#define loga(x_, ...) log_assert(x_, __VA_ARGS__)

void log_enable(unsigned char mask);
void log_disable(unsigned char mask);

void log__log(int level,
              const char* file,
              int line,
              const char* func,
              const char* fmt,
              ...);

#endif /* __CORE_LOG_H__ */
