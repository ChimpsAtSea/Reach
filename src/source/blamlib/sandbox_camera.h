#pragma once
#ifndef __SANDBOX_CAMERA_H__
#define __SANDBOX_CAMERA_H__

/* ---------- headers */

#include "omaha\camera\camera.h"

/* ---------- constants */

/* ---------- definitions */

class c_sandbox_camera : public c_camera
{
public:
    c_sandbox_camera();
    c_sandbox_camera(long player_index);

    virtual e_camera_mode get_type() const
    {
        mangled_ppc("?get_type@c_sandbox_camera@@UBA?AW4e_camera_mode@@XZ");

        return _camera_mode_sandbox;
    };

    virtual e_director_perspective get_perspective() const
    {
        mangled_ppc("?get_perspective@c_sandbox_camera@@UBA?AW4e_director_perspective@@XZ");

        return _director_perspective_first_person;
    };

    virtual void update(e_output_user_index output_user_index, float dt, s_observer_command * result);

    virtual bool should_draw_reticule() const
    {
        mangled_ppc("?should_draw_reticule@c_sandbox_camera@@UBA_NXZ");

        return true;
    };

    float get_deterministic(real_point3d * position, vector3d * forward);

protected:
    long m_player_index; // 0x10
};
static_assert(sizeof(c_sandbox_camera) == 0x14, "c_sandbox_camera");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __SANDBOX_CAMERA_H__

