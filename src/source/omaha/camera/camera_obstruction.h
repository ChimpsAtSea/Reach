#pragma once
#ifndef __CAMERA_OBSTRUCTION_H__
#define __CAMERA_OBSTRUCTION_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"
#include "omaha\math\real_math.h"
#include "omaha\physics\collision_constants.h"

/* ---------- constants */

/* ---------- definitions */

// layout from camera_obstruction_struct (haloreach_tagtest_x360.json), sizeof(s_camera_obstruction_parameters)
struct s_camera_obstruction_parameters
{
    float cylinder_fraction; // 0x0
    float obstruction_test_angle; // 0x4
    float obstruction_max_inward_acceleration; // 0x8
    float obstruction_max_outward_acceleration; // 0xC
    float obstruction_max_velocity; // 0x10
    float obstruction_return_delay; // 0x14
};
static_assert(sizeof(s_camera_obstruction_parameters) == 0x18, "s_camera_obstruction_parameters");

// offsets from camera_obstruction.cpp (names are guesses)
struct s_camera_obstruction_state
{
    void initialize();

    float t; // 0x0
    float velocity; // 0x4
    float return_delay_timer; // 0x8
    real_point3d remembered_point; // 0xC
    bool remembered_point_valid; // 0x18
    long first_ignore_object_index; // 0x1C
    long second_ignore_object_index; // 0x20
};
static_assert(sizeof(s_camera_obstruction_state) == 0x24, "s_camera_obstruction_state");

/* ---------- prototypes */

void camera_obstruction_update(float dt, s_collision_test_flags const * flags, s_camera_obstruction_parameters const * parameters, s_camera_obstruction_state * state, real_point3d const * focus_point, real_point3d const * camera_point);
void camera_obstruction_update_spring(float dt, s_collision_test_flags const * flags, s_camera_obstruction_parameters const * parameters, s_camera_obstruction_state * state, real_point3d const * focus_point, real_point3d const * camera_point, float inward_spring_constant, float outward_spring_constant);

/* ---------- globals */

extern float observer_collision_speed_scale;
extern bool observer_collision_debug;

/* ---------- public code */

#endif // __CAMERA_OBSTRUCTION_H__

