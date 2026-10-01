#pragma once
#ifndef __GAME_ENGINE_SANDBOX_H__
#define __GAME_ENGINE_SANDBOX_H__

/* ---------- headers */

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

long game_engine_sandbox_get_edited_object_index_for_player(long player_index);
bool game_engine_sandbox_camera_should_apply_pitch_offset(long player_index);
float game_engine_sandbox_get_player_cursor_distance(long player_index);

/* ---------- globals */

class c_game_engine;
extern c_game_engine * sandbox_engine;

/* ---------- public code */

#endif // __GAME_ENGINE_SANDBOX_H__

