#pragma once
#ifndef __EVENT_CONTEXT_H__
#define __EVENT_CONTEXT_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"
#include "foundation\baselib\datatypes\static_array.h"
#include "foundation\baselib\datatypes\static_string.h"

/* ---------- constants */

/* ---------- definitions */

enum e_event_context_query_destination_type
{
    _event_context_query_destination_console = 0,
    _event_context_query_destination_log,
    _event_context_query_destination_remote_log,
    _event_context_query_destination_unknown3, // name unknown; describe() groups 1..3

    k_event_context_query_destination_count
};

// no constructor: lives inside the thread local s_event_thread_globals
class c_event_thread_context
{
public:
    struct s_stack_entry
    {
        char const * type; // 0x0
        char const * description; // 0x4
        bool display_to_console; // 0x8
    };

    void push(char const * type, char const * description, bool display_to_console);
    void pop(void);
    bool describe(e_event_context_query_destination_type destination_type, s_static_string<256> * out_description) const;

private:
    static long const k_stack_maximum_depth = 32;

    long m_stack_depth; // 0x0
    s_static_array<s_stack_entry, k_stack_maximum_depth> m_stack; // 0x4
};
static_assert(sizeof(c_event_thread_context) == 0x184, "c_event_thread_context");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __EVENT_CONTEXT_H__

