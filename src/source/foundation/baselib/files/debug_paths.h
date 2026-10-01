#pragma once
#ifndef __DEBUG_PATHS_H__
#define __DEBUG_PATHS_H__

/* ---------- headers */

#include "foundation\baselib\datatypes\static_string.h"
#include "foundation\baselib\files\file_path.h"
#include "foundation\baselib\files\file_location_manager.h"

/* ---------- constants */

/* ---------- definitions */

class c_debug_path
{
public:
    c_debug_path(void);
    e_file_location get_location(void);
    char const * get_full_path(char const * filename);
    void get_path(char const * filename, c_file_path * out_path);
    void get_directory_path(char const * directory, c_file_path * out_path);

private:
    void build_output_location_if_necessary(void);

    e_file_location m_location; // 0x0
    c_file_path m_path; // 0x4
    s_static_string<256> m_full_path; // 0x10C
};
static_assert(sizeof(c_debug_path) == 0x20C, "c_debug_path");

class c_crash_report_path
{
public:
    c_crash_report_path(void);
    e_file_location get_location(void);
    char const * get_full_path(char const * filename);
    void get_path(char const * filename, c_file_path * out_path);
    void get_directory_path(char const * directory, c_file_path * out_path);

private:
    void build_crash_report_location_if_necessary(void);

    e_file_location m_location; // 0x0
    s_static_string<256> m_directory; // 0x4
    c_file_path m_path; // 0x104
    s_static_string<256> m_full_path; // 0x20C
};
static_assert(sizeof(c_crash_report_path) == 0x30C, "c_crash_report_path");

/* ---------- prototypes */

/* ---------- globals */

extern char const * const k_crash_report_directory;

/* ---------- public code */

#endif // __DEBUG_PATHS_H__

