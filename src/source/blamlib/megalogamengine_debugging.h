#pragma once
#ifndef __MEGALOGAMENGINE_DEBUGGING_H__
#define __MEGALOGAMENGINE_DEBUGGING_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"
#include "foundation\baselib\datatypes\static_array.h"
#include "omaha\profiler\profiler_stopwatch.h"
#include "omaha\render\render_debug_graph.h"

/* ---------- constants */

long const k_megalo_profiling_frame_count = 60;
long const k_megalo_profiling_trigger_count = 320;

// $TODO names inferred from megalogamengine_render_debug_profiling_info graph titles
enum e_megalo_profiling_mode
{
    _megalo_profiling_mode_none = 0,
    _megalo_profiling_mode_elapsed_time,
    _megalo_profiling_mode_execution_count,

    k_megalo_profiling_mode_count
};

/* ---------- definitions */

struct s_trigger_profile_info
{
    real elapsed_time; // 0x0 (milliseconds)
    long execution_count; // 0x4
};
static_assert(sizeof(s_trigger_profile_info) == 0x8, "s_trigger_profile_info");

struct s_frame_info
{
    s_trigger_profile_info triggers[k_megalo_profiling_trigger_count];
};
static_assert(sizeof(s_frame_info) == 0xA00, "s_frame_info");

struct s_megalogamengine_profiling_state
{
    s_static_array<s_frame_info, k_megalo_profiling_frame_count> frames; // 0x0
    long max_execution_count; // 0x25800
    real max_elapsed_time; // 0x25804
    long current_frame_index; // 0x25808
    long previous_frame_index; // 0x2580C
};
static_assert(sizeof(s_megalogamengine_profiling_state) == 0x25810, "s_megalogamengine_profiling_state");

class c_megalogamengine_profiling_info_iterator :
    public c_render_debug_graph_iterator
{
public:
    c_megalogamengine_profiling_info_iterator(void);

    virtual void begin_all_series(void);
    virtual bool next_series(c_static_string<256> * series_name);
    virtual bool next_data_point_in_series(real_point2d * point);

protected:
    long m_trigger_index; // 0x4
    long m_frame_offset; // 0x8
};
static_assert(sizeof(c_megalogamengine_profiling_info_iterator) == 0xC, "c_megalogamengine_profiling_info_iterator");

class megalogamengine_log_trigger_execution
{
public:
    megalogamengine_log_trigger_execution(long trigger_index);
    ~megalogamengine_log_trigger_execution(void);

protected:
    c_stop_watch m_stop_watch; // 0x0
    long m_trigger_index; // 0x18
};
static_assert(sizeof(megalogamengine_log_trigger_execution) == 0x20, "megalogamengine_log_trigger_execution");

/* ---------- prototypes */

extern void megalogamengine_debugging_initialize(void);
extern void megalogamengine_debugging_update_before_engine(void);
extern void megalogamengine_render_debug_profiling_info(void);

/* ---------- globals */

extern s_megalogamengine_profiling_state g_profiling_state;
extern long megalo_profiling_mode;

/* ---------- public code */

#endif // __MEGALOGAMENGINE_DEBUGGING_H__

