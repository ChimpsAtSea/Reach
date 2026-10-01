#pragma once
#ifndef __SYNCHRONIZATION_EVENT_WINDOWS_H__
#define __SYNCHRONIZATION_EVENT_WINDOWS_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"
#include "foundation\baselib\multithreading\synchronization\synchronization_object.h"

/* ---------- constants */

/* ---------- definitions */

struct s_synchronization_event_definition
{
    char const * name;
    bool manual_reset;
    bool initial_state;
    bool allow_wait_with_locks_held; // skips g_synchronization_lock_tracker->check_empty() when waiting
};
static_assert(sizeof(s_synchronization_event_definition) == 0x8, "s_synchronization_event_definition");

struct s_synchronization_event
{
    unsigned long object_id;
};
static_assert(sizeof(s_synchronization_event) == 0x4, "s_synchronization_event");

/* ---------- prototypes */

extern s_synchronization_event synchronization_event_declare(long synchronization_group_index, s_synchronization_event_definition const * definition);
extern void synchronization_event_create(c_synchronization_handle * event, unsigned long object_id, s_synchronization_event_definition const * definition);
extern void synchronization_event_destroy(c_synchronization_handle * event);
extern void synchronization_event_wait_internal(s_synchronization_event event);
extern bool synchronization_event_wait_timeout_internal(s_synchronization_event event, long timeout);
extern void synchronization_event_set_internal(s_synchronization_event event);
extern void synchronization_event_reset_internal(s_synchronization_event event);
extern bool synchronization_event_has_automatic_reset(s_synchronization_event event);

/* ---------- globals */

/* ---------- public code */

#endif // __SYNCHRONIZATION_EVENT_WINDOWS_H__

