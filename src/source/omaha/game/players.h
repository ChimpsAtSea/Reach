#pragma once
#ifndef __PLAYERS_H__
#define __PLAYERS_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"
#include "foundation\baselib\datatypes\data_array.h"
#include "omaha\game\game_constants.h"
#include "omaha\memory\static_arrays.h"

/* ---------- constants */

/* ---------- definitions */

struct s_data_array;

// only the range is verified (c_enum<e_loadout_palette_type, char, -1, 6>)
enum e_loadout_palette_type
{
    _loadout_palette_type_none = -1,
    k_loadout_palette_type_count = 6
};

// names from H3; only _player_left_game_bit (1) and the count (20, c_flags_no_init<e_player_flags, unsigned long, 20>) are verified
enum e_player_flags
{
    _player_active_in_game_bit = 0,
    _player_left_game_bit,

    k_player_flags_count = 20
};

// $TODO: only the fields used so far are reversed (size from data_new in players_initialize;
// 0x3B0..0x4D0 from determinism_debug_consumer_players.obj)
struct player_datum
{
    // implicit in the target (f i, players.obj): constructs the member c_enums; body not reversed yet
    player_datum(void);

    unsigned char __unknown0[0x4];
    c_flags_no_init<e_player_flags, unsigned long, k_player_flags_count> flags; // 0x4 (c_authored_camera::update)
    unsigned char __unknown8[0x28 - 0x8];
    long unit_index; // 0x28
    unsigned char __unknown2C[0xAC - 0x2C];
    c_game_team team; // 0xAC $TODO name (H3 configuration.host.team_index); read by game_engine_scripting.obj
    unsigned char __unknownAE[0x28C - 0xAE];
    long respawn_timer; // 0x28C (H3 respawn_timer; game_engine_respawn_override_timers)
    unsigned char __unknown290[0x3B0 - 0x290];
    long player_display_index; // 0x3B0 (H3 multiplayer.player_display_index)
    unsigned char __unknown3B4[0x3BC - 0x3B4];
    short player_display_count; // 0x3BC (H3 multiplayer.player_display_count)
    short remaining_lives; // 0x3BE (H3 multiplayer.remaining_lives; game_engine_active_player_count_by_team)
    unsigned char __unknown3C0[0x490 - 0x3C0];
    long __unknown490; // 0x490 $TODO a player index; c_dead_camera::set_target prefers it (read via unit last_player_index) over the top attacker as the killer
    unsigned char __unknown494[0x4C8 - 0x494];
    long __unknown4C8; // 0x4C8 $TODO reset to NONE by the determinism consumer when the game is distributed and predicted
    c_enum<e_loadout_palette_type, char, _loadout_palette_type_none, k_loadout_palette_type_count> loadout_palette_type; // 0x4CC $TODO name
    unsigned char __unknown4CD[0x4D0 - 0x4CD];
    long __unknown4D0; // 0x4D0 $TODO
    unsigned char __unknown4D4[0x578 - 0x4D4];
};
static_assert(sizeof(player_datum) == 0x578, "player_datum");

// all members non-inline in players.obj; bodies not reversed yet
class c_player_in_game_iterator
{
public:
    void begin(void);
    bool next(void);
    player_datum * get_datum(void);
    long get_index(void) const;
    short get_absolute_index(void) const;

protected:
    c_data_iterator<player_datum> m_player_iterator; // 0x0
};
static_assert(sizeof(c_player_in_game_iterator) == 0x14, "c_player_in_game_iterator");

/* ---------- prototypes */

void players_initialize_for_saved_game(long game_state_proc_flags);
long player_index_from_absolute_player_index(long absolute_player_index);
long player_index_from_unit_index(long unit_index);
long player_get_unit_index_even_if_dead(long player_index);

/* ---------- globals */

extern __declspec(thread) s_data_array * player_data;

/* ---------- public code */

#endif // __PLAYERS_H__

