#ifndef _CE_CORE_LOG_H_
#define _CE_CORE_LOG_H_

#include "cengine/core/base.h"

#if CE_COMPILER_MSVC
    #define CE_BREAKPOINT __debugbreak()
#else
    #include <signal.h>
    #define CE_BREAKPOINT raise(SIGTRAP)
#endif

enum
{
    CE_LOG_LEVEL_trace  = 1U << 0,
    CE_LOG_LEVEL_debug  = 1U << 1,
    CE_LOG_LEVEL_info   = 1U << 2,
    CE_LOG_LEVEL_warn   = 1U << 3,
    CE_LOG_LEVEL_error  = 1U << 4,
    CE_LOG_LEVEL_fatal  = 1U << 5,
    CE_LOG_LEVEL_assert = 1U << 6,

    CE_LOG_LEVEL_max = (1U << 8) - 1
};

#define ce_trace(...)\
    ce__log(CE_LOG_LEVEL_trace, FILENAME, __LINE__, __func__, __VA_ARGS__)

#define ce_debug(...)\
    ce__log(CE_LOG_LEVEL_debug, FILENAME, __LINE__, __func__, __VA_ARGS__)

#define ce_info(...)\
    ce__log(CE_LOG_LEVEL_info,  FILENAME, __LINE__, __func__, __VA_ARGS__)

#define ce_warn(...)\
    ce__log(CE_LOG_LEVEL_warn,  FILENAME, __LINE__, __func__, __VA_ARGS__)

#define ce_error(...)\
    ce__log(CE_LOG_LEVEL_error, FILENAME, __LINE__, __func__, __VA_ARGS__)

#define ce_fatal(...)                                                           \
    do {                                                                        \
        ce__log(CE_LOG_LEVEL_fatal, FILENAME, __LINE__, __func__, __VA_ARGS__); \
        CE_BREAKPOINT;                                                          \
    } while (0)

#define ce_assert(cond_, ...)\
    do {                                                                            \
        if (!(cond_)) {                                                             \
            ce__log(CE_LOG_LEVEL_assert, FILENAME, __LINE__, __func__, __VA_ARGS__);\
            CE_BREAKPOINT;                                                          \
        }                                                                           \
    } while (0)

void ce_logEnable(unsigned char mask);
void ce_logDisable(unsigned char mask);

void ce__log(int level, const char* file, int line, const char* func, const char* fmt, ...);

#endif /* _CE_CORE_LOG_H_ */
