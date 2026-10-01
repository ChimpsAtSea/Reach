#pragma once
#ifndef __ASYNC_COMPARE_PRIVATE_H__
#define __ASYNC_COMPARE_PRIVATE_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"
#include "foundation\threadlib\async\async.h"

/* ---------- constants */

/* ---------- definitions */

class c_async_task_element_comparer
{
public:
    c_async_task_element_comparer(long thread_index);
    ~c_async_task_element_comparer(void);

    bool operator()(s_async_task_element const & a, s_async_task_element const & b);

private:
    unsigned char m_storage[0x80];
    long m_thread_index;
};
static_assert(sizeof(c_async_task_element_comparer) == 0x84, "c_async_task_element_comparer");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __ASYNC_COMPARE_PRIVATE_H__

