#pragma once
#ifndef __SOUND_MANAGER_PLATFORM_PLAYBACK_H__
#define __SOUND_MANAGER_PLATFORM_PLAYBACK_H__

/* ---------- headers */

/* ---------- constants */

enum
{
    k_game_sound_platform_type_bits = 2,
};

enum e_game_sound_platform_playback_type
{
    _game_sound_platform_playback_tag = 0,
    _game_sound_platform_playback_global,
    _game_sound_platform_playback_scenario,
    _game_sound_platform_playback_suppress,

    k_number_of_game_sound_platform_playback_types
};

/* ---------- definitions */

struct s_platform_sound_playback_definition;

/* ---------- prototypes */

long game_sound_find_platform_playback_by_label(long playback_label);
long game_sound_get_platform_playback_label(long playback_designator);
s_platform_sound_playback_definition const * game_sound_get_platform_playback_definition(long definition_index, long playback_designator);
s_platform_sound_playback_definition const * game_sound_get_default_platform_playback_definition(long definition_index);

/* ---------- globals */

/* ---------- public code */

#endif // __SOUND_MANAGER_PLATFORM_PLAYBACK_H__

