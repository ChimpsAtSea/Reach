#pragma once
#ifndef __EVENT_BUFFER_H__
#define __EVENT_BUFFER_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"
#include "foundation\baselib\datatypes\static_array.h"

/* ---------- constants */

/* ---------- definitions */

struct s_event_buffer_entry
{
    char const * string; // 0x0
    union
    {
        long text_size; // 0x4 (includes the terminator)
        long length; // legacy name used by event_globals.cpp
    };
};
static_assert(sizeof(s_event_buffer_entry) == 0x8, "s_event_buffer_entry");

class c_event_buffer
{
public:
    void reset(void);
    void add_event(char const * event_string);
    void verify(void) const;
    long get_event_history(s_event_buffer_entry const ** out_events) const;

private:
    static long const k_event_buffer_max_entries = 128;
    static long const k_event_buffer_size = 65536;

    void get_empty_space(long size_required, long deleted_entries, long * out_write_offset, long * out_end_offset) const;
    void make_entries(long entry_count);
    void make_space(long size_required);
    void delete_entries(long delete_entry_count);

    long m_entry_count; // 0x0
    s_static_array<s_event_buffer_entry, 128> m_entries; // 0x4
    s_static_array<char, 65536> m_data; // 0x404
};
static_assert(sizeof(c_event_buffer) == 0x10404, "c_event_buffer");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __EVENT_BUFFER_H__

