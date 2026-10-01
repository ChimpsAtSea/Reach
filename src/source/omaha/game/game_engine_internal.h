#ifndef __GAME_ENGINE_INTERNAL_H__
#define __GAME_ENGINE_INTERNAL_H__
#pragma once

/* ---------- headers */

#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_macros.h"
#include "omaha\game\game.h"
#include "omaha\game\game_options.h"
#include "omaha\game\game_variant.h"

/* ---------- constants */

/* ---------- definitions */

class c_game_engine_scope_lock
{
public:
    c_game_engine_scope_lock();
    ~c_game_engine_scope_lock();
};

/* ---------- prototypes */

// f i (network_game_definitions.obj)
inline c_game_variant const * current_game_variant(void)
{
    s_game_options const * options = game_options_get();
    assert_decomp(options!=0, "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\game\\game_engine_internal.h", 734);

    c_game_variant const * variant = NULL;
    if (options->game_mode == _game_mode_multiplayer || options->game_mode == _game_mode_campaign || options->game_mode == _game_mode_survival)
    {
        variant = &options->game_variant;
    }

    return variant;
};

/* ---------- globals */

/* ---------- public code */

#endif // __GAME_ENGINE_INTERNAL_H__

