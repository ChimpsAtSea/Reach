#pragma once
#ifndef __MEGALOGAMENGINE_SOUND_DEFINITIONS_H__
#define __MEGALOGAMENGINE_SOUND_DEFINITIONS_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"
#include "omaha\tag_files\tag_groups.h"

/* ---------- constants */

enum
{
    k_megalogamengine_sounds_definition_tag = 'mgls',
};

// names from the megalogamengine_sounds_struct_definition fields (tag json)
enum e_megalo_sound
{
    _megalo_sound_slayer = 0,
    _megalo_sound_ctf,
    _megalo_sound_flag_captured,
    _megalo_sound_flag_dropped,
    _megalo_sound_flag_recovered,
    _megalo_sound_flag_reset,
    _megalo_sound_flag_stolen,
    _megalo_sound_flag_taken,
    _megalo_sound_vip,
    _megalo_sound_new_vip,
    _megalo_sound_vip_killed,
    _megalo_sound_juggernaut,
    _megalo_sound_new_juggernaut,
    _megalo_sound_territories,
    _megalo_sound_territory_captured,
    _megalo_sound_territory_lost,
    _megalo_sound_assault,
    _megalo_sound_bomb_armed,
    _megalo_sound_bomb_detonated,
    _megalo_sound_bomb_disarmed,
    _megalo_sound_bomb_dropped,
    _megalo_sound_bomb_reset,
    _megalo_sound_bomb_returned,
    _megalo_sound_bomb_taken,
    _megalo_sound_infection,
    _megalo_sound_infected,
    _megalo_sound_last_man_standing,
    _megalo_sound_new_zombie,
    _megalo_sound_oddball,
    _megalo_sound_ball_spawned,
    _megalo_sound_ball_taken,
    _megalo_sound_ball_dropped,
    _megalo_sound_ball_reset,
    _megalo_sound_king,
    _megalo_sound_hill_controlled,
    _megalo_sound_hill_contested,
    _megalo_sound_hill_moved,
    _megalo_sound_headhunter,
    _megalo_sound_stockpile,
    _megalo_sound_race,
    _megalo_sound_defense,
    _megalo_sound_offense,
    _megalo_sound_destination_moved,
    _megalo_sound_generator_armed,
    _megalo_sound_core_armed,
    _megalo_sound_generator_disarmed,
    _megalo_sound_core_disarmed,
    _megalo_sound_sudden_death,
    _megalo_sound_game_over,
    _megalo_sound_bone_cv_defeat,
    _megalo_sound_bone_cv_ph1_defeat,
    _megalo_sound_bone_cv_ph1_intro,
    _megalo_sound_bone_cv_ph1_victory,
    _megalo_sound_bone_cv_ph2_defeat,
    _megalo_sound_bone_cv_ph2_victory,
    _megalo_sound_bone_cv_ph3_victory,
    _megalo_sound_bone_cv_victory,
    _megalo_sound_bone_sp_defeat,
    _megalo_sound_bone_sp_ph1_intro,
    _megalo_sound_bone_sp_ph1_victory,
    _megalo_sound_bone_sp_ph2_intro,
    _megalo_sound_bone_sp_ph2_victory,
    _megalo_sound_bone_sp_ph3_intro,
    _megalo_sound_bone_sp_ph3_victory,
    _megalo_sound_isle_cv_defeat,
    _megalo_sound_isle_cv_ph1_defeat,
    _megalo_sound_isle_cv_ph1_intro,
    _megalo_sound_isle_cv_ph2_intro,
    _megalo_sound_isle_cv_ph2_victory,
    _megalo_sound_isle_cv_ph3_intro,
    _megalo_sound_isle_cv_ph3_victory,
    _megalo_sound_isle_sp_defeat,
    _megalo_sound_isle_sp_ph1_defeat,
    _megalo_sound_isle_sp_ph1_extra,
    _megalo_sound_isle_sp_ph1_intro,
    _megalo_sound_isle_sp_ph1_victory,
    _megalo_sound_isle_sp_ph2_defeat,
    _megalo_sound_isle_sp_ph2_victory,
    _megalo_sound_isle_sp_ph3_victory,
    _megalo_sound_isle_sp_victory,
    _megalo_sound_bone_sp_ph3_defeat,
    _megalo_sound_isle_cv_ph3_defeat,
    _megalo_sound_covy_big_win,
    _megalo_sound_covy_win1,
    _megalo_sound_covy_win2,
    _megalo_sound_invasion_beginning,
    _megalo_sound_unsc_big_win,
    _megalo_sound_unsc_win1,
    _megalo_sound_unsc_win2,
    _megalo_sound_power_down,
    _megalo_sound_reinforcements,
    _megalo_sound_respawn_tick,
    _megalo_sound_alpha_under_attack,
    _megalo_sound_bravo_under_attack,
    _megalo_sound_charlie_under_attack,

    k_megalo_sound_count,
    _megalo_sound_none = -1
};

/* ---------- definitions */

struct s_megalogamengine_sound_group
{
    s_tag_reference sounds[k_megalo_sound_count]; // 0x0
};
static_assert(sizeof(s_megalogamengine_sound_group) == 0x5F0, "s_megalogamengine_sound_group");

/* ---------- prototypes */

long megalogamengine_get_sound_definition_index(e_megalo_sound megalo_sound);

/* ---------- globals */

/* ---------- public code */

#endif // __MEGALOGAMENGINE_SOUND_DEFINITIONS_H__

