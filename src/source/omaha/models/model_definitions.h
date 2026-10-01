#pragma once
#ifndef __MODEL_DEFINITIONS_H__
#define __MODEL_DEFINITIONS_H__

/* ---------- headers */

#include "omaha\tag_files\tag_groups.h"
#include "omaha\math\real_math.h"
#include "omaha\models\damage_info_definitions.h"
#include "core\corelib\cseries\cseries_macros.h"

/* ---------- constants */

enum
{
    MODEL_DEFINITION_TAG = 'hlmt',
};

enum
{
    MAXIMUM_NODES_PER_MODEL = 255,
};

/* ---------- definitions */

// model_node_block
struct s_model_node
{
    long name; // 0x0
    short parent_node_index; // 0x4
    short first_child_node_index; // 0x6
    short next_sibling_node_index; // 0x8
    unsigned short pad; // 0xA
    real_point3d default_translation; // 0xC
    real_quaternion default_rotation; // 0x18
    float default_inverse_scale; // 0x28
    vector3d default_inverse_forward; // 0x2C
    vector3d default_inverse_left; // 0x38
    vector3d default_inverse_up; // 0x44
    real_point3d default_inverse_position; // 0x50
};
static_assert(sizeof(s_model_node) == 0x5C, "s_model_node");

// model_region_block
struct s_model_region
{
    long name; // 0x0
    char collision_region_index; // 0x4
    char physics_region_index; // 0x5
    unsigned char pad[2]; // 0x6
    s_tag_block permutations; // 0x8
};
static_assert(sizeof(s_model_region) == 0x14, "s_model_region");

// model_block_struct
struct s_model_definition
{
    s_tag_reference render_model; // 0x0
    s_tag_reference collision_model; // 0x10
    s_tag_reference animation_graph; // 0x20
    s_tag_reference physics_model; // 0x30
    s_tag_reference imposter_model; // 0x40
    long runtime_render_checksum; // 0x50
    long runtime_collision_checksum; // 0x54
    float disappear_distance; // 0x58
    float begin_fade_distance; // 0x5C
    float animation_lod_distance; // 0x60
    float shadow_fade_distance; // 0x64
    float imposter_render_distance; // 0x68
    short imposter_quality; // 0x6C
    short imposter_policy; // 0x6E
    float imposter_brightness_adjustment; // 0x70
    float instance_disappear_distance; // 0x74
    float midrange_detail_disappear_distance; // 0x78
    float close_detail_disappear_distance; // 0x7C
    float tessellation_max_draw_distance; // 0x80
    s_tag_block variants; // 0x84
    s_tag_block region_sort; // 0x90
    s_tag_block instance_groups; // 0x9C
    s_tag_block materials_old; // 0xA8
    s_tag_block model_materials; // 0xB4
    s_tag_block new_damage_info; // 0xC0
    s_new_model_damage_info damage_info; // 0xCC
    s_tag_block targets_old; // 0x108
    s_tag_block model_targets; // 0x114
    s_tag_block runtime_regions; // 0x120
    s_tag_block runtime_nodes; // 0x12C
    long runtime_node_list_checksum; // 0x138
    s_tag_reference default_dialogue; // 0x13C
    s_tag_reference default_dialogue_female; // 0x14C
    unsigned long flags; // 0x15C
    long default_dialogue_effect; // 0x160
    unsigned long render_only_node_flags[8]; // 0x164
    unsigned long render_only_section_flags[8]; // 0x184
    unsigned long runtime_flags; // 0x1A4
    s_tag_block scenario_load_parameters; // 0x1A8
    float sky_parallax_percent; // 0x1B4
    float shadow_depth_compare_bias; // 0x1B8
    float shadow_slope_scale_bias; // 0x1BC
    float shadow_depth_compare_bias_dynamic_lights; // 0x1C0
    float shadow_slope_scale_bias_dynamic_lights; // 0x1C4
    char prt_shadow_detail; // 0x1C8
    char prt_shadow_bounces; // 0x1C9
    unsigned short pad; // 0x1CA
    s_tag_block shadow_cast_override; // 0x1CC
    s_tag_block shadow_receive_override; // 0x1D8
    s_tag_block occlusion_spheres; // 0x1E4
    s_tag_reference shield_impact_parameter_override; // 0x1F0
    s_tag_reference first_person_shield_impact_parameter_override; // 0x200
    float runtime_bounding_radius; // 0x210
    real_point3d runtime_bounding_offset; // 0x214
};
static_assert(sizeof(s_model_definition) == 0x220, "s_model_definition");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __MODEL_DEFINITIONS_H__
