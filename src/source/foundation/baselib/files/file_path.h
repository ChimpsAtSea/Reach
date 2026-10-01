#pragma once
#ifndef __FILE_PATH_H__
#define __FILE_PATH_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"
#include "foundation\baselib\datatypes\flags.h"
#include "foundation\baselib\datatypes\static_string.h"
#include "foundation\baselib\files\file_location_manager.h"

/* ---------- constants */

long const k_maximum_filename_length = 256;

enum e_file_path_get_bits
{
    _file_path_get_directory_bit = 0,
    _file_path_get_parent_directory_bit,
    _file_path_get_filename_bit,
    _file_path_get_extension_bit,
    _file_path_get_location_relative_bit,

    k_file_path_get_bit_count
};

/* ---------- definitions */

class c_file_path
{
public:
    enum e_file_path_flags
    {
        _file_path_has_filename_bit = 0,

        k_number_of_file_path_flags
    };

    void clear(void);
    void set_root(e_file_location location);
    void set_file_path(e_file_location location, char const * path);
    void set_directory_path(e_file_location location, char const * path);
    void copy(c_file_path const * source);
    bool is_directory(void) const;
    bool is_equal(c_file_path const * path) const;
    e_file_location get_location(void) const;
    char const * get_filename_direct(void) const;
    void add_directory(char const * directory);
    void remove_directory(void);
    void set_filename(char const * name);
    void remove_filename(void);
    char * get_full_path(char * out_name, long name_length) const;
    char * get(unsigned long path_flags, char * out_name, long name_length) const;

    template<long k_maximum_count>
    char * get_full_path(char (&out_path)[k_maximum_count]) const
    {
        return get_full_path(out_path, k_maximum_count);
    };

    template<long k_maximum_count>
    char * get_full_path(s_static_string<k_maximum_count> * out_path) const
    {
        return get_full_path(out_path->get_buffer(), out_path->max_length());
    };

    template<long k_maximum_count>
    char * get_name(unsigned long path_flags, s_static_string<k_maximum_count> * out_name) const
    {
        return get(path_flags, out_name->get_buffer(), out_name->max_length());
    };

    char * get_parent_directory(char * out_name, long name_length) const
    {
        return get(FLAG(_file_path_get_parent_directory_bit), out_name, name_length);
    };

    template<long k_maximum_count>
    char * get_parent_directory(s_static_string<k_maximum_count> * out_name) const
    {
        return get_parent_directory(out_name->get_buffer(), out_name->max_length());
    };

    char * get_filename(char * out_name, long name_length) const
    {
        return get(FLAG(_file_path_get_filename_bit) | FLAG(_file_path_get_extension_bit), out_name, name_length);
    };

    template<long k_maximum_count>
    char * get_filename(s_static_string<k_maximum_count> * out_name) const
    {
        return get_filename(out_name->get_buffer(), out_name->max_length());
    };

private:
    void initialize(e_file_location location);

    static void path_add_name(char * path, long path_length, char const * name);
    static void path_add_extension(char * path, long path_length, char const * extension);
    static void path_remove_name(char * path);
    static void path_split(char * path, char ** out_directory, char ** out_parent_directory, char ** out_filename, char ** out_extension, bool split_filename);

    s_static_string<256> m_path; // 0x0
    e_file_location m_location; // 0x100
    s_flags<e_file_path_flags, unsigned long, k_number_of_file_path_flags> m_flags; // 0x104
};
static_assert(sizeof(c_file_path) == 0x108, "c_file_path");

/* ---------- prototypes */

/* ---------- globals */

extern char const * const k_file_extension_string;
extern char const * const k_file_directory_string;
extern char const * const k_file_current_directory_string;
extern char const * const k_file_parent_directory_string;

/* ---------- public code */

#endif // __FILE_PATH_H__

