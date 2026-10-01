#pragma once
#ifndef __GAME_RESULTS_H__
#define __GAME_RESULTS_H__

/* ---------- headers */

/* ---------- constants */

/* ---------- definitions */

enum e_controller_index;
enum e_cookie_award_client_authoritative_type;
enum e_cookie_award_host_authoritative_type;

/* ---------- prototypes */

void game_results_local_cookies_add(e_controller_index controller_index, long cookies, e_cookie_award_client_authoritative_type cookie_award_type);
void game_results_cookies_add(long player_absolute_index, long cookies, e_cookie_award_host_authoritative_type cookie_award_type);
bool game_results_get_game_recording();
void game_results_local_commendation_increment(e_controller_index controller_index, long commendation_absolute_index);
void game_results_commendation_increment(long player_absolute_index, long commendation_absolute_index);
void game_results_medal_increment(long player_absolute_index, long medal_index, long count);

/* ---------- globals */

/* ---------- public code */

#endif // __GAME_RESULTS_H__

