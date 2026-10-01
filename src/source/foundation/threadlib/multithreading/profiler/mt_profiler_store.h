#pragma once
#ifndef __MT_PROFILER_STORE_H__
#define __MT_PROFILER_STORE_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"

/* ---------- constants */

/* ---------- definitions */

// $TODO: enumerator names unknown (c_job::execute uses 6, c_job_list::return_to_free_list uses 10)
enum e_mt_color
{
    k_mt_color_none = 0,
};

// $TODO: enumerator names unknown; 1..3 select a performance-counter setup (see mt_profiler_internal::get_hw_counter)
enum e_mt_profiler_mode
{
    _mt_profiler_mode_none = 0,
    _mt_profiler_mode_1,
    _mt_profiler_mode_2,
    _mt_profiler_mode_3,

    k_mt_profiler_mode_count
};

struct s_storage_context
{
    void set_start(float start)
    {
        mangled_ppc("?set_start@s_storage_context@@QAAXM@Z");

        start_time = encode(start);
    }

    unsigned short encode(float value)
    {
        mangled_ppc("?encode@s_storage_context@@QAAGM@Z");

        unsigned short integer = static_cast<unsigned short>(value);
        unsigned short fraction = static_cast<unsigned short>(512.0f * (value - integer));
        return (integer << 9) | fraction;
    }

    void set_end(float end)
    {
        mangled_ppc("?set_end@s_storage_context@@QAAXM@Z");

        end_time = encode(end);
    }

    float user_hw;
    unsigned short start_time;
    unsigned short end_time;
    unsigned short profiler_index;
    unsigned char thread_index;
    unsigned char depth : 6;
    unsigned char wrapped : 2;
};
static_assert(sizeof(s_storage_context) == 0xC, "s_storage_context");

struct s_storage_thread
{
    unsigned long thread_id;
    unsigned long depth; // max depth while gathering, then the display row offset
    unsigned long hw_thread;
    unsigned long unknown_C;
};
static_assert(sizeof(s_storage_thread) == 0x10, "s_storage_thread");

long const k_profiler_hw_counter_count = 6;

struct s_profiler_frame_header
{
    s_storage_context * get_context_ptr(void)
    {
        mangled_ppc("?get_context_ptr@s_profiler_frame_header@@QAAPAUs_storage_context@@XZ");

        return reinterpret_cast<s_storage_context *>(this + 1);
    }

    s_storage_thread * get_thread_ptr(void)
    {
        mangled_ppc("?get_thread_ptr@s_profiler_frame_header@@QAAPAUs_storage_thread@@XZ");

        return reinterpret_cast<s_storage_thread *>(get_context_ptr() + context_count);
    }

    unsigned long size;
    unsigned long context_count;
    __int64 start_time;
    __int64 end_time;
    __int64 frame_number;
    __int64 vsync_cycles;
    float average_user_hw;
    float max_end_time;
    float hw_counters[k_profiler_hw_counter_count];
    unsigned short thread_count;
};
static_assert(sizeof(s_profiler_frame_header) == 0x50, "s_profiler_frame_header");

// packed profiler id: group name index (12 bits), name index (12 bits), color index (8 bits)
struct s_global_def
{
    void set(unsigned short group_name_index, unsigned short name_index, unsigned short color_index)
    {
        group = group_name_index;
        name = name_index;
        color = color_index;
    }

    union
    {
        struct
        {
            unsigned long group : 12;
            unsigned long name : 12;
            unsigned long color : 8;
        };
        unsigned long value;
    };
};
static_assert(sizeof(s_global_def) == 0x4, "s_global_def");

struct s_mt_context_detail
{
    unsigned long color_index;
    unsigned long name_index;
};
static_assert(sizeof(s_mt_context_detail) == 0x8, "s_mt_context_detail");

/* ---------- prototypes */

extern s_profiler_frame_header * profiler_storage_request(unsigned long context_count, unsigned long thread_count);
extern void profiler_publish_frame(s_profiler_frame_header * frame);
extern e_mt_profiler_mode mt_profiler_get_mode(void);
extern unsigned short profiler_get_index(char const * group_name, char const * name, e_mt_color color);
extern unsigned long mt_profiler_get_color_from_index(long index);
extern unsigned long mt_profiler_get_color_from_user(float user, float max_user);
extern char const * mt_profiler_get_name_from_index(long index);
extern s_mt_context_detail mt_profiler_get_context_detail(unsigned short id);
extern s_profiler_frame_header * mt_profiler_get_frame(long frame_offset);
extern void mt_profiler_toggle_capture(void);
extern void mt_profiler_initialize(void);
extern void mt_profiler_dispose(void);
extern void mt_profiler_set_mode(e_mt_profiler_mode mode);

/* ---------- globals */

/* ---------- public code */

#endif // __MT_PROFILER_STORE_H__

