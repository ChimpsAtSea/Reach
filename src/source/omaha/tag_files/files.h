#pragma once
#ifndef __FILES_H__
#define __FILES_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"

/* ---------- constants */

// $TODO names from H3; only _name_filename_bit verified (megalo_convert_variant_files)
enum e_name_flags
{
    _name_directory_bit = 0,
    _name_parent_directory_bit,
    _name_filename_bit,
    _name_extension_bit,

    _name_full_mask = 0xD, // FLAG(_name_directory_bit) | FLAG(_name_filename_bit) | FLAG(_name_extension_bit)
};

// $TODO names from H3; only _permission_write_bit verified (hs_dump_script_to_file)
enum e_permission_flags
{
    _permission_read_bit = 0,
    _permission_write_bit,
    _permission_write_append_bit,
    _permission_write_allow_read_bit,

    k_permission_flag_count
};

/* ---------- definitions */

// $TODO: layout not yet reversed (size from megalogamengine_loading stack frames)
struct s_file_reference
{
    char data[0x110];
};
static_assert(sizeof(s_file_reference) == 0x110, "s_file_reference");

// $TODO: layout not yet reversed (size from c_autosave_queue_enumerate_async: find data 0x220, next member 0x5A8;
// matches H3 flags/depth/location/path[256]/search_spec[256]/handles[16] + WIN32_FIND_DATAA 0x140)
struct s_find_file_data
{
    char data[0x388];
};
static_assert(sizeof(s_find_file_data) == 0x388, "s_find_file_data");

struct s_file_last_modification_date
{
    char data[8]; // 0x0 (FILETIME)
};
static_assert(sizeof(s_file_last_modification_date) == 0x8, "s_file_last_modification_date");

struct s_file_handle
{
    void * handle; // 0x0
};
static_assert(sizeof(s_file_handle) == 0x4, "s_file_handle");

/* ---------- prototypes */

extern s_file_reference * file_reference_create_from_path(s_file_reference * reference, char const * path, bool directory);
extern char * file_reference_get_name(s_file_reference const * reference, unsigned long flags, char * out_name, long name_length);
extern char * file_reference_get_directory(s_file_reference const * reference, char * out_name, long name_length);
extern bool file_read_into_buffer(s_file_reference * reference, void * buffer, unsigned long size);
extern s_file_reference * file_reference_copy(s_file_reference * destination, s_file_reference const * source);
extern void directory_create_or_delete_contents(char const * directory);

// files_windows
extern s_file_reference * file_reference_create(s_file_reference * reference, short location);
extern bool file_create(s_file_reference * file);
extern bool file_delete(s_file_reference * file);
extern bool file_open(s_file_reference * file, unsigned long open_flags, unsigned long * error);
extern bool file_close(s_file_reference * file);
extern bool file_write(s_file_reference * file, unsigned long size, void const * buffer);
extern bool file_reference_get_file_handle(s_file_reference const * reference, s_file_handle * out_handle);
extern bool file_handle_is_valid(s_file_handle handle);
extern bool file_exists(s_file_reference const * file);
extern bool file_create_parent_directories_if_not_present(s_file_reference const * file);
extern bool file_get_size(s_file_reference const * file, unsigned long * size);
extern bool file_read(s_file_reference * file, unsigned long size, bool suppress_errors, void * buffer);
extern bool file_set_position(s_file_reference * file, unsigned long offset, bool suppress_errors);
extern unsigned long file_get_position(s_file_reference const * file);
extern unsigned long file_get_eof(s_file_reference const * file);
extern void find_files_start(s_find_file_data * data, unsigned long flags, s_file_reference const * directory);
extern void find_files_start_with_search_spec(s_find_file_data * data, unsigned long flags, s_file_reference const * directory, char const * search_spec);
extern bool find_files_next(s_find_file_data * data, s_file_reference * file, s_file_last_modification_date * date);
extern void find_files_end(s_find_file_data * data);

template<long k_name_length>
char * file_reference_get_name(s_file_reference const * reference, unsigned long flags, char (&out_name)[k_name_length])
{
    return file_reference_get_name(reference, flags, out_name, k_name_length);
}

template<long k_name_length>
char * file_reference_get_directory(s_file_reference const * reference, char (&out_name)[k_name_length])
{
    return file_reference_get_directory(reference, out_name, k_name_length);
}

extern int file_compare_last_modification_dates(s_file_last_modification_date const * date1, s_file_last_modification_date const * date2);

// "f i", owned by shell_xenon.obj
inline char * file_reference_get_path(s_file_reference const * reference, char * out_path, long path_length)
{
    return file_reference_get_name(reference, FLAG(_name_directory_bit) | FLAG(_name_filename_bit) | FLAG(_name_extension_bit), out_path, path_length);
}

/* ---------- globals */

/* ---------- public code */

#endif // __FILES_H__

