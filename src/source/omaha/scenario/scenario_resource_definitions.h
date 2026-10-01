#pragma once
#ifndef __SCENARIO_RESOURCE_DEFINITIONS_H__
#define __SCENARIO_RESOURCE_DEFINITIONS_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"
#include "omaha\memory\static_arrays.h"
#include "omaha\tag_files\tag_groups.h"

/* ---------- constants */

enum e_scenario_split_resource_bit
{
    _scenario_split_resource_dont_reset_split_resource_paths_bit = 0,

    k_number_of_scenario_split_resource_bits
};

/* ---------- definitions */

struct s_scenario_resources_block
{
    c_flags_no_init<e_scenario_split_resource_bit, unsigned long, k_number_of_scenario_split_resource_bits> flags; // 0x0
    s_tag_block script_source; // 0x4
    s_tag_block ai_resources; // 0x10
    s_tag_block new_split_resources; // 0x1C
};
static_assert(sizeof(s_scenario_resources_block) == 0x28, "s_scenario_resources_block");

struct s_scenario_hs_source_reference_block
{
    s_tag_reference reference; // 0x0
};
static_assert(sizeof(s_scenario_hs_source_reference_block) == 0x10, "s_scenario_hs_source_reference_block");

struct s_scenario_split_resources_block
{
    s_tag_reference scenery_resource; // 0x0
    s_tag_reference biped_resource; // 0x10
    s_tag_reference vehicle_resource; // 0x20
    s_tag_reference equipment_resource; // 0x30
    s_tag_reference weapon_resource; // 0x40
    s_tag_reference light_resource; // 0x50
    s_tag_reference device_resource; // 0x60
    s_tag_reference effect_scenery; // 0x70
    s_tag_reference decal_resource; // 0x80
    s_tag_reference cutscene_data_resource; // 0x90
    s_tag_reference trigger_volume_resource; // 0xA0
    s_tag_reference cluster_data_resource; // 0xB0
    s_tag_reference sound_scenery_resource; // 0xC0
    s_tag_reference comment_flag_resource; // 0xD0
    s_tag_reference creature_resource; // 0xE0
    s_tag_reference structure_lighting_resource; // 0xF0
    s_tag_reference decorator_resource; // 0x100
    s_tag_reference sky_reference_resource; // 0x110
    s_tag_reference cubemap_reference_resource; // 0x120
    s_tag_reference performance_reference_resource; // 0x130
    s_tag_reference dumpling_reference_resource; // 0x140
};
static_assert(sizeof(s_scenario_split_resources_block) == 0x150, "s_scenario_split_resources_block");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __SCENARIO_RESOURCE_DEFINITIONS_H__

