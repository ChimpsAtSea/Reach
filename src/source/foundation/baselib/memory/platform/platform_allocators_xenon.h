#pragma once
#ifndef __PLATFORM_ALLOCATORS_XENON_H__
#define __PLATFORM_ALLOCATORS_XENON_H__

/* ---------- headers */

#include <xtl.h>

/* ---------- constants */

/* ---------- definitions */

class c_allocation_override_xenon
{
public:
    virtual void * allocate(unsigned int size, XALLOC_ATTRIBUTES attributes) = 0;
    virtual void deallocate(void * address, XALLOC_ATTRIBUTES attributes) = 0;
    virtual unsigned int allocation_size(void * address, XALLOC_ATTRIBUTES attributes) = 0;
};

class c_buffer_allocation_override_xenon :
    public c_allocation_override_xenon
{
public:
    c_buffer_allocation_override_xenon(unsigned int buffer_size, void * buffer);

    virtual void * allocate(unsigned int size, XALLOC_ATTRIBUTES attributes);
    virtual void deallocate(void * address, XALLOC_ATTRIBUTES attributes);
    virtual unsigned int allocation_size(void * address, XALLOC_ATTRIBUTES attributes);

private:
    unsigned int m_buffer_size;
    void * m_buffer;
    long m_offset;
};

/* ---------- prototypes */

extern void allocation_override_xenon_register(XALLOC_ALLOCATOR_IDS allocator_id, c_allocation_override_xenon * override);
extern void allocation_override_xenon_deregister(XALLOC_ALLOCATOR_IDS allocator_id, c_allocation_override_xenon * override);
extern float allocation_xenon_get_failure_chance(void);
extern void allocation_xenon_set_failure_chance(float failure_chance);
extern void * XMemAlloc_baselib(unsigned long size, unsigned long attributes);
extern void XMemFree_baselib(void * address, unsigned long attributes);
extern unsigned long XMemSize_baselib(void * address, unsigned long attributes);

/* ---------- globals */

/* ---------- public code */

#endif // __PLATFORM_ALLOCATORS_XENON_H__

