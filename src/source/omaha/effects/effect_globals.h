#pragma once
#ifndef __EFFECT_GLOBALS_H__
#define __EFFECT_GLOBALS_H__

/* ---------- headers */

#include "omaha\tag_files\tag_groups.h"

/* ---------- constants */

enum e_effect_priority
{
    _effect_priority_normal = 0,
    _effect_priority_high,
    _effect_priority_essential,

    k_effect_priority_max
};

enum e_effect_holdback_type
{
    _effect_holdback_type_effect = 0,
    _effect_holdback_type_event,
    _effect_holdback_type_location,
    _effect_holdback_type_lightprobe,
    _effect_holdback_type_effect_message,
    _effect_holdback_type_beam_system,
    _effect_holdback_type_beam_location,
    _effect_holdback_type_beam,
    _effect_holdback_type_beam_profile_row,
    _effect_holdback_type_contrail_system,
    _effect_holdback_type_contrail_location,
    _effect_holdback_type_contrail,
    _effect_holdback_type_contrail_profile_row,
    _effect_holdback_type_decal_system,
    _effect_holdback_type_decal,
    _effect_holdback_type_decal_vertex,
    _effect_holdback_type_decal_index,
    _effect_holdback_type_light_volume_system,
    _effect_holdback_type_light_volume_location,
    _effect_holdback_type_light_volume,
    _effect_holdback_type_light_volume_profile_row,
    _effect_holdback_type_particle_system,
    _effect_holdback_type_particle_location,
    _effect_holdback_type_particle_emitter,
    _effect_holdback_type_cpu_particle,
    _effect_holdback_type_gpu_particle_row,
    _effect_holdback_type_contrail_queue,
    _effect_holdback_type_particle_queue,

    k_effect_holdback_type_max
};

/* ---------- definitions */

struct s_effect_component_holdbacks
{
    struct s_holdback
    {
        e_effect_priority m_priority; // 0x0
        unsigned long m_absolute; // 0x4
        float m_relative; // 0x8
        unsigned long m_budget; // 0xC
    };

    static bool holdback_compare_proc(void const * element_a, void const * element_b, void const * context);
    static bool postprocess_block_proc(long tag_index, void * element, bool for_editor);

    s_holdback * get_holdback_modifiable(long holdback_index)
    {
        mangled_ppc("?get_holdback_modifiable@s_effect_component_holdbacks@@QAAPAUs_holdback@1@J@Z");

        return static_cast<s_holdback *>(tag_block_get_element_with_size(&m_holdbacks, holdback_index, sizeof(s_holdback)));
    };

    s_holdback const * get_holdback(long holdback_index) const
    {
        mangled_ppc("?get_holdback@s_effect_component_holdbacks@@QBAPBUs_holdback@1@J@Z");

        return static_cast<s_holdback const *>(tag_block_get_element_with_size(&m_holdbacks, holdback_index, sizeof(s_holdback)));
    };

    e_effect_holdback_type m_holdback_type; // 0x0
    unsigned long m_absolute_budget; // 0x4
    s_tag_block m_holdbacks; // 0x8
};
static_assert(sizeof(s_effect_component_holdbacks::s_holdback) == 0x10, "s_effect_component_holdbacks::s_holdback");
static_assert(sizeof(s_effect_component_holdbacks) == 0x14, "s_effect_component_holdbacks");

struct s_effect_globals_definition
{
    enum
    {
        k_tag_type = 'effg',
        k_tag_version = 1
    };

    static bool component_holdback_compare_proc(void const * element_a, void const * element_b, void const * context);
    static bool postprocess_proc(c_tag_index tag_index, bool for_editor);

    s_effect_component_holdbacks * get_component_holdback_modifiable(long holdback_type)
    {
        mangled_ppc("?get_component_holdback_modifiable@s_effect_globals_definition@@QAAPAUs_effect_component_holdbacks@@J@Z");

        return static_cast<s_effect_component_holdbacks *>(tag_block_get_element_with_size(&m_component_holdbacks, holdback_type, sizeof(s_effect_component_holdbacks)));
    };

    s_effect_component_holdbacks const * get_component_holdback(long holdback_type) const
    {
        mangled_ppc("?get_component_holdback@s_effect_globals_definition@@QBAPBUs_effect_component_holdbacks@@J@Z");

        return static_cast<s_effect_component_holdbacks const *>(tag_block_get_element_with_size(&m_component_holdbacks, holdback_type, sizeof(s_effect_component_holdbacks)));
    };

    s_tag_block m_component_holdbacks; // 0x0
    s_tag_reference m_grunt_birthday_effect; // 0xC
    s_tag_block m_multiplayer_spawn_effects; // 0x1C
    s_tag_block m_survival_spawn_effects; // 0x28
    s_tag_block m_campaign_spawn_effects; // 0x34
};
static_assert(sizeof(s_effect_globals_definition) == 0x40, "s_effect_globals_definition");

/* ---------- prototypes */

char const * effect_globals_get_priority_name(unsigned char priority);

/* ---------- globals */

extern char const * g_effect_priority_names[k_effect_priority_max];

/* ---------- public code */

#endif // __EFFECT_GLOBALS_H__

