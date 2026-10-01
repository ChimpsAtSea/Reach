#pragma once
#ifndef __SIMPLE_FILE_H__
#define __SIMPLE_FILE_H__

/* ---------- headers */

#include <stdio.h>
#include "foundation\baselib\files\file_errors.h"
#include "foundation\baselib\files\file_path.h"

/* ---------- constants */

enum e_simple_file_open_flags
{
    _simple_file_open_binary_bit = 0,
    _simple_file_open_read_bit,
    _simple_file_open_write_bit,
    _simple_file_open_write_append_bit,
    _simple_file_open_write_allow_read_bit,
    _simple_file_open_silent_bit, // name unverified
    _simple_file_open_delete_on_close_bit, // name unverified

    k_simple_file_open_flag_count
};

enum e_simple_file_flags
{
    _simple_file_reading_bit = 0,
    _simple_file_writing_bit,
    _simple_file_silent_bit, // name unverified
    _simple_file_delete_on_close_bit, // name unverified

    k_simple_file_flag_count
};

/* ---------- definitions */

class c_simple_file
{
public:
    c_simple_file(void);
    c_simple_file(char const * debug_filename);
    c_simple_file(c_file_path const * path);
    ~c_simple_file(void);

    bool is_open(void) const
    {
        mangled_ppc("?is_open@c_simple_file@@QBA_NXZ");

        return m_file_handle != NULL;
    };

    void set_debug_filename(char const * debug_filename);
    void set_path(c_file_path const * path);
    e_file_error_mode get_error_mode(void) const;
    bool is_silent(void) const;
    bool open(long flags);
    void close(void);
    unsigned int get_position(void);
    bool set_position(unsigned int position);
    bool set_position_eof(void);
    bool at_eof(void);
    void flush(void);
    void print(char const * string);
    void printf(char const * format, ...);
    void vprintf(char const * format, char * arglist);
    bool read(unsigned int size, void * buffer);
    bool write(unsigned int size, void const * buffer);
    bool read_from_position(unsigned int position, unsigned int size, void * buffer);
    bool write_to_position(unsigned int position, unsigned int size, void const * buffer);

private:
    long m_flags; // 0x0
    c_file_path m_path; // 0x4
    FILE * m_file_handle; // 0x10C
};
static_assert(sizeof(c_simple_file) == 0x110, "c_simple_file");

/* ---------- prototypes */

FILE * platform_fopen(char const * filename, char const * mode);
unsigned int platform_fseek(FILE * file, unsigned int offset, long origin);
__int64 platform_ftell(FILE * file);

/* ---------- globals */

/* ---------- public code */

#endif // __SIMPLE_FILE_H__

