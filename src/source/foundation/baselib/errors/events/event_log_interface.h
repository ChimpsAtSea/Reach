#pragma once
#ifndef __EVENT_LOG_INTERFACE_H__
#define __EVENT_LOG_INTERFACE_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_events.h"
#include "foundation\baselib\datatypes\flags.h"

/* ---------- constants */

enum e_event_log_index;
enum e_report_file_location;

/* ---------- definitions */

class c_file_path;
struct s_critical_section;

typedef unsigned long (*event_log_thread_function_t)(void * parameter);

// implemented by c_event_log_thread_implementation (threads.obj)
class c_event_log_thread_interface
{
public:
    virtual void start_thread(event_log_thread_function_t const thread_function) = 0;
    virtual void stop_thread(void) = 0;
    virtual bool is_crashed(void) = 0;
    virtual void thread_idle(void) = 0;
    virtual bool thread_should_exit(void) = 0;
};

class c_event_logs_critical_section
{
public:
    c_event_logs_critical_section(void);
    ~c_event_logs_critical_section(void);

private:
    bool m_locked;
};

/* ---------- prototypes */

extern void event_logs_initialize(void);
extern void event_logs_dispose(void);
extern void event_logs_set_thread_interface(c_event_log_thread_interface * thread_interface);
extern void event_logs_set_subfolder(char const * subfolder);
extern bool event_logs_get_subfolder(long subfolder_length, char * out_subfolder);
extern e_event_log_index event_logs_create_log(char const * filename, s_flags<e_event_log_flags, unsigned long, k_event_log_flag_count> flags);
extern void event_logs_write(long event_log_count, e_event_log_index const * event_log_indices, char const * string);
extern void event_logs_flush(void);
extern long event_logs_build_snapshot_files(long maximum_file_count, c_file_path * out_file_list);
extern bool event_logs_build_report_file_path(char const * filename, e_report_file_location location, c_file_path * out_file_path);
extern void event_logs_get_synchronization_objects(s_critical_section * out_critical_section);
extern bool event_logs_usable(void);
extern void event_logs_flush_cache(void);

/* ---------- globals */

/* ---------- public code */

#endif // __EVENT_LOG_INTERFACE_H__

