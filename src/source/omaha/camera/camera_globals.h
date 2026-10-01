#pragma once
#ifndef __CAMERA_GLOBALS_H__
#define __CAMERA_GLOBALS_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"
#include "omaha\camera\observer.h"

/* ---------- constants */

/* ---------- definitions */

// layout from camera_block (haloreach_tagtest_x360.json, starts at s_camera_block+0x24); offsets verified in camera_globals_initialize_from_tags
struct s_camera_globals
{
    float camera_field_of_view_scale; // 0x0
    float camera_yaw_scale; // 0x4
    float camera_pitch_scale; // 0x8
    float camera_forward_scale; // 0xC
    float camera_side_scale; // 0x10
    float camera_up_scale; // 0x14
    float dead_camera_transition_time; // 0x18
    float dead_camera_falling_death_transition_time; // 0x1C
    float dead_camera_initial_distance; // 0x20
    float dead_camera_final_distance; // 0x24
    float dead_camera_z_offset; // 0x28
    float dead_camera_maximum_elevation; // 0x2C
    float dead_camera_movement_delay; // 0x30
    float dead_camera_time_to_auto_switch_to_orbiting; // 0x34
    float dead_camera_ignore_stick_time; // 0x38
    float dead_camera_ignore_button_time; // 0x3C
    float dead_camera_minimum_falling_velocity; // 0x40
    float flying_camera_maximum_boost_speed; // 0x44
    float flying_camera_time_to_maximum_boost; // 0x48
    short flying_camera_boost_transition_function; // 0x4C
    short pad; // 0x4E
    float flying_camera_zoomed_field_of_view; // 0x50
    float flying_camera_zoomed_look_speed_scale; // 0x54
    float flying_camera_bounding_sphere_radius; // 0x58
    float flying_camera_movement_delay; // 0x5C
    float flying_camera_zoom_transition_time; // 0x60
    float flying_camera_vertical_time_to_max_speed; // 0x64
    short flying_camera_vertical_transition_function; // 0x68
    short pad1; // 0x6A
    float survival_switch_time; // 0x6C
    float orbiting_camera_minimum_distance; // 0x70
    float orbiting_camera_maximum_distance; // 0x74
    float orbiting_camera_movement_delay; // 0x78
    float orbiting_camera_z_offset; // 0x7C
    float orbiting_camera_minimum_elevation; // 0x80
    float orbiting_camera_maximum_elevation; // 0x84
    float saved_film_director_max_playback_speed; // 0x88
    float saved_film_rewind_fade_out_time; // 0x8C
    float saved_film_rewind_fade_in_time; // 0x90
    float game_director_enter_vehicle_transition_time; // 0x94
    float game_director_exit_vehicle_transition_time; // 0x98
    s_observer_parameter_block_unknownB8 observer_parameters; // 0x9C camera obstruction (camera_obstruction_struct); struct-copied into s_observer_command::unknownB8 (c_sandbox_camera::update)
};
static_assert(sizeof(s_camera_globals) == 0xB4, "s_camera_globals");

/* ---------- prototypes */

void camera_globals_reinitialize_from_tags();
void camera_globals_initialize_from_tags();

/* ---------- globals */

extern float g_objective_auto_switch_to_dead_cam_delay;
extern bool g_flying_camera_has_collision;
extern bool g_editor_director_mouse_wheel_speed_enabled;
extern float g_director_camera_speed_scale;
extern s_camera_globals g_camera_globals;
extern bool g_flying_camera_use_old_controls;

/* ---------- public code */

#endif // __CAMERA_GLOBALS_H__

