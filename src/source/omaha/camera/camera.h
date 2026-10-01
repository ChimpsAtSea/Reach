#pragma once
#ifndef __CAMERA_H__
#define __CAMERA_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"
#include "omaha\memory\static_arrays.h"

/* ---------- constants */

// values verified against every c_*_camera::get_type in the target
enum e_camera_mode
{
    _camera_mode_none = -1,
    _camera_mode_following = 0,
    _camera_mode_orbiting,
    _camera_mode_flying,
    _camera_mode_first_person,
    _camera_mode_dead,
    _camera_mode_static,
    _camera_mode_scripted,
    _camera_mode_authored,
    _camera_mode_respawning,
    _camera_mode_animated_trick,
    _camera_mode_tracked_target,
    _camera_mode_sandbox,
    _camera_mode_space_fighter,

    k_number_of_camera_modes
};

enum e_director_perspective
{
    _director_perspective_first_person = 0,
    _director_perspective_third_person,
    _director_perspective_scripted,
    _director_perspective_neutral,

    k_number_of_director_perspectives
};

/* ---------- definitions */

enum e_output_user_index;
union real_point3d;
union vector3d;
struct s_observer_command;
class c_global_screen_effect_state;

// vtable order verified against ??_7c_camera@@6B@ (17 slots, no virtual destructor)
class c_camera
{
public:
    enum e_base_camera_flags
    {
        _move_instantly = 0,

        k_number_of_base_camera_flags
    };

    c_camera();

    virtual e_camera_mode get_type() const = 0;
    virtual e_director_perspective get_perspective() const = 0;
    virtual void update(e_output_user_index output_user_index, float dt, s_observer_command * result) = 0;
    virtual long get_target() const;
    virtual void set_target(long object_index);
    virtual void set_position(real_point3d const * position);
    virtual void set_forward(vector3d const * forward);
    virtual void set_roll(float roll);
    virtual void enable_orientation(bool enabled);
    virtual void enable_movement(bool enabled);
    virtual void enable_roll(bool enabled);
    virtual bool should_draw_reticule() const;
    virtual bool should_apply_player_effects() const;
    virtual long get_camera_hidden_object_index(e_output_user_index output_user_index) const;
    virtual void handle_deleted_player(long player_index);
    virtual void handle_deleted_object(long object_index);
    virtual void assemble_screen_effects(c_global_screen_effect_state * screen_effect_state);

    void pre_update();
    void post_update(s_observer_command * result);
    void set_next_move_instantly();

protected:
    long m_target_object_index; // 0x4

private:
    c_flags_no_init<e_base_camera_flags, long, k_number_of_base_camera_flags> m_base_camera_flags; // 0x8 (class type verified by the implicit c_camera::operator= in authored_camera.obj)
    long m_move_instant_ticks; // 0xC
};
static_assert(sizeof(c_camera) == 0x10, "c_camera");

/* ---------- prototypes */

enum e_controller_index;

bool camera_input_inhibited(e_controller_index controller_index);

/* ---------- globals */

extern char const * global_camera_mode_names[k_number_of_camera_modes];

/* ---------- public code */

#endif // __CAMERA_H__

