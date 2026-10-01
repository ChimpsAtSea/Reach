#pragma once
#ifndef __SHIELD_IMPACT_DEFINITIONS_H__
#define __SHIELD_IMPACT_DEFINITIONS_H__

/* ---------- headers */

#include "omaha\tag_files\tag_groups.h"
#include "omaha\math\real_math.h"
#include "omaha\math\function_definitions.h"
#include "core\corelib\cseries\cseries_macros.h"

/* ---------- constants */

enum
{
    SHIELD_IMPACT_TAG = 'shit',
};

/* ---------- definitions */

struct s_shield_function
{
    long input_variable; // 0x0
    long range_variable; // 0x4
    c_function_definition mapping; // 0x8
};
static_assert(sizeof(s_shield_function) == 0x1C, "s_shield_function");

struct s_shield_parameters
{
    static bool on_new(void * element);
    static bool postprocess(long tag_index, void * element, bool for_editor);

    unsigned short flags; // 0x0
    short version; // 0x2
    float recent_damage_intensity; // 0x4
    float current_damage_intensity; // 0x8
    float depth_fade_range; // 0xC
    float outer_fade_radius; // 0x10
    float center_radius; // 0x14
    float inner_fade_radius; // 0x18
    s_shield_function edge_glow_color; // 0x1C
    s_shield_function edge_glow_intensity; // 0x38
    float plasma_depth_fade_range; // 0x54
    s_tag_reference plasma_noise_texture0; // 0x58
    s_tag_reference plasma_noise_texture1; // 0x68
    float tiling_scale; // 0x78
    float scroll_speed; // 0x7C
    float edge_sharpness; // 0x80
    float center_sharpness; // 0x84
    float plasma_outer_fade_radius; // 0x88
    float plasma_center_radius; // 0x8C
    float plasma_inner_fade_radius; // 0x90
    s_shield_function plasma_center_color; // 0x94
    s_shield_function plasma_center_intensity; // 0xB0
    s_shield_function plasma_edge_color; // 0xCC
    s_shield_function plasma_edge_intensity; // 0xE8
    s_tag_reference oscillation_texture0; // 0x104
    s_tag_reference oscillation_texture1; // 0x114
    float oscillation_tiling_scale; // 0x124
    float oscillation_scroll_speed; // 0x128
    s_shield_function extrusion_amount; // 0x12C
    s_shield_function oscillation_amplitude; // 0x148
    float hit_time; // 0x164
    s_shield_function hit_color; // 0x168
    s_shield_function hit_radius; // 0x184
    vector4d edge_scales; // 0x1A0
    vector4d edge_offsets; // 0x1B0
    vector4d plasma_scales; // 0x1C0
    vector4d depth_fade_params; // 0x1D0
};
static_assert(sizeof(s_shield_parameters) == 0x1E0, "s_shield_parameters");

/* ---------- prototypes */

void init_color_function(s_shield_function * function, unsigned long color);
void init_scalar_function(s_shield_function * function, float clamp_range_min, float clamp_range_max);

/* ---------- globals */

/* ---------- public code */

#endif // __SHIELD_IMPACT_DEFINITIONS_H__

