#pragma once
#ifndef __ASYNC_PROFILE_H__
#define __ASYNC_PROFILE_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"
#include "foundation\baselib\datatypes\static_array.h"
#include "foundation\threadlib\async\async.h"
#include "foundation\threadlib\async\async_setup.h"

/* ---------- constants */

enum e_async_profile_blocks
{
    _async_profile_block_thread_tick = 0,
    _async_profile_block_task_add_sized_task_data_unsafe,

    k_async_profile_block_count
};

/* ---------- definitions */

struct s_async_thread_context;

struct s_async_thread_statistics
{
    long work_list_size;
    long unknown4; // s_async_thread_internal_statistics::unknown0
    long unknown8; // s_async_thread_internal_statistics::unknown4
    s_static_array<long, k_maximum_async_priority> unknownC;
    s_static_array<long, k_maximum_async_priority> unknown8C;
    s_static_array<s_async_task_priority_timings, k_maximum_async_priority> priority_timings;
};
static_assert(sizeof(s_async_thread_statistics) == 0x28C, "s_async_thread_statistics");

class c_async_profile_interface
{
public:
    virtual void register_profile_blocks(char const ** block_names, long block_count) = 0;
    virtual void start_profile_block(char const * block_name, unsigned char * const block_data) = 0;
    virtual void end_profile_block(unsigned char * const block_data) = 0;
    virtual ~c_async_profile_interface(void)
    {
    }
};

class c_async_profile_block
{
public:
    c_async_profile_block(char const * block_name);
    ~c_async_profile_block(void);

private:
    unsigned char m_block_data[0x80]; // passed to the registered profiler
};
static_assert(sizeof(c_async_profile_block) == 0x80, "c_async_profile_block");

/* ---------- prototypes */

extern void async_profile_get_statistics_for_thread(long thread_index, s_async_thread_statistics * statistics);
extern long async_profile_get_total_tasks_added(void);
extern char const * async_profile_get_block_name(e_async_profile_blocks block_index);
extern void async_profile_record_task_timings(s_async_thread_context * thread_context, long priority, unsigned long elapsed_time);

/* ---------- globals */

/* ---------- public code */

#endif // __ASYNC_PROFILE_H__

