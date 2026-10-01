#pragma once
#ifndef __LOADOUT_DEFINITION_H__
#define __LOADOUT_DEFINITION_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"
#include "omaha\game\game_engine_player_traits_structures.h"
#include "omaha\memory\static_arrays.h"
#include "omaha\tag_files\tag_groups.h"

/* ---------- constants */

enum
{
    k_maximum_loadouts = 128,
    k_maximum_loadout_palettes = 64,
    k_maximum_loadouts_per_palette = 5,
    k_maximum_loadout_names = 128,
    k_maximum_game_engine_loadout_palettes = 6,
};

/* ---------- definitions */

struct s_loadout_tag_definition
{
    long loadout_name; // 0x0 string_id
    long initial_primary_weapon; // 0x4 string_id
    long initial_secondary_weapon; // 0x8 string_id
    long initial_equipment; // 0xC string_id
    c_enum_no_init<e_grenade_count_setting, unsigned char, _grenade_count_setting_unchanged, k_grenade_count_setting_count> initial_grenade_count; // 0x10
    unsigned char pad[3]; // 0x11
};
static_assert(sizeof(s_loadout_tag_definition) == 0x14, "s_loadout_tag_definition");

struct s_loadout_tag_reference
{
    short loadout_index; // 0x0 short block index into s_loadout_globals_tag_definition::loadouts
    unsigned char pad[2]; // 0x2
};
static_assert(sizeof(s_loadout_tag_reference) == 0x4, "s_loadout_tag_reference");

struct s_loadout_name_tag_definition
{
    long display_name; // 0x0 string_id
};
static_assert(sizeof(s_loadout_name_tag_definition) == 0x4, "s_loadout_name_tag_definition");

struct s_loadout_palette_tag_definition
{
    long palette_name; // 0x0 string_id
    s_tag_block loadouts; // 0x4 s_loadout_tag_reference
};
static_assert(sizeof(s_loadout_palette_tag_definition) == 0x10, "s_loadout_palette_tag_definition");

struct s_loadout_globals_tag_definition
{
    s_tag_block loadouts; // 0x0 s_loadout_tag_definition
    s_tag_block loadout_palettes; // 0xC s_loadout_palette_tag_definition
    s_tag_block loadout_names; // 0x18 s_loadout_name_tag_definition
};
static_assert(sizeof(s_loadout_globals_tag_definition) == 0x24, "s_loadout_globals_tag_definition");

struct s_loadout_palette_entry_definition
{
    long palette_name; // 0x0 string_id
};
static_assert(sizeof(s_loadout_palette_entry_definition) == 0x4, "s_loadout_palette_entry_definition");

struct s_game_engine_loadout_definition
{
    enum e_flags
    {
        _spartan_loadouts_enabled_bit = 0,
        _elite_loadouts_enabled_bit,

        k_flags_count
    };

    c_flags_no_init<e_flags, unsigned char, k_flags_count> flags; // 0x0
    unsigned char pad[3]; // 0x1
    s_tag_block loadout_palettes; // 0x4 s_loadout_palette_entry_definition
};
static_assert(sizeof(s_game_engine_loadout_definition) == 0x10, "s_game_engine_loadout_definition");

/* ---------- prototypes */

long loadout_tag_get_loadout_name(long loadout_name_absolute_index);
long loadout_tag_find_loadout_name_absolute_index(long loadout_name);
s_loadout_globals_tag_definition const * try_and_get_loadout_globals(void);

/* ---------- globals */

/* ---------- public code */

#endif // __LOADOUT_DEFINITION_H__

