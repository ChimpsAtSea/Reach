#pragma once
#ifndef __GAME_ENGINE_TRAITS_METADATA_H__
#define __GAME_ENGINE_TRAITS_METADATA_H__

/* ---------- headers */

#include "omaha\game\game_engine.h"

/* ---------- constants */

/* ---------- definitions */

class c_game_engine_base_variant;

/* ---------- prototypes */

extern void game_engine_variant_initialize_built_in_metadata(c_game_engine_base_variant * variant, unsigned int variant_index, e_game_engine_type game_engine_index, unsigned __int64 timestamp);
extern void game_engine_variant_update_built_in_metadata(c_game_engine_base_variant * variant, unsigned int variant_index);

/* ---------- globals */

/* ---------- public code */

#endif // __GAME_ENGINE_TRAITS_METADATA_H__

