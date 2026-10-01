#pragma once
#ifndef __ROCKALL_HEAP_H__
#define __ROCKALL_HEAP_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"

/* ---------- constants */

/* ---------- definitions */

class ROCKALL_FRONT_END;

class c_rockall_heap
{
public:
    ~c_rockall_heap(void);
    void * allocate(long size);
    void * reallocate(void * pointer, long size);
    void deallocate(void * pointer);
    bool verify_pointer(void * pointer);
    long get_allocation_size(void * pointer);

protected:
    c_rockall_heap(ROCKALL_FRONT_END * rockall_front_end, bool is_debug_heap);

    ROCKALL_FRONT_END * m_rockall_front_end; // 0x0
    long m_extant_allocation_count; // 0x4
    bool m_is_debug_heap; // 0x8
};
static_assert(sizeof(c_rockall_heap) == 0xC, "c_rockall_heap");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __ROCKALL_HEAP_H__

