#pragma once
#ifndef __STATIC_CAMERA_H__
#define __STATIC_CAMERA_H__

/* ---------- headers */

#include "omaha\camera\camera.h"
#include "omaha\math\real_math.h"

/* ---------- constants */

/* ---------- definitions */

class c_static_camera : public c_camera
{
public:
    c_static_camera();
    c_static_camera(e_output_user_index output_user_index);

    virtual e_camera_mode get_type() const
    {
        mangled_ppc("?get_type@c_static_camera@@UBA?AW4e_camera_mode@@XZ");

        return _camera_mode_static;
    };

    virtual e_director_perspective get_perspective() const
    {
        mangled_ppc("?get_perspective@c_static_camera@@UBA?AW4e_director_perspective@@XZ");

        return _director_perspective_neutral;
    };

    virtual void update(e_output_user_index output_user_index, float dt, s_observer_command * result);
    virtual void set_target(long object_index);

    virtual void set_position(real_point3d const * position)
    {
        mangled_ppc("?set_position@c_static_camera@@UAAXPBTreal_point3d@@@Z");

        m_position = *position;
    };

    virtual void set_forward(vector3d const * forward)
    {
        mangled_ppc("?set_forward@c_static_camera@@UAAXPBTvector3d@@@Z");

        m_forward = *forward;
    };

    virtual bool should_apply_player_effects() const
    {
        mangled_ppc("?should_apply_player_effects@c_static_camera@@UBA_NXZ");

        return false;
    };

private:
    real_point3d m_position; // 0x10
    vector3d m_forward; // 0x1C
    float m_field_of_view; // 0x28
};
static_assert(sizeof(c_static_camera) == 0x2C, "c_static_camera");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __STATIC_CAMERA_H__
