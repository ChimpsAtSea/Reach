#pragma once
#ifndef __MUTEX_WINDOWS_H__
#define __MUTEX_WINDOWS_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"
#include "foundation\baselib\multithreading\synchronization\synchronization_object.h"

/* ---------- constants */

enum e_mutex_recursive
{
    _mutex_non_recursive = 0,
    _mutex_recursive,

    k_mutex_recursive_count
};

/* ---------- definitions */

struct s_mutex
{
    unsigned long object_id;
};
static_assert(sizeof(s_mutex) == 0x4, "s_mutex");

struct s_mutex_definition
{
    char const * name;
    bool initial_owner;
};
static_assert(sizeof(s_mutex_definition) == 0x8, "s_mutex_definition");

/* ---------- prototypes */

extern void mutex_create(c_synchronization_handle * mutex, unsigned long object_id, long lock_node_index, s_mutex_definition const * definition);
extern void mutex_destroy(c_synchronization_handle * mutex);
extern void mutex_force_release_if_owned_by_thread(c_synchronization_handle * mutex, long thread_index);

extern s_mutex mutex_declare(long synchronization_group_index, s_mutex_definition const * definition);
extern void mutex_dependency(s_mutex parent_mutex, s_mutex child_mutex);
extern void mutex_critical_section_dependency(s_mutex parent_mutex, unsigned long child_critical_section_id);
extern void mutex_take_internal(s_mutex mutex, e_mutex_recursive recursive);
extern bool mutex_take_timeout_internal(s_mutex mutex, long timeout_milliseconds);
extern void mutex_release_internal(s_mutex mutex, e_mutex_recursive recursive);

/* ---------- globals */

/* ---------- public code */

#endif // __MUTEX_WINDOWS_H__

