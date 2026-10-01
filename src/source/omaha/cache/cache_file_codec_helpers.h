#ifndef __CACHE_FILE_CODEC_HELPERS_H__
#define __CACHE_FILE_CODEC_HELPERS_H__
#pragma once

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"
#include "omaha\memory\wrapped_arrays.h"

/* ---------- constants */

/* ---------- definitions */

class c_persist_stream;

class c_bufferred_output_stream
{
public:
    c_bufferred_output_stream(c_persist_stream * stream);
    ~c_bufferred_output_stream(void);
    c_basic_buffer<void> get_buffer(void);
    void commit_buffer(c_basic_buffer<void> finished_buffer);
    bool flush(void);
    void flunk(void);

private:
    enum
    {
        k_write_buffer_size = 0x4000
    };

    c_persist_stream * m_stream; // 0x0
    bool m_failed; // 0x4
    char m_write_buffer_storage[k_write_buffer_size]; // 0x5
    c_basic_buffer<void> m_write_buffer; // 0x4008
    c_basic_buffer<void> m_buffer_left; // 0x4010
};
static_assert(sizeof(c_bufferred_output_stream) == 0x4018, "c_bufferred_output_stream");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __CACHE_FILE_CODEC_HELPERS_H__

