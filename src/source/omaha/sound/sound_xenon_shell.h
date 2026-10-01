#pragma once
#ifndef __SOUND_XENON_SHELL_H__
#define __SOUND_XENON_SHELL_H__

/* ---------- headers */

#include "foundation\baselib\memory\platform\platform_allocators_xenon.h"

/* ---------- constants */

/* ---------- definitions */

class c_sound_allocation_override_xenon :
    public c_allocation_override_xenon
{
public:
    virtual void * allocate(unsigned int size, XALLOC_ATTRIBUTES attributes);
    virtual void deallocate(void * address, XALLOC_ATTRIBUTES attributes);
    virtual unsigned int allocation_size(void * address, XALLOC_ATTRIBUTES attributes);
};

/* ---------- prototypes */

extern void shell_sound_memory_initialize(void);
extern void shell_sound_memory_dispose(void);
extern char const * xaudio_allocation_type_name(unsigned long object_type);

/* ---------- globals */

/* ---------- public code */

#endif // __SOUND_XENON_SHELL_H__

