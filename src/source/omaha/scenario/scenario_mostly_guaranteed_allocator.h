#pragma once
#ifndef __SCENARIO_MOSTLY_GUARANTEED_ALLOCATOR_H__
#define __SCENARIO_MOSTLY_GUARANTEED_ALLOCATOR_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"
#include "core\corelib\cseries\cseries_memory.h"
#include "foundation\baselib\memory\allocation_interface.h"
#include "foundation\baselib\memory\debug_memory\debug_memory_allocators.h"
#include "omaha\cache\optional_cache_constants.h"
#include "omaha\cseries\cseries.h"
#include "omaha\memory\wrapped_arrays.h"

/* ---------- constants */

/* ---------- definitions */

// f i (scenario_mostly_guaranteed_allocator.obj)
class c_tracked_allocation_base :
    public c_allocation_interface
{
public:
    virtual void * allocate(unsigned int size, char const * file, long line, char const * type, char const * subtype, char const * name)
    {
        mangled_ppc("?allocate@c_tracked_allocation_base@@UAAPAXIPBDJ000@Z");

        void * result = allocate_internal(size);
        if (result)
        {
            debug_track_nonheap_alloc(offset_pointer(this, reinterpret_cast<long>(result)), size, _debug_memory_exclude_from_minidump_bit, file, line, NONE, type, subtype, name);
        }

        return result;
    };

    virtual void deallocate(void * pointer, char const * file, long line)
    {
        mangled_ppc("?deallocate@c_tracked_allocation_base@@UAAXPAXPBDJ@Z");

        if (pointer)
        {
            debug_track_nonheap_free(offset_pointer(this, reinterpret_cast<long>(pointer)), file, line);
        }
        deallocate_internal(pointer);
    };

private:
    virtual void * allocate_internal(unsigned int size) = 0;
    virtual void deallocate_internal(void * pointer) = 0;
};
static_assert(sizeof(c_tracked_allocation_base) == 0x4, "c_tracked_allocation_base");

class c_scenario_mostly_guaranteed_allocation :
    public c_tracked_allocation_base,
    public c_optional_cache_user_callback
{
public:
    enum e_allocation_type
    {
        _allocation_type_none = -1,
        _allocation_type_unknown0 = 0,
        _allocation_type_resource_stoler,
    };

    c_scenario_mostly_guaranteed_allocation(void);

private:
    virtual char const * get_name(void);
    virtual void get_memory_configuration(e_map_memory_configuration map_configuration, s_optional_cache_user_memory_configuration * memory_configuration);
    virtual void idle(void const * pointer);
    virtual void terminate(void const * pointer);
    virtual void * allocate_internal(unsigned int size);
    virtual void deallocate_internal(void * ptr);

    e_allocation_type m_allocation_type; // 0x8
    c_basic_buffer<void> m_allocation; // 0xC
};
static_assert(sizeof(c_scenario_mostly_guaranteed_allocation) == 0x14, "c_scenario_mostly_guaranteed_allocation");

/* ---------- prototypes */

c_allocation_interface * scenario_mostly_guaranteed_allocator_initialize(void);
void scenario_mostly_guaranteed_allocator_dispose(void);

/* ---------- globals */

extern c_scenario_mostly_guaranteed_allocation g_scenario_single_allocation;

/* ---------- public code */

#endif // __SCENARIO_MOSTLY_GUARANTEED_ALLOCATOR_H__

