#pragma once
#ifndef __CSERIES_WINDOWS_DEBUG_H__
#define __CSERIES_WINDOWS_DEBUG_H__

/* ---------- headers */

#include "foundation\baselib\datatypes\static_string.h"
#include "omaha\main\main.h"

/* ---------- constants */

#define FAKE_EXCEPTION_CODE 'stk'

/* ---------- definitions */

struct _EXCEPTION_POINTERS;

class c_debug_output_path
{
public:
    c_debug_output_path();
    char const * get_root();
    char const * get_path(char const * file_name);

private:
    void build_root_if_necessary();

    c_static_string<32> m_root;
    c_static_string<260> m_path;
};
static_assert(sizeof(c_debug_output_path) == 0x124, "c_debug_output_path");

class c_crash_report_output_path
{
public:
    c_crash_report_output_path();
    char const * get_path(char const * file_name);
    char const * get_root();

private:
    c_static_string<32> m_root;
    c_static_string<32> m_crash_folder_name;
    c_static_string<260> m_path;
};
static_assert(sizeof(c_crash_report_output_path) == 0x144, "c_crash_report_output_path");

/* ---------- prototypes */

long generic_exception_filter(unsigned long exception_code, _EXCEPTION_POINTERS * exception_pointers);
c_static_string<260> make_debug_path(char const * file_name);
extern long exceptions_update(void);
bool debug_get_binary_filename(c_static_string<260> * binary_filename);
void build_error_report_progress_string(char * buffer, long buffer_size, char const * status);
void error_report_think_of_the_kittens(char * buffer, long buffer_capacity);
void crash_uploading_render_pregame_safe(char const * text, e_main_pregame_frame pregame_frame_type);

/* ---------- globals */

/* ---------- public code */

#endif // __CSERIES_WINDOWS_DEBUG_H__

