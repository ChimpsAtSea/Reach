#ifndef __SYNCHRONIZATION_OBJECT_H__
#define __SYNCHRONIZATION_OBJECT_H__
#pragma once

/* ---------- headers */

#include "baselib\synchronized_value_windows.h"
#include "core\corelib\cseries\cseries_macros.h"
#include "foundation\baselib\datatypes\flags.h"
#include "omaha\cseries\cseries.h"

/* ---------- constants */

#define __SYNCHRONIZATION_OBJECT_H_FILE__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\foundation\\baselib/multithreading/synchronization/synchronization_object.h"

enum e_synchronization_object_flags
{
    _synchronization_object_non_stack_ordering_bit = 0,

    k_synchronization_object_flags_count
};

/* ---------- definitions */

class c_synchronization_object
{
public:
    unsigned long get_object_id(void) const;
    long get_synchronization_group_index(void) const;
    char const * get_name(void) const;
    long get_lock_node_index(void) const;
    bool get_non_stack_ordering(void) const;
    void initialize(unsigned long object_id)
    {
        mangled_ppc("?initialize@c_synchronization_object@@QAAXK@Z");

        m_object_id = object_id;
        m_lock_node_index = NONE;
        m_flags.clear();
        reset();
    }

    void set_lock_node_index(long lock_node_index)
    {
        mangled_ppc("?set_lock_node_index@c_synchronization_object@@QAAXJ@Z");

        m_lock_node_index = lock_node_index;
    }

    void reset(void)
    {
        mangled_ppc("?reset@c_synchronization_object@@QAAXXZ");

        m_locking_thread.set(NONE);
        m_lock_count.set(0);
    }

    long get_lock_count(void) const;
    void set_lock_count(long locking_thread, long lock_count);
    void acquire_prerequisites(void) const;
    void release_prerequisites(void) const;

    void set_non_stack_ordering(bool non_stack_ordering)
    {
        mangled_ppc("?set_non_stack_ordering@c_synchronization_object@@QAAX_N@Z");

        m_flags.set(_synchronization_object_non_stack_ordering_bit, non_stack_ordering);
    }

    long get_locking_thread(void) const
    {
        mangled_ppc("?get_locking_thread@c_synchronization_object@@QBAJXZ");

        return m_lock_count.peek() > 0 ? m_locking_thread.peek() : NONE;
    }

    void increment_lock_count(long thread_index)
    {
        mangled_ppc("?increment_lock_count@c_synchronization_object@@QAAXJ@Z");

        m_locking_thread.set(thread_index);
        m_lock_count.increment();
    }

    void decrement_lock_count(void)
    {
        mangled_ppc("?decrement_lock_count@c_synchronization_object@@QAAXXZ");

        long lock_count = m_lock_count.decrement();
        dassert_decomp(lock_count >= 0, "unmatched enter/leave to synchronization object", __SYNCHRONIZATION_OBJECT_H_FILE__, 123);
    }

protected:
    unsigned long m_object_id; // 0x0
    s_flags<e_synchronization_object_flags, unsigned long, k_synchronization_object_flags_count> m_flags; // 0x4
    long m_lock_node_index; // 0x8
    c_interlocked_int32 m_locking_thread; // 0xC
    c_interlocked_int32 m_lock_count; // 0x10
};
static_assert(sizeof(c_synchronization_object) == 0x14, "c_synchronization_object");

class c_synchronization_handle :
    public c_synchronization_object
{
public:
    c_synchronization_handle(void) :
        m_handle(reinterpret_cast<void *>(-1))
    {
    }

    void set_handle(void * handle);
    void * get_handle(void) const;

protected:
    void * m_handle; // 0x14
};
static_assert(sizeof(c_synchronization_handle) == 0x18, "c_synchronization_handle");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __SYNCHRONIZATION_OBJECT_H__

