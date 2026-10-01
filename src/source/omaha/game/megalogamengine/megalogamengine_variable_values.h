#ifndef __MEGALOGAMENGINE_VARIABLE_VALUES_H__
#define __MEGALOGAMENGINE_VARIABLE_VALUES_H__
#pragma once

/* ---------- headers */

#include "foundation\baselib\datatypes\data_array.h"
#include "foundation\baselib\datatypes\static_array.h"
#include "omaha\game\game_constants.h"
#include "omaha\memory\static_arrays.h"

/* ---------- constants */

/* ---------- definitions */

struct s_global_variable_traits
{
    // $TODO remaining counts (numeric/player/team/timer)
    static long const k_number_of_object_variables = 16;
    static long const k_number_of_player_variables = 8;
    static long const k_number_of_team_variables = 8;
};

template<typename t_variable_traits>
struct s_variable_values
{
    // f i (megalogamengine_explicit_player.obj for global traits)
    long get_player_variable(long variable_index) const;
    void set_player_variable(long variable_index, long player_index)
    {
        player_variables[variable_index] = static_cast<char>(DATUM_INDEX_TO_ABSOLUTE_INDEX(player_index));
    };

    // $TODO remaining members (layout only verified for global traits)
    s_static_array<long, t_variable_traits::k_number_of_object_variables> object_variables; // 0x0
    s_static_array<c_enum<e_multiplayer_team_designator, char, _multiplayer_team_designator_none, k_multiplayer_team_designator_count, s_multiplayer_team_designator_string_resolver>, t_variable_traits::k_number_of_team_variables> team_variables; // 0x40
    unsigned char __unknown48[0x80 - 0x48]; // $TODO global traits only
    s_static_array<char, t_variable_traits::k_number_of_player_variables> player_variables; // 0x80
};

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __MEGALOGAMENGINE_VARIABLE_VALUES_H__

