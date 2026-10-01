#pragma once
#ifndef __DETERMINISM_DEBUG_CONSUMER_EFFECTS_H__
#define __DETERMINISM_DEBUG_CONSUMER_EFFECTS_H__

/* ---------- headers */

#include "omaha\saved_games\determinism_debug\determinism_debug_consumers.h"

/* ---------- constants */

/* ---------- definitions */

struct effect_datum;
struct event_datum;
struct effect_location_datum;

class c_game_state_consumer_effects :
    public c_game_state_consumer_datum_array<effect_datum>
{
public:
    virtual bool iterate_next(s_game_state_consumer_iterator * iterator);
    virtual unsigned long get_deterministic_item_checksum(unsigned long crc, long index, void const * game_state_base_address);
    virtual void get_deterministic_item_data(long index, void const * game_state_base_address, void * data_out, long max_size, long * size_out);
};
static_assert(sizeof(c_game_state_consumer_effects) == 0x4, "c_game_state_consumer_effects");

class c_game_state_consumer_events :
    public c_game_state_consumer_datum_array<event_datum>
{
public:
    virtual bool iterate_next(s_game_state_consumer_iterator * iterator);
};
static_assert(sizeof(c_game_state_consumer_events) == 0x4, "c_game_state_consumer_events");

class c_game_state_consumer_effect_locations :
    public c_game_state_consumer_datum_array<effect_location_datum>
{
public:
    virtual bool iterate_next(s_game_state_consumer_iterator * iterator);
};
static_assert(sizeof(c_game_state_consumer_effect_locations) == 0x4, "c_game_state_consumer_effect_locations");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __DETERMINISM_DEBUG_CONSUMER_EFFECTS_H__

