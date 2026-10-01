#pragma once
#ifndef __CSERIES_EVENTS_H__
#define __CSERIES_EVENTS_H__

/* ---------- headers */

#include <vadefs.h>
#include <stdarg.h>

/* ---------- constants */

enum e_event_level
{
    _event_verbose = 0,
    _event_status,
    _event_message,
    _event_warning,
    _event_error,
    _event_critical,

    k_event_level_count
};

// bits 0-3 named from H3; bit 4 enables trimming in c_event_log_manager::log_file_open
enum e_event_log_flags
{
    _event_log_append_to_file_bit = 0,
    _event_log_place_in_root_bit,
    _event_log_only_for_custom_subfolder,
    _event_log_disable_file_trimming,
    _event_log_trim_file_bit,

    k_event_log_flag_count
};

// usage: event(_event_message, "format", ...);
#define event(level, ...) \
    { \
        static long volatile x_event_category_index = -1; \
        s_event_properties event_properties = { level, 0, x_event_category_index }; \
        if (event_query(&event_properties)) \
        { \
            long event_category_index = event_process(&event_properties, __VA_ARGS__); \
            if (event_properties.category_index == -1) \
            { \
                event_store_category(event_category_index, &x_event_category_index); \
            } \
        } \
    }

// usage: event_wrapped(_event_warning, "format", ...); (c_event_wrapper flavour)
#define event_wrapped(level, ...) \
    { \
        static long volatile x_event_category_index = -1; \
        s_event_properties event_properties = { level, 0, x_event_category_index }; \
        c_event_wrapper _event_wrapper(&event_properties); \
        if (event_query(&event_properties)) \
        { \
            long event_category_index = _event_wrapper.process(__VA_ARGS__); \
            if (event_properties.category_index == -1) \
            { \
                event_store_category(event_category_index, &x_event_category_index); \
            } \
        } \
    }

/* ---------- definitions */

struct s_event_properties
{
    e_event_level level;
    unsigned long flags;
    long category_index;
};

long event_process_va(s_event_properties const * properties, char const * format, va_list arglist);

class c_event_wrapper
{
public:
    c_event_wrapper(s_event_properties const * properties) :
        m_properties(properties)
    {
        mangled_ppc("??0c_event_wrapper@@QAA@PBUs_event_properties@@@Z");
    }

    long process(char const * format, ...)
    {
        mangled_ppc("?process@c_event_wrapper@@QAAJPBDZZ");

        long result = -1;
        va_list arglist;
        va_start(arglist, format);
        result = event_process_va(m_properties, format, arglist);
        va_end(arglist);
        return result;
    }

protected:
    s_event_properties const * m_properties;
};

// ??0c_event_context@@QAA@PBDK0ZZ / ??1c_event_context@@QAA@XZ are inline ("f i", owned by object_placement.obj), bodies not added yet:
// ctor = cvsnzprintf(m_context, k_maximum_size, format, ...) then event_context_push(type, flags, m_context)
class c_event_context
{
public:
    c_event_context(char const * type, unsigned long flags, char const * format, ...);
    ~c_event_context(void);

private:
    static long const k_maximum_size = 256;

    char m_context[k_maximum_size]; // 0x0
};

/* ---------- prototypes */

bool event_level_query(e_event_level level);
bool event_query(s_event_properties const * properties);
long event_process(s_event_properties const * properties, char const * format, ...);
long event_process_va(s_event_properties const * properties, char const * format, va_list arglist);
void event_store_category(long arg1, long volatile * arg2);
void event_context_push(char const * arg1, unsigned long arg2, char const * arg3);
void event_context_pop(void);

/* ---------- globals */

/* ---------- public code */

#endif // __CSERIES_EVENTS_H__
