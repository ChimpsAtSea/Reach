#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\scenario\\scenario_mostly_guaranteed_allocator.cpp"
/* ---------- headers */

#include "omaha\scenario\scenario_mostly_guaranteed_allocator.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "omaha\tag_files\tag_resource_runtime.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

c_scenario_mostly_guaranteed_allocation g_scenario_single_allocation;

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// const c_scenario_mostly_guaranteed_allocation::`vftable'{for `c_optional_cache_user_callback'}; // "??_7c_scenario_mostly_guaranteed_allocation@@6Bc_optional_cache_user_callback@@@"
// const c_scenario_mostly_guaranteed_allocation::`vftable'{for `c_tracked_allocation_base'}; // "??_7c_scenario_mostly_guaranteed_allocation@@6Bc_tracked_allocation_base@@@"
// class c_scenario_mostly_guaranteed_allocation g_scenario_single_allocation; // "?g_scenario_single_allocation@@3Vc_scenario_mostly_guaranteed_allocation@@A"

// class c_allocation_interface * scenario_mostly_guaranteed_allocator_initialize(void);
// void scenario_mostly_guaranteed_allocator_dispose(void);
// public: c_scenario_mostly_guaranteed_allocation::c_scenario_mostly_guaranteed_allocation(void);
// public: virtual void * c_tracked_allocation_base::allocate(unsigned int, char const *, long, char const *, char const *, char const *);
// public: virtual void c_tracked_allocation_base::deallocate(void *, char const *, long);
// private: virtual char const * c_scenario_mostly_guaranteed_allocation::get_name(void);
// private: virtual void c_scenario_mostly_guaranteed_allocation::get_memory_configuration(enum e_map_memory_configuration, struct s_optional_cache_user_memory_configuration *);
// private: virtual void c_scenario_mostly_guaranteed_allocation::idle(void const *);
// private: virtual void c_scenario_mostly_guaranteed_allocation::terminate(void const *);
// private: virtual void * c_scenario_mostly_guaranteed_allocation::allocate_internal(unsigned int);
// private: virtual void c_scenario_mostly_guaranteed_allocation::deallocate_internal(void *);
// public: c_tracked_allocation_base::c_tracked_allocation_base(void);

// $TODO nonmatching: target leaf uses the unrelocated absolute address of g_scenario_single_allocation (lis/subi); ours is a lis/addi relocation pair (only diff)
c_allocation_interface * scenario_mostly_guaranteed_allocator_initialize(void)
{
    mangled_ppc("?scenario_mostly_guaranteed_allocator_initialize@@YAPAVc_allocation_interface@@XZ");

    return &g_scenario_single_allocation;
};

void scenario_mostly_guaranteed_allocator_dispose(void)
{
    mangled_ppc("?scenario_mostly_guaranteed_allocator_dispose@@YAXXZ");
};

c_scenario_mostly_guaranteed_allocation::c_scenario_mostly_guaranteed_allocation(void)
{
    mangled_ppc("??0c_scenario_mostly_guaranteed_allocation@@QAA@XZ");
};

// c_tracked_allocation_base::allocate / deallocate / constructor are inline (f i) in scenario_mostly_guaranteed_allocator.h

char const * c_scenario_mostly_guaranteed_allocation::get_name(void)
{
    mangled_ppc("?get_name@c_scenario_mostly_guaranteed_allocation@@EAAPBDXZ");

    return "scenario_single_allocation";
};

void c_scenario_mostly_guaranteed_allocation::get_memory_configuration(e_map_memory_configuration map_configuration, s_optional_cache_user_memory_configuration * memory_configuration)
{
    mangled_ppc("?get_memory_configuration@c_scenario_mostly_guaranteed_allocation@@EAAXW4e_map_memory_configuration@@PAUs_optional_cache_user_memory_configuration@@@Z");

    memory_configuration->maximum_priority = _optional_cache_user_cant_fail_blocking;
    memory_configuration->maximum_size = 0;
};

void c_scenario_mostly_guaranteed_allocation::idle(void const * pointer)
{
    mangled_ppc("?idle@c_scenario_mostly_guaranteed_allocation@@EAAXPBX@Z");
};

void c_scenario_mostly_guaranteed_allocation::terminate(void const * pointer)
{
    mangled_ppc("?terminate@c_scenario_mostly_guaranteed_allocation@@EAAXPBX@Z");

    dassert_tag_debug_untracked_jul_11_2011(46, false, "can't free single scenario allocation while it is use! :(");
};

void * c_scenario_mostly_guaranteed_allocation::allocate_internal(unsigned int size)
{
    mangled_ppc("?allocate_internal@c_scenario_mostly_guaranteed_allocation@@EAAPAXI@Z");

    assert_tag_debug_untracked_jul_11_2011(55, m_allocation.empty());

    m_allocation = tag_resources_try_to_steal_memory(size);
    if (!m_allocation.empty())
    {
        m_allocation_type = _allocation_type_resource_stoler;
    }

    return m_allocation.empty() ? NULL : m_allocation.begin();
};

void c_scenario_mostly_guaranteed_allocation::deallocate_internal(void * ptr)
{
    mangled_ppc("?deallocate_internal@c_scenario_mostly_guaranteed_allocation@@EAAXPAX@Z");

    assert_tag_debug_untracked_jul_11_2011(70, ptr==m_allocation.begin());
    assert_tag_debug_untracked_jul_11_2011(71, m_allocation_type==_allocation_type_resource_stoler);

    if (m_allocation_type == _allocation_type_resource_stoler)
    {
        tag_resources_return_memory(m_allocation);
    }
    m_allocation.clear();
    m_allocation_type = _allocation_type_none;
};

