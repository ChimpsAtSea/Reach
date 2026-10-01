#ifndef __NETWORK_CONFIGURATION_H__
#define __NETWORK_CONFIGURATION_H__
#pragma once

/* ---------- headers */

#include "foundation\baselib\datatypes\static_array.h"
#include "omaha\game\player_rewards\player_grade_definitions.h"

/* ---------- constants */

/* ---------- definitions */

// $TODO: Reach layout differs from H3; only the members used so far are placed (g_network_configuration spans <= 0x2254 bytes)
struct s_network_configuration
{
    char unknown0[0x1D08]; // 0x0
    s_static_array<s_static_array<float, k_player_sub_grade_count>, k_player_grade_count> cookie_multipliers; // 0x1D08 used by game_completion_rewards_get_cookie_award
};

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __NETWORK_CONFIGURATION_H__

