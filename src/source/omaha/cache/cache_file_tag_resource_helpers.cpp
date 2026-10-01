#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\cache\\cache_file_tag_resource_helpers.cpp"
/* ---------- headers */

#include "omaha\cache\cache_file_tag_resource_helpers.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "omaha\math\integer_math.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// public: c_cache_file_zone_resource_collector::c_cache_file_zone_resource_collector(class c_wrapped_flags, class c_wrapped_flags, bool, struct s_cache_file_loaded_tags_header const *);
// public: c_cache_file_zone_resource_collector::c_cache_file_zone_resource_collector(class c_wrapped_flags, class c_wrapped_flags, bool);
// public: void c_cache_file_zone_resource_collector::add_zone_mask(class c_typed_tag_block<struct s_cache_file_zone_manifest> const *, unsigned long);
// public: void c_cache_file_zone_resource_collector::add_all_zones(class c_typed_tag_block<struct s_cache_file_zone_manifest> const *);
// private: void c_cache_file_zone_resource_collector::add_single_zone(struct s_cache_file_zone_manifest const *);
// public: void c_cache_file_zone_resource_collector::add_all_resources(void);
// public: void c_bit_vector_operator_interface<class c_wrapped_flags>::set_all(void);
// public: c_typed_opaque_data<class c_wrapped_flags, 8, 4>::c_typed_opaque_data<class c_wrapped_flags, 8, 4>(void);
// public: class c_wrapped_flags * c_typed_opaque_data<class c_wrapped_flags, 8, 4>::get(void);
// public: bool c_typed_opaque_data<class c_wrapped_flags, 8, 4>::alive(void) const;
// public: class c_wrapped_flags * c_typed_opaque_data<class c_wrapped_flags, 8, 4>::construct<class c_wrapped_flags>(class c_wrapped_flags);
// public: class c_wrapped_flags * c_opaque_data<class c_wrapped_flags, 8, 4>::get(void);

c_cache_file_zone_resource_collector::c_cache_file_zone_resource_collector(c_wrapped_flags active_resources, c_wrapped_flags active_resource_owners, bool cache_streaming_data, s_cache_file_loaded_tags_header const * tags_header) :
    m_active_resources(),
    m_active_resource_owners(),
    m_cache_streaming_data(cache_streaming_data)
{
    mangled_ppc("??0c_cache_file_zone_resource_collector@@QAA@Vc_wrapped_flags@@0_NPBUs_cache_file_loaded_tags_header@@@Z");

    cache_file_get_instance_bounds_from_header(tags_header, &m_instance_bounds);

    if (active_resources.bit_count() != 0)
    {
        m_active_resources.construct(active_resources);
        m_active_resources.get()->clear();
    }

    if (active_resource_owners.bit_count() != 0)
    {
        m_active_resource_owners.construct(active_resource_owners);
        bit_vector_set_range_to_false(m_active_resource_owners.get()->bit_count(), m_active_resource_owners.get()->get_bits_unsafe(), m_instance_bounds.first_tag_instance_index, m_instance_bounds.tag_instance_count);
    }
};

c_cache_file_zone_resource_collector::c_cache_file_zone_resource_collector(c_wrapped_flags active_resources, c_wrapped_flags active_resource_owners, bool cache_streaming_data) :
    m_active_resources(),
    m_active_resource_owners()
{
    mangled_ppc("??0c_cache_file_zone_resource_collector@@QAA@Vc_wrapped_flags@@0_N@Z");

    m_instance_bounds.first_tag_instance_index = 0;
    m_instance_bounds.tag_instance_count = 20000;

    if (active_resources.bit_count() != 0)
    {
        m_active_resources.construct(active_resources);
        m_active_resources.get()->clear();
    }

    if (active_resource_owners.bit_count() != 0)
    {
        m_active_resource_owners.construct(active_resource_owners);
        bit_vector_set_range_to_false(m_active_resource_owners.get()->bit_count(), m_active_resource_owners.get()->get_bits_unsafe(), m_instance_bounds.first_tag_instance_index, m_instance_bounds.tag_instance_count);
    }
};

void c_cache_file_zone_resource_collector::add_zone_mask(c_typed_tag_block<s_cache_file_zone_manifest> const * zone_block, unsigned long zone_mask)
{
    mangled_ppc("?add_zone_mask@c_cache_file_zone_resource_collector@@QAAXPBV?$c_typed_tag_block@Us_cache_file_zone_manifest@@@@K@Z");

    for (long zone_index = 0; zone_index < zone_block->count(); zone_index++)
    {
        if ((zone_mask & (1 << zone_index)) != 0)
        {
            s_cache_file_zone_manifest const * zone_manifest = zone_block->get_element(zone_index);
            add_single_zone(zone_manifest);
        }
    }
};

void c_cache_file_zone_resource_collector::add_all_zones(c_typed_tag_block<s_cache_file_zone_manifest> const * zone_block)
{
    mangled_ppc("?add_all_zones@c_cache_file_zone_resource_collector@@QAAXPBV?$c_typed_tag_block@Us_cache_file_zone_manifest@@@@@Z");

    for (long zone_index = 0; zone_index < zone_block->count(); zone_index++)
    {
        s_cache_file_zone_manifest const * zone_manifest = zone_block->get_element(zone_index);
        add_single_zone(zone_manifest);
    }
};

void c_cache_file_zone_resource_collector::add_single_zone(s_cache_file_zone_manifest const * zone_manifest)
{
    mangled_ppc("?add_single_zone@c_cache_file_zone_resource_collector@@AAAXPBUs_cache_file_zone_manifest@@@Z");

    assert_tag_debug_untracked_jul_11_2011(97, m_instance_bounds.first_tag_instance_index==0);

    if (m_active_resources.alive())
    {
        bit_vector_or(m_active_resources.get()->bit_count(), m_active_resources.get()->get_bits(), zone_manifest->required_resources_bitvector.get_bits(), m_active_resources.get()->get_bits_unsafe());

        if (m_cache_streaming_data)
        {
            bit_vector_or(m_active_resources.get()->bit_count(), m_active_resources.get()->get_bits(), zone_manifest->streamed_resources_bitvector.get_bits(), m_active_resources.get()->get_bits_unsafe());
        }
    }

    if (m_active_resource_owners.alive())
    {
        assert_tag_debug_untracked_jul_11_2011(111, zone_manifest->active_resource_owners.bit_count()<=m_active_resource_owners.get()->bit_count());

        bit_vector_or(zone_manifest->active_resource_owners.bit_count(), m_active_resource_owners.get()->get_bits(), zone_manifest->active_resource_owners.get_bits(), m_active_resource_owners.get()->get_bits_unsafe());
    }
};

void c_cache_file_zone_resource_collector::add_all_resources()
{
    mangled_ppc("?add_all_resources@c_cache_file_zone_resource_collector@@QAAXXZ");

    if (m_active_resources.alive())
    {
        m_active_resources.get()->set_all();
    }

    if (m_active_resource_owners.alive())
    {
        bit_vector_set_range_to_true(m_active_resource_owners.get()->bit_count(), m_active_resource_owners.get()->get_bits_unsafe(), m_instance_bounds.first_tag_instance_index, m_instance_bounds.tag_instance_count);
    }
};
