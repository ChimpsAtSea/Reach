#pragma once
#ifndef __ASYNC_XOVERLAPPED_MEMORY_H__
#define __ASYNC_XOVERLAPPED_MEMORY_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"
#include "foundation\baselib\memory\allocation_interface.h"

/* ---------- constants */

/* ---------- definitions */

struct c_status_line;
struct s_data_array;

class c_async_xoverlapped_memory_scope_lock
{
public:
    c_async_xoverlapped_memory_scope_lock(void);
    ~c_async_xoverlapped_memory_scope_lock(void);
};

class c_overlapped_allocation : public c_allocation_interface
{
public:
    c_overlapped_allocation(void);

    virtual void * allocate(unsigned int size, char const * file, long line, char const * type, char const * subtype, char const * name);
    virtual void deallocate(void * pointer, char const * file, long line);
};
static_assert(sizeof(c_overlapped_allocation) == 0x4, "c_overlapped_allocation");

/* ---------- prototypes */

extern void overlapped_memory_initialize(void);
extern void overlapped_memory_dispose(void);
extern void overlapped_memory_print_usage(void);
extern c_allocation_interface * overlapped_memory_allocation(void);
extern void * overlapped_malloc_tracked(unsigned int size, char const * file, long line);
extern void * overlapped_calloc_tracked(unsigned int size, char const * file, long line);
extern void * overlapped_realloc_tracked(void * ptr, unsigned int size, char const * file, long line);
extern s_data_array * overlapped_data_new_tracked(char const * name, long maximum_count, long size, char const * file, long line);
extern void overlapped_free(void const * ptr);
extern void overlapped_memory_pool_verify(void);
extern void overlapped_memory_dump(char const * prefix);
extern c_allocation_interface * get_overlapped_allocation(void);

/* ---------- globals */

extern bool g_display_overlapped_memory;
extern c_status_line g_overlapped_memory_status_line;

/* ---------- public code */

#endif // __ASYNC_XOVERLAPPED_MEMORY_H__
