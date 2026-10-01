#pragma once
#ifndef __EVENT_LOG_CACHE_H__
#define __EVENT_LOG_CACHE_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"
#include "foundation\baselib\datatypes\flags.h"
#include "foundation\baselib\datatypes\static_array.h"
#include "foundation\baselib\datatypes\static_stack.h"

/* ---------- constants */

enum e_event_log_index;

inline e_event_log_index & operator++(e_event_log_index & event_log_index)
{
    event_log_index = static_cast<e_event_log_index>(event_log_index + 1);

    return event_log_index;
};

/* ---------- definitions */

class c_event_log_manager;

class c_event_log_cache
{
public:
    struct s_cache_entry
    {
        s_flags<e_event_log_index, unsigned long, 32> event_log_indices; // 0x0
        char const * string; // 0x4
    };

    void initialize(c_event_log_manager * manager);
    void dispose(void);
    bool is_empty(void) const;
    bool is_space_available(long string_size_required) const;
    bool add_to_cache(long event_log_count, e_event_log_index const * event_log_indices, char const * string, bool * out_request_flush);
    void flush(void);
    unsigned long get_last_flush_time(void) const;

    void set_enabled(bool enabled)
    {
        m_enabled = enabled;
    };

    bool get_enabled(void) const
    {
        return m_enabled;
    };

private:
    static long const k_maximum_cache_entries = 1024;
    static long const k_string_buffer_size = 0x8000;
    static long const k_string_buffer_flush_threshold = 0x7800;

    c_event_log_manager * m_manager; // 0x0
    bool m_enabled; // 0x4
    unsigned long m_last_flush_time; // 0x8
    s_flags<e_event_log_index, unsigned long, 32> m_cached_log_mask; // 0xC
    c_static_stack<s_cache_entry, k_maximum_cache_entries> m_cache_entries; // 0x10
    long m_string_buffer_size; // 0x2014
    s_static_array<char, k_string_buffer_size> m_string_buffer; // 0x2018
};
static_assert(sizeof(c_event_log_cache::s_cache_entry) == 0x8, "c_event_log_cache::s_cache_entry");
static_assert(sizeof(c_event_log_cache) == 0xA018, "c_event_log_cache");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __EVENT_LOG_CACHE_H__

