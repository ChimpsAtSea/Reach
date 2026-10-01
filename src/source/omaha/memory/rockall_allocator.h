#pragma once
#ifndef __ROCKALL_ALLOCATOR_H__
#define __ROCKALL_ALLOCATOR_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"
#include "foundation\baselib\memory\allocation_interface.h"

/* ---------- constants */

/* ---------- definitions */

class c_rockall_heap;

class c_rockall_allocator : public c_allocation_interface
{
public:
    c_rockall_allocator(c_rockall_heap * rockall_heap);

    virtual void * allocate(unsigned int size, char const * file, long line, char const * type, char const * subtype, char const * name);
    virtual void deallocate(void * pointer, char const * file, long line);

private:
    c_rockall_heap * m_rockall_heap; // 0x4
};
static_assert(sizeof(c_rockall_allocator) == 0x8, "c_rockall_allocator");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __ROCKALL_ALLOCATOR_H__

