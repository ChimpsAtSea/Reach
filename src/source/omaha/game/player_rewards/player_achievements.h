#pragma once
#ifndef __PLAYER_ACHIEVEMENTS_H__
#define __PLAYER_ACHIEVEMENTS_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"
#include "omaha\tag_files\tag_groups.h"
#include "omaha\memory\static_arrays.h"
#include "omaha\game\game_globals.h"
#include "omaha\networking\online\online_achievements.h"

/* ---------- constants */

enum
{
    ACHIEVEMENTS_TAG = 'achi',
};

/* ---------- definitions */

enum e_controller_index;

struct s_single_achievement_restricted_level_definition
{
    long level_name; // 0x0 string_id, compared to scenario::map_name
};
static_assert(sizeof(s_single_achievement_restricted_level_definition) == 0x4, "s_single_achievement_restricted_level_definition");

struct s_single_achievement_definition
{
    long name; // 0x0 string_id
    c_enum_no_init<e_achievement, char, _achievement_first, k_achievement_count> type; // 0x4
    c_flags_no_init<e_campaign_difficulty_level, unsigned char, k_campaign_difficulty_levels_count> difficulty; // 0x5
    unsigned char pad[2]; // 0x6
    s_tag_block restricted_levels; // 0x8 s_single_achievement_restricted_level_definition
};
static_assert(sizeof(s_single_achievement_definition) == 0x14, "s_single_achievement_definition");

struct s_game_achievements_definition
{
    s_tag_block achievements; // 0x0 s_single_achievement_definition
};
static_assert(sizeof(s_game_achievements_definition) == 0xC, "s_game_achievements_definition");

/* ---------- prototypes */

bool game_achievements_enabled(void);
void game_achievements_enable(bool enable);
bool game_achievements_validation_get_disabled(void);
void game_achievements_validation_disable(bool disable);
s_single_achievement_definition * game_achievements_find_achievement(e_achievement achievement);
s_single_achievement_definition * game_achievements_find_achievement_by_name(long achievement_name);
long achievement_get_name(e_achievement achievement);
e_achievement achievement_get_by_name(long achievement_name);
bool game_conditions_allow_achievement(e_controller_index controller_index, e_achievement achievement);
bool achievements_enabled(void);
void player_grant_achievement(long player_index, e_achievement achievement);
void player_grant_achievement_by_name(long player_index, long achievement_name);
void player_grant_achievement_by_name(long player_index, long achievement_name);

/* ---------- globals */

/* ---------- public code */

#endif // __PLAYER_ACHIEVEMENTS_H__

