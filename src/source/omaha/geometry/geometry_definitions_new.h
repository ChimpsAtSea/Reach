#pragma once
#ifndef __GEOMETRY_DEFINITIONS_NEW_H__
#define __GEOMETRY_DEFINITIONS_NEW_H__

/* ---------- headers */

#include "omaha\tag_files\tag_groups.h"
#include "omaha\math\real_math.h"
#include "core\corelib\cseries\cseries_macros.h"
#include "omaha\memory\static_arrays.h"

/* ---------- constants */

enum e_geometry_material_lightmap_flags
{
    _geometry_material_lightmap_ignore_default_resolution_scale_bit = 0,
    _geometry_material_lightmap_transparency_override_bit,
    _geometry_material_lightmap_lighting_from_both_sides_bit,
    _geometry_material_lightmap_version1_bit,

    k_geometry_material_lightmap_flag_count
};

enum e_geometry_block_info_bit
{
    _geometry_block_cached_bit = 0,
    _geometry_block_uses_dynamic_cache_bit,
    _geometry_block_predicted_bit,

    k_number_of_geometry_block_info_bits
};

/* ---------- definitions */

struct scenario_lightmap_setting;

// layout from global_geometry_material_block (Reach tag definitions)
struct geometry_material
{
    void clear_non_render_information(void);
    static bool postprocess(long tag_index, void * address, bool for_editor);

    s_tag_reference render_method; // 0x0
    long imported_material_index; // 0x10
    real lightmap_resolution_scale; // 0x14
    unsigned long lightmap_additive_transparency_color; // 0x18
    unsigned long lightmap_translucency_tint_color; // 0x1C
    real lightmap_analytical_light_absorb; // 0x20
    real lightmap_normal_light_absorb; // 0x24
    unsigned char lightmap_flags; // 0x28
    char breakable_surface_index; // 0x29
    short lightmap_chart_group_index; // 0x2A
};
static_assert(sizeof(geometry_material) == 0x2C, "geometry_material");

struct geometry_block_info
{
    long geometry_block_offset; // 0x0
    long geometry_block_size; // 0x4
    long section_data_size; // 0x8
    long resource_data_size; // 0xC
    s_tag_block resources; // 0x10
    long owner_tag_index; // 0x1C
    short owner_tag_section_offset; // 0x20
    bool runtime_section_data_valid; // 0x22
    c_flags_no_init<e_geometry_block_info_bit, unsigned char, k_number_of_geometry_block_info_bits> flags; // 0x23
    long runtime_cache_block_index; // 0x24
};
static_assert(sizeof(geometry_block_info) == 0x28, "geometry_block_info");

/* ---------- prototypes */

real geometry_material_get_lightmap_resolution_scale(geometry_material const * material, scenario_lightmap_setting const * lightmap_setting);
unsigned long geometry_material_get_lightmap_translucency_tint_color(geometry_material const * material);
unsigned long geometry_material_get_lightmap_additive_transparency(geometry_material const * material);
real geometry_material_get_lightmap_analytical_bounce_modifier(geometry_material const * material);
real geometry_material_get_lightmap_normal_bounce_modifier(geometry_material const * material);
bool geometry_material_get_lightmap_transparency_override(geometry_material const * material);
bool geometry_material_get_lightmap_lighting_from_both_sides(geometry_material const * material);
bool geometry_material_get_lightmap_ignore_default_resolution_scale(geometry_material const * material);

/* ---------- globals */

/* ---------- public code */

#endif // __GEOMETRY_DEFINITIONS_NEW_H__

