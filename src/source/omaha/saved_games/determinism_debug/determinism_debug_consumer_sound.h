#pragma once
#ifndef __DETERMINISM_DEBUG_CONSUMER_SOUND_H__
#define __DETERMINISM_DEBUG_CONSUMER_SOUND_H__

/* ---------- headers */

#include "omaha\saved_games\determinism_debug\determinism_debug_consumers.h"

/* ---------- constants */

/* ---------- definitions */

struct s_game_sound_impulse_datum;

class c_game_state_consumer_game_sound_scripted_impulses :
    public c_game_state_consumer_generic<s_game_sound_impulse_datum, 32>
{
public:
    virtual unsigned long get_deterministic_item_checksum(unsigned long crc, long index, void const * game_state_base_address);
    virtual void get_deterministic_item_data(long index, void const * game_state_base_address, void * data_out, long max_size, long * size_out);
};
static_assert(sizeof(c_game_state_consumer_game_sound_scripted_impulses) == 0x4, "c_game_state_consumer_game_sound_scripted_impulses");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __DETERMINISM_DEBUG_CONSUMER_SOUND_H__

