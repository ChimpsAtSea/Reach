#pragma once
#ifndef __EVENT_LOG_FOLDER_MANAGER_H__
#define __EVENT_LOG_FOLDER_MANAGER_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"
#include "foundation\baselib\datatypes\static_string.h"

/* ---------- constants */

enum e_report_file_location;

/* ---------- definitions */

class c_file_path;

class c_event_log_folder_manager
{
public:
    void initialize(void);
    void dispose(void);
    void obtain_report_directory_lock(void);
    void release_report_directory_lock(void);
    bool has_subfolder(void) const;
    bool get_subfolder(long subfolder_length, char * out_subfolder) const;
    void set_subfolder(char const * subfolder);
    void build_report_file_path(char const * filename, e_report_file_location location, c_file_path * out_path) const;

private:
    static long const k_directory_lock_invalid = -1;

    s_static_string<128> m_subfolder; // 0x0
};
static_assert(sizeof(c_event_log_folder_manager) == 0x80, "c_event_log_folder_manager");

/* ---------- prototypes */

/* ---------- globals */

extern char const * const k_reports_directory_name;

/* ---------- public code */

#endif // __EVENT_LOG_FOLDER_MANAGER_H__

