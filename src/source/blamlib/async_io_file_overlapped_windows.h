#pragma once
#ifndef __ASYNC_IO_FILE_OVERLAPPED_WINDOWS_H__
#define __ASYNC_IO_FILE_OVERLAPPED_WINDOWS_H__

/* ---------- headers */

#include <xtl.h>
#include "baselib\synchronized_value_windows.h"
#include "core\corelib\cseries\cseries_macros.h"

/* ---------- constants */

/* ---------- definitions */

struct s_simple_read_file_ex_overlapped_result
{
    void reset(void)
    {
        done.set(0);
    }

    c_synchronized_int32 done;
    unsigned long error_code;
    unsigned long bytes_transferred;
    unsigned long bytes_requested;
};
static_assert(sizeof(s_simple_read_file_ex_overlapped_result) == 0x10, "s_simple_read_file_ex_overlapped_result");

/* ---------- prototypes */

void initialize_simple_overlapped(unsigned long offset, unsigned long size, _OVERLAPPED * out_overlapped, s_simple_read_file_ex_overlapped_result * out_overlapped_result);
void simple_read_file_ex_completion_routine(unsigned long error_code, unsigned long bytes_transferred, _OVERLAPPED * overlapped);

/* ---------- globals */

/* ---------- public code */

#endif // __ASYNC_IO_FILE_OVERLAPPED_WINDOWS_H__

