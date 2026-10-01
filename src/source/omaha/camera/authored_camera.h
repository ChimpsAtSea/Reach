#pragma once
#ifndef __AUTHORED_CAMERA_H__
#define __AUTHORED_CAMERA_H__

/* ---------- headers */

#include "omaha\camera\camera.h"
#include "omaha\camera\first_person_camera.h"
#include "omaha\math\real_math.h"

/* ---------- constants */

/* ---------- definitions */

class c_authored_camera : public c_camera
{
public:
    c_authored_camera();
    c_authored_camera(e_output_user_index output_user_index);

    virtual e_camera_mode get_type() const
    {
        mangled_ppc("?get_type@c_authored_camera@@UBA?AW4e_camera_mode@@XZ");

        return _camera_mode_authored;
    };

    virtual e_director_perspective get_perspective() const;
    virtual void update(e_output_user_index output_user_index, float dt, s_observer_command * result);
    virtual long get_target() const;
    virtual void set_target(long object_index);
    virtual bool should_draw_reticule() const;
    virtual bool should_apply_player_effects() const;
    virtual void handle_deleted_object(long object_index);

private:
    bool m_last_update_first_person; // 0x10
    bool m_last_zoomed; // 0x11
    c_first_person_camera m_first_person_camera; // 0x14
    real_point3d m_position; // 0x34
    vector3d m_forward; // 0x40
};
static_assert(sizeof(c_authored_camera) == 0x4C, "c_authored_camera");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __AUTHORED_CAMERA_H__

