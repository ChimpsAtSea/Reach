#pragma once
#ifndef __FLYING_CAMERA_H__
#define __FLYING_CAMERA_H__

/* ---------- headers */

#include "omaha\camera\camera.h"

/* ---------- constants */

/* ---------- definitions */

// $TODO: layout not reversed yet; only the methods used so far are declared
class c_flying_camera : public c_camera
{
public:
    void set_lock_in_xy_plane(bool lock);
    void set_collision(bool collision);
};

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __FLYING_CAMERA_H__

