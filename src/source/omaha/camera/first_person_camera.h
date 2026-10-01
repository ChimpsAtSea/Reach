#pragma once
#ifndef __FIRST_PERSON_CAMERA_H__
#define __FIRST_PERSON_CAMERA_H__

/* ---------- headers */

#include "omaha\camera\camera.h"
#include "omaha\math\real_math.h"

/* ---------- constants */

/* ---------- definitions */

class c_first_person_camera : public c_camera
{
public:
    c_first_person_camera();
    c_first_person_camera(long object_index);

    virtual e_camera_mode get_type() const
    {
        mangled_ppc("?get_type@c_first_person_camera@@UBA?AW4e_camera_mode@@XZ");

        return _camera_mode_first_person;
    };

    virtual e_director_perspective get_perspective() const
    {
        mangled_ppc("?get_perspective@c_first_person_camera@@UBA?AW4e_director_perspective@@XZ");

        return _director_perspective_first_person;
    };

    virtual void update(e_output_user_index output_user_index, float dt, s_observer_command * result);
    virtual void set_target(long object_index);
    virtual bool should_draw_reticule() const;
    virtual void assemble_screen_effects(c_global_screen_effect_state * screen_effect_state);

    void set_allow_controlled_facing(bool allow_controlled_facing);

private:
    float m_last_horizontal_field_of_view; // 0x10
    euler_angles2d m_orientation_offset; // 0x14
    bool m_allow_controlled_facing; // 0x1C
};
static_assert(sizeof(c_first_person_camera) == 0x20, "c_first_person_camera");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __FIRST_PERSON_CAMERA_H__

