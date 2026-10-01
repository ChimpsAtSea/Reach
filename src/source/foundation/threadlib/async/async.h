#pragma once
#ifndef __ASYNC_H__
#define __ASYNC_H__

/* ---------- headers */

#include "baselib\synchronized_value_windows.h"
#include "core\corelib\cseries\cseries_macros.h"

/* ---------- constants */

enum
{
    k_maximum_async_priority = 32,
    k_maximum_async_task_data_size = 0x120,
    k_async_task_id_thread_index_bits = 8,
};

enum e_async_completion
{
    _async_completion_retry = 0,
    _async_completion_done,
    _async_completion_thread_exit,

    k_async_completion_count
};

enum e_async_block_if_full
{
    _async_do_not_block_if_full = 0,
    _async_block_if_full,

    k_async_block_if_full_count
};

// values per c_saved_game_file_load_metadata_async (2 = still running; 1/0 = finished ok/failed)
enum e_async_pending_bool
{
    _async_pending_bool_false = 0,
    _async_pending_bool_true,
    _async_pending_bool_pending,

    k_async_pending_bool_count
};

/* ---------- definitions */

struct s_async_task_id
{
    long value; // (thread task counter << 16) | (thread index << 8) | local index
};
static_assert(sizeof(s_async_task_id) == 0x4, "s_async_task_id");

class c_async_completion_flag
{
public:
    c_async_completion_flag(void)
    {
    }

    ~c_async_completion_flag(void)
    {
    }

    long peek(void) const
    {
        return m_flag.peek();
    }

    bool is_done(void) const
    {
        mangled_ppc("?is_done@c_async_completion_flag@@QBA_NXZ");

        return static_cast<bool>(peek());
    }

    void set(long value)
    {
        mangled_ppc("?set@c_async_completion_flag@@QAAXJ@Z");

        m_flag.set(value);
    }

    long get_internal_data(void) const
    {
        mangled_ppc("?get_internal_data@c_async_completion_flag@@QBAJXZ");

        return m_internal_data.peek();
    }

    void set_internal_data(long internal_data)
    {
        mangled_ppc("?set_internal_data@c_async_completion_flag@@QAAXJ@Z");

        m_internal_data.set(internal_data);
    }

private:
    c_synchronized_int32 m_flag;
    c_synchronized_int32 m_internal_data; // thread index
};
static_assert(sizeof(c_async_completion_flag) == 0x8, "c_async_completion_flag");

struct s_async_task_element
{
    s_async_task_id task_id;
    long category;
    long priority;
    unsigned char task_data[k_maximum_async_task_data_size];
    e_async_completion (*callback)(void * task_data);
    c_async_completion_flag * completion_flag;
};
static_assert(sizeof(s_async_task_element) == 0x134, "s_async_task_element");

/* ---------- prototypes */

extern void async_initialize(void);
extern void async_request_shutdown(void);
extern void async_dispose(void);
extern void async_idle(void);
extern bool async_category_in_queue(long category);
extern bool async_task_change_priority(s_async_task_id task_id, long priority);
extern s_async_task_id async_task_add_simple_function(long priority, long category, e_async_completion (*callback)(void *), c_async_completion_flag * completion_flag);
extern s_async_task_id async_task_add_sized_task_data_unsafe(long priority, long category, void const * task_data, long task_data_size, e_async_completion (*callback)(void *), c_async_completion_flag * completion_flag, e_async_block_if_full blocking_behavior);
extern void async_yield_begin(c_async_completion_flag const * completion_flag);
extern void async_yield_end(c_async_completion_flag const * completion_flag);
extern void async_yield_until_done_simple(s_async_task_id task_id, c_async_completion_flag const * completion_flag);
extern long async_get_thread_index_from_task_id(s_async_task_id task_id);
extern long async_get_local_index_from_task_id(s_async_task_id task_id);
extern s_async_task_id async_build_task_id(long task_counter, long thread_index, long local_index);
extern s_async_task_id async_task_add_sized_task_data_with_thread_index_unsafe(long thread_index, long priority, long category, void const * task_data, long task_data_size, e_async_completion (*callback)(void *), c_async_completion_flag * completion_flag, e_async_block_if_full blocking_behavior, bool * out_blocked);

/* ---------- globals */

extern s_async_task_id const k_invalid_async_task_id;

/* ---------- public code */

inline bool async_task_id_is_valid(s_async_task_id task_id)
{
    mangled_ppc("?async_task_id_is_valid@@YA_NUs_async_task_id@@@Z");

    return task_id.value != k_invalid_async_task_id.value;
}

// ??$async_task_add_ex@PAVc_content_task@@@@YA?AUs_async_task_id@@JPBQAVc_content_task@@JP6A?AW4e_async_completion@@PAX@ZPAVc_async_completion_flag@@W4e_async_block_if_full@@@Z
template<typename t_task_data>
s_async_task_id async_task_add_ex(long priority, t_task_data const * task_data, long category, e_async_completion (*callback)(void *), c_async_completion_flag * completion_flag, e_async_block_if_full blocking_behavior)
{
    long const task_data_size = sizeof(t_task_data);
    return async_task_add_sized_task_data_unsafe(priority, category, task_data, task_data_size, callback, completion_flag, blocking_behavior);
}

// ??$async_task_add@PAVc_content_task@@@@YA?AUs_async_task_id@@JPBQAVc_content_task@@JP6A?AW4e_async_completion@@PAX@ZPAVc_async_completion_flag@@@Z
template<typename t_task_data>
s_async_task_id async_task_add(long priority, t_task_data const * task_data, long category, e_async_completion (*callback)(void *), c_async_completion_flag * completion_flag)
{
    return async_task_add_ex(priority, task_data, category, callback, completion_flag, _async_block_if_full);
}

#endif // __ASYNC_H__

