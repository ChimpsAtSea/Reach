#pragma once
#ifndef __GAME_ENGINE_MEGALO_H__
#define __GAME_ENGINE_MEGALO_H__

/* ---------- headers */

#include "omaha\game\megalogamengine\megalogamengine_variable_values.h"

/* ---------- constants */

/* ---------- definitions */

// $TODO layout not yet reversed; field names unverified
struct s_custom_game_engine_globals
{
    long current_object_index; // 0x0
    long current_player_index; // 0x4
    long current_team; // 0x8 (c_explicit_team::get_team_designator)
    unsigned char unknownC[0x10 - 0xC];
    long hud_player_index; // 0x10
    long hud_target_player_index; // 0x14
    long target_object_index; // 0x18
    long killed_object_index; // 0x1C
    long killer_object_index; // 0x20
    long killer_player_index; // 0x24
    unsigned char unknown28[0x3C - 0x28];
    s_variable_values<s_global_variable_traits> global_variables; // 0x3C
};

/* ---------- prototypes */

struct s_custom_game_engine_definition;

// $TODO inline in the target (f i, game_engine_megalo.obj)
extern s_custom_game_engine_globals * get_custom_game_engine_globals(void);
class c_game_engine_custom_variant;

extern c_game_engine_custom_variant const * get_custom_game_engine_variant(void);

// $TODO inline in the target (f i, game_engine_megalo.obj): get_custom_game_engine_variant()->get_game_engine()
extern s_custom_game_engine_definition const * get_custom_game_engine_definition(void);

/* ---------- globals */

class c_game_engine;
extern c_game_engine * custom_engine;

/* ---------- public code */

#endif // __GAME_ENGINE_MEGALO_H__

