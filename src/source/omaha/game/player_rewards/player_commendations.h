#pragma once
#ifndef __PLAYER_COMMENDATIONS_H__
#define __PLAYER_COMMENDATIONS_H__

/* ---------- headers */

#include "omaha\game\player_rewards\player_commendation_definitions.h"
#include "omaha\input\controllers.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

bool player_rewards_commendation_progress_increment_for_controller(e_controller_index controller_index, long commendation_name);
bool player_rewards_commendation_progress_increment_local(e_controller_index controller_index, long commendation_absolute_index);
e_commendation_progression_level commendation_get_cookie_reward_cap_level(s_commendation_globals_definition const * commendation_globals, s_commendation_definition const * commendation);
bool player_rewards_commendation_progress_increment_for_player(long player_index, long commendation_name);
long player_rewards_commendation_get_progress(e_controller_index controller_index, long commendation_name);
long player_rewards_commendation_get_next_level_goal(e_controller_index controller_index, long commendation_name);
unsigned char player_rewards_commendation_calculate_percent_completed(e_controller_index controller_index);
void player_rewards_commendation_progress_increment_hs(e_controller_index controller_index, long commendation_name);
bool player_rewards_commendation_set_progress_for_controller_hs(e_controller_index controller_index, long commendation_name, long progress);

/* ---------- globals */

extern bool g_allow_offline_commendations;

/* ---------- public code */

#endif // __PLAYER_COMMENDATIONS_H__

