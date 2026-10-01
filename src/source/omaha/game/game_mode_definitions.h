#pragma once
#ifndef __GAME_MODE_DEFINITIONS_H__
#define __GAME_MODE_DEFINITIONS_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"
#include "omaha\memory\static_arrays.h"

/* ---------- constants */

enum e_campaign_difficulty_level; // game_globals.h (not included: the target TUs using this header do not pull in observer.h)

// $TODO enumerators not reversed (8 legacy game types, see c_flags<e_game_type_legacy, unsigned char, 8>)
enum e_game_type_legacy
{
    k_game_type_legacy_count = 8
};

/* ---------- definitions */

// game_mode_flags_struct
struct s_game_mode_flags
{
    unsigned char game_mode; // 0x0 byte flags (game_type_enum_definition)
    unsigned char matchmaking_type; // 0x1 byte flags (game_matchmaking_flags_definition)
    unsigned char difficulty; // 0x2 byte flags (global_campaign_difficulty_flags)
    char player_count; // 0x3 char enum (game_player_count_flags_definition)
};
static_assert(sizeof(s_game_mode_flags) == 0x4, "s_game_mode_flags");

/* ---------- prototypes */

void version_old_allowed_game_type_flags_to_new_flags(c_flags<e_game_type_legacy, unsigned char, k_game_type_legacy_count> const * game_types, long player_count, c_flags<e_campaign_difficulty_level, unsigned char, static_cast<e_campaign_difficulty_level>(4)> const * difficulty, s_game_mode_flags * game_mode_flags);
void version_old_disallowed_game_type_flags_to_new_flags(c_flags<e_game_type_legacy, unsigned char, k_game_type_legacy_count> const * game_types, long player_count, c_flags<e_campaign_difficulty_level, unsigned char, static_cast<e_campaign_difficulty_level>(4)> const * difficulty, s_game_mode_flags * game_mode_flags);
bool test_allowed_game_mode_flags(s_game_mode_flags const & game_mode_flags);

/* ---------- globals */

/* ---------- public code */

#endif // __GAME_MODE_DEFINITIONS_H__

