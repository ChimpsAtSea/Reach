#pragma once
#ifndef __MINIDUMP_FILE_OUTPUT_H__
#define __MINIDUMP_FILE_OUTPUT_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"
#include "omaha\cseries\minidump_secure_writer_helper.h"
#include "omaha\tag_files\files.h"
#include "omaha\toolbox\file_helpers.h"

/* ---------- constants */

enum
{
    k_minidump_secure_stream_directory_count = 10,
};

enum e_minidump_secure_header_flags
{
    _minidump_secure_header_compressed_bit = 0,
    _minidump_secure_header_encrypted_bit,

    k_minidump_secure_header_flag_count
};

/* ---------- definitions */

struct s_minidump_secure_header
{
    unsigned long signature; // 0x0
    unsigned long flags; // 0x4
    char encrypted_session_key[0x100]; // 0x8
    unsigned long stream_count; // 0x108
};
static_assert(sizeof(s_minidump_secure_header) == 0x10C, "s_minidump_secure_header");

struct s_minidump_secure_stream_directory
{
    unsigned long flags; // 0x0
    unsigned long file_offset; // 0x4
    unsigned long stream_offset; // 0x8
    unsigned long uncompressed_bytes; // 0xC
    unsigned long compressed_bytes; // 0x10
    unsigned long encrypted_bytes; // 0x14
};
static_assert(sizeof(s_minidump_secure_stream_directory) == 0x18, "s_minidump_secure_stream_directory");

// vtable order from ??_7c_minidump_file_output_secure@@6B@
class c_minidump_file_output_interface
{
public:
    virtual void open(char const * file_name) = 0;
    virtual bool close(void) = 0;
    virtual bool is_valid(void) = 0;
    virtual bool write(void const * data, long size) = 0;
    virtual bool seek(long offset) = 0;
    virtual long tell(void) = 0;
};
static_assert(sizeof(c_minidump_file_output_interface) == 0x4, "c_minidump_file_output_interface");

class c_minidump_file_output_secure :
    public c_minidump_file_output_interface
{
public:
    c_minidump_file_output_secure(void);
    ~c_minidump_file_output_secure(void)
    {
    };

    virtual void open(char const * file_name);
    virtual bool close(void);
    virtual bool is_valid(void);
    virtual bool write(void const * data, long size);
    virtual bool seek(long offset);
    virtual long tell(void);

private:
    bool write_header_and_directory_entries(bool initial_write);
    bool begin_current_stream(void);
    bool end_current_stream(void);

    bool m_valid; // 0x4
    long m_current_stream_index; // 0x8
    long m_position; // 0xC
    s_file_reference m_file; // 0x10
    c_aligned_stored_buffered_file_writer<4096> m_aligned_file_writer; // 0x120
    c_minidump_secure_writer_helper m_secure_writer_helper; // 0x1130
};
static_assert(sizeof(c_minidump_file_output_secure) == 0x1300, "c_minidump_file_output_secure");

/* ---------- prototypes */

/* ---------- globals */

extern s_minidump_secure_stream_directory g_secure_stream_directory_memory[k_minidump_secure_stream_directory_count];

/* ---------- public code */

#endif // __MINIDUMP_FILE_OUTPUT_H__

