#pragma once
#ifndef __GAME_COMPLETION_REWARDS_H__
#define __GAME_COMPLETION_REWARDS_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"
#include "omaha\input\controllers.h"

/* ---------- constants */

// indexes s_game_completion_rewards_globals::categories
enum e_game_completion_category
{
    _game_completion_category_campaign = 0,
    _game_completion_category_firefight,
    _game_completion_category_multiplayer,
    _game_completion_category_never_online,

    k_number_of_toplevel_categories
};

// indexes s_game_completion_rewards_category::modes for _game_completion_category_multiplayer
enum e_game_completion_multiplayer_mode
{
    _game_completion_multiplayer_mode_arena = 0,
    _game_completion_multiplayer_mode_invasion,
    _game_completion_multiplayer_mode_bungie,
    _game_completion_multiplayer_mode_custom,

    k_number_of_multiplayer_game_modes
};

/* ---------- definitions */

struct s_game_completion_rewards_globals;

// built by game_results_award_completion_from_finalized_results
struct s_game_completion_results
{
    long category; // 0x0 e_game_completion_category
    union
    {
        long subcategory; // 0x4
        long difficulty_level; // 0x4 e_campaign_difficulty_level (campaign, firefight)
        long multiplayer_mode; // 0x4 e_game_completion_multiplayer_mode (multiplayer)
    };
    long length_seconds; // 0x8
    bool won; // 0xC
    bool placed; // 0xD
    char pad0[0x2]; // 0xE
};
static_assert(sizeof(s_game_completion_results) == 0x10, "s_game_completion_results");

struct s_game_completion_overrides
{
    bool enabled; // 0x0
    char pad0[0x3]; // 0x1
    float earn_scale; // 0x4 scales hopper_scaling_factor
    float win_scale; // 0x8 scales winner_scaling_factor
    float performance_scale; // 0xC scales performance_scaling_factor
};
static_assert(sizeof(s_game_completion_overrides) == 0x10, "s_game_completion_overrides");

struct s_game_completion_cookie_result
{
    long time_spent_cookies; // 0x0
    long time_spent_and_performance_cookies; // 0x4
};
static_assert(sizeof(s_game_completion_cookie_result) == 0x8, "s_game_completion_cookie_result");

/* ---------- prototypes */

bool game_completion_rewards_get_cookie_award(e_controller_index controller_index, s_game_completion_results const * results, s_game_completion_overrides const * overrides, s_game_completion_cookie_result * cookie_result_out);
s_game_completion_rewards_globals const * game_completion_rewards_globals_get();

/* ---------- globals */

/* ---------- public code */

#endif // __GAME_COMPLETION_REWARDS_H__

