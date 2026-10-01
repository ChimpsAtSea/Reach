#pragma once
#ifndef __PLAYER_MAPPING_H__
#define __PLAYER_MAPPING_H__

/* ---------- headers */

/* ---------- constants */

enum e_output_user_index
{
    k_output_user_none = -1,
    _output_user_0, // $unsure
    _output_user_1, // $unsure
    _output_user_2, // $unsure
    _output_user_3, // $unsure
    k_number_of_users
};

/* ---------- definitions */

/* ---------- prototypes */

long player_mapping_get_unit_by_output_user(e_output_user_index user_index);
long player_mapping_get_player_by_output_user(e_output_user_index output_user_index);
long player_mapping_get_player_by_input_controller(enum e_controller_index controller_index);
enum e_controller_index player_mapping_get_input_controller(long player_index);
void player_mapping_attach_output_user(e_output_user_index output_user_index, long player_index);
e_output_user_index player_mapping_first_active_output_user();

/* ---------- globals */

/* ---------- public code */

#endif // __PLAYER_MAPPING_H__
