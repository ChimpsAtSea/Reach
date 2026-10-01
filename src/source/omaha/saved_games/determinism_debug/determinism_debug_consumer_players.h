#pragma once
#ifndef __DETERMINISM_DEBUG_CONSUMER_PLAYERS_H__
#define __DETERMINISM_DEBUG_CONSUMER_PLAYERS_H__

/* ---------- headers */

#include "omaha\saved_games\determinism_debug\determinism_debug_consumers.h"

/* ---------- constants */

/* ---------- definitions */

struct player_datum;

class c_game_state_consumer_players :
    public c_game_state_consumer_datum_array<player_datum>
{
public:
    virtual unsigned long get_deterministic_item_checksum(unsigned long crc, long index, void const * game_state_base_address);
    virtual void get_deterministic_item_data(long index, void const * game_state_base_address, void * data_out, long max_size, long * size_out);
};
static_assert(sizeof(c_game_state_consumer_players) == 0x4, "c_game_state_consumer_players");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __DETERMINISM_DEBUG_CONSUMER_PLAYERS_H__

