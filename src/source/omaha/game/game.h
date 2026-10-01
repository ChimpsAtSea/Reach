#pragma once
#ifndef __GAME_H__
#define __GAME_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"
#include "foundation\baselib\datatypes\static_array.h"
#include "omaha\memory\static_arrays.h"

/* ---------- constants */

// values per game_engine_variant_initialize_built_in_metadata (campaign 1, survival 2, multiplayer 3);
// range per c_enum_no_init<e_game_mode, char, 0, 6>; names of 4 and 5 unknown
enum e_game_mode
{
    _game_mode_none = 0,
    _game_mode_campaign,
    _game_mode_survival,
    _game_mode_multiplayer,

    k_game_mode_count = 6
};

enum
{
    k_maximum_multiplayer_players = 16,
};

/* ---------- definitions */

struct s_game_options;

// Reach: s_static_array<c_big_flags_typed_no_init<long, 255>, 16> (scenario_sky.obj element/set calls)
struct s_game_cluster_bit_vectors
{
    s_static_array<c_big_flags_typed_no_init<long, 255>, 16> bit_vectors; // 0x0
};
static_assert(sizeof(s_game_cluster_bit_vectors) == 0x200, "s_game_cluster_bit_vectors");

/* ---------- prototypes */

void game_options_validate_for_saved_game(long game_state_proc_flags);
extern bool game_in_progress(void);
extern bool game_is_ui_shell(void);
extern bool game_is_multiplayer(void);
extern bool game_is_lost(void);
extern bool game_is_campaign(void);
extern bool game_is_survival(void);
extern bool game_is_playback();
extern enum e_campaign_difficulty_level game_difficulty_level_get(void);
extern bool game_is_authoritative();
extern bool game_is_distributed(void);
extern bool game_is_predicted(void);
extern void game_options_new(s_game_options * options);
extern s_game_options const * game_options_get(void);
extern void game_options_setup_default_players(long player_count, s_game_options * options);

/* ---------- globals */

extern char const * global_campaign_difficulty_level_names[];

/* ---------- public code */

#endif // __GAME_H__

