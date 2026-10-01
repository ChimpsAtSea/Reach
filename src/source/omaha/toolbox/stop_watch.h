#ifndef __STOP_WATCH_H__
#define __STOP_WATCH_H__
#pragma once

/* ---------- headers */

/* ---------- constants */

/* ---------- definitions */

class c_default_stop_watch_traits
{
public:
    static __int64 cycles_per_second(void);
    static __int64 get_absolute_time(void);
};

class c_thread_stop_watch_traits
{
public:
    static __int64 cycles_per_second(void);
    static __int64 get_absolute_time(void);
};

class c_kernel_stop_watch_traits
{
public:
    static __int64 cycles_per_second(void);
    static __int64 get_absolute_time(void);
};

class c_game_time_stop_watch_traits
{
public:
    static __int64 cycles_per_second(void);
    static __int64 get_absolute_time(void);
};

class c_rasterizer_frame_stop_watch_traits
{
public:
    static __int64 cycles_per_second(void);
    static __int64 get_absolute_time(void);
};

class c_tick_stop_watch_traits
{
public:
    static __int64 cycles_per_second(void);
    static __int64 get_absolute_time(void);
};

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __STOP_WATCH_H__

