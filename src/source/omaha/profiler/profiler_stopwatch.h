#pragma once
#ifndef __PROFILER_STOPWATCH_H__
#define __PROFILER_STOPWATCH_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"

/* ---------- constants */

/* ---------- definitions */

class c_stop_watch
{
public:
    c_stop_watch();
    c_stop_watch(bool start_paused);
    ~c_stop_watch();

    __int64 start();
    __int64 hold();
    __int64 reset();
    __int64 stop();
    bool paused() const;
    static __int64 cycles_per_second();
    static float cycles_to_seconds(__int64 cycles);
    __int64 total_elapsed_time_in_cycles() const;
    float total_elapsed_time_in_seconds() const;

private:
    __int64 get_current_delta() const;
    static __int64 get_absolute_time();

    __int64 m_total_time; // 0x0
    __int64 m_start_time; // 0x8
    bool m_paused; // 0x10
};
static_assert(sizeof(c_stop_watch) == 0x18, "c_stop_watch");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __PROFILER_STOPWATCH_H__

