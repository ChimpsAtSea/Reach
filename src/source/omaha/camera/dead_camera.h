#pragma once
#ifndef __DEAD_CAMERA_H__
#define __DEAD_CAMERA_H__

/* ---------- headers */

#include "omaha\camera\camera.h"
#include "omaha\game\player_mapping.h"
#include "omaha\math\real_math.h"

/* ---------- constants */

/* ---------- definitions */

// layout verified against the target (offsets from set_target / update / the constructors)
class c_dead_camera : public c_camera
{
public:
    c_dead_camera();
    c_dead_camera(e_output_user_index output_user_index);

    virtual e_camera_mode get_type() const
    {
        mangled_ppc("?get_type@c_dead_camera@@UBA?AW4e_camera_mode@@XZ");

        return _camera_mode_dead;
    };

    virtual e_director_perspective get_perspective() const
    {
        mangled_ppc("?get_perspective@c_dead_camera@@UBA?AW4e_director_perspective@@XZ");

        return _director_perspective_third_person;
    };

    virtual void update(e_output_user_index output_user_index, float dt, s_observer_command * result);
    virtual void set_target(long object_index);
    virtual void handle_deleted_player(long player_index);
    virtual void handle_deleted_object(long object_index);

private:
    long get_target_unit_index();
    long get_target_player_index();
    bool get_killer_position(real_point3d * position);

    real_point3d m_falling_camera_position; // 0x10
    euler_angles2d m_orientation; // 0x1C
    float m_distance; // 0x24
    float m_field_of_view; // 0x28
    float m_timer; // 0x2C
    long m_player_index; // 0x30
    long m_killer_object_index; // 0x34
    bool m_unit_fell_to_death; // 0x38
    e_output_user_index m_output_user_index; // 0x3C
};
static_assert(sizeof(c_dead_camera) == 0x40, "c_dead_camera");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __DEAD_CAMERA_H__

