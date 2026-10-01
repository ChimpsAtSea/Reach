#pragma once
#ifndef __THREAD_MANIPULATION_WINDOWS_H__
#define __THREAD_MANIPULATION_WINDOWS_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"

/* ---------- constants */

/* ---------- definitions */

struct s_thread_id
{
    unsigned long id;
};
static_assert(sizeof(s_thread_id) == 0x4, "s_thread_id");

struct s_thread_handle
{
    void * handle;
};
static_assert(sizeof(s_thread_handle) == 0x4, "s_thread_handle");

enum e_thread_priority
{
    _thread_priority_idle = 0,
    _thread_priority_lowest,
    _thread_priority_below_normal,
    _thread_priority_normal,
    _thread_priority_above_normal,
    _thread_priority_highest,
    _thread_priority_time_critical,

    k_thread_priority_count
};

enum e_thread_creation_state
{
    _thread_creation_state_running = 0,
    _thread_creation_state_suspended,

    k_thread_creation_state_count
};

enum e_thread_creation_inheritance
{
    _thread_creation_inheritance_none = 0,

    k_thread_creation_inheritance_count
};

/* ---------- prototypes */

extern e_thread_priority thread_get_priority(s_thread_handle thread_handle);
extern void thread_set_priority(s_thread_handle thread_handle, e_thread_priority priority);
extern bool thread_handle_valid(s_thread_handle thread_handle);
extern s_thread_handle thread_get_current_handle(void);
extern bool thread_id_valid(s_thread_id thread_id);
extern s_thread_id thread_get_current_id(void);
extern s_thread_handle thread_create(unsigned long (* const thread_function)(void *), void * thread_parameters, e_thread_creation_state creation_state, e_thread_creation_inheritance creation_inheritance, unsigned int stack_size, s_thread_id * out_thread_id);
extern void thread_resume(s_thread_handle thread_handle);
extern void thread_destroy(s_thread_handle thread_handle);
extern void thread_wait(s_thread_handle thread_handle);
extern bool thread_wait_timeout(s_thread_handle thread_handle, long timeout);
extern void thread_set_current_thread_name_for_platform(char const * name);

/* ---------- globals */

extern s_thread_handle const k_thread_handle_invalid;
extern s_thread_id const k_thread_id_invalid;

/* ---------- public code */

#endif // __THREAD_MANIPULATION_WINDOWS_H__

