#pragma once
#ifndef __ORBITING_CAMERA_H__
#define __ORBITING_CAMERA_H__

/* ---------- headers */

#include "omaha\camera\camera.h"
#include "omaha\math\real_math.h"

/* ---------- constants */

/* ---------- definitions */

// $TODO: only the members used so far are known; the rest of the layout is not yet reversed
class c_orbiting_camera : public c_camera
{
public:
    void get_orientation(euler_angles2d * orientation);
    void set_orientation(euler_angles2d const * orientation);
    void set_distance(float distance);
    void set_vertical_offset(float vertical_offset);
    void set_horizontal_offset(float horizontal_offset);

private:
    euler_angles2d m_orientation; // 0x10
};

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __ORBITING_CAMERA_H__

