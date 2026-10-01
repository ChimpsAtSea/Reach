#pragma once
#ifndef __GAME_ENGINE_PLAYER_RATING_PARAMETERS_H__
#define __GAME_ENGINE_PLAYER_RATING_PARAMETERS_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"
#include "foundation\baselib\datatypes\static_array.h"
#include "omaha\memory\static_arrays.h"

class c_bitstream;

/* ---------- constants */

enum e_game_engine_player_rating_flags
{
    _game_engine_player_rating_flag_unknown0 = 0, // $TODO name unknown

    k_game_engine_player_rating_flags_count
};

long const k_maximum_megalo_game_statistics = 4;

long const k_game_engine_player_rating_parameter_count = 15;
long const k_game_engine_player_rating_parameter_first_megalo_custom_stat = 9; // parameters [9, 13) are megalo custom stat weights

/* ---------- definitions */

struct s_game_engine_player_rating_parameters
{
    void clear(void);
    void initialize_to_default(void);
    bool is_valid(void) const;
    float get_megalo_custom_stat_parameter_weight(long custom_stat_index) const;
    void set_megalo_custom_stat_parameter_weight(long custom_stat_index, float weight);
    void encode(c_bitstream * packet) const;
    void decode(c_bitstream * packet);

    s_static_array<float, k_game_engine_player_rating_parameter_count> parameters; // 0x0
    c_flags_no_init<e_game_engine_player_rating_flags, unsigned char, k_game_engine_player_rating_flags_count> flags; // 0x3C
};
static_assert(sizeof(s_game_engine_player_rating_parameters) == 0x40, "s_game_engine_player_rating_parameters");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __GAME_ENGINE_PLAYER_RATING_PARAMETERS_H__

