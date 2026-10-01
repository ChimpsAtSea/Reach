#pragma once
#ifndef __LOCKFREE_EVENT_FIFO_H__
#define __LOCKFREE_EVENT_FIFO_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_macros.h"
#include "core\corelib\cseries\cseries_memory.h"
#include "foundation\baselib\datatypes\static_array.h"
#include "foundation\baselib\multithreading\primitives\synchronized_list_windows.h"

/* ---------- constants */

/* ---------- definitions */

// t_type must have an s_synchronized_list_entry `list_entry` as its first member
template<typename t_type, long k_maximum_count>
class t_event_fifo
{
public:
    t_event_fifo(void);
    ~t_event_fifo(void);

    void initialize(void);
    void dispose(void);
    void reset(void);

    long peek_pending_count(void) const;

    t_type * get_next_readable_event(void);
    t_type * get_next_writable_event(void);
    void queue_readable_event(t_type * event);
    void queue_writable_event(t_type * event);

    bool valid_event(t_type const * event) const;

private:
    enum
    {
        k_readable_list_count = 2
    };

    s_static_array<t_type, k_maximum_count> m_events;
    s_synchronized_list_header m_readable_lists[k_readable_list_count];
    s_synchronized_list_header m_writable_list;
    bool m_initialized;
};

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#include "foundation\threadlib\multithreading\datatypes\lockfree_event_fifo.inl"

#endif // __LOCKFREE_EVENT_FIFO_H__
