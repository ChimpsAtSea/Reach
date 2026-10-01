#pragma once
#ifndef __PHYSICAL_MEMORY_REGIONS_H__
#define __PHYSICAL_MEMORY_REGIONS_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"
#include "foundation\baselib\datatypes\static_array.h"
#include "omaha\memory\wrapped_arrays.h"

/* ---------- constants */

enum e_physical_memory_allocation_region
{
    _physical_memory_allocation_region_xaudio = 0,

    k_physical_memory_allocation_region_count
};

/* ---------- definitions */

class c_physical_memory_allocation_region
{
public:
    c_physical_memory_allocation_region(void)
    {
        mangled_ppc("??0c_physical_memory_allocation_region@@QAA@XZ");
    };

    void initialize(c_basic_buffer<void> allocation_range);
    void * allocate(char const * region_name, char const * name, unsigned long size, long alignment_bits);

protected:
    c_basic_buffer<void> m_allocation_range; // 0x0
    c_basic_buffer<void> m_range_left; // 0x8
};
static_assert(sizeof(c_physical_memory_allocation_region) == 0x10, "c_physical_memory_allocation_region");

struct s_physical_memory_allocation_region_globals
{
    s_static_array<c_physical_memory_allocation_region, k_physical_memory_allocation_region_count> regions; // 0x0
};
static_assert(sizeof(s_physical_memory_allocation_region_globals) == 0x10, "s_physical_memory_allocation_region_globals");

/* ---------- prototypes */

void physical_memory_regions_initialize(void);
c_physical_memory_allocation_region * get_allocation_region(e_physical_memory_allocation_region region);
void physical_memory_regions_dispose(void);
void * _physical_memory_region_allocate(e_physical_memory_allocation_region region, unsigned long size, long alignment_bits, char const * name);

/* ---------- globals */

extern s_physical_memory_allocation_region_globals g_physical_memory_allocation_region_globals;

/* ---------- public code */

#endif // __PHYSICAL_MEMORY_REGIONS_H__

