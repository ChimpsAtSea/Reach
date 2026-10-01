#pragma once
#ifndef __ASYNC_SETUP_H__
#define __ASYNC_SETUP_H__

/* ---------- headers */

#include "baselib\synchronized_value_windows.h"
#include "core\corelib\cseries\cseries_macros.h"
#include "foundation\baselib\datatypes\static_array.h"
#include "foundation\baselib\multithreading\synchronization\critical_section_windows.h"
#include "foundation\baselib\multithreading\synchronization\semaphore_windows.h"
#include "foundation\baselib\multithreading\synchronization\virtual_guard_block.h"
#include "foundation\threadlib\async\async.h"
#include "foundation\threadlib\multithreading\datatypes\thread_safe_linked_list.h"

/* ---------- constants */

enum
{
    k_max_async_thread_count = 4,
    k_maximum_async_category = 32,
    k_maximum_async_work_items_per_thread = 128,
};

/* ---------- definitions */

class c_async_profile_interface;

// built on the stack by c_async_task_element_comparer::operator() for each element
struct s_async_task_compare_element
{
    long priority;
    void * callback;
    void const * task_data;
};
static_assert(sizeof(s_async_task_compare_element) == 0xC, "s_async_task_compare_element");

struct s_async_task_compare_interface
{
    void * unknown0;
    bool (*compare)(void * comparer_storage, s_async_task_compare_element const * a, s_async_task_compare_element const * b); // called by c_async_task_element_comparer::operator()
    void (*unknown8)(void * comparer_storage); // dispose, called by c_async_task_element_comparer::~c_async_task_element_comparer()
};
static_assert(sizeof(s_async_task_compare_interface) == 0xC, "s_async_task_compare_interface");

struct s_async_task_priority_timings
{
    unsigned long maximum_time;
    unsigned long total_time;
    long count;
};
static_assert(sizeof(s_async_task_priority_timings) == 0xC, "s_async_task_priority_timings");

struct s_async_thread_internal_statistics
{
    long unknown0;
    c_interlocked_int32 unknown4;
    s_static_array<long, k_maximum_async_priority> unknown8;
    s_static_array<long, k_maximum_async_priority> unknown88;
    s_static_array<s_async_task_priority_timings, k_maximum_async_priority> priority_timings;
};
static_assert(sizeof(s_async_thread_internal_statistics) == 0x288, "s_async_thread_internal_statistics");

struct s_async_thread_context
{
    t_thread_safe_list<s_async_task_element> free_list;
    t_thread_safe_list<s_async_task_element> work_list;
    s_static_array<t_thread_safe_list<s_async_task_element>::s_list_element, k_maximum_async_work_items_per_thread> element_storage;
    s_semaphore work_available_semaphore;
    s_virtual_guard_block guard_block;
    void (*free_list_blocked_callback)(void);
    s_async_task_compare_interface compare_interface;
    long thread_index;
    c_synchronized_int32 unknown9C2C;
    s_async_thread_internal_statistics statistics;
    c_interlocked_int32 work_delay;
};
static_assert(sizeof(s_async_thread_context) == 0x9EBC, "s_async_thread_context");

/* ---------- prototypes */

extern void async_setup_initialize(void);
extern void async_setup_dispose(void);
extern long async_setup_get_encoding_bit_count_for_thread_indices(void);
extern void async_setup_set_thread_count(long thread_count);
extern long async_setup_get_thread_count(void);
extern void async_setup_set_categories_for_thread(long thread_index, long const * categories, long category_count);
extern void async_setup_synchronization_for_thread(long thread_index, s_semaphore work_available_semaphore, s_critical_section free_list_section, s_critical_section work_list_section, s_virtual_guard_block guard_block);
extern void async_setup_set_thread_work_delay(long thread_index, long work_delay);
extern void async_setup_set_free_list_blocked_callback_for_thread(long thread_index, void (*callback)(void));
extern void async_setup_set_profiler(c_async_profile_interface * profiler);
extern void async_setup_set_compare_interface_for_thread(long thread_index, s_async_task_compare_interface * compare_interface);
extern long async_setup_get_thread_work_delay(long thread_index);
extern long async_setup_get_thread_index_for_category(long category);
extern bool async_setup_is_thread_index_valid(long thread_index);
extern s_async_thread_context * async_setup_get_context_for_thread(long thread_index);
extern s_async_thread_context * async_setup_get_context_for_category(long category);
extern long async_setup_get_total_tasks_added(void);
extern long async_setup_increment_total_tasks_added(void);
extern c_async_profile_interface * async_setup_get_registered_profiler(void);
extern s_async_task_compare_interface * async_setup_get_compare_interface_for_thread(long thread_index);

/* ---------- globals */

/* ---------- public code */

#endif // __ASYNC_SETUP_H__

