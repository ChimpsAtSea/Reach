#pragma once
#ifndef __GAME_GLOBALS_H__
#define __GAME_GLOBALS_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"
#include "omaha\math\color_math.h"
#include "omaha\tag_files\tag_groups.h"
#include "omaha\memory\static_arrays.h"
#include "omaha\math\function_definitions.h"
#include "omaha\camera\camera_globals.h"

/* ---------- constants */

enum
{
    GAME_GLOBALS_DEFINITION_TAG = 'matg',
};

enum e_campaign_difficulty_level
{
    _campaign_difficulty_level_easy = 0,
    _campaign_difficulty_level_normal,
    _campaign_difficulty_level_hard,
    _campaign_difficulty_level_impossible,

    k_campaign_difficulty_levels_count,
    k_campaign_difficulty_level_bits = 2,
    k_campaign_difficulty_level_none = -1
};

enum e_player_color_index
{
    _player_color_first = 0,

    k_player_color_index_count = 32,
    _player_color_none = -1,
    _player_color_index_min_value = _player_color_none
};

enum e_player_model_choice
{
    _player_model_choice_first = 0,

    k_player_model_choice_count = 2
};

/* ---------- definitions */

typedef c_enum_no_init<e_player_color_index, char, _player_color_index_min_value, k_player_color_index_count> c_player_color_index;
typedef c_enum_no_init<e_player_model_choice, char, _player_model_choice_first, k_player_model_choice_count> c_player_model_choice;

// $TODO: only the leading fields are reversed; layout from camera_block (tag json), size 0xD8
struct s_camera_block
{
    s_tag_reference default_unit_camera_track; // 0x0
    c_function_definition pitch_to_vertical_offset; // 0x10 (evaluated directly by c_sandbox_camera::update)
    s_camera_globals camera_globals; // 0x24 (copied over g_camera_globals by camera_globals_initialize_from_tags)
};
static_assert(sizeof(s_camera_block) == 0xD8, "s_camera_block");

// Reach layout from globals_struct_definition (tag json), size 0x714
struct s_game_globals
{
    char unused0[0xAC]; // 0x0
    long language; // 0xAC
    s_tag_block havok_cleanup_resources; // 0xB0
    s_tag_block sound_globals; // 0xBC
    s_tag_block ai_globals; // 0xC8
    s_tag_reference ai_globals_ref; // 0xD4
    s_tag_block damage_table; // 0xE4
    s_tag_reference load_screen_globals_ref; // 0xF0
    s_tag_block sounds; // 0x100
    s_tag_block camera; // 0x10C
    s_tag_block controller_input; // 0x118
    s_tag_block player_control; // 0x124
    s_tag_block default_player_traits; // 0x130
    s_tag_block difficulty; // 0x13C
    s_tag_block coop_difficulty; // 0x148
    s_tag_block grenades; // 0x154
    s_tag_block soft_ceilings; // 0x160
    s_tag_block null_block; // 0x16C
    s_tag_block interface_tags; // 0x178
    s_tag_block weapon_list; // 0x184
    s_tag_block cheat_powerups; // 0x190
    s_tag_block player_information; // 0x19C
    s_tag_block player_representation; // 0x1A8
    s_tag_block damage; // 0x1B4
    s_tag_block shield_boost; // 0x1C0
    s_tag_block materials; // 0x1CC
    s_tag_block profile_colors; // 0x1D8
    s_tag_block emblem_colors; // 0x1E4
    s_tag_block visor_colors; // 0x1F0
    real_rgb_color elite_specular_tertiary_color; // 0x1FC
    real_rgb_color elite_specular_quaternary_color; // 0x208
    s_tag_block forge_colors; // 0x214
    s_tag_reference game_engine_globals; // 0x220
    s_tag_reference multiplayer_globals; // 0x230
    s_tag_reference survival_mode_globals; // 0x240
    s_tag_reference multiplayer_object_type_list; // 0x250
    s_tag_block cinematics_globals; // 0x260
    s_tag_block campaign_metagame_block; // 0x26C
    s_tag_reference game_medal_globals; // 0x278
    char language_packs[12][0x44]; // 0x288
    s_tag_reference rasterizer_globals_ref; // 0x5B8
    s_tag_reference default_camera_fx_settings; // 0x5C8
    s_tag_reference default_wind_settings; // 0x5D8
    s_tag_reference weather_globals; // 0x5E8
    s_tag_reference collision_damage_effect; // 0x5F8
    s_tag_reference collision_damage; // 0x608
    long global_water_material; // 0x618
    long global_air_material; // 0x61C
    short global_water_material_type; // 0x620
    short global_air_material_type; // 0x622
    s_tag_reference effect_globals; // 0x624
    s_tag_reference havok_collision_filter; // 0x634
    s_tag_reference default_item_grounded_friction; // 0x644
    s_tag_block active_camo; // 0x654
    s_tag_reference incident_global_properties; // 0x660
    s_tag_reference player_grade_globals; // 0x670
    s_tag_reference player_model_customization_globals; // 0x680
    s_tag_reference loadout_globals; // 0x690
    s_tag_reference challenge_globals; // 0x6A0
    s_tag_reference game_completion_rewards_globals; // 0x6B0
    s_tag_reference game_achievements; // 0x6C0
    s_tag_reference game_avatar_awards; // 0x6D0
    s_tag_reference game_performance_throttles_default; // 0x6E0
    s_tag_block garbage_collection; // 0x6F0
    s_tag_block camera_impulse; // 0x6FC
    s_tag_block runtime_materials; // 0x708
};
static_assert(sizeof(s_game_globals) == 0x714, "s_game_globals");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __GAME_GLOBALS_H__

