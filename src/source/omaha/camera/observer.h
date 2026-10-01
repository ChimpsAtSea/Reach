#pragma once
#ifndef __OBSERVER_H__
#define __OBSERVER_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"
#include "omaha\math\real_math.h"

/* ---------- constants */

// dynamically initialized in every TU that includes this header (??__Ek_horizontal_field_of_view_min@@YAXXZ)
static float const k_horizontal_field_of_view_min = 1.0f * k_degrees_to_radians;
static float const k_horizontal_field_of_view_max = 150.0f * k_degrees_to_radians;

enum e_observer_command_flags
{
    _observer_command_valid_bit = 0,
    _observer_command_force_under_media_bit,
    _observer_command_force_above_media_bit,
    _observer_command_force_time_bit,
    _observer_command_ignore_obstructions_bit,
    _observer_command_only_collides_with_environment_bit, // new in Reach (name guessed from s_unit_camera flags); verified via animated_trick_camera_setup_collision/setup_fov masks
    _observer_command_has_collision_ignore_objects_bit,
    _observer_command_use_recent_ignore_objects_bit,
    _observer_command_freeze_camera_bit,
    _observer_command_relative_bit,
    _observer_command_variable_up_bit,
    _observer_command_has_safe_position_bit,
    _observer_command_can_modify_fov_bit,
    _observer_command_anticipate_collision_bit,
    _observer_command_collision_free_pill_bit,

    k_observer_command_flags_count
};

// s_observer_command::parameter_flags bits (H3 names; values verified in c_dead_camera::update)
enum e_observer_time_flags
{
    _observer_time_valid_bit = 0,
    _observer_time_force_bit,

    k_observer_time_flags_count
};

// s_observer_command::parameter_flags / parameter_timers indices (H3 names; offsets verified in c_dead_camera::update)
enum e_observer_parameter
{
    _observer_focus_position = 0,
    _observer_focus_offset,
    _observer_view_offset,
    _observer_focus_distance,
    _observer_field_of_view,
    _observer_orientation,

    k_observer_parameters_count
};

/* ---------- definitions */

enum e_output_user_index;

struct s_observer_depth_of_field
{
    long flags; // 0x0
    float near_focal_plane_distance; // 0x4
    float far_focal_plane_distance; // 0x8
    float focal_depth; // 0xC
    float blur_amount; // 0x10
};
static_assert(sizeof(s_observer_depth_of_field) == 0x14, "s_observer_depth_of_field");

// $TODO: 6 per-parameter floats new in Reach, name unknown
struct s_observer_parameter_block_unknownB8
{
    float parameters[6];
};
static_assert(sizeof(s_observer_parameter_block_unknownB8) == 0x18, "s_observer_parameter_block_unknownB8");

struct s_observer_command
{
    unsigned long flags; // 0x0
    union
    {
        struct
        {
            real_point3d focus_position; // 0x4
            vector3d focus_offset; // 0x10
            real_point2d view_offset; // 0x1C
            float focus_distance; // 0x24
            float horizontal_field_of_view; // 0x28
            vector3d forward; // 0x2C
            vector3d up; // 0x38
        };
        float parameters[16]; // 0x4
    };
    vector3d focus_velocity; // 0x44
    real_matrix4x3 focus_space; // 0x50
    long relative_space_identifier; // 0x84
    real_point3d safe_position; // 0x88
    float timer; // 0x94
    long collision_ignore_objects[2]; // 0x98
    long collision_ignore_objects_count; // 0xA0
    real_point3d pill_base; // 0xA4
    float pill_height; // 0xB0
    float pill_width; // 0xB4
    s_observer_parameter_block_unknownB8 unknownB8; // 0xB8 Reach only; struct-copied from g_camera_globals (c_sandbox_camera::update)
    unsigned char parameter_flags[6]; // 0xD0 (Reach target: field_of_view flag at 0xD4)
    float parameter_timers[6]; // 0xD8 (Reach target: field_of_view timer at 0xE8)
    s_observer_depth_of_field depth_of_field; // 0xF0
};
static_assert(sizeof(s_observer_command) == 0x104, "s_observer_command"); // memset size in observer_command_clear

struct s_observer_result
{
    real_point3d position; // 0x0
    unsigned long location; // 0xC $TODO s_location
    vector3d velocity; // 0x10
    vector3d rotation; // 0x1C
    vector3d forward; // 0x28
    vector3d up; // 0x34
    float horizontal_field_of_view; // 0x40
    s_observer_depth_of_field depth_of_field; // 0x44
    float aspect_ratio; // 0x58
    real_point2d view_offset; // 0x5C
    float magic_crosshair_offset; // 0x64
    float vertical_field_of_view; // 0x68
    float field_of_view_scale; // 0x6C
};
static_assert(sizeof(s_observer_result) == 0x70, "s_observer_result");

/* ---------- prototypes */

void observer_initialize_before_saved_game(long game_state_proc_flags);
void observer_initialize_for_saved_game(long game_state_proc_flags);
void observer_initialize_after_load_saved_game(long game_state_proc_flags);
s_observer_result const * observer_get_camera(e_output_user_index output_user_index);
void observer_validate_camera_command(s_observer_command * command);
void observer_apply_focus_offset(real_point3d * position, vector3d const * focus_offset, vector3d const * forward, vector3d const * up);
float observer_suggested_field_of_view();

/* ---------- globals */

/* ---------- public code */

#endif // __OBSERVER_H__

