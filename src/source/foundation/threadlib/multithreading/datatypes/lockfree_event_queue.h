#pragma once
#ifndef __LOCKFREE_EVENT_QUEUE_H__
#define __LOCKFREE_EVENT_QUEUE_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_macros.h"
#include "core\corelib\cseries\cseries_memory.h"
#include "foundation\baselib\datatypes\static_array.h"
#include "foundation\baselib\multithreading\primitives\synchronized_list_windows.h"

/* ---------- constants */

enum e_event_queue_chain_order
{
    _event_queue_chain_order_lifo = 0,
    _event_queue_chain_order_fifo,

    k_event_queue_chain_order_count
};

/* ---------- definitions */

// t_type must derive from s_synchronized_list_entry
template<typename t_type, long k_maximum_count>
class t_event_queue
{
public:
    t_event_queue(void);
    ~t_event_queue(void);

    void initialize(void);
    void initialize_limited(long limit_count);
    void set_name(char const * name);
    void dispose(void);
    void reset(void);

    long peek_pending_count(void) const;

    t_type * allocate_event(void);
    void queue_event(t_type * event);
    t_type * acquire_top_event(void);
    t_type * acquire_event_chain(e_event_queue_chain_order desired_order);
    t_type * release_chain_top_event(t_type * chain);
    t_type * requeue_chain_top_event(t_type * chain);

    bool valid_event(void const * event) const;
    void assert_valid_chain(s_synchronized_list_entry * chain) const;

private:
    s_static_array<t_type, k_maximum_count> m_events;
    s_synchronized_list_header m_pending_list;
    s_synchronized_list_header m_free_list;
    bool m_initialized;
    long m_limit_count;
    char const * m_name;
};

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#include "foundation\threadlib\multithreading\datatypes\lockfree_event_queue.inl"

#endif // __LOCKFREE_EVENT_QUEUE_H__
