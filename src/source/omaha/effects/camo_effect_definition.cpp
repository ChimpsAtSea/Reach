#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\effects\\camo_effect_definition.cpp"
/* ---------- headers */

#include "omaha\effects\camo_effect_definition.h"
#include "omaha\cseries\cseries.h"
#include "omaha\math\random_math.h"
#include "omaha\objects\objects.h"
#include "graphicslib\render_time.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// struct s_tag_block_definition camo_block; // "?camo_block@@3Us_tag_block_definition@@A"
// struct s_tag_reference_definition global_camo_effect_reference; // "?global_camo_effect_reference@@3Us_tag_reference_definition@@A"
// struct s_tag_group camo_group; // "?camo_group@@3Us_tag_group@@A"
// struct s_tag_group_legacy_vtable legacy_camo_vtable; // "?legacy_camo_vtable@@3Us_tag_group_legacy_vtable@@A"
// struct s_tag_group_stream_definition legacy_camo_stream_definition; // "?legacy_camo_stream_definition@@3Us_tag_group_stream_definition@@A"
// struct s_tag_group_sync_definition legacy_camo_xsync_declaration; // "?legacy_camo_xsync_declaration@@3Us_tag_group_sync_definition@@A"
// class c_legacy_tag_group_vtable_shim legacy_camo_vtable_shim; // "?legacy_camo_vtable_shim@@3Vc_legacy_tag_group_vtable_shim@@A"

// public: static bool s_camo_effect_definition::on_new(void *);
// void init_scalar_function(struct s_camo_function *, float, float);
// public: static bool s_camo_effect_definition::postprocess(long, void *, bool);
// public: void s_camo_effect_definition::evaluate(long, float, long *, long *) const;
// float eval_scalar_function(struct s_camo_function const *, struct s_camo_function_state const *);
// public: float s_camo_function_state::eval_string_id(long, float) const;

bool s_camo_effect_definition::on_new(void * element)
{
    mangled_ppc("?on_new@s_camo_effect_definition@@SA_NPAX@Z");

    s_camo_effect_definition * definition = static_cast<s_camo_effect_definition *>(element);
    init_scalar_function(&definition->active_camo_amount, 0.0f, 1.0f);
    return true;
};

void init_scalar_function(s_camo_function * function, float clamp_range_min, float clamp_range_max)
{
    mangled_ppc("?init_scalar_function@@YAXPAUs_camo_function@@MM@Z");

    c_function_definition_editor editor(&function->function);
    editor.set_color_graph_type(c_function_definition::_function_color_graph_type_scalar);
    editor.set_function_type(c_function_definition::_function_type_linear);
    editor.calc_default_values();
    editor.set_control_point_y(0, 0, 0.0f);
    editor.set_control_point_y(0, 1, 1.0f);
    editor.set_clamp_range_min(clamp_range_min);
    editor.set_clamp_range_max(clamp_range_max);
};

bool s_camo_effect_definition::postprocess(long tag_index, void * element, bool for_editor)
{
    mangled_ppc("?postprocess@s_camo_effect_definition@@SA_NJPAX_N@Z");

    return true;
};

void s_camo_effect_definition::evaluate(long object_index, float camo_value, long * active_camo_amount_out, long * shadow_amount_out) const
{
    mangled_ppc("?evaluate@s_camo_effect_definition@@QBAXJMPAJ0@Z");

    s_camo_function_state state;
    state.object_index = object_index;
    state.time = g_render_time.frame_seconds;
    state.camo_value = camo_value;

    float active_camo = eval_scalar_function(&active_camo_amount, &state);
    float shadow = eval_scalar_function(&shadow_amount, &state);
    *shadow_amount_out = static_cast<long>(shadow * 255.0f + 0.5f);
    *active_camo_amount_out = static_cast<long>(active_camo * 255.0f + 0.5f);
};

float eval_scalar_function(s_camo_function const * function, s_camo_function_state const * state)
{
    mangled_ppc("?eval_scalar_function@@YAMPBUs_camo_function@@PBUs_camo_function_state@@@Z");

    float input_scalar = state->eval_string_id(function->input_variable, g_render_time.wrapped_periods[2]);
    float range_scalar = state->eval_string_id(function->range_variable, _real_random(get_local_random_seed_address(), NULL, __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__, 160));
    return function->function.evaluate_scalar(input_scalar, range_scalar);
};

float s_camo_function_state::eval_string_id(long name, float default_value) const
{
    mangled_ppc("?eval_string_id@s_camo_function_state@@QBAMJM@Z");

    float result = default_value;
    switch (name)
    {
    case 0:
        break;
    case 0x1B6:
        result = time;
        break;
    case 0x4AA:
        result = camo_value;
        break;
    default:
        if (object_index != NONE)
        {
            result = object_get_function_value_simple(object_index, name, NONE);
        }
        break;
    }
    return result;
};

