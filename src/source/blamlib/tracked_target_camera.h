#pragma once
#ifndef __TRACKED_TARGET_CAMERA_H__
#define __TRACKED_TARGET_CAMERA_H__

/* ---------- headers */

#include "omaha\camera\camera.h"

/* ---------- constants */

/* ---------- definitions */

class c_tracked_target_camera : public c_camera
{
public:
    c_tracked_target_camera();
    c_tracked_target_camera(long target_object_index);

    virtual e_camera_mode get_type() const
    {
        mangled_ppc("?get_type@c_tracked_target_camera@@UBA?AW4e_camera_mode@@XZ");

        return _camera_mode_tracked_target;
    };

    virtual e_director_perspective get_perspective() const
    {
        mangled_ppc("?get_perspective@c_tracked_target_camera@@UBA?AW4e_director_perspective@@XZ");

        return _director_perspective_third_person;
    };

    virtual void update(e_output_user_index output_user_index, float dt, s_observer_command * result);

    virtual bool should_draw_reticule() const
    {
        mangled_ppc("?should_draw_reticule@c_tracked_target_camera@@UBA_NXZ");

        return true;
    };
};

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __TRACKED_TARGET_CAMERA_H__

