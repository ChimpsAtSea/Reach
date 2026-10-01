#pragma once
#ifndef __PHYSICAL_MEMORY_MAP_H__
#define __PHYSICAL_MEMORY_MAP_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"
#include "foundation\baselib\memory\allocation_interface.h"

/* ---------- constants */

enum memory_stage
{
    _memory_stage_initial = 0,
    _memory_stage_game_initialize,
    _memory_stage_resize_initialize,
    _memory_stage_resize_available,
    _memory_stage_map_configuration,
    _memory_stage_level_initialize,
    _memory_stage_resize_locked,
    _memory_stage_in_level,

    k_memory_stage_count
};

enum e_physical_memory_flags
{
    _physical_memory_minidump_bit = 0,
    _physical_memory_allocation_tracked_externally_bit,
    _physical_memory_internal_fixed_address_bit,
    _physical_memory_internal_lock_entire_resize_region_bit,

    k_physical_memory_flags_count
};

/* ---------- definitions */

void physical_memory_free(void * pointer);

class c_physical_memory_allocation : public c_allocation_interface
{
public:
    // verified via fallback_optional_cache_backend.obj callers; body owned by cache_file_tag_resource_runtime.obj
    c_physical_memory_allocation(memory_stage stage, char const * name) :
        m_stage(stage),
        m_name(name)
    {
    };

    virtual void * allocate(unsigned int size, char const * file, long line, char const * type, char const * subtype, char const * name);

    // unverified: owned by cache_file_tag_resource_runtime.obj
    virtual void deallocate(void * pointer, char const * file, long line)
    {
        physical_memory_free(pointer);
    };

private:
    memory_stage m_stage;
    char const * m_name;
};
static_assert(sizeof(c_physical_memory_allocation) == 0xC, "c_physical_memory_allocation");

/* ---------- prototypes */

void physical_memory_register_allocation(void);
unsigned long physical_memory_get_page_size(void const volatile * address);
void * _physical_memory_malloc(memory_stage stage, char const * name, long size, unsigned long flags, char const * file, long line);
void physical_memory_make_range_write_combined(void * base, unsigned long length);
long physical_memory_get_minidump_count(void);
void * physical_memory_get_minidump_block(long block_index, unsigned long * out_size);

/* ---------- globals */

/* ---------- public code */

#endif // __PHYSICAL_MEMORY_MAP_H__

