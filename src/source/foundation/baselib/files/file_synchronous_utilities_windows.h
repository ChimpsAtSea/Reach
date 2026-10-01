#pragma once
#ifndef __FILE_SYNCHRONOUS_UTILITIES_WINDOWS_H__
#define __FILE_SYNCHRONOUS_UTILITIES_WINDOWS_H__

/* ---------- headers */

#include <xtl.h>
#include "core\corelib\cseries\cseries_macros.h"
#include "foundation\baselib\datatypes\flags.h"
#include "foundation\baselib\datatypes\static_array.h"
#include "foundation\baselib\datatypes\static_string.h"
#include "foundation\baselib\files\file_path.h"
#include "foundation\baselib\files\file_synchronous_utilities.h"

/* ---------- constants */

long const k_find_files_maximum_search_depth = 16;

/* ---------- definitions */

struct s_file_time;

struct s_find_files_data
{
    s_flags<e_find_files_flags, unsigned long, k_find_files_flags_count> flags; // 0x0
    long depth; // 0x4
    c_file_path directory; // 0x8
    s_static_string<256> search_spec; // 0x110
    s_static_array<void *, k_find_files_maximum_search_depth> handles; // 0x210
    WIN32_FIND_DATAA find_data; // 0x250
};
static_assert(sizeof(s_find_files_data) == 0x390, "s_find_files_data");

/* ---------- prototypes */

bool file_exists(c_file_path const * path);
bool file_is_read_only(c_file_path const * path);
bool file_set_read_only(c_file_path const * path, bool read_only);
bool file_get_size(c_file_path const * path, unsigned int * out_size);
bool file_create(c_file_path const * path, e_file_overwrite_mode overwrite_mode);
bool file_delete(c_file_path const * path);
bool file_rename(c_file_path const * path, char const * new_name);
bool file_copy(c_file_path const * source_path, c_file_path const * destination_path, e_file_overwrite_mode overwrite_mode);
bool file_move(c_file_path const * source_path, c_file_path const * destination_path, e_file_overwrite_mode overwrite_mode);
bool file_build_temporary_path(char const * name, c_file_path * out_path);
bool directory_exists(c_file_path const * path);
bool directory_create(c_file_path const * path);
bool directory_delete_recursive(c_file_path const * path);
bool directory_rename(c_file_path const * path, char const * new_name);
bool directory_move(c_file_path const * source_path, c_file_path const * destination_path, e_file_overwrite_mode overwrite_mode);
void find_files_start(s_flags<e_find_files_flags, unsigned long, k_find_files_flags_count> flags, c_file_path const * directory, char const * search_spec, s_find_files_data * state);
void find_files_end(s_find_files_data * state);
bool find_files_next(s_find_files_data * state, c_file_path * out_path, s_file_time * out_time);

/* ---------- globals */

extern char const * const k_find_files_default_search_spec;

/* ---------- public code */

#endif // __FILE_SYNCHRONOUS_UTILITIES_WINDOWS_H__

