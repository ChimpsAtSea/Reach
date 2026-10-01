#pragma once
#ifndef __GAME_ENGINE_PLAYER_TRAITS_STRUCTURES_H__
#define __GAME_ENGINE_PLAYER_TRAITS_STRUCTURES_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"

/* ---------- constants */

// enumerator names from the Reach tag string list player_trait_grenade_count_setting
enum e_grenade_count_setting
{
    _grenade_count_setting_unchanged = 0,
    _grenade_count_setting_map_default,
    _grenade_count_setting_none,
    _grenade_count_setting_1_frag,
    _grenade_count_setting_2_frag,
    _grenade_count_setting_3_frag,
    _grenade_count_setting_4_frag,
    _grenade_count_setting_1_plasma,
    _grenade_count_setting_2_plasma,
    _grenade_count_setting_3_plasma,
    _grenade_count_setting_4_plasma,
    _grenade_count_setting_1_each,
    _grenade_count_setting_2_each,
    _grenade_count_setting_3_each,
    _grenade_count_setting_4_each,

    k_grenade_count_setting_count
};

/* ---------- definitions */

// $TODO: data members not yet reversed (size per c_game_engine_map_override_options' powerup trait offsets)
class c_player_traits
{
public:
    void clear(void);
    void set(c_player_traits const * traits, bool force);

private:
    unsigned char m_storage[0x2C];
};
static_assert(sizeof(c_player_traits) == 0x2C, "c_player_traits");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __GAME_ENGINE_PLAYER_TRAITS_STRUCTURES_H__

