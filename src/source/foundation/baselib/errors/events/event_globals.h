#pragma once
#ifndef __EVENT_GLOBALS_H__
#define __EVENT_GLOBALS_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_events.h"
#include "foundation\baselib\errors\events\event_manager.h"
#include "foundation\baselib\datatypes\static_array.h"
#include "foundation\baselib\multithreading\synchronization\critical_section_windows.h"
#include "foundation\baselib\multithreading\synchronization\semaphore_windows.h"

/* ---------- constants */

enum e_report_file_location;

/* ---------- definitions */

class c_event_buffer;
class c_event_listener;
class c_event_log_thread_interface;
class c_event_thread_context;
class c_file_path;

struct s_event_synchronization_objects
{
    s_static_array<s_critical_section, 2> critical_sections; // 0x0 (manager lock, buffer lock)
    s_static_array<s_semaphore, 2> semaphores; // 0x8 (manager lock, buffer lock)
    s_critical_section event_log_critical_section; // 0x10
};
static_assert(sizeof(s_event_synchronization_objects) == 0x14, "s_event_synchronization_objects");

typedef void (*event_datamine_handler_t)(e_event_level level, char const * category, char const * format, char * arglist);
typedef void (*event_time_format_function_t)(long time, char * out_string);
typedef void (*event_blocking_function_t)(void);
typedef void (*event_guard_function_t)(void);

class c_event_manager_read_lock
{
public:
    c_event_manager_read_lock(void);
    ~c_event_manager_read_lock(void);

    c_event_manager const * manager(void);

private:
    bool m_locked;
};

class c_event_manager_write_lock
{
public:
    c_event_manager_write_lock(void);
    ~c_event_manager_write_lock(void);

    c_event_manager * manager(void);

private:
    bool m_locked;
};

class c_event_buffer_read_lock
{
public:
    c_event_buffer_read_lock(void);
    ~c_event_buffer_read_lock(void);

    c_event_buffer const * buffer(void);

private:
    bool m_locked;
};

class c_event_buffer_write_lock
{
public:
    c_event_buffer_write_lock(void);
    ~c_event_buffer_write_lock(void);

    c_event_buffer * buffer(void);

private:
    bool m_locked;
};

/* ---------- prototypes */

extern void events_initialize(long default_category_count, s_event_category_default_configuration const * default_categories);
extern void events_start_threads(c_event_log_thread_interface * thread_interface);
extern void events_dispose(void);
extern void events_dump_categories(char const * category_name);
extern void events_build_correct_category_name(char const * category_name, char * out_category_name, long out_category_name_length);
extern void events_set_output_level_global(e_event_level level);
extern void events_set_log_level_global(e_event_level level);
extern void events_set_debug_level_global(e_event_level level);
extern void events_set_datamine_level_global(e_event_level level);
extern void events_set_output_level_by_name(char const * category_name, e_event_level level);
extern void events_set_log_level_by_name(char const * category_name, e_event_level level);
extern void events_set_debug_level_by_name(char const * category_name, e_event_level level);
extern void events_set_debugger_break_level_by_name(char const * category_name, e_event_level level);
extern void events_set_halt_level_by_name(char const * category_name, e_event_level level);
extern void events_set_datamine_level_by_name(char const * category_name, e_event_level level);
extern void events_set_force_output_level_by_name(char const * category_name, e_event_level level);
extern bool events_register_listener(c_event_listener * event_listener);
extern void events_unregister_listener(c_event_listener * listener);
extern void events_attach_datamine_handler(event_datamine_handler_t const datamine_handler);
extern void events_detach_datamine_handler(event_datamine_handler_t const datamine_handler);
extern void events_attach_time_format_function(event_time_format_function_t const time_format_function);
extern void events_detach_time_format_function(event_time_format_function_t const time_format_function);
extern void events_attach_blocking_functions(event_blocking_function_t const blocking_begin_function, event_blocking_function_t const blocking_end_function);
extern void events_detach_blocking_functions(event_blocking_function_t const blocking_begin_function, event_blocking_function_t const blocking_end_function);
extern void events_attach_guard_functions(event_guard_function_t const guard_begin_function, event_guard_function_t const guard_end_function);
extern void events_detach_guard_functions(event_guard_function_t const guard_begin_function, event_guard_function_t const guard_end_function);
extern void events_enable(bool enable);
extern void events_suppression_enable(bool enable);
extern void events_spam_suppression_enable(bool enable);
extern void events_suppress_output(bool suppress);
extern long events_get_recent(long maximum_event_count, long buffer_size, char * buffer);
extern void events_internal_error(char const * format, ...);
extern void events_disable_thread_push(void);
extern void events_disable_thread_pop(void);
extern bool events_disabled_thread(void);
extern void events_blocking_begin(void);
extern void events_blocking_end(void);
extern c_event_thread_context * events_thread_context_get(void);
extern void events_clear(void);
extern void events_flush(void);
extern void events_snapshot(void);
extern long events_build_snapshot_files(long maximum_file_count, c_file_path * out_file_list);
extern long events_get_spamming(long line_count, char const ** out_lines);
extern bool events_get_output_suppressed(void);
extern bool events_get_current_desired_output(void);
extern void events_get_synchronization_objects(s_event_synchronization_objects * out_objects);
extern void events_set_subfolder(char const * subfolder);
extern bool events_get_subfolder(long subfolder_length, char * out_subfolder);
extern bool events_build_report_file_path(char const * filename, e_report_file_location location, c_file_path * out_file_path);
extern void events_force_emergency_redirection_thread_push(void);
extern void events_force_emergency_redirection_thread_pop(void);
extern bool events_should_use_emergency_redirection_for_thread(void);
extern bool events_try_to_initialize(void);

/* ---------- globals */

extern char const * const k_primary_event_log_filename;
extern char const * const k_primary_full_event_log_filename;
extern char const * const k_error_snapshot_directory;
extern char const * const k_thrown_away_events_log_file_name_format_string_with_id;
extern char const * const k_thrown_away_events_log_file_name_format_string_with_name;
extern char const * const k_thrown_away_events_log_file_name_search_spec;
extern char const * k_event_level_severity_strings[k_event_level_count];

/* ---------- public code */

#endif // __EVENT_GLOBALS_H__
