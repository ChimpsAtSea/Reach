#pragma once
#ifndef __GAME_COMPLETION_REWARDS_DEFINITIONS_H__
#define __GAME_COMPLETION_REWARDS_DEFINITIONS_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"
#include "omaha\tag_files\tag_groups.h"

/* ---------- constants */

enum
{
    GAME_COMPLETION_REWARDS_GLOBALS_TAG = 'gcrg',
};

enum
{
    k_game_completion_rewards_category_count = 4,
    k_game_completion_rewards_mode_count = 4,
};

/* ---------- definitions */

// game_completion_rewards_falloff_point_block
struct s_game_completion_rewards_falloff_point
{
    short start_time; // 0x0
    short cookies_per_minute; // 0x2
};
static_assert(sizeof(s_game_completion_rewards_falloff_point) == 0x4, "s_game_completion_rewards_falloff_point");

// game_completion_rewards_definition_block
struct s_game_completion_rewards_definition
{
    long initial_cookies_per_minute; // 0x0
    float hopper_scaling_factor; // 0x4
    float winner_scaling_factor; // 0x8
    float performance_scaling_factor; // 0xC
    s_tag_block cpm_falloff_curve; // 0x10 s_game_completion_rewards_falloff_point
};
static_assert(sizeof(s_game_completion_rewards_definition) == 0x1C, "s_game_completion_rewards_definition");

// game_completion_rewards_difficulty_block / _multiplayer_block / _never_online_block
struct s_game_completion_rewards_category
{
    s_tag_block modes[k_game_completion_rewards_mode_count]; // 0x0 s_game_completion_rewards_definition (difficulty / multiplayer mode)
};
static_assert(sizeof(s_game_completion_rewards_category) == 0x30, "s_game_completion_rewards_category");

// game_completion_rewards_globals_block (campaign, firefight, multiplayer, never_online)
struct s_game_completion_rewards_globals
{
    s_tag_block categories[k_game_completion_rewards_category_count]; // 0x0 s_game_completion_rewards_category
};
static_assert(sizeof(s_game_completion_rewards_globals) == 0x30, "s_game_completion_rewards_globals");

/* ---------- prototypes */

char * format_game_completion_rewards_falloff_point_block(long block_index, __int64 flags, s_tag_block * block, long element_index, char * buffer, long buffer_size);
char * format_game_completion_rewards_definition_block(long block_index, __int64 flags, s_tag_block * block, long element_index, char * buffer, long buffer_size);
bool gcrg_postprocess(long element_index, s_game_completion_rewards_globals * definition, bool for_editor);

/* ---------- globals */

/* ---------- public code */

#endif // __GAME_COMPLETION_REWARDS_DEFINITIONS_H__
