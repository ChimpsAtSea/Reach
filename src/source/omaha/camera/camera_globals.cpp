#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\camera\\camera_globals.cpp"
/* ---------- headers */

#include "omaha\camera\camera_globals.h"
#include "omaha\game\game_globals.h"
#include "omaha\game\game_time.h"
#include "omaha\scenario\scenario.h"
#include "omaha\tag_files\tag_groups.h"
#include "core\corelib\cseries\cseries_macros.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

float g_objective_auto_switch_to_dead_cam_delay = -1.0f;
bool g_flying_camera_has_collision = true;
bool g_editor_director_mouse_wheel_speed_enabled = true;
float g_director_camera_speed_scale = 1.0f;
s_camera_globals g_camera_globals;
bool g_flying_camera_use_old_controls;

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// float g_objective_auto_switch_to_dead_cam_delay; // "?g_objective_auto_switch_to_dead_cam_delay@@3MA"
// bool g_flying_camera_has_collision; // "?g_flying_camera_has_collision@@3_NA"
// bool g_editor_director_mouse_wheel_speed_enabled; // "?g_editor_director_mouse_wheel_speed_enabled@@3_NA"
// float g_director_camera_speed_scale; // "?g_director_camera_speed_scale@@3MA"
// struct s_tag_struct_definition camera_block_struct_definition; // "?camera_block_struct_definition@@3Us_tag_struct_definition@@A"
// struct s_tag_block_definition camera_block; // "?camera_block@@3Us_tag_block_definition@@A"
// struct s_camera_globals g_camera_globals; // "?g_camera_globals@@3Us_camera_globals@@A"
// bool g_flying_camera_use_old_controls; // "?g_flying_camera_use_old_controls@@3_NA"

// void camera_globals_reinitialize_from_tags(void);
// void camera_globals_initialize_from_tags(void);

void camera_globals_reinitialize_from_tags()
{
    mangled_ppc("?camera_globals_reinitialize_from_tags@@YAXXZ");

    long reinitialize_interval_seconds = 10;
    if (game_time_get() % (reinitialize_interval_seconds * game_tick_rate()) == 0)
    {
        camera_globals_initialize_from_tags();
    }
};

void camera_globals_initialize_from_tags()
{
    mangled_ppc("?camera_globals_initialize_from_tags@@YAXXZ");

    static s_camera_globals last_globals = g_camera_globals;

    s_camera_globals const * tag_globals = &static_cast<s_camera_block *>(tag_block_get_element_with_size(&scenario_get_game_globals()->camera, 0, sizeof(s_camera_block)))->camera_globals;

    if (g_camera_globals.camera_field_of_view_scale == last_globals.camera_field_of_view_scale)
    {
        g_camera_globals.camera_field_of_view_scale = tag_globals->camera_field_of_view_scale;
    }
    if (g_camera_globals.camera_yaw_scale == last_globals.camera_yaw_scale)
    {
        g_camera_globals.camera_yaw_scale = tag_globals->camera_yaw_scale;
    }
    if (g_camera_globals.camera_pitch_scale == last_globals.camera_pitch_scale)
    {
        g_camera_globals.camera_pitch_scale = tag_globals->camera_pitch_scale;
    }
    if (g_camera_globals.camera_forward_scale == last_globals.camera_forward_scale)
    {
        g_camera_globals.camera_forward_scale = tag_globals->camera_forward_scale;
    }
    if (g_camera_globals.camera_side_scale == last_globals.camera_side_scale)
    {
        g_camera_globals.camera_side_scale = tag_globals->camera_side_scale;
    }
    if (g_camera_globals.camera_up_scale == last_globals.camera_up_scale)
    {
        g_camera_globals.camera_up_scale = tag_globals->camera_up_scale;
    }
    if (g_camera_globals.dead_camera_transition_time == last_globals.dead_camera_transition_time)
    {
        g_camera_globals.dead_camera_transition_time = tag_globals->dead_camera_transition_time;
    }
    if (g_camera_globals.dead_camera_falling_death_transition_time == last_globals.dead_camera_falling_death_transition_time)
    {
        g_camera_globals.dead_camera_falling_death_transition_time = tag_globals->dead_camera_falling_death_transition_time;
    }
    if (g_camera_globals.dead_camera_initial_distance == last_globals.dead_camera_initial_distance)
    {
        g_camera_globals.dead_camera_initial_distance = tag_globals->dead_camera_initial_distance;
    }
    if (g_camera_globals.dead_camera_final_distance == last_globals.dead_camera_final_distance)
    {
        g_camera_globals.dead_camera_final_distance = tag_globals->dead_camera_final_distance;
    }
    if (g_camera_globals.dead_camera_z_offset == last_globals.dead_camera_z_offset)
    {
        g_camera_globals.dead_camera_z_offset = tag_globals->dead_camera_z_offset;
    }
    if (g_camera_globals.dead_camera_maximum_elevation == last_globals.dead_camera_maximum_elevation)
    {
        g_camera_globals.dead_camera_maximum_elevation = tag_globals->dead_camera_maximum_elevation;
    }
    if (g_camera_globals.dead_camera_movement_delay == last_globals.dead_camera_movement_delay)
    {
        g_camera_globals.dead_camera_movement_delay = tag_globals->dead_camera_movement_delay;
    }
    if (g_camera_globals.dead_camera_time_to_auto_switch_to_orbiting == last_globals.dead_camera_time_to_auto_switch_to_orbiting)
    {
        g_camera_globals.dead_camera_time_to_auto_switch_to_orbiting = tag_globals->dead_camera_time_to_auto_switch_to_orbiting;
    }
    if (g_camera_globals.dead_camera_ignore_stick_time == last_globals.dead_camera_ignore_stick_time)
    {
        g_camera_globals.dead_camera_ignore_stick_time = tag_globals->dead_camera_ignore_stick_time;
    }
    if (g_camera_globals.dead_camera_ignore_button_time == last_globals.dead_camera_ignore_button_time)
    {
        g_camera_globals.dead_camera_ignore_button_time = tag_globals->dead_camera_ignore_button_time;
    }
    if (g_objective_auto_switch_to_dead_cam_delay >= 0.0f)
    {
        g_camera_globals.dead_camera_time_to_auto_switch_to_orbiting = g_objective_auto_switch_to_dead_cam_delay;
    }
    if (g_camera_globals.dead_camera_minimum_falling_velocity == last_globals.dead_camera_minimum_falling_velocity)
    {
        g_camera_globals.dead_camera_minimum_falling_velocity = tag_globals->dead_camera_minimum_falling_velocity;
    }
    if (g_camera_globals.flying_camera_maximum_boost_speed == last_globals.flying_camera_maximum_boost_speed)
    {
        g_camera_globals.flying_camera_maximum_boost_speed = tag_globals->flying_camera_maximum_boost_speed;
    }
    if (g_camera_globals.flying_camera_time_to_maximum_boost == last_globals.flying_camera_time_to_maximum_boost)
    {
        g_camera_globals.flying_camera_time_to_maximum_boost = tag_globals->flying_camera_time_to_maximum_boost;
    }
    if (g_camera_globals.flying_camera_boost_transition_function == last_globals.flying_camera_boost_transition_function)
    {
        g_camera_globals.flying_camera_boost_transition_function = tag_globals->flying_camera_boost_transition_function;
    }
    if (g_camera_globals.flying_camera_zoomed_field_of_view == last_globals.flying_camera_zoomed_field_of_view)
    {
        g_camera_globals.flying_camera_zoomed_field_of_view = tag_globals->flying_camera_zoomed_field_of_view;
    }
    if (g_camera_globals.flying_camera_zoomed_look_speed_scale == last_globals.flying_camera_zoomed_look_speed_scale)
    {
        g_camera_globals.flying_camera_zoomed_look_speed_scale = tag_globals->flying_camera_zoomed_look_speed_scale;
    }
    if (g_camera_globals.flying_camera_bounding_sphere_radius == last_globals.flying_camera_bounding_sphere_radius)
    {
        g_camera_globals.flying_camera_bounding_sphere_radius = tag_globals->flying_camera_bounding_sphere_radius;
    }
    if (g_camera_globals.flying_camera_movement_delay == last_globals.flying_camera_movement_delay)
    {
        g_camera_globals.flying_camera_movement_delay = tag_globals->flying_camera_movement_delay;
    }
    if (g_camera_globals.flying_camera_zoom_transition_time == last_globals.flying_camera_zoom_transition_time)
    {
        g_camera_globals.flying_camera_zoom_transition_time = tag_globals->flying_camera_zoom_transition_time;
    }
    if (g_camera_globals.flying_camera_vertical_time_to_max_speed == last_globals.flying_camera_vertical_time_to_max_speed)
    {
        g_camera_globals.flying_camera_vertical_time_to_max_speed = tag_globals->flying_camera_vertical_time_to_max_speed;
    }
    // the target checks flying_camera_boost_transition_function a second time here instead of flying_camera_vertical_transition_function
    if (g_camera_globals.flying_camera_boost_transition_function == last_globals.flying_camera_boost_transition_function)
    {
        g_camera_globals.flying_camera_boost_transition_function = tag_globals->flying_camera_boost_transition_function;
    }
    if (g_camera_globals.survival_switch_time == last_globals.survival_switch_time)
    {
        g_camera_globals.survival_switch_time = tag_globals->survival_switch_time;
    }
    if (g_camera_globals.orbiting_camera_minimum_distance == last_globals.orbiting_camera_minimum_distance)
    {
        g_camera_globals.orbiting_camera_minimum_distance = tag_globals->orbiting_camera_minimum_distance;
    }
    if (g_camera_globals.orbiting_camera_maximum_distance == last_globals.orbiting_camera_maximum_distance)
    {
        g_camera_globals.orbiting_camera_maximum_distance = tag_globals->orbiting_camera_maximum_distance;
    }
    if (g_camera_globals.orbiting_camera_movement_delay == last_globals.orbiting_camera_movement_delay)
    {
        g_camera_globals.orbiting_camera_movement_delay = tag_globals->orbiting_camera_movement_delay;
    }
    if (g_camera_globals.orbiting_camera_z_offset == last_globals.orbiting_camera_z_offset)
    {
        g_camera_globals.orbiting_camera_z_offset = tag_globals->orbiting_camera_z_offset;
    }
    if (g_camera_globals.orbiting_camera_minimum_elevation == last_globals.orbiting_camera_minimum_elevation)
    {
        g_camera_globals.orbiting_camera_minimum_elevation = tag_globals->orbiting_camera_minimum_elevation;
    }
    if (g_camera_globals.orbiting_camera_maximum_elevation == last_globals.orbiting_camera_maximum_elevation)
    {
        g_camera_globals.orbiting_camera_maximum_elevation = tag_globals->orbiting_camera_maximum_elevation;
    }
    if (g_camera_globals.saved_film_director_max_playback_speed == last_globals.saved_film_director_max_playback_speed)
    {
        g_camera_globals.saved_film_director_max_playback_speed = tag_globals->saved_film_director_max_playback_speed;
    }
    if (g_camera_globals.saved_film_rewind_fade_in_time == last_globals.saved_film_rewind_fade_in_time)
    {
        g_camera_globals.saved_film_rewind_fade_in_time = tag_globals->saved_film_rewind_fade_in_time;
    }
    if (g_camera_globals.saved_film_rewind_fade_out_time == last_globals.saved_film_rewind_fade_out_time)
    {
        g_camera_globals.saved_film_rewind_fade_out_time = tag_globals->saved_film_rewind_fade_out_time;
    }
    if (g_camera_globals.game_director_enter_vehicle_transition_time == last_globals.game_director_enter_vehicle_transition_time)
    {
        g_camera_globals.game_director_enter_vehicle_transition_time = tag_globals->game_director_enter_vehicle_transition_time;
    }
    if (g_camera_globals.game_director_exit_vehicle_transition_time == last_globals.game_director_exit_vehicle_transition_time)
    {
        g_camera_globals.game_director_exit_vehicle_transition_time = tag_globals->game_director_exit_vehicle_transition_time;
    }
    if (g_camera_globals.observer_parameters.parameters[0] == last_globals.observer_parameters.parameters[0])
    {
        g_camera_globals.observer_parameters.parameters[0] = tag_globals->observer_parameters.parameters[0];
    }
    if (g_camera_globals.observer_parameters.parameters[1] == last_globals.observer_parameters.parameters[1])
    {
        g_camera_globals.observer_parameters.parameters[1] = tag_globals->observer_parameters.parameters[1];
    }
    if (g_camera_globals.observer_parameters.parameters[2] == last_globals.observer_parameters.parameters[2])
    {
        g_camera_globals.observer_parameters.parameters[2] = tag_globals->observer_parameters.parameters[2];
    }
    if (g_camera_globals.observer_parameters.parameters[3] == last_globals.observer_parameters.parameters[3])
    {
        g_camera_globals.observer_parameters.parameters[3] = tag_globals->observer_parameters.parameters[3];
    }
    if (g_camera_globals.observer_parameters.parameters[4] == last_globals.observer_parameters.parameters[4])
    {
        g_camera_globals.observer_parameters.parameters[4] = tag_globals->observer_parameters.parameters[4];
    }
    if (g_camera_globals.observer_parameters.parameters[5] == last_globals.observer_parameters.parameters[5])
    {
        g_camera_globals.observer_parameters.parameters[5] = tag_globals->observer_parameters.parameters[5];
    }

    last_globals = *tag_globals;
};

