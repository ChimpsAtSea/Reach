#pragma once
#ifndef __SPRING_ACCELERATION_H__
#define __SPRING_ACCELERATION_H__

/* ---------- headers */

#include "omaha\math\real_math.h"
#include "core\corelib\cseries\cseries_macros.h"

/* ---------- constants */

/* ---------- definitions */

// layout inferred from spring_acceleration_state_update (size not verified against callers)
struct s_spring_acceleration_state
{
    vector3d acceleration; // 0x0
    vector3d position; // 0xC
    vector3d velocity; // 0x18
    vector3d previous_world_velocity; // 0x24
};
static_assert(sizeof(s_spring_acceleration_state) == 0x30, "s_spring_acceleration_state");

/* ---------- prototypes */

void spring_acceleration_state_update(s_spring_acceleration_state * state, long spring_acceleration_index, vector3d const * world_velocity, bool reset);

/* ---------- globals */

/* ---------- public code */

#endif // __SPRING_ACCELERATION_H__

