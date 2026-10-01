#pragma once
#ifndef __CRITICAL_SECTION_WINDOWS_H__
#define __CRITICAL_SECTION_WINDOWS_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"
#include "foundation\baselib\multithreading\synchronization\synchronization_object.h"

/* ---------- constants */

/* ---------- definitions */

enum e_critical_section_recursive
{
    _critical_section_non_recursive = 0,
    _critical_section_recursive,

    k_critical_section_recursive_count
};

struct s_critical_section
{
    unsigned long object_id;
};
static_assert(sizeof(s_critical_section) == 0x4, "s_critical_section");

struct s_critical_section_definition
{
    char const * name;
    long spin_count;
    bool unknown8;
    bool non_stack_ordering;
    short unknownA;
};
static_assert(sizeof(s_critical_section_definition) == 0xC, "s_critical_section_definition");

class c_critical_section_instance :
    public c_synchronization_object
{
public:
    long m_critical_section[7]; // 0x14 CRITICAL_SECTION
};
static_assert(sizeof(c_critical_section_instance) == 0x30, "c_critical_section_instance");

class c_critical_section_scope
{
public:
    c_critical_section_scope(s_critical_section critical_section);
    c_critical_section_scope(s_critical_section critical_section, long try_acquire_milliseconds, bool * out_lock_acquired);
    ~c_critical_section_scope(void);

private:
    s_critical_section m_critical_section; // 0x0
    bool m_lock_entered; // 0x4
};
static_assert(sizeof(c_critical_section_scope) == 0x8, "c_critical_section_scope");

/* ---------- prototypes */

extern void critical_section_create(c_critical_section_instance * section, unsigned long object_id, long lock_node_index, s_critical_section_definition const * definition);
extern void critical_section_destroy(c_critical_section_instance * section);
extern void critical_section_force_release_if_owned_by_thread(c_critical_section_instance * section, long thread_index);

extern s_critical_section critical_section_declare(long synchronization_group_index, s_critical_section_definition const * definition);
extern void critical_section_enter_internal(s_critical_section critical_section, e_critical_section_recursive recursive);
extern bool critical_section_try_and_enter_internal(s_critical_section critical_section);
extern void critical_section_leave_internal(s_critical_section critical_section, e_critical_section_recursive recursive);
extern bool critical_section_inside(s_critical_section critical_section);

/* ---------- globals */

extern s_critical_section const k_critical_section_invalid;

/* ---------- public code */

#endif // __CRITICAL_SECTION_WINDOWS_H__

