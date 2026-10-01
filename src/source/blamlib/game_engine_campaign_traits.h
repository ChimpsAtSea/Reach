#pragma once
#ifndef __GAME_ENGINE_CAMPAIGN_TRAITS_H__
#define __GAME_ENGINE_CAMPAIGN_TRAITS_H__

/* ---------- headers */

#include "omaha\game\game_engine_traits_structures.h"

/* ---------- constants */

/* ---------- definitions */

struct s_game_engine_campaign_variant_definition : s_game_engine_base_variant_definition
{
};
static_assert(sizeof(s_game_engine_campaign_variant_definition) == 0x50, "s_game_engine_campaign_variant_definition");

class c_game_engine_campaign_variant : public c_game_engine_base_variant
{
public:
    virtual void initialize(void);

    void set(s_game_engine_campaign_variant_definition const * definition);
};

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __GAME_ENGINE_CAMPAIGN_TRAITS_H__

