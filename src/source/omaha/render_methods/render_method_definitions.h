#ifndef __RENDER_METHOD_DEFINITIONS_H__
#define __RENDER_METHOD_DEFINITIONS_H__
#pragma once

/* ---------- headers */

#include "omaha\tag_files\tag_groups.h"
#include "core\corelib\cseries\cseries_macros.h"

/* ---------- constants */

enum
{
    SHADER_SCREEN_TAG = 'rmss',
};

/* ---------- definitions */

struct s_render_method_postprocess_definition
{
    enum e_runtime_queryable_property
    {
        _query_blend_map = 0,
        _query_albedo_base_map_0,
        _query_albedo_base_map_1,
        _query_albedo_base_map_2,
        _query_albedo_color,
        _query_albedo_base_map_3,
        _query_alpha_map,

        k_runtime_queryable_properties_count = 28
    };

    bool query_bitmap_reference(e_runtime_queryable_property property, s_tag_reference const ** reference) const;

    s_tag_reference shader_template; // 0x0
    s_tag_block textures; // 0x10
    s_tag_block real_vectors; // 0x1C
    s_tag_block int_constants; // 0x28
    long bool_constants; // 0x34
    s_tag_block entry_points; // 0x38
    s_tag_block passes; // 0x44
    s_tag_block routing_info; // 0x50
    s_tag_block overlays; // 0x5C
    long blend_mode; // 0x68
    unsigned long flags; // 0x6C
    long im_so_fired_pad; // 0x70
    short runtime_queryable_properties_table[k_runtime_queryable_properties_count]; // 0x74
};
static_assert(sizeof(s_render_method_postprocess_definition) == 0xAC, "s_render_method_postprocess_definition");

class c_render_method
{
public:
    bool postprocess_as_child(long tag_index, bool for_editor);
    bool test_category_option(char const * category, char const * option) const;
    static bool get_is_transparent(long tag_index);

    s_render_method_postprocess_definition const * get_postprocess_definition(void) const
    {
        mangled_ppc("?get_postprocess_definition@c_render_method@@QBAPBUs_render_method_postprocess_definition@@XZ");

        return static_cast<s_render_method_postprocess_definition const *>(tag_block_get_element_with_size(&m_postprocess_definition, 0, sizeof(s_render_method_postprocess_definition)));
    };

    s_tag_reference m_definition; // 0x0
    s_tag_reference m_reference; // 0x10
    s_tag_block m_options; // 0x20
    s_tag_block m_parameters; // 0x2C
    s_tag_block m_postprocess_definition; // 0x38
    long m_is_template; // 0x44
    unsigned long m_locked_options; // 0x48
    s_tag_block m_locked_parameters; // 0x4C
    unsigned short m_flags; // 0x58
    unsigned char m_sort_layer; // 0x5A
    char m_version; // 0x5B
    long m_custom_fog_setting_index; // 0x5C
    long m_prediction_atom_index; // 0x60
};
static_assert(sizeof(c_render_method) == 0x64, "c_render_method");

class c_render_method_shader_decal :
    public c_render_method
{
public:
    long m_specular_modulate; // 0x64
};
static_assert(sizeof(c_render_method_shader_decal) == 0x68, "c_render_method_shader_decal");

class c_render_method_shader_screen :
    public c_render_method
{
public:
    // f i
    static c_render_method_shader_screen const * get(long tag_index)
    {
        mangled_ppc("?get@c_render_method_shader_screen@@SAPBV1@J@Z");

        return static_cast<c_render_method_shader_screen const *>(tag_get(SHADER_SCREEN_TAG, tag_index));
    };

    long m_material_name; // 0x64
    char m_render_layer; // 0x68
    char m_sort_order; // 0x69
    unsigned char m_render_flags; // 0x6A
    unsigned char pad[1]; // 0x6B
};
static_assert(sizeof(c_render_method_shader_screen) == 0x6C, "c_render_method_shader_screen");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __RENDER_METHOD_DEFINITIONS_H__

