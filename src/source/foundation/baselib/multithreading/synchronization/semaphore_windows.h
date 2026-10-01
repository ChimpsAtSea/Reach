#pragma once
#ifndef __SEMAPHORE_WINDOWS_H__
#define __SEMAPHORE_WINDOWS_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"
#include "foundation\baselib\datatypes\static_array.h"
#include "foundation\baselib\multithreading\synchronization\synchronization_object.h"

/* ---------- constants */

/* ---------- definitions */

struct s_semaphore
{
    unsigned long object_id;
};
static_assert(sizeof(s_semaphore) == 0x4, "s_semaphore");

struct s_semaphore_definition
{
    char const * name;
    long initial_count;
    long maximum_count;
    bool universal;
};
static_assert(sizeof(s_semaphore_definition) == 0x10, "s_semaphore_definition");

class c_semaphore_instance :
    public c_synchronization_handle
{
public:
    c_semaphore_instance(void) :
        m_universal_reference_count(false)
    {
    }

    bool is_universal(void) const;
    void reset_reference_counts(bool universal);
    void force_release_if_owned_by_thread(long thread_index);
    long get_reference_count(void) const;
    void add_reference(void);
    void remove_reference(void);

protected:
    bool m_universal_reference_count; // 0x18
    s_static_array<long, 23> m_reference_counts; // 0x1C
};
static_assert(sizeof(c_semaphore_instance) == 0x78, "c_semaphore_instance");

/* ---------- prototypes */

extern s_semaphore semaphore_declare(long synchronization_group_index, s_semaphore_definition const * definition);
extern void semaphore_create(c_semaphore_instance * semaphore, unsigned long object_id, long lock_node_index, s_semaphore_definition const * definition);
extern void semaphore_destroy(c_semaphore_instance * semaphore);

extern long semaphore_release_internal(s_semaphore semaphore, bool * out_released);
extern void semaphore_take_internal(s_semaphore semaphore);
extern bool semaphore_try_and_take_internal(s_semaphore semaphore);
extern bool semaphore_is_valid(s_semaphore semaphore);
extern long semaphore_get_initial_count(s_semaphore semaphore);
extern long semaphore_get_maximum_count(s_semaphore semaphore);
extern long semaphore_get_current_thread_reference_count(s_semaphore semaphore);

/* ---------- globals */

extern s_semaphore const k_semaphore_invalid;

/* ---------- public code */

#endif // __SEMAPHORE_WINDOWS_H__

