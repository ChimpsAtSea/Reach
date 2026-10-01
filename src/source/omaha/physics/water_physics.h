#pragma once
#ifndef __WATER_PHYSICS_H__
#define __WATER_PHYSICS_H__

/* ---------- headers */

#include "omaha\math\real_math.h"
#include "omaha\game\materials.h"

/* ---------- constants */

/* ---------- definitions */

union real_point3d;
class c_global_material_type;

struct s_water_physics_effect_parameters
{
    vector3d water_velocity; // 0x0
    vector3d water_interaction_velocity; // 0xC
};
static_assert(sizeof(s_water_physics_effect_parameters) == 0x18, "s_water_physics_effect_parameters");

// layout from water_physics_test_vector (Reach differs from H3: t moved to 0x1C, trailing bool)
// default constructor is implicit (f i in projectiles.obj: only constructs material_type)
struct s_water_physics_test_vector_result
{
    real_point3d position; // 0x0
    vector3d normal; // 0xC
    real unknown18; // 0x18 $TODO name (set from the test point's z)
    real t; // 0x1C
    long structure_bsp_index; // 0x20
    long water_instance_index; // 0x24
    c_global_material_type material_type; // 0x28
    s_water_physics_effect_parameters effect_parameters; // 0x2C
    bool unknown44; // 0x44 $TODO name
};
static_assert(sizeof(s_water_physics_test_vector_result) == 0x48, "s_water_physics_test_vector_result");

/* ---------- prototypes */

bool water_physics_test_point(real_point3d const * point, c_global_material_type * material_type);
bool water_physics_test_vector_solid(real_point3d const * point, vector3d const * vector, s_water_physics_test_vector_result * result);
bool water_physics_test_extruded_water(long object_index, real extrusion, real_point3d const * point, vector3d const * vector, real length, real * out_depth);

/* ---------- globals */

/* ---------- public code */

#endif // __WATER_PHYSICS_H__

