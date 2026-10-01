#ifndef __ASYNC_BUFFER_H__
#define __ASYNC_BUFFER_H__
#pragma once

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"

/* ---------- constants */

enum e_async_buffer_file_access
{
    _async_buffer_file_access_write = 0,
    _async_buffer_file_access_read,
    _async_buffer_file_access_read_write,

    k_async_buffer_file_access_count,
    k_async_buffer_file_access_none = -1
};

enum e_async_buffer_disposition
{
    _async_buffer_disposition_create_always = 0,
    _async_buffer_disposition_open_existing,

    k_async_buffer_disposition_count,
    k_async_buffer_disposition_none = -1
};

/* ---------- definitions */

class c_allocation_interface;

// $TODO data members not recovered yet (IDA/H3: c_async_buffer_set_base with s_static_array<s_async_buffer, 3>, then file state)
class c_async_buffer_set
{
public:
    c_async_buffer_set(long buffer_count, long buffer_size_bits, long alignment_bits);
    ~c_async_buffer_set(); // $TODO inline in target (calls ~c_async_buffer_set_base), owned by sound_manager.obj

    bool allocate_storage(c_allocation_interface * allocation, long buffer_size);
    void use_external_storage(char ** buffers, long buffer_count, long buffer_size);
    void release_storage(c_allocation_interface * allocation);
    bool open_file(char const * file_name, e_async_buffer_file_access file_access, e_async_buffer_disposition disposition);
    bool close_file(void);
    void write(void const * buffer, long buffer_size, long * bytes_written, bool * out_error);
    void block_until_not_busy(void);

private:
    // $TODO placeholder: base (0x0-0x73) and file state (0x74-0x93) not recovered;
    // 0x94/0x98 hold the buffer_size_bits/alignment_bits ctor args. sizeof verified 0x9C (saved_film_scratch_memory stride)
    char m_unrecovered[0x9C];
};
static_assert(sizeof(c_async_buffer_set) == 0x9C, "c_async_buffer_set");

template<long k_buffer_size_bits, long k_alignment_bits>
class c_async_double_buffer : public c_async_buffer_set
{
public:
    c_async_double_buffer() :
        c_async_buffer_set(2, k_buffer_size_bits, k_alignment_bits)
    {
    };
};

template<long k_buffer_size_bits, long k_alignment_bits>
class c_async_single_buffer : public c_async_buffer_set
{
public:
    c_async_single_buffer() :
        c_async_buffer_set(1, k_buffer_size_bits, k_alignment_bits)
    {
    };
};

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __ASYNC_BUFFER_H__

