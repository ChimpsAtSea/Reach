#ifndef __SIMULATION_ENCODING_H__
#define __SIMULATION_ENCODING_H__
#pragma once

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"
#include "omaha\math\real_math.h"

/* ---------- constants */

enum e_simulation_update_camera_type
{
    _simulation_update_camera_none = 0,
    _simulation_update_camera_first_person,
    _simulation_update_camera_third_person_or_flying,

    k_simulation_update_camera_type_count
};

/* ---------- definitions */

// H3 simulation_update.h; layout verified in c_authored_camera::update
struct s_simulation_camera_update
{
    e_simulation_update_camera_type camera_type; // 0x0
    long target_absolute_player_index; // 0x4
    real_point3d position; // 0x8
    vector3d forward; // 0x14
    bool zoomed; // 0x20
};
static_assert(sizeof(s_simulation_camera_update) == 0x24, "s_simulation_camera_update");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __SIMULATION_ENCODING_H__

