#pragma once
#ifndef __FOLLOWING_CAMERA_H__
#define __FOLLOWING_CAMERA_H__

/* ---------- headers */

#include "omaha\math\real_math.h"

/* ---------- constants */

// $TODO names unknown; animated_trick_camera_setup_target passes 1
enum e_following_camera_deterministic_blending
{
    _following_camera_deterministic_blending_none = 0,
    _following_camera_deterministic_blending_enabled,

    k_following_camera_deterministic_blending_count
};

/* ---------- definitions */

struct s_observer_command;

/* ---------- prototypes */

void following_camera_deterministic(long unit_index, real_point3d * position, vector3d * forward, e_following_camera_deterministic_blending blending);
void following_camera_at_point(long unit_index, real_point3d const * position, vector3d const * forward, vector3d const * up, s_observer_command * result);

/* ---------- globals */

/* ---------- public code */

#endif // __FOLLOWING_CAMERA_H__

