#pragma once
#ifndef __SIMULATION_QUEUE_GLOBAL_EVENTS_H__
#define __SIMULATION_QUEUE_GLOBAL_EVENTS_H__

/* ---------- headers */

/* ---------- constants */

// Reach: game_finish = 1 (game_engine_finish_game); other values unverified (H3 had game_simulation_server at 1)
enum e_simulation_queue_game_global_event_type
{
    _simulation_queue_game_global_event_type_claim_authority_gameworld = 0,
    _simulation_queue_game_global_event_type_game_finish,
};

/* ---------- definitions */

/* ---------- prototypes */

extern void simulation_queue_game_global_event_insert(e_simulation_queue_game_global_event_type event_type);

/* ---------- globals */

/* ---------- public code */

#endif // __SIMULATION_QUEUE_GLOBAL_EVENTS_H__

