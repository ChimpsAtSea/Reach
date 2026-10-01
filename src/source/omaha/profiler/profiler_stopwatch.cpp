#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\profiler\\profiler_stopwatch.cpp"
/* ---------- headers */

#include "omaha\profiler\profiler_stopwatch.h"
#include "core\corelib\cseries\cseries_asserts.h"

#include <ppcintrinsics.h>

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// public: c_stop_watch::c_stop_watch(void);
// public: c_stop_watch::c_stop_watch(bool);
// public: __int64 c_stop_watch::start(void);
// public: __int64 c_stop_watch::hold(void);
// public: __int64 c_stop_watch::reset(void);
// public: __int64 c_stop_watch::stop(void);
// public: bool c_stop_watch::paused(void) const;
// private: __int64 c_stop_watch::get_current_delta(void) const;
// private: static __int64 c_stop_watch::get_absolute_time(void);
// public: static __int64 c_stop_watch::cycles_per_second(void);
// public: static float c_stop_watch::cycles_to_seconds(__int64);
// public: __int64 c_stop_watch::total_elapsed_time_in_cycles(void) const;
// public: float c_stop_watch::total_elapsed_time_in_seconds(void) const;

c_stop_watch::c_stop_watch()
{
    mangled_ppc("??0c_stop_watch@@QAA@XZ");

    m_total_time = 0;
    m_start_time = get_absolute_time();
    m_paused = false;
};

c_stop_watch::c_stop_watch(bool start_paused)
{
    mangled_ppc("??0c_stop_watch@@QAA@_N@Z");

    m_total_time = 0;
    m_start_time = get_absolute_time();
    m_paused = start_paused;
};

__int64 c_stop_watch::start()
{
    mangled_ppc("?start@c_stop_watch@@QAA_JXZ");

    __int64 result = total_elapsed_time_in_cycles();
    if (m_paused)
    {
        m_paused = false;
        m_start_time = get_absolute_time();
    }
    return result;
};

__int64 c_stop_watch::hold()
{
    mangled_ppc("?hold@c_stop_watch@@QAA_JXZ");

    if (!m_paused)
    {
        m_total_time += get_current_delta();
        m_paused = true;
    }
    return m_total_time;
};

__int64 c_stop_watch::reset()
{
    mangled_ppc("?reset@c_stop_watch@@QAA_JXZ");

    __int64 result = stop();
    start();
    return result;
};

__int64 c_stop_watch::stop()
{
    mangled_ppc("?stop@c_stop_watch@@QAA_JXZ");

    __int64 result = hold();
    m_total_time = 0;
    return result;
};

bool c_stop_watch::paused() const
{
    mangled_ppc("?paused@c_stop_watch@@QBA_NXZ");

    return m_paused;
};

__int64 c_stop_watch::get_current_delta() const
{
    mangled_ppc("?get_current_delta@c_stop_watch@@ABA_JXZ");

    __int64 result = 0;
    assert_tag_debug_untracked_jul_11_2011(85, !m_paused);

    result = get_absolute_time() - m_start_time;
    if (result < 0)
    {
        result = 0;
    }
    return result;
};

__int64 c_stop_watch::get_absolute_time()
{
    mangled_ppc("?get_absolute_time@c_stop_watch@@CA_JXZ");

    __int64 result = 0;
    result = __mftb();
    return result;
};

__int64 c_stop_watch::cycles_per_second()
{
    mangled_ppc("?cycles_per_second@c_stop_watch@@SA_JXZ");

    __int64 result = 1000;
    result = 49875000;
    return result;
};

float c_stop_watch::cycles_to_seconds(__int64 cycles)
{
    mangled_ppc("?cycles_to_seconds@c_stop_watch@@SAM_J@Z");

    __int64 cycles_per_second = c_stop_watch::cycles_per_second();
    float result;
    __int64 seconds = cycles / cycles_per_second;
    __int64 remainder = cycles - seconds * cycles_per_second;
    result = static_cast<float>(remainder) / static_cast<float>(cycles_per_second);
    result += static_cast<float>(seconds);
    return result;
};

__int64 c_stop_watch::total_elapsed_time_in_cycles() const
{
    mangled_ppc("?total_elapsed_time_in_cycles@c_stop_watch@@QBA_JXZ");

    __int64 result = m_total_time;
    if (!m_paused)
    {
        result += get_current_delta();
    }
    return result;
};

float c_stop_watch::total_elapsed_time_in_seconds() const
{
    mangled_ppc("?total_elapsed_time_in_seconds@c_stop_watch@@QBAMXZ");

    __int64 cycles = total_elapsed_time_in_cycles();
    float time_in_seconds = cycles_to_seconds(cycles);
    return time_in_seconds;
};
