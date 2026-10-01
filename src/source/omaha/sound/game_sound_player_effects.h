#pragma once
#ifndef __GAME_SOUND_PLAYER_EFFECTS_H__
#define __GAME_SOUND_PLAYER_EFFECTS_H__

/* ---------- headers */

#include "omaha\cache\restricted_memory_regions.h"

/* ---------- constants */

/* ---------- definitions */

struct s_game_sound_player_effects_globals;

/* ---------- prototypes */

void __tls_set_g_player_effects_globals_allocator(void * new_address);
void game_sound_player_effects_initialize(void);
void game_sound_player_effects_dispose(void);
void game_sound_player_effects_initialize_for_new_map(void);
void game_sound_player_effects_dispose_from_old_map(void);
void game_sound_player_effects_handle_tag_reload(void);
void game_sound_player_effects_restore(void);
void game_sound_player_effects_update(float dt);
void game_sound_player_effects_start_global_effect(long effect_label, float scale, float duration);
void game_sound_player_effects_stop_global_effect(long effect_label);

/* ---------- globals */

extern __declspec(thread) s_game_sound_player_effects_globals * g_game_sound_player_effects_globals;
extern t_restricted_allocation_manager<2, 0, 0, __tls_set_g_player_effects_globals_allocator> g_player_effects_globals_allocator;

/* ---------- public code */

#endif // __GAME_SOUND_PLAYER_EFFECTS_H__

