#pragma once
#ifndef __GAME_ENGINE_CAMPAIGN_H__
#define __GAME_ENGINE_CAMPAIGN_H__

/* ---------- headers */

#include "omaha\game\game_engine_default.h"

/* ---------- constants */

/* ---------- definitions */

// empty; constructed in game_engine_globals->multiplayer_globals_storage (operator new size 1)
struct s_campaign_globals
{
    // f i (game_engine_campaign.obj)
    s_campaign_globals(void)
    {
    };
};

class c_campaign_engine :
    public c_game_engine
{
public:
    virtual bool initialize_for_new_map(void) const;
    virtual void dispose_from_old_map(void) const;
    virtual e_game_engine_type get_type(void) const;
    virtual e_network_game_simulation_protocol get_simulation_protocol(void) const;
    virtual bool requires_valid_multiplayer_globals_in_scenario(void) const;
    virtual bool desires_round_based_fading(void) const;
    virtual bool competitive_game_in_progress(void) const;
    virtual bool requires_scenario_object(long scenario_datum_index, e_object_type object_type, long object_definition_index, s_scenario_object const * scenario_object, s_scenario_multiplayer_object_properties const * multiplayer_properties) const;
    virtual bool requires_unplaced_object(s_object_placement_data const * placement_data) const;
    virtual void player_update(long player_index) const;
    virtual bool desires_garbage_collection(void) const;
    virtual bool desires_influence_based_spawning(void) const;

    // f i (game_engine_campaign.obj)
    virtual bool desires_teleporters(void) const
    {
        return false;
    };
};
static_assert(sizeof(c_campaign_engine) == 0x4, "c_campaign_engine");

/* ---------- prototypes */

/* ---------- globals */

class c_game_engine;
extern c_game_engine * campaign_engine;

/* ---------- public code */

#endif // __GAME_ENGINE_CAMPAIGN_H__

