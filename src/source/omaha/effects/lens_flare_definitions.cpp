/* ---------- headers */

#include "omaha\effects\lens_flare_definitions.h"
#include "omaha\tag_files\tag_groups.h"
#include "omaha\math\real_math.h"
#include "omaha\math\color_math.h"
#include "omaha\math\function_definitions.h"
#include "core\corelib\cseries\cseries_macros.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// struct s_tag_block_definition lens_flare_block; // "?lens_flare_block@@3Us_tag_block_definition@@A"
// struct s_tag_reference_definition global_lens_flare_reference; // "?global_lens_flare_reference@@3Us_tag_reference_definition@@A"
// struct s_tag_group lens_flare_group; // "?lens_flare_group@@3Us_tag_group@@A"
// struct s_tag_group_legacy_vtable legacy_lens_flare_vtable; // "?legacy_lens_flare_vtable@@3Us_tag_group_legacy_vtable@@A"
// struct s_tag_group_stream_definition legacy_lens_flare_stream_definition; // "?legacy_lens_flare_stream_definition@@3Us_tag_group_stream_definition@@A"
// struct s_tag_group_sync_definition legacy_lens_flare_xsync_declaration; // "?legacy_lens_flare_xsync_declaration@@3Us_tag_group_sync_definition@@A"
// class c_legacy_tag_group_vtable_shim legacy_lens_flare_vtable_shim; // "?legacy_lens_flare_vtable_shim@@3Vc_legacy_tag_group_vtable_shim@@A"

// bool lens_flare_reflection_new_block_proc(void *);
// bool lens_flare_reflection_post_process_block_proc(long, void *, bool);
// bool lens_flare_definition_postprocess_block_proc(long, void *, bool);
// bool new_color_block_proc(void *);
// bool lens_flare_definition_new_block_proc(void *);

bool lens_flare_reflection_new_block_proc(void * element)
{
    mangled_ppc("?lens_flare_reflection_new_block_proc@@YA_NPAX@Z");

    s_lens_flare_reflection * reflection = static_cast<s_lens_flare_reflection *>(element);
    reflection->color = global_real_argb_white->rgb;
    reflection->tint_power = 1.0f;
    reflection->version = 1;

    c_function_definition_editor editor(&reflection->brightness_curve);
    editor.set_color_graph_type(c_function_definition::_function_color_graph_type_scalar);
    editor.set_function_type(c_function_definition::_function_type_linear);
    editor.calc_default_values();
    editor.set_control_point_y(0, 0, 0.0f);
    editor.set_control_point_y(0, 1, 1.0f);
    editor.set_clamp_range_min(0.0f);

    c_function_definition_editor radius_editor(&reflection->radius_curve);
    radius_editor.set_color_graph_type(c_function_definition::_function_color_graph_type_scalar);
    radius_editor.set_function_type(c_function_definition::_function_type_linear);
    radius_editor.calc_default_values();
    radius_editor.set_control_point_y(0, 0, 0.0f);
    radius_editor.set_control_point_y(0, 1, 0.1f);
    radius_editor.set_clamp_range_min(0.0f);

    reflection->axis_offset = 0.0f;

    return true;
};

bool lens_flare_reflection_post_process_block_proc(long element_index, void * element, bool for_editor)
{
    mangled_ppc("?lens_flare_reflection_post_process_block_proc@@YA_NJPAX_N@Z");

    s_lens_flare_reflection * reflection = static_cast<s_lens_flare_reflection *>(element);
    switch (reflection->version)
    {
    case 0:
    {
        float tint_power = reflection->tint_power <= 0.0001f ? 4.0f : reflection->tint_power;
        reflection->tint_power = tint_power + 1.0f;
        reflection->version = 1;
    }
        break;
    }

    return true;
};

// $TODO nonmatching
bool lens_flare_definition_postprocess_block_proc(long element_index, void * element, bool for_editor)
{
    mangled_ppc("?lens_flare_definition_postprocess_block_proc@@YA_NJPAX_N@Z");

    if (!for_editor)
    {
        s_lens_flare_definition * definition = static_cast<s_lens_flare_definition *>(element);
        bool enable = true;
        SET_BIT(definition->runtime_flags, 0, enable);
        definition->falloff_angle = PIN(definition->falloff_angle, 0.0f, 180.0f * k_degrees_to_radians);
        definition->cutoff_angle = PIN(definition->cutoff_angle, definition->falloff_angle, 180.0f * k_degrees_to_radians);
    }

    return true;
};

bool new_color_block_proc(void * element)
{
    mangled_ppc("?new_color_block_proc@@YA_NPAX@Z");

    s_editing_function * color_function = static_cast<s_editing_function *>(element);
    c_function_definition_editor color_editor(&color_function->mapping);
    color_editor.set_color_graph_type(c_function_definition::_function_color_graph_type_two_color);
    color_editor.set_color(0, 0xFFFFFFFF);
    color_editor.set_color(1, 0xFFFFFFFF);
    color_editor.set_color(2, 0xFFFFFFFF);
    color_editor.set_color(3, 0xFFFFFFFF);

    return true;
};

bool lens_flare_definition_new_block_proc(void * element)
{
    mangled_ppc("?lens_flare_definition_new_block_proc@@YA_NPAX@Z");

    s_lens_flare_definition * definition = static_cast<s_lens_flare_definition *>(element);
    definition->near_fade_distance = 90.0f;
    definition->far_fade_distance = 100.0f;
    definition->near_fade_begin_distance = 0.0f;
    definition->near_fade_end_distance = 0.0f;
    definition->occlusion_offset_distance = 0.05f;
    definition->occlusion_inner_radius_scale = 0.25f;
    tag_block_add_element(&definition->reflections);

    return true;
};

