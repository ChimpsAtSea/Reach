#pragma once
#ifndef __GAME_PLAYER_GLOBALS_H__
#define __GAME_PLAYER_GLOBALS_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"
#include "omaha\math\function_definitions.h"
#include "omaha\math\real_math.h"
#include "omaha\tag_files\tag_groups.h"

/* ---------- constants */

enum e_player_character_type
{
    _player_character_type_spartan = 0,
    _player_character_type_elite,
    _player_character_type_monitor,

    k_player_character_type_count
};

/* ---------- definitions */

// player_information_block (Reach tag layout)
struct s_game_globals_player_information
{
    real walking_speed; // 0x0
    real run_forward; // 0x4
    real run_backward; // 0x8
    real run_sideways; // 0xC
    real run_acceleration; // 0x10
    real sneak_forward; // 0x14
    real sneak_backward; // 0x18
    real sneak_sideways; // 0x1C
    real sneak_acceleration; // 0x20
    real airborne_acceleration; // 0x24
    real_point3d grenade_origin; // 0x28
    s_scalar_function_named_struct grenade_aiming; // 0x34
    real_bounds first_person_idle_time; // 0x48
    real first_person_skip_fraction; // 0x50
    s_tag_reference coop_countdown_sound; // 0x54
    s_tag_reference coop_respawn_sound; // 0x64
    s_tag_reference coop_respawn_effect; // 0x74
    s_tag_reference hologram_death_effect; // 0x84
    long binoculars_zoom_count; // 0x94
    real_bounds binoculars_zoom_range; // 0x98
    s_tag_reference night_vision_sounds[2]; // 0xA0 on, off
    real fire_team_objective_range; // 0xC0
    real fire_team_sandbox_range; // 0xC4
    real fire_team_cone_angle; // 0xC8
    real sprint_seconds_to_start; // 0xCC
    real sprint_seconds_to_full_speed; // 0xD0
    real sprint_decay_rate; // 0xD4
    real sprint_full_speed_multiplier; // 0xD8
    real sprint_turn_multiplier; // 0xDC
    real sprint_max_look_yaw_velocity; // 0xE0
    real sprint_max_look_pitch_velocity; // 0xE4
    real sprint_minimum_velocity; // 0xE8
    real sprint_window_length; // 0xEC
    long sprint_animation_stance; // 0xF0
};
static_assert(sizeof(s_game_globals_player_information) == 0xF4, "s_game_globals_player_information");

// player_representation_block (Reach tag layout)
struct s_game_globals_player_representation
{
    unsigned char flags; // 0x0
    unsigned char pad[3]; // 0x1
    s_tag_reference chud; // 0x4
    s_tag_reference first_person_hands; // 0x14
    s_tag_reference first_person_body; // 0x24
    s_tag_reference third_person_unit; // 0x34
    long third_person_variant; // 0x44
    s_tag_reference binoculars_zoom_in_sound; // 0x48
    s_tag_reference binoculars_zoom_out_sound; // 0x58
    long player_information_index; // 0x68
};
static_assert(sizeof(s_game_globals_player_representation) == 0x6C, "s_game_globals_player_representation");

/* ---------- prototypes */

extern char * format_player_character_block_names(long tag_index, __int64 tag_group, s_tag_block * block, long block_index, char * buffer, long buffer_length);
extern void prune_player_information(s_game_globals_player_information * player_information);
extern void prune_player_representation(s_game_globals_player_representation * player_representation);

/* ---------- globals */

/* ---------- public code */

#endif // __GAME_PLAYER_GLOBALS_H__

