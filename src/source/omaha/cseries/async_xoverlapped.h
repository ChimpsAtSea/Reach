#ifndef __ASYNC_XOVERLAPPED_H__
#define __ASYNC_XOVERLAPPED_H__
#pragma once

/* ---------- headers */

#include "omaha\memory\static_arrays.h"

/* ---------- constants */

enum e_overlapped_task_state
{
    k_overlapped_task_state_count = 6
};

/* ---------- definitions */

// layout from ??0c_overlapped_task@@QAA@PBDJ@Z (async_xoverlapped.obj); virtuals other than the destructor not declared yet
class c_overlapped_task
{
public:
    enum e_overlapped_task_flags
    {
        k_overlapped_task_flags_count = 2
    };

    virtual ~c_overlapped_task();

    bool busy() const; // $TODO inline in the target (f i), body not reversed yet

protected:
    c_flags<e_overlapped_task_flags, unsigned short, k_overlapped_task_flags_count> m_flags; // 0x4
    c_enum<e_overlapped_task_state, unsigned short, 0, k_overlapped_task_state_count> m_task_state; // 0x6
    char const * m_file; // 0x8
    long m_line; // 0xC
    unsigned long m_unknown10; // 0x10
    unsigned long m_unknown14; // 0x14
};
static_assert(sizeof(c_overlapped_task) == 0x18, "c_overlapped_task");

/* ---------- prototypes */

void overlapped_task_block_until_finished(c_overlapped_task const * task);

/* ---------- globals */

/* ---------- public code */

#endif // __ASYNC_XOVERLAPPED_H__

