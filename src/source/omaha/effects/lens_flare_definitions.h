#pragma once
#ifndef __LENS_FLARE_DEFINITIONS_H__
#define __LENS_FLARE_DEFINITIONS_H__

/* ---------- headers */

#include "omaha\tag_files\tag_groups.h"
#include "omaha\math\real_math.h"
#include "omaha\math\color_math.h"
#include "omaha\math\function_definitions.h"
#include "core\corelib\cseries\cseries_macros.h"

/* ---------- constants */

/* ---------- definitions */

// lens_flare_reflection_block
struct s_lens_flare_reflection
{
    unsigned char flags; // 0x0
    char version; // 0x1
    short bitmap_index; // 0x2
    float rotation_offset; // 0x4
    float axis_offset; // 0x8
    real_bounds bounds_radius; // 0xC
    real_bounds bounds_brightness; // 0x14
    c_function_definition radius_curve; // 0x1C
    c_function_definition brightness_curve; // 0x30
    float modulation_factor; // 0x44
    real_rgb_color color; // 0x48
    float tint_power; // 0x54
};
static_assert(sizeof(s_lens_flare_reflection) == 0x58, "s_lens_flare_reflection");

// lens_flare_color_function_struct
struct s_editing_function
{
    long input_variable; // 0x0
    long range_variable; // 0x4
    short output_modifier; // 0x8
    unsigned char pad[2]; // 0xA
    long output_modifier_input; // 0xC
    c_function_definition mapping; // 0x10
};
static_assert(sizeof(s_editing_function) == 0x24, "s_editing_function");

// lens_flare_struct_definition
struct s_lens_flare_definition
{
    float falloff_angle; // 0x0
    float cutoff_angle; // 0x4
    float occlusion_offset_distance; // 0x8
    short occlusion_offset_direction; // 0xC
    unsigned char pad0[2]; // 0xE
    float occlusion_inner_radius_scale; // 0x10
    float near_fade_begin_distance; // 0x14
    float near_fade_end_distance; // 0x18
    float near_fade_distance; // 0x1C
    float far_fade_distance; // 0x20
    s_tag_reference bitmap; // 0x24
    unsigned short flags; // 0x34
    unsigned short runtime_flags; // 0x36
    short rotation_function; // 0x38
    unsigned char pad1[2]; // 0x3A
    float rotation_function_scale; // 0x3C
    short falloff_function; // 0x40
    unsigned char pad2[2]; // 0x42
    s_tag_block reflections; // 0x44
    unsigned short animation_flags; // 0x50
    unsigned char pad3[2]; // 0x52
    s_tag_block time_brightness; // 0x54
    s_tag_block age_brightness; // 0x60
    s_tag_block time_color; // 0x6C
    s_tag_block age_color; // 0x78
    s_tag_block time_rotation; // 0x84
    s_tag_block age_rotation; // 0x90
};
static_assert(sizeof(s_lens_flare_definition) == 0x9C, "s_lens_flare_definition");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __LENS_FLARE_DEFINITIONS_H__

