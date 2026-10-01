#pragma once
#ifndef __STRUCTURE_LIGHTING_DEFINITIONS_H__
#define __STRUCTURE_LIGHTING_DEFINITIONS_H__

/* ---------- headers */

#include "omaha\tag_files\tag_groups.h"
#include "omaha\math\real_math.h"
#include "omaha\math\color_math.h"
#include "core\corelib\cseries\cseries_macros.h"

/* ---------- constants */

enum
{
    SCENARIO_STRUCTURE_LIGHTING_INFO_TAG = 'stli',
};

// structure_lighting_generic_light_type_enum
enum e_structure_lighting_generic_light_type
{
    _structure_lighting_generic_light_type_omni = 0,
    _structure_lighting_generic_light_type_spot,
    _structure_lighting_generic_light_type_directional,

    k_structure_lighting_generic_light_type_count
};

// structure_lighting_generic_light_flags
enum e_structure_lighting_generic_light_flags
{
    _structure_lighting_generic_light_use_near_attenuation_bit = 0,
    _structure_lighting_generic_light_use_far_attenuation_bit,
    _structure_lighting_generic_light_inverse_squared_falloff_bit,
    _structure_lighting_generic_light_version_1_bit,
    _structure_lighting_generic_light_has_clipping_planes_bit,

    k_structure_lighting_generic_light_flags_count
};

// structure_lighting_bungie_light_type_enum
enum e_structure_lighting_bungie_light_type
{
    _structure_lighting_bungie_light_type_default_lightmap_light = 0,
    _structure_lighting_bungie_light_type_uber_light,
    _structure_lighting_bungie_light_type_inlined_light,
    _structure_lighting_bungie_light_type_screen_space_light,
    _structure_lighting_bungie_light_type_rerender_lights,

    k_structure_lighting_bungie_light_type_count
};

// light_instance_flags
enum e_light_instance_flags
{
    _light_instance_screen_space_light_has_specular_bit = 0,
    _light_instance_version_1_instances_bit,
    _light_instance_rain_volume_bit,
    _light_instance_has_lens_flare_bit,

    k_light_instance_flags_count
};

/* ---------- definitions */

struct s_structure_lighting_generic_light_definition
{
    static bool postprocess_proc(long tag_index, void * data, bool for_editor);

    short type; // 0x0
    unsigned short flags; // 0x2
    short shape; // 0x4
    short pad; // 0x6
    real_rgb_color color; // 0x8
    real intensity; // 0x14
    real hotspot_size; // 0x18
    real hotspot_cutoff_size; // 0x1C
    real hotspot_falloff_speed; // 0x20
    real_bounds near_attenuation_bounds; // 0x24
    real_bounds far_attenuation_bounds; // 0x2C
    real aspect; // 0x34
    real clipping_planes_x_pos; // 0x38
    real clipping_planes_x_neg; // 0x3C
    real clipping_planes_y_pos; // 0x40
    real clipping_planes_y_neg; // 0x44
    real clipping_planes_z_pos; // 0x48
    real clipping_planes_z_neg; // 0x4C
};
static_assert(sizeof(s_structure_lighting_generic_light_definition) == 0x50, "s_structure_lighting_generic_light_definition");

struct s_structure_lighting_generic_light_instance
{
    static bool postprocess_proc(long tag_index, void * data, bool for_editor);

    long definition_index; // 0x0
    long shader_reference_index; // 0x4
    real_point3d origin; // 0x8
    vector3d forward; // 0x14
    vector3d up; // 0x20
    unsigned short bungie_light_type; // 0x2C
    unsigned short flags; // 0x2E
    real bounce_light_control; // 0x30
    real light_volume_distance; // 0x34
    real light_volume_intensity_scalar; // 0x38
    real fade_out_distance; // 0x3C
    real fade_start_distance; // 0x40
    s_tag_reference user_control; // 0x44
    s_tag_reference shader_reference; // 0x54
    s_tag_reference gel_reference; // 0x64
    s_tag_reference lens_flare_reference; // 0x74
};
static_assert(sizeof(s_structure_lighting_generic_light_instance) == 0x84, "s_structure_lighting_generic_light_instance");

struct s_screen_space_light_shader_override
{
    real_rgb_color specular_color_normal; // 0x0
    real specular_steepness; // 0xC
    real_rgb_color specular_color_gazing; // 0x10
    real specular_coeff; // 0x1C
    real diffuse_coeff; // 0x20
    real roughness_offset; // 0x24
    real albedo_blend; // 0x28
};
static_assert(sizeof(s_screen_space_light_shader_override) == 0x2C, "s_screen_space_light_shader_override");

struct s_structure_material_lighting_info
{
    static bool postprocess_proc(long tag_index, void * data, bool for_editor);

    real emissive_power; // 0x0
    real_rgb_color emissive_color; // 0x4
    real emissive_quality; // 0x10
    real emissive_focus; // 0x14
    unsigned long flags; // 0x18
    real attenuation_falloff; // 0x1C
    real attenuation_cutoff; // 0x20
    real bounce_ratio; // 0x24
};
static_assert(sizeof(s_structure_material_lighting_info) == 0x28, "s_structure_material_lighting_info");

struct s_structure_lighting_info
{
    static bool structure_lighting_info_postprocess(long tag_index, bool for_editor);

    long import_info_checksum; // 0x0
    s_tag_block generic_light_definitions; // 0x4
    s_tag_block generic_light_instances; // 0x10
    s_tag_block screen_space_light_shader_overrides; // 0x1C
    s_tag_block regions; // 0x28
    s_tag_block material_info; // 0x34
    s_tag_block instance_imposter_infos; // 0x40
};
static_assert(sizeof(s_structure_lighting_info) == 0x4C, "s_structure_lighting_info");

/* ---------- prototypes */

/* ---------- globals */

extern bool lightmap_light_preview_mode;

/* ---------- public code */

#endif // __STRUCTURE_LIGHTING_DEFINITIONS_H__
