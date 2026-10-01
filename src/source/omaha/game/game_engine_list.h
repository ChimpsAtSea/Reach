#pragma once
#ifndef __GAME_ENGINE_LIST_H__
#define __GAME_ENGINE_LIST_H__

/* ---------- headers */

#include "omaha\game\game_engine.h"
#include "foundation\baselib\datatypes\static_string.h"

/* ---------- constants */

/* ---------- definitions */

class c_game_engine;

// names used by the target's to_string asserts ("(long)value >= (long)c_game_engine_type::k_minimum_value")
struct c_game_engine_type
{
    enum
    {
        k_minimum_value = _game_engine_type_none,
        k_maximum_value_plus_one = k_game_engine_type_count,
    };
};

struct s_game_engine_type_string_resolver
{
    static void to_string(e_game_engine_type value, c_static_string<64> * string);
};

/* ---------- prototypes */

extern char const * game_engine_type_get_string(e_game_engine_type game_engine_type);
extern long game_engine_type_get_string_id(e_game_engine_type game_engine_type);

/* ---------- globals */

extern char const * k_game_engine_type_names[k_game_engine_type_count];
extern c_game_engine * game_engines[k_game_engine_type_count];

/* ---------- public code */

#endif // __GAME_ENGINE_LIST_H__

