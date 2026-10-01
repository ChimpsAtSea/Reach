#ifndef __FILE_HELPERS_H__
#define __FILE_HELPERS_H__
#pragma once

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"
#include "omaha\tag_files\files.h"

/* ---------- constants */

/* ---------- definitions */

#define __FILE_HELPERS_H_FILE__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\toolbox\\file_helpers.h"

// methods are defined out of line in hs_dump.cpp (hs_dump.obj owns them; their asserts name this header)
class c_transacted_file_reference
{
public:
    c_transacted_file_reference(s_file_reference const * file);
    bool begin(void);
    s_file_reference * get_file(void);
    bool commit(void);

private:
    bool m_file_is_open; // 0x0
    s_file_reference m_temporary_file; // 0x1
    s_file_reference m_destination_file; // 0x111
};
static_assert(sizeof(c_transacted_file_reference) == 0x221, "c_transacted_file_reference");

class c_file_finder
{
public:
    c_file_finder(unsigned long flags, s_file_reference const * starting_directory);
    c_file_finder(unsigned long flags, s_file_reference const * starting_directory, char const * file_spec);
    ~c_file_finder(void);
    bool next(s_file_reference * out_file_reference, s_file_last_modification_date * out_modification_date);

private:
    s_find_file_data m_find_file_data; // 0x0
};
static_assert(sizeof(c_file_finder) == 0x388, "c_file_finder");

class c_aligned_buffered_file_writer
{
public:
    c_aligned_buffered_file_writer(void);
    void initialize(s_file_reference * file, char * write_buffer, long write_buffer_size);
    bool write(char const * data, long count);
    bool flush(void);
    unsigned long get_position(void);
    bool set_position(unsigned long offset);

private:
    unsigned long get_physical_file_size(void);
    bool get_is_at_end_of_phyisical_file(void);
    bool read_current_block_into_buffer(void);

    s_file_reference * m_file; // 0x0
    char * m_write_buffer; // 0x4
    long m_write_buffer_size; // 0x8
    long m_write_buffer_count; // 0xC
};
static_assert(sizeof(c_aligned_buffered_file_writer) == 0x10, "c_aligned_buffered_file_writer");

// inline methods are emitted by their users (rasterizer_xenon_main, online_files, network_blf_compress)
template<long k_stored_buffer_size>
class c_aligned_stored_buffered_file_writer
{
public:
    c_aligned_stored_buffered_file_writer(void)
    {
    };

    void initialize(s_file_reference * file)
    {
        m_writer.initialize(file, m_buffer, k_buffer_size);
    };

    bool write(char const * data, long count)
    {
        return m_writer.write(data, count);
    };

    bool flush(void)
    {
        return m_writer.flush();
    };

    unsigned long get_position(void)
    {
        return m_writer.get_position();
    };

    bool set_position(unsigned long offset)
    {
        return m_writer.set_position(offset);
    };

private:
    static long const k_buffer_size = k_stored_buffer_size;

    c_aligned_buffered_file_writer m_writer; // 0x0
    char m_buffer[k_buffer_size]; // 0x10
};

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __FILE_HELPERS_H__

