#pragma once
#ifndef __SIMULATION_H__
#define __SIMULATION_H__

/* ---------- headers */

/* ---------- constants */

/* ---------- definitions */

struct s_network_configuration;

/* ---------- prototypes */

s_network_configuration & get_network_configuration();
void simulation_prepare_to_load_saved_game(long game_state_proc_flags);
void simulation_initialize_for_saved_game(long game_state_proc_flags);

/* ---------- globals */

/* ---------- public code */

#endif // __SIMULATION_H__

