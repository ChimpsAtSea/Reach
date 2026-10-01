#pragma once
#ifndef __RUNTIME_STATE_H__
#define __RUNTIME_STATE_H__

/* ---------- headers */

#include "foundation\baselib\memory\allocation_interface.h"
#include "core\corelib\cseries\cseries_macros.h"

/* ---------- constants */

unsigned long const k_runtime_state_size = 0x3B0000;

/* ---------- definitions */

struct s_runtime_state_globals
{
    bool locked; // 0x0
    bool fatal_error_recorded; // 0x1
    bool unused_flags[2]; // 0x2
    void * base_address; // 0x4
    long allocated_size; // 0x8
    unsigned long size_checksum; // 0xC
};

/* ---------- prototypes */

extern void runtime_state_shell_initialize(void);
extern void runtime_state_shell_dispose(void);
extern void runtime_state_adjust_available_region(unsigned long old_allocated_size, unsigned long new_allocated_size);
extern void runtime_state_initialize(void);
extern void runtime_state_dispose(void);
extern void runtime_state_initialize_for_new_map(void);
extern void runtime_state_dispose_from_old_map(void);
extern void * runtime_state_malloc_verbose(char const * file, long line, char const * name, char const * type, long size);
extern void * runtime_state_malloc_aligned_verbose(char const * file, long line, char const * name, char const * type, long size, long alignment_bits);
extern void const * runtime_state_get_buffer_address(long * buffer_size);

// runtime_state_windows.obj
extern void * runtime_state_allocate_buffer(long size);
extern void runtime_state_free_buffer(void * buffer);

class c_runtime_state_allocation : public c_allocation_interface
{
public:
    virtual void * allocate(unsigned int size, char const * file, long line, char const * type, char const * subtype, char const * name)
    {
        mangled_ppc("?allocate@c_runtime_state_allocation@@UAAPAXIPBDJ000@Z");

        void * result = runtime_state_malloc_verbose(file, line, name, type, size);
        return result;
    }

    virtual void deallocate(void * pointer, char const * file, long line)
    {
        mangled_ppc("?deallocate@c_runtime_state_allocation@@UAAXPAXPBDJ@Z");
    }
};

/* ---------- globals */

extern c_allocation_interface * g_runtime_state_allocation;
extern s_runtime_state_globals g_runtime_state_globals;
extern c_runtime_state_allocation g_actual_runtime_state_allocation;

/* ---------- public code */

#endif // __RUNTIME_STATE_H__
