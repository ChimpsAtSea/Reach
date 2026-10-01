#pragma once
#ifndef __FILE_OUTPUT_BUFFER_H__
#define __FILE_OUTPUT_BUFFER_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"
#include "foundation\baselib\datatypes\static_array.h"

/* ---------- constants */

/* ---------- definitions */

struct s_file_accessor;

class c_file_output_buffer
{
public:
    c_file_output_buffer(void);
    ~c_file_output_buffer(void);

    void attach_file(s_file_accessor * file);
    void release_file(void);
    void write(long buffer_size, void const * buffer);
    void flush(void);

private:
    void write_internal(long buffer_size, void const * buffer);

    static long const k_buffer_size = 0x4000;

    s_file_accessor * m_file; // 0x0
    s_static_array<unsigned char, k_buffer_size> m_buffer; // 0x4
    long m_buffer_length; // 0x4004
};
static_assert(sizeof(c_file_output_buffer) == 0x4008, "c_file_output_buffer");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __FILE_OUTPUT_BUFFER_H__

