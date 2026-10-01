#ifndef __GAME_CONSTANTS_H__
#define __GAME_CONSTANTS_H__
#pragma once

/* ---------- headers */

#include "foundation\baselib\datatypes\static_string.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_macros.h"
#include "omaha\memory\static_arrays.h"

/* ---------- constants */

enum e_multiplayer_team_designator
{
    _multiplayer_team_designator_none = -1,
    _multiplayer_team_designator_first = 0,
    _multiplayer_team_designator_defender = 0,
    _multiplayer_team_designator_attacker,
    _multiplayer_team_designator_third_party,
    _multiplayer_team_designator_fourth_party,
    _multiplayer_team_designator_fifth_party,
    _multiplayer_team_designator_sixth_party,
    _multiplayer_team_designator_seventh_party,
    _multiplayer_team_designator_eigth_party,
    _multiplayer_team_designator_neutral,

    k_multiplayer_team_designator_count
};

// range per c_game_team::get_campaign_team (c_enum_no_init<e_campaign_team, char, -1, 8>); names from H3, only default..covenant assumed
enum e_campaign_team
{
    _campaign_team_none = -1,
    _campaign_team_default = 0,
    _campaign_team_player,
    _campaign_team_human,
    _campaign_team_covenant,

    k_campaign_team_count = 8
};

// storage range per c_game_team::get_multiplayer_team (c_enum_no_init<e_multiplayer_team, char, -1, 16>);
// scripting validates [0, 8) (game_engine_scripting.obj)
enum e_multiplayer_team
{
    _multiplayer_team_none = -1,
    _multiplayer_team_first = 0,
    _multiplayer_team_red = 0,
    _multiplayer_team_blue,
    _multiplayer_team_green,
    _multiplayer_team_yellow,
    _multiplayer_team_purple,
    _multiplayer_team_orange,
    _multiplayer_team_brown,
    _multiplayer_team_grey,

    k_multiplayer_team_count,
    k_multiplayer_team_maximum_count = 16
};

/* ---------- definitions */

struct s_multiplayer_team_designator_string_resolver
{
    static void to_string(e_multiplayer_team_designator value, c_static_string<64> * string);
};

#define __GAME_CONSTANTS_H_FILE__ "C:\SD\Reach\Publishing\Main\shared\engine\source\omaha\game\game_constants.h"

// size 2 per game_get_player_team (copies two bytes); other methods (clear, build*, *_valid, get_campaign_team, ==, !=) not reversed yet
class c_game_team
{
public:
    c_game_team(void);

    // f i (simulation_game_internal.obj); verified via game_engine_scripting.obj callers
    c_enum_no_init<e_multiplayer_team, char, _multiplayer_team_none, k_multiplayer_team_maximum_count> get_multiplayer_team(void) const
    {
        assert_decomp(m_multiplayer_team.in_range(), __GAME_CONSTANTS_H_FILE__, 279);

        return m_multiplayer_team;
    };

protected:
    c_enum_no_init<e_campaign_team, char, _campaign_team_none, k_campaign_team_count> m_campaign_team; // 0x0
    c_enum_no_init<e_multiplayer_team, char, _multiplayer_team_none, k_multiplayer_team_maximum_count> m_multiplayer_team; // 0x1
};
static_assert(sizeof(c_game_team) == 0x2, "c_game_team");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __GAME_CONSTANTS_H__

