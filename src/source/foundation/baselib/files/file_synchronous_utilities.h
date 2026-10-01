#pragma once
#ifndef __FILE_SYNCHRONOUS_UTILITIES_H__
#define __FILE_SYNCHRONOUS_UTILITIES_H__

/* ---------- headers */

#include "foundation\baselib\datatypes\flags.h"

/* ---------- constants */

enum e_file_overwrite_mode
{
    _file_overwrite_mode_fail_if_exists = 0,
    _file_overwrite_mode_overwrite,

    k_file_overwrite_mode_count
};

enum e_find_files_flags
{
    _find_files_recursive_bit = 0,
    _find_files_enumerate_directories_bit,
    _find_files_enumerate_files_with_directories_bit,

    k_find_files_flags_count
};

/* ---------- definitions */

class c_file_path;
class c_allocation_interface;

/* ---------- prototypes */

bool file_is_readable(c_file_path const * path);
bool file_create_parent_directories(c_file_path const * path);
bool file_read_into_memory(c_file_path const * path, c_allocation_interface * allocator, unsigned int extra_padding_size, void ** out_buffer, unsigned int * out_buffer_size, unsigned int * out_file_size);
bool file_read_into_buffer(c_file_path const * path, void * buffer, unsigned int buffer_size, unsigned int * out_bytes_read, unsigned int * out_file_size);
bool file_trim(c_file_path const * path, unsigned int maximum_size);
bool file_trim_fast(c_file_path const * path, unsigned int maximum_size, void * working_buffer, unsigned int working_buffer_size);
bool directory_create_and_delete_contents(c_file_path const * path);
bool directory_create_recursive(c_file_path const * path);
bool directory_copy_recursive(c_file_path const * source_path, c_file_path const * destination_path, e_file_overwrite_mode overwrite_mode);
long find_files(s_flags<e_find_files_flags, unsigned long, k_find_files_flags_count> flags, c_file_path const * directory, char const * search_spec, long maximum_result_count, c_file_path * out_results);
bool directory_create_and_delete_contents(c_file_path const * path);

/* ---------- globals */

/* ---------- public code */

#endif // __FILE_SYNCHRONOUS_UTILITIES_H__

