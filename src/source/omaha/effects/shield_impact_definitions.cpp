/* ---------- headers */

#include "omaha\effects\shield_impact_definitions.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// struct s_tag_block_definition shield_impact_block; // "?shield_impact_block@@3Us_tag_block_definition@@A"
// struct s_tag_reference_definition global_shield_parameters_reference; // "?global_shield_parameters_reference@@3Us_tag_reference_definition@@A"
// struct s_tag_group shield_impact_group; // "?shield_impact_group@@3Us_tag_group@@A"
// struct s_tag_group_legacy_vtable legacy_shield_impact_vtable; // "?legacy_shield_impact_vtable@@3Us_tag_group_legacy_vtable@@A"
// struct s_tag_group_stream_definition legacy_shield_impact_stream_definition; // "?legacy_shield_impact_stream_definition@@3Us_tag_group_stream_definition@@A"
// struct s_tag_group_sync_definition legacy_shield_impact_xsync_declaration; // "?legacy_shield_impact_xsync_declaration@@3Us_tag_group_sync_definition@@A"
// class c_legacy_tag_group_vtable_shim legacy_shield_impact_vtable_shim; // "?legacy_shield_impact_vtable_shim@@3Vc_legacy_tag_group_vtable_shim@@A"

// public: static bool s_shield_parameters::on_new(void *);
// void init_color_function(struct s_shield_function *, unsigned long);
// void init_scalar_function(struct s_shield_function *, float, float);
// public: static bool s_shield_parameters::postprocess(long, void *, bool);

bool s_shield_parameters::on_new(void * element)
{
    mangled_ppc("?on_new@s_shield_parameters@@SA_NPAX@Z");

    s_shield_parameters * shield = static_cast<s_shield_parameters *>(element);

    shield->flags = 0;
    shield->version = 4;
    shield->depth_fade_range = 0.6f;
    shield->plasma_depth_fade_range = 0.6f;
    shield->recent_damage_intensity = 0.4f;
    shield->current_damage_intensity = 0.6f;
    shield->outer_fade_radius = 1.0f;
    shield->center_radius = 0.5f;
    shield->inner_fade_radius = 0.1f;
    shield->plasma_outer_fade_radius = 1.0f;
    shield->plasma_center_radius = 0.5f;
    shield->plasma_inner_fade_radius = 0.1f;
    tag_reference_initialize(&shield->plasma_noise_texture0);
    tag_reference_initialize(&shield->plasma_noise_texture1);
    tag_reference_set(&shield->plasma_noise_texture0, SHIELD_IMPACT_TAG, "test\\chris\\noise\\blur_noise256_a");
    tag_reference_set(&shield->plasma_noise_texture1, SHIELD_IMPACT_TAG, "test\\chris\\noise\\blur_noise256_b");
    shield->tiling_scale = 1.0f;
    shield->scroll_speed = 0.5f;
    shield->edge_sharpness = 4.0f;
    shield->center_sharpness = 80.0f;
    tag_reference_initialize(&shield->oscillation_texture0);
    tag_reference_initialize(&shield->oscillation_texture1);
    tag_reference_set(&shield->oscillation_texture0, SHIELD_IMPACT_TAG, "test\\chris\\noise\\blur_noise256_a");
    tag_reference_set(&shield->oscillation_texture1, SHIELD_IMPACT_TAG, "test\\chris\\noise\\blur_noise256_b");
    shield->oscillation_tiling_scale = 2.0f;
    shield->oscillation_scroll_speed = 0.1f;
    init_color_function(&shield->edge_glow_color, 0x00194CFF);
    init_scalar_function(&shield->edge_glow_intensity, 0.0f, 0.7f);
    init_color_function(&shield->plasma_center_color, 0x00194CFF);
    init_scalar_function(&shield->plasma_center_intensity, 0.0f, 0.07f);
    init_color_function(&shield->plasma_edge_color, 0x00194CFF);
    init_scalar_function(&shield->plasma_edge_intensity, 0.0f, 2.5f);
    init_scalar_function(&shield->extrusion_amount, 0.015f, 0.04f);
    init_scalar_function(&shield->oscillation_amplitude, 0.0f, 0.1f);
    shield->hit_time = 1.0f;
    init_color_function(&shield->hit_color, 0x00FF194C);
    init_scalar_function(&shield->hit_radius, 0.05f, 0.2f);

    return true;
};

void init_color_function(s_shield_function * function, unsigned long color)
{
    mangled_ppc("?init_color_function@@YAXPAUs_shield_function@@K@Z");

    c_function_definition_editor editor(&function->mapping);
    editor.set_color_graph_type(c_function_definition::_function_color_graph_type_two_color);
    editor.set_function_type(c_function_definition::_function_type_constant);
    editor.calc_default_values();
    editor.set_color(0, color);
    editor.set_color(1, color);
};

void init_scalar_function(s_shield_function * function, float clamp_range_min, float clamp_range_max)
{
    mangled_ppc("?init_scalar_function@@YAXPAUs_shield_function@@MM@Z");

    c_function_definition_editor editor(&function->mapping);
    editor.set_color_graph_type(c_function_definition::_function_color_graph_type_scalar);
    editor.set_function_type(c_function_definition::_function_type_linear);
    editor.calc_default_values();
    editor.set_control_point_y(0, 0, 0.0f);
    editor.set_control_point_y(0, 1, 1.0f);
    editor.set_clamp_range_min(clamp_range_min);
    editor.set_clamp_range_max(clamp_range_max);
};

bool s_shield_parameters::postprocess(long tag_index, void * element, bool for_editor)
{
    mangled_ppc("?postprocess@s_shield_parameters@@SA_NJPAX_N@Z");

    s_shield_parameters * shield = static_cast<s_shield_parameters *>(element);

    switch (shield->version)
    {
    case 0:
    case 1:
        on_new(element);
        shield->version = 2;
    case 2:
        shield->plasma_outer_fade_radius = shield->outer_fade_radius;
        shield->plasma_center_radius = shield->center_radius;
        shield->plasma_inner_fade_radius = shield->inner_fade_radius;
        shield->version = 3;
    case 3:
        shield->plasma_depth_fade_range = shield->depth_fade_range;
        shield->version = 4;
    }

    if (!for_editor)
    {
        shield->outer_fade_radius = 1.0f - shield->outer_fade_radius;
        shield->center_radius = 1.0f - shield->center_radius;
        shield->inner_fade_radius = 1.0f - shield->inner_fade_radius;
        shield->plasma_outer_fade_radius = 1.0f - shield->plasma_outer_fade_radius;
        shield->plasma_center_radius = 1.0f - shield->plasma_center_radius;
        shield->plasma_inner_fade_radius = 1.0f - shield->plasma_inner_fade_radius;

        float scale_outer = 1.0f / (shield->center_radius - shield->outer_fade_radius);
        float offset_outer = -shield->outer_fade_radius * scale_outer;
        float plasma_scale_outer = 1.0f / (shield->plasma_center_radius - shield->plasma_outer_fade_radius);
        float plasma_offset_outer = -shield->plasma_outer_fade_radius * plasma_scale_outer;
        float scale_inner = 1.0f / (shield->center_radius - shield->inner_fade_radius);
        float offset_inner = -shield->inner_fade_radius * scale_inner;
        float plasma_scale_inner = 1.0f / (shield->plasma_center_radius - shield->plasma_inner_fade_radius);
        float plasma_offset_inner = -shield->plasma_inner_fade_radius * plasma_scale_inner;

        set_real_vector4d(&shield->edge_scales, scale_outer, scale_inner, plasma_scale_outer, plasma_scale_inner);
        set_real_vector4d(&shield->edge_offsets, offset_outer, offset_inner, plasma_offset_outer, plasma_offset_inner);
        set_real_vector4d(&shield->plasma_scales, shield->tiling_scale, shield->tiling_scale, shield->edge_sharpness - shield->center_sharpness, shield->center_sharpness);
        set_real_vector4d(&shield->depth_fade_params, 1.0f / real_max(shield->depth_fade_range, k_real_epsilon), 1.0f / real_max(shield->plasma_depth_fade_range, k_real_epsilon), 0.0f, 0.0f);
        shield->hit_time = 1.0f / real_max(shield->hit_time, k_real_epsilon);
    }

    return true;
};

