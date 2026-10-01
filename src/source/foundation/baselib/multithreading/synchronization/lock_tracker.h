#pragma once
#ifndef __LOCK_TRACKER_H__
#define __LOCK_TRACKER_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"
#include "foundation\baselib\datatypes\static_stack.h"

/* ---------- constants */

long const k_lock_tracker_maximum_entries = 32;

/* ---------- definitions */

class c_lock_hierarchy;
class c_synchronization_object;

struct s_lock_tracker_entry
{
    unsigned long object_id; // 0x0
    long lock_node_index; // 0x4
    c_synchronization_object const * object; // 0x8
    char const * name; // 0xC
};
static_assert(sizeof(s_lock_tracker_entry) == 0x10, "s_lock_tracker_entry");

class c_lock_tracker
{
public:
    c_lock_tracker(void)
    {
        mangled_ppc("??0c_lock_tracker@@QAA@XZ");
    };

    ~c_lock_tracker(void)
    {
        mangled_ppc("??1c_lock_tracker@@QAA@XZ");
    };

    void initialize(c_lock_hierarchy const * hierarchy);
    void dispose(void);
    void set_enforcement_enabled(bool enabled);
    void check_empty(void) const;
    void verify_push(c_synchronization_object const * object);
    void push(c_synchronization_object const * object);
    void pop(c_synchronization_object const * object);

private:
    bool m_enforcement_enabled; // 0x0
    c_static_stack<s_lock_tracker_entry, k_lock_tracker_maximum_entries> m_lock_stack; // 0x4
    c_lock_hierarchy const * m_hierarchy; // 0x208
};
static_assert(sizeof(c_lock_tracker) == 0x20C, "c_lock_tracker");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __LOCK_TRACKER_H__

