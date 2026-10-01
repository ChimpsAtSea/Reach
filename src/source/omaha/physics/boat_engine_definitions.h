#pragma once
#ifndef __BOAT_ENGINE_DEFINITIONS_H__
#define __BOAT_ENGINE_DEFINITIONS_H__

/* ---------- headers */

#include "omaha\math\function_definitions.h"
#include "omaha\memory\static_arrays.h"
#include "core\corelib\cseries\cseries_macros.h"

/* ---------- constants */

/* ---------- definitions */

// boat_engine_definition_block (haloreach_tagtest_x360.json)
struct s_boat_engine_definition
{
    enum e_boat_flags
    {
        _boat_uses_fake_physics_bit = 0,

        k_boat_flags_count
    };

    c_flags_no_init<e_boat_flags, unsigned char, k_boat_flags_count> flags; // 0x0
    unsigned char pad[3]; // 0x1
    long propeller_marker_name; // 0x4 $TODO c_string_id
    float out_of_water_thrust_scale; // 0x8
    float out_of_water_torque_scale; // 0xC
    float propeller_radius; // 0x10
    float propeller_torque_scale; // 0x14
    float reverse_linear_acceleration; // 0x18
    float linear_acceleration; // 0x1C
    float angular_acceleration; // 0x20
    float stabilization_angular_acceleration; // 0x24
    float stabilization_desired_inclination; // 0x28
    float drag_input_range_velocity; // 0x2C
    c_function_definition normal_drag; // 0x30 (scalar_function_named_struct)
    c_function_definition boost_drag; // 0x44 (scalar_function_named_struct)
    c_function_definition air_drag; // 0x58 (scalar_function_named_struct)
};
static_assert(sizeof(s_boat_engine_definition) == 0x6C, "s_boat_engine_definition");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __BOAT_ENGINE_DEFINITIONS_H__

