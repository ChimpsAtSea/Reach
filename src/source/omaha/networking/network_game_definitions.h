#pragma once
#ifndef __NETWORK_GAME_DEFINITIONS_H__
#define __NETWORK_GAME_DEFINITIONS_H__

/* ---------- headers */

/* ---------- constants */

// names/values from H3; synchronous (1) per c_campaign_engine::get_simulation_protocol
enum e_network_game_simulation_protocol
{
    _network_game_simulation_protocol_local = 0,
    _network_game_simulation_protocol_synchronous,
    _network_game_simulation_protocol_distributed,

    k_network_game_simulation_protocol_count
};

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __NETWORK_GAME_DEFINITIONS_H__

