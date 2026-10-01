/* ---------- headers */

#include "omaha\toolbox\stop_watch.h"
#include "omaha\game\game_time.h"
#include "omaha\main\main_time.h"
#include "baselib\system_time_xenon.h"

#include <xtl.h>

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// public: static __int64 c_default_stop_watch_traits::get_absolute_time(void);
// public: static __int64 c_default_stop_watch_traits::cycles_per_second(void);
// public: static __int64 c_thread_stop_watch_traits::get_absolute_time(void);
// public: static __int64 c_thread_stop_watch_traits::cycles_per_second(void);
// public: static __int64 c_kernel_stop_watch_traits::get_absolute_time(void);
// public: static __int64 c_kernel_stop_watch_traits::cycles_per_second(void);
// public: static __int64 c_game_time_stop_watch_traits::get_absolute_time(void);
// public: static __int64 c_game_time_stop_watch_traits::cycles_per_second(void);
// public: static __int64 c_rasterizer_frame_stop_watch_traits::cycles_per_second(void);
// public: static __int64 c_rasterizer_frame_stop_watch_traits::get_absolute_time(void);
// public: static __int64 c_tick_stop_watch_traits::cycles_per_second(void);
// public: static __int64 c_tick_stop_watch_traits::get_absolute_time(void);

__int64 c_default_stop_watch_traits::get_absolute_time(void)
{
    mangled_ppc("?get_absolute_time@c_default_stop_watch_traits@@SA_JXZ");

    __int64 result = __mftb();
    return result;
};

__int64 c_default_stop_watch_traits::cycles_per_second(void)
{
    mangled_ppc("?cycles_per_second@c_default_stop_watch_traits@@SA_JXZ");

    __int64 result = 49875000;
    return result;
};

__int64 c_thread_stop_watch_traits::get_absolute_time(void)
{
    mangled_ppc("?get_absolute_time@c_thread_stop_watch_traits@@SA_JXZ");

    __int64 result = 0;
    FILETIME dummy_times[3];
    GetThreadTimes(GetCurrentThread(), &dummy_times[0], &dummy_times[1], &dummy_times[2], reinterpret_cast<LPFILETIME>(&result));
    return result;
};

__int64 c_thread_stop_watch_traits::cycles_per_second(void)
{
    mangled_ppc("?cycles_per_second@c_thread_stop_watch_traits@@SA_JXZ");

    __int64 result = 10000000;
    return result;
};

__int64 c_kernel_stop_watch_traits::get_absolute_time(void)
{
    mangled_ppc("?get_absolute_time@c_kernel_stop_watch_traits@@SA_JXZ");

    __int64 result = 0;
    FILETIME dummy_times[3];
    GetThreadTimes(GetCurrentThread(), &dummy_times[0], &dummy_times[1], reinterpret_cast<LPFILETIME>(&result), &dummy_times[2]);
    return result;
};

__int64 c_kernel_stop_watch_traits::cycles_per_second(void)
{
    mangled_ppc("?cycles_per_second@c_kernel_stop_watch_traits@@SA_JXZ");

    __int64 result = 10000000;
    return result;
};

__int64 c_game_time_stop_watch_traits::get_absolute_time(void)
{
    mangled_ppc("?get_absolute_time@c_game_time_stop_watch_traits@@SA_JXZ");

    return game_time_get();
};

__int64 c_game_time_stop_watch_traits::cycles_per_second(void)
{
    mangled_ppc("?cycles_per_second@c_game_time_stop_watch_traits@@SA_JXZ");

    return game_tick_rate();
};

__int64 c_rasterizer_frame_stop_watch_traits::cycles_per_second(void)
{
    mangled_ppc("?cycles_per_second@c_rasterizer_frame_stop_watch_traits@@SA_JXZ");

    return main_time_get_absolute_rate();
};

__int64 c_rasterizer_frame_stop_watch_traits::get_absolute_time(void)
{
    mangled_ppc("?get_absolute_time@c_rasterizer_frame_stop_watch_traits@@SA_JXZ");

    return main_time_get_absolute();
};

__int64 c_tick_stop_watch_traits::cycles_per_second(void)
{
    mangled_ppc("?cycles_per_second@c_tick_stop_watch_traits@@SA_JXZ");

    return 1000;
};

__int64 c_tick_stop_watch_traits::get_absolute_time(void)
{
    mangled_ppc("?get_absolute_time@c_tick_stop_watch_traits@@SA_JXZ");

    return system_milliseconds();
};

