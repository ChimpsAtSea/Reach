#pragma once
#ifndef __ANIMATED_TRICK_CAMERA_H__
#define __ANIMATED_TRICK_CAMERA_H__

/* ---------- headers */

#include "omaha\camera\camera.h"

/* ---------- constants */

/* ---------- definitions */

struct s_unit_camera_info;

class c_animated_trick_camera : public c_camera
{
public:
    c_animated_trick_camera();
    c_animated_trick_camera(long unit_index);

    virtual e_camera_mode get_type() const
    {
        mangled_ppc("?get_type@c_animated_trick_camera@@UBA?AW4e_camera_mode@@XZ");

        return _camera_mode_animated_trick;
    };

    virtual e_director_perspective get_perspective() const
    {
        mangled_ppc("?get_perspective@c_animated_trick_camera@@UBA?AW4e_director_perspective@@XZ");

        return _director_perspective_third_person;
    };

    virtual void update(e_output_user_index output_user_index, float dt, s_observer_command * result);

    virtual bool should_draw_reticule() const
    {
        mangled_ppc("?should_draw_reticule@c_animated_trick_camera@@UBA_NXZ");

        return true;
    };
};
static_assert(sizeof(c_animated_trick_camera) == 0x10, "c_animated_trick_camera");

/* ---------- prototypes */

bool animated_trick_camera_setup_target(long unit_index, s_unit_camera_info const * camera_info, s_observer_command * out_result);
void animated_trick_camera_setup_fov(long unit_index, s_unit_camera_info const * camera_info, s_observer_command * out_result);
void animated_trick_camera_setup_collision(long unit_index, s_unit_camera_info const * camera_info, s_observer_command * out_result);

/* ---------- globals */

extern long debug_vehicle_animated_trick_camera_name;
extern long debug_vehicle_animated_trick_animation_name;

/* ---------- public code */

#endif // __ANIMATED_TRICK_CAMERA_H__
