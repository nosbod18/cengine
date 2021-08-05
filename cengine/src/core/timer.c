#include "cengine/core/timer.h"
#include "cengine/core/base.h"

#include <stdio.h>

#if PLATFORM_WINDOWS

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

#else /* PLATFORM_WINDOWS */
    #include <time.h>
#endif /* PLATFORM_WINDOWS */


double
time_now(void)
{
    struct timespec ts = {0};
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (double)ts.tv_sec + ((double)ts.tv_nsec * 1.0e9);
}

timer_t
timer_start(void)
{
    return time_now();
}

double
timer_split(timer_t* timer)
{
    const double now = time_now();
    const double elapsed = now - *timer;

    *timer = now;
    return elapsed;
}

double
timer_read(const timer_t timer)
{
    return time_now() - timer;
}

void
time_stamp(char* buf)
{
    struct timespec ts = {0};
    clock_gettime(CLOCK_MONOTONIC, &ts);
    long milli = (long)(((double)ts.tv_nsec / 1.0e6) + 0.5);

    time_t now;
    time(&now);
    struct tm* tm = localtime(&now);

    strftime(buf, 16, "%H:%M:%S", tm);
    int count = snprintf(buf, 16, "%s.%3ld", buf, milli);
    buf[count] = '\0';
}
