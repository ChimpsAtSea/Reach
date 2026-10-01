#pragma once
#ifndef __PLAYER_COOKIES_H__
#define __PLAYER_COOKIES_H__

/* ---------- headers */

#include "omaha\input\controllers.h"
#include "omaha\game\player_rewards\player_grade_definitions.h"

/* ---------- constants */

// $TODO: enumerator names unknown (asserts reference k_cookie_award_host_authoritative_type_count)
enum e_cookie_award_host_authoritative_type
{
    _cookie_award_host_authoritative_type_hs = 3, // $unsure: used by player_rewards_add_cookies_to_player_hs
};

// $TODO: enumerator names unknown (asserts reference k_cookie_award_client_authoritative_type_count)
enum e_cookie_award_client_authoritative_type
{
    _cookie_award_client_authoritative_type_hs = 3, // $unsure: used by player_rewards_add_cookies_to_controller_hs
    _cookie_award_client_authoritative_type_ignore_daily_cap = 9, // $unsure: bypasses the daily cookie cap
};

/* ---------- definitions */

/* ---------- prototypes */

long player_rewards_reconcile_cookies_from_game_results(e_controller_index controller_index, long previous_cookies, long current_cookies, e_cookie_award_host_authoritative_type cookie_award_type);
long player_rewards_add_cookies_direct(e_controller_index controller_index, long cookies, bool ignore_daily_cap);
bool player_rewards_add_cookies_to_controller_hs(e_controller_index controller_index, long cookies);
bool player_rewards_add_cookies_to_controller(e_controller_index controller_index, long cookies, e_cookie_award_client_authoritative_type cookie_award_type);
bool player_rewards_add_cookies_local(e_controller_index controller_index, long cookies, e_cookie_award_client_authoritative_type cookie_award_type);
bool player_rewards_add_cookies_to_player_hs(long player_index, long cookies);
bool player_rewards_add_cookies_to_player(long player_index, long cookies, e_cookie_award_host_authoritative_type cookie_award_type);
long player_rewards_get_cookie_total(e_controller_index controller_index);
long player_rewards_get_spent_cookies(e_controller_index controller_index);
long player_rewards_get_available_cookies(e_controller_index controller_index);
void player_rewards_notify_grade_advancement(e_controller_index controller_index, e_player_grade old_grade, e_player_grade new_grade);
void player_rewards_notify_sub_grade_advancement(e_controller_index controller_index, e_player_sub_grade old_sub_grade, e_player_sub_grade new_sub_grade);

/* ---------- globals */

/* ---------- public code */

#endif // __PLAYER_COOKIES_H__

