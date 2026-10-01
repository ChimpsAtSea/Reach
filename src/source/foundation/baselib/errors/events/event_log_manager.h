#pragma once
#ifndef __EVENT_LOG_MANAGER_H__
#define __EVENT_LOG_MANAGER_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_events.h"
#include "core\corelib\cseries\cseries_macros.h"
#include "foundation\baselib\datatypes\flags.h"
#include "foundation\baselib\datatypes\static_array.h"
#include "foundation\baselib\datatypes\static_stack.h"
#include "foundation\baselib\datatypes\static_string.h"
#include "foundation\baselib\errors\events\file_output_buffer.h"
#include "foundation\baselib\files\file_path.h"
#include "foundation\baselib\files\file_synchronous_io.h"

/* ---------- constants */

enum e_event_log_index;

long const k_maximum_event_logs = 32;

/* ---------- definitions */

class c_event_log_folder_manager;

class c_event_log_manager
{
public:
    enum e_write_buffer_mode
    {
        _write_buffer_mode_buffered = 0,
        _write_buffer_mode_flush,

        k_write_buffer_mode_count
    };

    struct s_event_log
    {
        s_static_string<256> filename; // 0x0
        s_flags<e_event_log_flags, unsigned long, k_event_log_flag_count> flags; // 0x100
        bool path_built; // 0x104
        bool opened_at_least_once; // 0x105
        bool unknown106; // 0x106
        bool file_open; // 0x107
        c_file_path path; // 0x108
        s_file_accessor file; // 0x210
        c_file_output_buffer output_buffer; // 0x31C
    };

    void initialize(c_event_log_folder_manager * folder_manager);
    void dispose(void);
    e_event_log_index create_log(char const * filename, s_flags<e_event_log_flags, unsigned long, k_event_log_flag_count> flags);
    bool log_is_valid(e_event_log_index event_log_index) const;
    void begin_writing(e_event_log_index event_log_index);
    void write_to_log(e_event_log_index event_log_index, e_write_buffer_mode mode, char const * string);
    void flush_all_open_logs(void);
    void touch_all_logs(void);
    void close_all_logs(void);
    void reset_all_logs_for_redirect(void);
    long get_log_paths(long maximum_file_count, c_file_path * out_file_paths);

    void set_retain_open_files(bool retain_open_files)
    {
        m_retain_open_files = retain_open_files;
    };

    bool get_retain_open_files(void) const
    {
        return m_retain_open_files;
    };

private:
    static bool can_write_to_event_log(s_event_log const * event_log, bool unknown);
    bool log_file_open(e_event_log_index event_log_index);
    void log_file_write_internal(e_event_log_index event_log_index, e_write_buffer_mode mode, char const * string);
    void log_file_close(e_event_log_index event_log_index);
    e_event_log_index find_existing_event_log(char const * filename, s_flags<e_event_log_flags, unsigned long, k_event_log_flag_count> flags);

    static long const k_maximum_event_log_filename_length = 256;
    static long const k_file_buffer_size = 0x10000;

    c_event_log_folder_manager * m_folder_manager; // 0x0
    bool m_retain_open_files; // 0x4
    c_static_stack<s_event_log, k_maximum_event_logs> m_logs; // 0x8
    s_static_array<unsigned char, k_file_buffer_size> m_file_buffer; // 0x8648C
};
static_assert(sizeof(c_event_log_manager::s_event_log) == 0x4324, "c_event_log_manager::s_event_log");
static_assert(sizeof(c_event_log_manager) == 0x9648C, "c_event_log_manager");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __EVENT_LOG_MANAGER_H__

