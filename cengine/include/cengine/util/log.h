#ifndef _CE_UTIL_LOG_H_
#define _CE_UTIL_LOG_H_

#include <string.h>
#include <stdio.h>

#define FILENAME (strrchr("/" __FILE__, '/') + 1)

#if defined(_MSC_VER)
    #define CE_BREAKPOINT __debugbreak()
#else
    #include <signal.h>
    #define CE_BREAKPOINT raise(SIGTRAP)
#endif

enum
{
    CE_LOG_LEVEL_trace = 1U << 0,
    CE_LOG_LEVEL_debug = 1U << 1,
    CE_LOG_LEVEL_info  = 1U << 2,
    CE_LOG_LEVEL_warn  = 1U << 3,
    CE_LOG_LEVEL_error = 1U << 4,
    CE_LOG_LEVEL_fatal = 1U << 5,

    CE_LOG_LEVEL_max = 255U
};

#define ce_logTrace(...)\
    ce__log(CE_LOG_LEVEL_trace, __func__, FILENAME, __LINE__, __VA_ARGS__)

#define ce_logDebug(...)\
    ce__log(CE_LOG_LEVEL_debug, __func__, FILENAME, __LINE__, __VA_ARGS__)

#define ce_logInfo(...)\
    ce__log(CE_LOG_LEVEL_info,  __func__, FILENAME, __LINE__, __VA_ARGS__)

#define ce_logWarn(...)\
    ce__log(CE_LOG_LEVEL_warn,  __func__, FILENAME, __LINE__, __VA_ARGS__)

#define ce_logError(...)\
    ce__log(CE_LOG_LEVEL_error, __func__, FILENAME, __LINE__, __VA_ARGS__)

#define ce_logFatal(...)                                                        \
    do {                                                                        \
        ce__log(CE_LOG_LEVEL_fatal, __func__, FILENAME, __LINE__, __VA_ARGS__); \
        CE_BREAKPOINT;                                                          \
    } while (0)

#define ce_logt(...) ce_logTrace(__VA_ARGS__)
#define ce_logd(...) ce_logDebug(__VA_ARGS__)
#define ce_logi(...) ce_logInfo(__VA_ARGS__)
#define ce_logw(...) ce_logWarn(__VA_ARGS__)
#define ce_loge(...) ce_logError(__VA_ARGS__)
#define ce_logf(...) ce_logFatal(__VA_ARGS__)

void ce_logEnable(unsigned char mask);
void ce_logDisable(unsigned char mask);

void ce__log(int level, const char* func, const char* file, int line, const char* fmt, ...);

#endif /* _CE_UTIL_LOG_H_ */
