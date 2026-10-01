#pragma once
#ifndef __GAME_ENGINE_H__
#define __GAME_ENGINE_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"
#include "foundation\baselib\datatypes\static_array.h"

/* ---------- constants */

// $TODO values other than megalo (2, per megalogamengine_render_debug_profiling_info) and campaign (3, per c_campaign_engine::get_type) are unverified
enum e_game_engine_type
{
    _game_engine_type_none = 0,
    _game_engine_type_sandbox,
    _game_engine_type_megalo,
    _game_engine_type_campaign,
    _game_engine_type_survival,

    k_game_engine_type_count
};

// $TODO only the values used so far; names from H3 (same values), unverified for Reach
enum e_game_engine_end_condition
{
    _game_engine_end_default = 0,
    _game_engine_game_end_scripting = 1, // game_engine_game_won
    _game_engine_round_end_editor_reset = 21,
};

/* ---------- definitions */

// Reach size 0x1C per s_static_array<s_player_navpoint_data, 16>::operator[]; only the first field is verified
struct s_player_navpoint_data
{
    bool last_living_location_valid; // 0x0
    unsigned char __unknown1[0x1C - 0x1];
};
static_assert(sizeof(s_player_navpoint_data) == 0x1C, "s_player_navpoint_data");

// size per game_engine_initialize (reserve_memory / memset 0x8228)
struct s_game_engine_globals
{
    unsigned char unknown0[0x164]; // $TODO not yet reversed
    unsigned char multiplayer_globals_storage[0x31F8 - 0x164]; // 0x164 per-engine globals (placement new in initialize_for_new_map) $TODO real size (H3: 0x1800) and members up to 0x31F8
    s_static_array<s_player_navpoint_data, 16> player_navpoint_data; // 0x31F8 (game_engine_respawn_override_timers)
    unsigned char __unknown33B8[0x8228 - 0x33B8]; // $TODO not yet reversed
};
static_assert(sizeof(s_game_engine_globals) == 0x8228, "s_game_engine_globals");

/* ---------- prototypes */

extern short get_current_game_engine_index(void);

class c_game_engine;

// $TODO inline in the target (f i, network_game_definitions.obj): game_engines[get_current_game_engine_index()] or NULL
extern c_game_engine const * current_game_engine(void);
extern bool game_engine_running(void);
// $TODO inline in the target (f i, network_game_definitions.obj); body not reversed yet
extern bool game_engine_has_teams(void);
extern void game_engine_end_round_with_winner(long winner_index, bool end_game_instead_of_round, e_game_engine_end_condition end_condition);

/* ---------- globals */

extern __declspec(thread) s_game_engine_globals * game_engine_globals;

/* ---------- public code */

#endif // __GAME_ENGINE_H__

