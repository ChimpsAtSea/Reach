#pragma once
#ifndef __GAME_ENGINE_LOADOUT_TRAITS_H__
#define __GAME_ENGINE_LOADOUT_TRAITS_H__

/* ---------- headers */

#include "foundation\baselib\datatypes\static_array.h"
#include "omaha\game\loadout_definition.h"
#include "omaha\memory\static_arrays.h"

/* ---------- constants */

/* ---------- definitions */

class c_loadout_traits
{
public:
    enum e_flags
    {
        _enabled_bit = 0,

        k_flags_count
    };

    void set(s_loadout_tag_definition const * loadout_definition);

    long get_name(void) const;
    char get_name_absolute_index(void) const;
    void set_name(long name);
    void set_name_absolute_index(char name_absolute_index);

    long get_initial_primary_weapon(void) const;
    char get_initial_primary_weapon_absolute_index(void) const;
    void set_initial_primary_weapon(long initial_primary_weapon);
    void set_initial_primary_weapon_absolute_index(char initial_primary_weapon_absolute_index);

    long get_initial_secondary_weapon(void) const;
    char get_initial_secondary_weapon_absolute_index(void) const;
    void set_initial_secondary_weapon(long initial_secondary_weapon);
    void set_initial_secondary_weapon_absolute_index(char initial_secondary_weapon_absolute_index);

    long get_initial_equipment(void) const;
    char get_initial_equipment_absolute_index(void) const;
    void set_initial_equipment(long initial_equipment);
    void set_initial_equipment_absolute_index(char initial_equipment_absolute_index);

protected:
    c_flags_no_init<e_flags, unsigned char, k_flags_count> m_flags; // 0x0
    char m_name_absolute_index; // 0x1
    char m_initial_primary_weapon_absolute_index; // 0x2
    char m_initial_secondary_weapon_absolute_index; // 0x3
    char m_initial_equipment_absolute_index; // 0x4
    c_enum_no_init<e_grenade_count_setting, unsigned char, _grenade_count_setting_unchanged, k_grenade_count_setting_count> m_initial_grenade_count; // 0x5
};
static_assert(sizeof(c_loadout_traits) == 0x6, "c_loadout_traits");

class c_loadout_palette_traits
{
public:
    void set(s_loadout_palette_tag_definition const * loadout_palette_definition);

protected:
    s_static_array<c_loadout_traits, k_maximum_loadouts_per_palette> m_loadouts; // 0x0
};
static_assert(sizeof(c_loadout_palette_traits) == 0x1E, "c_loadout_palette_traits");

class c_game_engine_loadout_traits
{
public:
    void set(s_game_engine_loadout_definition const * loadout_traits_definition);

protected:
    c_flags_no_init<s_game_engine_loadout_definition::e_flags, unsigned char, s_game_engine_loadout_definition::k_flags_count> m_flags; // 0x0
    s_static_array<c_loadout_palette_traits, k_maximum_game_engine_loadout_palettes> m_loadout_palettes; // 0x1
};
static_assert(sizeof(c_game_engine_loadout_traits) == 0xB5, "c_game_engine_loadout_traits");

/* ---------- prototypes */

s_loadout_palette_tag_definition const * loadout_palette_get_by_name(long palette_name);

/* ---------- globals */

/* ---------- public code */

#endif // __GAME_ENGINE_LOADOUT_TRAITS_H__

