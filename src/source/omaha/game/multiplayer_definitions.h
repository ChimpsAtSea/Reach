#pragma once
#ifndef __MULTIPLAYER_DEFINITIONS_H__
#define __MULTIPLAYER_DEFINITIONS_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"
#include "omaha\math\real_math.h"
#include "omaha\tag_files\tag_groups.h"

/* ---------- constants */

enum
{
    k_multiplayer_globals_definition_tag = 'mulg',
};

enum e_player_respawn_status_string
{
    _voluntary_respawn_control_instructions_string = 0,
    _spawn_allowed_default_respawn_string,
    _spawn_at_player_allowed_looking_at_self_string,
    _spawn_at_player_allowed_looking_at_target_string,
    _spawn_at_player_allowed_looking_at_potential_target_string,
    _spawn_at_territory_allowed_looking_at_target_string,
    _spawn_at_territory_allowed_looking_at_potential_target_string,
    _player_out_of_lives_string,
    _invalid_spawn_target_string,
    _targetted_player_enemies_near_by_string,
    _targetted_player_unfriendly_team_string,
    _targetted_player_is_dead_string,
    _targetted_player_in_combat_shields_string,
    _targetted_player_too_far_from_owned_flag_string,
    _no_available_netpoints_string,
    _netpoint_contested_string,

    k_number_of_respawn_status_strings
};

/* ---------- definitions */

struct s_weapon_spawn_influence
{
    s_tag_reference weapon; // 0x0
    real full_weight_range; // 0x10
    real fall_off_range; // 0x14
    real fall_off_cone_radius; // 0x18
    real weight; // 0x1C
};
static_assert(sizeof(s_weapon_spawn_influence) == 0x20, "s_weapon_spawn_influence");

struct s_vehicle_spawn_influence
{
    s_tag_reference vehicle; // 0x0
    real pill_radius; // 0x10
    real lead_time; // 0x14
    real minimum_velocity; // 0x18
    real weight; // 0x1C
};
static_assert(sizeof(s_vehicle_spawn_influence) == 0x20, "s_vehicle_spawn_influence");

struct s_projectile_spawn_influence
{
    s_tag_reference projectile; // 0x0
    real lead_time; // 0x10
    real collision_cylinder_radius; // 0x14
    real weight; // 0x18
};
static_assert(sizeof(s_projectile_spawn_influence) == 0x1C, "s_projectile_spawn_influence");

struct s_equipment_spawn_influence
{
    s_tag_reference equipment; // 0x0
    real weight; // 0x10
};
static_assert(sizeof(s_equipment_spawn_influence) == 0x14, "s_equipment_spawn_influence");

// $TODO: only the tail (influencers onward) is laid out; layout from multiplayer_constants_block (tag json)
struct s_multiplayer_constants
{
    unsigned char __unknown0[0xC4]; // 0x0
    s_tag_block weapon_influencers; // 0xC4
    s_tag_block vehicle_influencers; // 0xD0
    s_tag_block projectile_influencers; // 0xDC
    s_tag_block equipment_influencers; // 0xE8
    real maximum_random_spawn_bias; // 0xF4
    real teleporter_recharge_time; // 0xF8
    s_tag_reference sandbox_effect; // 0xFC
    long blocked_teleporter_string; // 0x10C
    long respawn_strings[k_number_of_respawn_status_strings]; // 0x110
};
static_assert(sizeof(s_multiplayer_constants) == 0x150, "s_multiplayer_constants");

struct s_multiplayer_globals_definition
{
    s_tag_block universal; // 0x0
    s_tag_block runtime; // 0xC
};
static_assert(sizeof(s_multiplayer_globals_definition) == 0x18, "s_multiplayer_globals_definition");

// layout from multiplayer_universal_block (tag json)
struct s_multiplayer_universal_globals_definition
{
    s_tag_reference random_player_names; // 0x0
    s_tag_reference team_names; // 0x10
    s_tag_block team_colors; // 0x20
    s_tag_reference multiplayer_text; // 0x2C
    s_tag_reference sandbox_text; // 0x3C
    s_tag_reference sandbox_object_properties_values; // 0x4C
};
static_assert(sizeof(s_multiplayer_universal_globals_definition) == 0x5C, "s_multiplayer_universal_globals_definition");

// $TODO: only the fields used so far are named; layout from multiplayer_runtime_block (tag json), size 0x1D4
struct s_multiplayer_runtime_globals_definition
{
    s_tag_reference editor_biped; // 0x0
    s_tag_reference editor_helper; // 0x10
    s_tag_reference flag; // 0x20
    s_tag_reference ball; // 0x30
    s_tag_reference assault_bomb; // 0x40
    s_tag_reference vip_influence_area; // 0x50
    s_tag_reference in_game_text; // 0x60
    s_tag_block sounds; // 0x70
    s_tag_block looping_sounds; // 0x7C
    s_tag_reference megalo_sounds; // 0x88
    s_tag_reference communication_sounds; // 0x98
    long maximum_frag_count; // 0xA8
    long maximum_plasma_count; // 0xAC
    s_tag_block requisition_constants; // 0xB0
    s_tag_block multiplayer_constants; // 0xBC
    s_tag_block state_responses; // 0xC8
    s_tag_reference scoreboard_emblem_bitmap; // 0xD4
    s_tag_reference scoreboard_dead_emblem_bitmap; // 0xE4
    s_tag_reference hill_shader; // 0xF4
    s_tag_reference unused_intro_message; // 0x104
    s_tag_reference sandbox_intro_message; // 0x114
    s_tag_reference custom_intro_message; // 0x124
    s_tag_reference campaign_intro_message; // 0x134
    s_tag_reference survival_intro_message; // 0x144
    s_tag_reference default_biped_simulation_interpolation; // 0x154
    s_tag_reference default_vehicle_simulation_interpolation; // 0x164
    s_tag_reference default_crate_simulation_interpolation; // 0x174
    s_tag_reference default_item_simulation_interpolation; // 0x184
    s_tag_reference default_projectile_simulation_interpolation; // 0x194
    s_tag_reference default_object_simulation_interpolation; // 0x1A4
    s_tag_reference coop_spawning_globals; // 0x1B4
    s_tag_reference megalo_string_id_table; // 0x1C4
};
static_assert(sizeof(s_multiplayer_runtime_globals_definition) == 0x1D4, "s_multiplayer_runtime_globals_definition");

/* ---------- prototypes */

s_multiplayer_runtime_globals_definition * scenario_multiplayer_globals_try_and_get_runtime_data(void);
s_multiplayer_universal_globals_definition * scenario_multiplayer_globals_try_and_get_universal_data(void);
s_multiplayer_universal_globals_definition * multiplayer_globals_try_and_get_universal_data(s_multiplayer_globals_definition const * multiplayer_globals);
void multiplayer_globals_fix_dependent_references(long multiplayer_globals_index, bool unused);

// inline in the target (f i, emitted in game_engine_coop_spawning.obj); body not reversed yet
s_multiplayer_runtime_globals_definition * multiplayer_globals_try_and_get_runtime_data(s_multiplayer_globals_definition const * multiplayer_globals);

/* ---------- globals */

/* ---------- public code */

#endif // __MULTIPLAYER_DEFINITIONS_H__

