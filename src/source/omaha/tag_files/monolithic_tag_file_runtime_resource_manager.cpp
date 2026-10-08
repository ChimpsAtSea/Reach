#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\tag_files\\monolithic_tag_file_runtime_resource_manager.cpp"
/* ---------- headers */

#include "omaha\tag_files\monolithic_tag_file_runtime_resource_manager.h"
#include "omaha\tag_files\tag_groups.h"
#include "core\corelib\cseries\cseries_asserts.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

c_tag_allocator_wrapper_to_allocation_base::c_tag_allocator_wrapper_to_allocation_base(void)
{
    mangled_ppc("??0c_tag_allocator_wrapper_to_allocation_base@@QAA@XZ");

    m_actual_allocator = NULL;
};

void c_tag_allocator_wrapper_to_allocation_base::set_allocator(c_tag_allocator * allocator)
{
    mangled_ppc("?set_allocator@c_tag_allocator_wrapper_to_allocation_base@@QAAXPAVc_tag_allocator@@@Z");

    m_actual_allocator = allocator;
};

void * c_tag_allocator_wrapper_to_allocation_base::allocate(unsigned int size, char const *, long, char const *, char const *, char const * name)
{
    mangled_ppc("?allocate@c_tag_allocator_wrapper_to_allocation_base@@UAAPAXIPBDJ000@Z");

    assert_tag_debug_untracked_jul_11_2011(46, m_actual_allocator);

    return m_actual_allocator->allocate(size, 0, name, 0);
};

void c_tag_allocator_wrapper_to_allocation_base::deallocate(void * address, char const *, long)
{
    mangled_ppc("?deallocate@c_tag_allocator_wrapper_to_allocation_base@@UAAXPAXPBDJ@Z");

    assert_tag_debug_untracked_jul_11_2011(57, m_actual_allocator);

    m_actual_allocator->deallocate(address, 0, 0);
};

void c_monolithic_tag_file_single_zone_set_resource_set::initialize(c_tag_resource_runtime_listener * listener)
{
    mangled_ppc("?initialize@c_monolithic_tag_file_single_zone_set_resource_set@@QAAXPAVc_tag_resource_runtime_listener@@@Z");

    __unknown4 = listener;
};

bool c_monolithic_tag_file_single_zone_set_resource_set::any_resources_active(void) const
{
    mangled_ppc("?any_resources_active@c_monolithic_tag_file_single_zone_set_resource_set@@UBA_NXZ");

    c_tag_resource_runtime_active_set * active_set = __unknown4->get_resource_active_set_dont_cache();

    return active_set && active_set->any_resources_active();
};

bool c_monolithic_tag_file_single_zone_set_resource_set::is_resource_required(long owner_index, long resource_index) const
{
    mangled_ppc("?is_resource_required@c_monolithic_tag_file_single_zone_set_resource_set@@UBA_NJJ@Z");

    c_tag_resource_runtime_active_set * active_set = __unknown4->get_resource_active_set_dont_cache();
    bool required = active_set && active_set->is_resource_required(owner_index, resource_index);

    return required;
};

bool c_monolithic_tag_file_single_zone_set_resource_set::is_resource_deferred(long owner_index, long resource_index) const
{
    mangled_ppc("?is_resource_deferred@c_monolithic_tag_file_single_zone_set_resource_set@@UBA_NJJ@Z");

    c_tag_resource_runtime_active_set * active_set = __unknown4->get_resource_active_set_dont_cache();
    bool deferred = active_set && active_set->is_resource_deferred(owner_index, resource_index);

    return deferred;
};

/* ---------- private code */

/* ---------- reverse engineering */
