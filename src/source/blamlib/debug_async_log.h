#pragma once
#ifndef __DEBUG_ASYNC_LOG_H__
#define __DEBUG_ASYNC_LOG_H__

/* ---------- headers */

#include "omaha\cseries\async_buffer.h"

/* ---------- constants */

/* ---------- definitions */

class c_debug_async_log : public c_async_double_buffer<14, 6>
{
public:
    void initialize(c_allocation_interface * allocation, unsigned long buffer_size);
    bool open(char const * file_name);
    void write(char const * string);
    void close(void);
    void dispose(c_allocation_interface * allocation);
};

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __DEBUG_ASYNC_LOG_H__

