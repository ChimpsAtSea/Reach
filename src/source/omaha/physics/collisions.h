#pragma once
#ifndef __COLLISIONS_H__
#define __COLLISIONS_H__

/* ---------- headers */

#include "omaha\physics\collision_constants.h"
#include "omaha\math\real_math.h"
#include "core\corelib\cseries\cseries_macros.h"

/* ---------- constants */

/* ---------- definitions */

// $TODO only partially reversed (Reach layout: c_collision_bsp_reference 0x18, c_global_material_type 0x20)
enum e_collision_result_type
{
    _collision_result_none = 0,
    _collision_result_structure,
    _collision_result_media,
    _collision_result_instanced_geometry,
    _collision_result_object,

    k_collision_result_type_count
};

struct collision_result
{
    collision_result(void); // $TODO inline in the target (f i, render_debug.obj); body not reversed yet

    long type; // 0x0
    real t; // 0x4
    real_point3d point; // 0x8
    unsigned char unknown14[0x24 - 0x14]; // 0x14 $TODO
    real_plane3d plane; // 0x24
    unsigned char unknown34[0x38 - 0x34]; // 0x34 $TODO
    long object_index; // 0x38 (user_get_look_at_point)
    unsigned char unknown3C[0x68 - 0x3C]; // 0x3C $TODO
};
static_assert(sizeof(collision_result) == 0x68, "collision_result");

/* ---------- prototypes */

bool collision_test_vector(s_collision_test_flags flags, real_point3d const * point, vector3d const * vector, long first_ignore_object_index, long second_ignore_object_index, collision_result * collision);
bool collision_test_line(s_collision_test_flags flags, real_point3d const * point0, real_point3d const * point1, long first_ignore_object_index, long second_ignore_object_index, collision_result * collision);

/* ---------- globals */

/* ---------- public code */

#endif // __COLLISIONS_H__

