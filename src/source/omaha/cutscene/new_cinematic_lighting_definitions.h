#pragma once
#ifndef __NEW_CINEMATIC_LIGHTING_DEFINITIONS_H__
#define __NEW_CINEMATIC_LIGHTING_DEFINITIONS_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"
#include "omaha\math\real_math.h"
#include "omaha\tag_files\tag_groups.h"

/* ---------- constants */

/* ---------- definitions */

struct s_cinematic_light_direction
{
    real screen_angle; // 0x0
    real front_back_angle; // 0x4

    void get_direction(real_matrix4x3 const * camera_matrix, vector3d * light_forward, vector3d * light_up) const;
};
static_assert(sizeof(s_cinematic_light_direction) == 0x8, "s_cinematic_light_direction");

struct s_cinematic_dynamic_light
{
    enum e_flags
    {
        _light_debug_bit = 0,
        _follow_object_bit,
        _move_to_marker_bit,

        k_number_of_flags
    };

    unsigned long flags; // 0x0
    s_cinematic_light_direction direction; // 0x4
    real distance; // 0xC
    s_tag_reference light_definition; // 0x10

    long create(real_point3d const * subject_point, real_matrix4x3 const * camera_matrix, long object_index, long marker_id);
};
static_assert(sizeof(s_cinematic_dynamic_light) == 0x20, "s_cinematic_dynamic_light");

struct s_cinematic_lighting
{
    enum
    {
        _tag = 'nclt',
    };

    real directional_color[3]; // 0x0
    real directional_scale; // 0xC
    s_cinematic_light_direction direction; // 0x10
    real bandwidth; // 0x18
    real analytical_color[3]; // 0x1C
    real analytical_scale; // 0x28
    s_cinematic_light_direction analytical_direction; // 0x2C
    real ambient_color[3]; // 0x34
    real ambient_scale; // 0x40
    real sampled_vmf_light_weight; // 0x44
    real sampled_analytical_light_weight; // 0x48
    real vmf_light_scale; // 0x4C
    real analytical_light_scale; // 0x50
    s_tag_block dynamic_lights; // 0x54

    static bool initialize_on_new(void * data);
    static bool postprocess(long tag_index, bool for_editor);
};
static_assert(sizeof(s_cinematic_lighting) == 0x60, "s_cinematic_lighting");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __NEW_CINEMATIC_LIGHTING_DEFINITIONS_H__
