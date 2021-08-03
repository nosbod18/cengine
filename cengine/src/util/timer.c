#include "cengine/util/timer.h"

#include <stdio.h>


#if defined(_WIN32)

    typedef long time_t;

    /* https://stackoverflow.com/a/31335254 */

    struct timespec { long tv_sec; long tv_nsec; };

    static int clock_gettime(int, struct timespec *spec)
    {
        __int64 wintime;
        GetSystemTimeAsFileTime((FILETIME*)&wintime);

        wintime      -= 116444736000000000i64;       /* 1jan1601 to 1jan1970 */
        spec->tv_sec  = wintime / 10000000i64;       /* seconds */
        spec->tv_nsec = wintime % 10000000i64 * 100; /* nano-seconds */
        return 0;
    }

#else /* _WIN32 */
    #include <time.h>
#endif /* _WIN32 */


double
ce_timeNow(void)
{
    struct timespec ts = {0};
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (double)ts.tv_sec + ((double)ts.tv_nsec * 1.0e9);
}

ce_Timer
ce_timerStart(void)
{
    return ce_timeNow();
}

double
ce_timerSplit(ce_Timer* timer)
{
    const double now = ce_timeNow();
    const double elapsed = now - *timer;

    *timer = now;
    return elapsed;
}

double
ce_timerRead(const ce_Timer timer)
{
    return ce_timeNow() - timer;
}

void
ce_timeStamp(char* buf)
{
    struct timespec ts = {0};
    clock_gettime(CLOCK_MONOTONIC, &ts);
    long milli = (long)(((double)ts.tv_nsec / 1.0e6) + 0.5);

    time_t now;
    time(&now);
    struct tm* tm = localtime(&now);

    strftime(buf, 32, "%H:%M:%S", tm);
    int count = snprintf(buf, 32, "%s.%3ld", buf, milli);
    buf[count] = '\0';
}
