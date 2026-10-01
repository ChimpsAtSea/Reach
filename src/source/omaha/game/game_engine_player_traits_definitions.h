#pragma once
#ifndef __GAME_ENGINE_PLAYER_TRAITS_DEFINITIONS_H__
#define __GAME_ENGINE_PLAYER_TRAITS_DEFINITIONS_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"
#include "omaha\tag_files\tag_groups.h"

/* ---------- constants */

/* ---------- definitions */

// player_trait_weapons_block (Reach tag layout)
struct s_player_trait_weapons
{
    char damage_modifier;
    char melee_damage_modifier;
    char recharging_grenades;
    char weapon_pickup;
    char initial_grenade_count;
    char infinite_ammo;
    char equipment_usage_available;
    char drop_equipment_on_death;
    char infinite_equipment_energy;
    char pad[3];
    long initial_primary_weapon;
    long initial_secondary_weapon;
    long initial_equipment;
};
static_assert(sizeof(s_player_trait_weapons) == 0x18, "s_player_trait_weapons");

// game_engine_player_traits_block (Reach tag layout)
struct s_game_engine_player_traits
{
    s_tag_block shield_traits; // 0x0
    s_tag_block weapon_traits; // 0xC
    s_tag_block movement_traits; // 0x18
    s_tag_block appearance_traits; // 0x24
    s_tag_block sensor_traits; // 0x30
};
static_assert(sizeof(s_game_engine_player_traits) == 0x3C, "s_game_engine_player_traits");

// game_engine_player_traits_list_block (Reach tag layout)
struct s_game_engine_player_traits_list_definition
{
    long name; // 0x0
    s_game_engine_player_traits player_traits; // 0x4
};
static_assert(sizeof(s_game_engine_player_traits_list_definition) == 0x40, "s_game_engine_player_traits_list_definition");

/* ---------- prototypes */

extern bool postprocess_player_trait_weapons_block(long block_index, void * element, bool for_editor);

/* ---------- globals */

/* ---------- public code */

#endif // __GAME_ENGINE_PLAYER_TRAITS_DEFINITIONS_H__

