#pragma once
#ifndef __GAME_CONTROLLER_GLOBALS_H__
#define __GAME_CONTROLLER_GLOBALS_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"
#include "omaha\math\real_math.h"
#include "omaha\tag_files\tag_groups.h"

/* ---------- constants */

/* ---------- definitions */

// Reach layout from gamepad_stick_info_block (tag json), size 0x28
struct s_gamepad_stick_settings
{
    char input_shape; // 0x0
    char pad0[3]; // 0x1
    real peg_threshold; // 0x4
    real_point2d pegged_time; // 0x8
    real_point2d pegged_scale; // 0x10
    real peg_max_angular_velocity; // 0x18
    s_tag_block input_mapping_function; // 0x1C
};
static_assert(sizeof(s_gamepad_stick_settings) == 0x28, "s_gamepad_stick_settings");

// Reach layout from player_control_block (tag json), size 0x8C
struct s_game_globals_player_control
{
    s_tag_block move_stick_info; // 0x0
    s_tag_block look_stick_info; // 0xC
    real magnetism_friction; // 0x18
    real magnetism_adhesion; // 0x1C
    real inconsequential_target_scale; // 0x20
    real_point2d crosshair_location; // 0x24
    real pegged_magnitude; // 0x2C
    real pegged_angular_threshold; // 0x30
    real fireteam_command_mode_duration; // 0x34
    real look_autolevelling_scale; // 0x38
    real gravity_scale; // 0x3C
    char pad0[2]; // 0x40
    short minimum_autolevelling_ticks; // 0x42
    real minimum_angle_for_vehicle_flipping; // 0x44
    real minimum_action_hold_time; // 0x48
    real pegged_zoom_supression_threshold; // 0x4C
    long auto_unzoom_ticks; // 0x50
    real minimum_vertical_velocity; // 0x54
    real cooldown_time; // 0x58
    real_point2d double_jump_velocity; // 0x5C
    real_point2d triple_jump_velocity; // 0x64
    real throw_channel_width; // 0x6C
    real throw_peg_threshold; // 0x70
    real throw_centered_min_time; // 0x74
    real throw_drawing_max_time; // 0x78
    real throw_drawn_max_time; // 0x7C
    real throw_throwing_max_time; // 0x80
    real flick_peg_jump_max_time; // 0x84
    real double_tap_interval_time; // 0x88
};
static_assert(sizeof(s_game_globals_player_control) == 0x8C, "s_game_globals_player_control");

/* ---------- prototypes */

extern bool postprocess_gamepad_stick_info_block(long element_index, void * element, bool for_editor);
extern bool postprocess_player_control_block(long element_index, void * element, bool for_editor);

/* ---------- globals */

/* ---------- public code */

#endif // __GAME_CONTROLLER_GLOBALS_H__

