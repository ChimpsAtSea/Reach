/* ---------- headers */

#include "baselib\system_time_windows.h"

#include <xtl.h>
#include <time.h>

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// __int64 system_seconds_since_1970(void);
// unsigned long system_seconds_since_1970_UNSAFE(void);
// __int64 system_performance_timer_get(void);
// __int64 system_performance_timer_frequency(void);

__int64 system_seconds_since_1970(void)
{
    mangled_ppc("?system_seconds_since_1970@@YA_JXZ");

    __time64_t current_time;

    _time64(&current_time);

    return current_time;
};

unsigned long system_seconds_since_1970_UNSAFE(void)
{
    mangled_ppc("?system_seconds_since_1970_UNSAFE@@YAKXZ");

    return static_cast<unsigned long>(system_seconds_since_1970());
};

__int64 system_performance_timer_get(void)
{
    mangled_ppc("?system_performance_timer_get@@YA_JXZ");

    LARGE_INTEGER counter;

    QueryPerformanceCounter(&counter);

    return counter.QuadPart;
};

__int64 system_performance_timer_frequency(void)
{
    mangled_ppc("?system_performance_timer_frequency@@YA_JXZ");

    LARGE_INTEGER frequency;

    QueryPerformanceFrequency(&frequency);

    return frequency.QuadPart;
};

