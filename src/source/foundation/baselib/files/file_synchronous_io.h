#pragma once
#ifndef __FILE_SYNCHRONOUS_IO_H__
#define __FILE_SYNCHRONOUS_IO_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"
#include "foundation\baselib\datatypes\flags.h"
#include "foundation\baselib\datatypes\static_string.h"
#include "foundation\baselib\files\file_errors.h"
#include "foundation\baselib\files\file_location_manager.h"

/* ---------- constants */

enum e_file_open_flags
{
    _file_open_read_bit = 0,
    _file_open_write_bit,
    _file_open_write_append_bit,
    _file_open_write_allow_read_bit,
    _file_open_temporary_bit, // FILE_ATTRIBUTE_TEMPORARY (name unverified)
    _file_open_delete_on_close_bit, // FILE_FLAG_DELETE_ON_CLOSE (name unverified)
    _file_open_random_access_bit,
    _file_open_sequential_scan_bit,

    k_file_open_flag_count
};

enum e_file_open_result
{
    _file_open_result_success = 0,
    _file_open_result_file_not_found, // names below unverified (from file_open GetLastError mapping)
    _file_open_result_access_denied,
    _file_open_result_invalid_name,
    _file_open_result_path_not_found,
    _file_open_result_invalid_drive,
    _file_open_result_sharing_violation,
    _file_open_result_append_failed,
    _file_open_result_unknown_error,

    k_file_open_result_count
};

/* ---------- definitions */

struct s_file_accessor
{
    void * handle; // 0x0
    e_file_location location; // 0x4
    unsigned long position; // 0x8
    s_static_string<256> path; // 0xC
};
static_assert(sizeof(s_file_accessor) == 0x10C, "s_file_accessor");

/* ---------- prototypes */

extern e_file_open_result file_open(class c_file_path const * path, c_flags_zero_init<e_file_open_flags, unsigned long, k_file_open_flag_count> flags, e_file_error_mode error_mode, s_file_accessor * out_file);
extern bool file_close(s_file_accessor * file);
extern bool file_get_read_only(s_file_accessor * file);
extern bool file_set_position(s_file_accessor * file, unsigned int position, e_file_error_mode error_mode);
extern bool file_set_position_eof(s_file_accessor * file);
extern unsigned int file_get_eof(s_file_accessor * file);
extern bool file_set_eof(s_file_accessor * file, unsigned int size);
extern bool file_at_eof(s_file_accessor * file);
extern bool file_flush(s_file_accessor * file);
extern bool file_read(s_file_accessor * file, unsigned int size, e_file_error_mode error_mode, void * buffer);
extern bool file_write(s_file_accessor * file, unsigned int size, e_file_error_mode error_mode, void const * buffer);
extern bool file_read_from_position(s_file_accessor * file, unsigned int position, unsigned int size, e_file_error_mode error_mode, void * buffer);
extern bool file_write_to_position(s_file_accessor * file, unsigned int position, unsigned int size, e_file_error_mode error_mode, void const * buffer);
extern void file_print(s_file_accessor * file, char const * string);
extern void file_printf(s_file_accessor * file, char const * format, ...);
extern void file_vprintf(s_file_accessor * file, char const * format, va_list arglist);
extern unsigned int file_get_position(s_file_accessor * file);

/* ---------- globals */

/* ---------- public code */

#endif // __FILE_SYNCHRONOUS_IO_H__

