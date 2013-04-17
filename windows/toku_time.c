#include <windows.h>
#include <assert.h>
#include <toku_time.h>

int 
gettimeofday(struct timeval *tv, struct timezone *tz) {
    FILETIME ft;
    ULARGE_INTEGER t;

    GetSystemTimeAsFileTime(&ft);
    t.u.LowPart = ft.dwLowDateTime;
    t.u.HighPart = ft.dwHighDateTime;
    t.QuadPart -= 116444736000000000i64;
    t.QuadPart /= 10; // convert to microseconds
    if (tv) {
        tv->tv_sec = t.QuadPart / 1000000;
        tv->tv_usec = t.QuadPart % 1000000;
    }
    if (tz) {
        assert(0);
    }
    return 0;
}

static int
clock_get_realtime(struct timespec *ts) {
    FILETIME ft;
    ULARGE_INTEGER t;

    GetSystemTimeAsFileTime(&ft);
    t.u.LowPart = ft.dwLowDateTime;
    t.u.HighPart = ft.dwHighDateTime;
    t.QuadPart -= 116444736000000000i64;
    t.QuadPart *= 100; // convert to nanoseconds
    if (ts) {
        ts->tv_sec = t.QuadPart / 1000000000;
        ts->tv_nsec = t.QuadPart % 1000000000;
    }
    return 0;
}

int
clock_gettime(clockid_t clockid, struct timespec *ts) {
    if (clockid == CLOCK_REALTIME)
        return clock_get_realtime(ts);
    else
        return -1;
}
