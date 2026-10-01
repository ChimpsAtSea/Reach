#pragma once
#ifndef __DECAL_DEFINITIONS_H__
#define __DECAL_DEFINITIONS_H__

/* ---------- headers */

#include "omaha\tag_files\tag_groups.h"
#include "omaha\render_methods\render_method_definitions.h"
#include "core\corelib\cseries\cseries_macros.h"

/* ---------- constants */

/* ---------- definitions */

class c_decal_definition
{
public:
    enum
    {
        _specular_modulate_bit = 0,
        _tangent_frame_required_bit,
        _has_sprite_bit,
        _debug_border_color_white_bit,

        k_max_flags
    };

    enum e_pass
    {
        _pass_pre_lighting = 0,
        _pass_post_lighting,

        k_max_pass
    };

    static bool new_block_proc(void * element);
    static bool postprocess_block_proc(long tag_index, void * element, bool for_editor);

    c_render_method_shader_decal const * get_shader(void) const
    {
        mangled_ppc("?get_shader@c_decal_definition@@QBAPBVc_render_method_shader_decal@@XZ");

        return &m_shader;
    };

    long get_name(void) const
    {
        mangled_ppc("?get_name@c_decal_definition@@QBAJXZ");

        return m_name;
    };

    float get_radius_max(void) const
    {
        mangled_ppc("?get_radius_max@c_decal_definition@@QBAMXZ");

        return m_radius_max;
    };

    float get_bitmap_aspect(void) const
    {
        mangled_ppc("?get_bitmap_aspect@c_decal_definition@@QBAMXZ");

        return m_bitmap_aspect;
    };

    void set_tangent_frame_required(bool tangent_frame_required);
    void set_has_sprite(bool has_sprite);
    void set_debug_border_color_white(bool debug_border_color_white);
    void set_pass(e_pass pass);
    void set_bitmap_aspect(float bitmap_aspect);
    void set_name(long name);

    static float x_cull_angle_min;
    static float x_clamp_angle_max;
    static float x_clamp_angle_default;
    static float x_cull_angle_default;

private:
    long m_name; // 0x0
    unsigned long m_flags; // 0x4
    c_render_method_shader_decal m_shader; // 0x8
    float m_radius_min; // 0x70
    float m_radius_max; // 0x74
    float m_decay_min; // 0x78
    float m_decay_max; // 0x7C
    float m_lifespan_min; // 0x80
    float m_lifespan_max; // 0x84
    float m_clamp_angle; // 0x88
    float m_cull_angle; // 0x8C
    e_pass m_pass; // 0x90
    float m_bitmap_aspect; // 0x94
};
static_assert(sizeof(c_decal_definition) == 0x98, "c_decal_definition");

class c_decal_system_definition
{
public:
    enum
    {
        k_tag_type = 'decs',
        k_tag_version = 1,
        k_max_decal = 16
    };

    enum
    {
        _random_rotation_bit = 0,
        _random_u_mirror_bit,
        _random_v_mirror_bit,
        _force_quad_bit,
        _force_planar_bit,
        _first_material_only_bit,
        _first_collision_only_bit,
        _no_structure_collision_bit,
        _no_instance_collision_bit,
        k_max_on_disk_flags,

        _overlap_amount_normalized_bit = k_max_on_disk_flags,

        k_max_flags
    };

    static bool postprocess_proc(c_tag_index tag_index, bool for_editor);
    c_decal_definition * get_decal_definition_modifiable(long block_index);

private:
    unsigned long m_flags; // 0x0
    long m_overlap_max_count; // 0x4
    float m_overlap_amount; // 0x8
    long m_chain_upgrade_threshold; // 0xC
    float m_chain_upgrade_checking_radius; // 0x10
    s_tag_reference m_next_decal_chain; // 0x14
    float m_distance_fade_start; // 0x24
    float m_distance_fade_end; // 0x28
    s_tag_block m_decals; // 0x2C
    float m_radius_max; // 0x38

    static float x_default_distance_fade_start;
    static float x_default_distance_fade_end;
};
static_assert(sizeof(c_decal_system_definition) == 0x3C, "c_decal_system_definition");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __DECAL_DEFINITIONS_H__

