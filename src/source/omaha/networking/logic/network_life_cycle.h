#pragma once
#ifndef __NETWORK_LIFE_CYCLE_H__
#define __NETWORK_LIFE_CYCLE_H__

/* ---------- headers */

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

class c_network_session;

bool network_life_cycle_in_squad_session(c_network_session ** out_active_squad_session);
bool network_life_cycle_in_group_session(c_network_session ** out_active_group_session);
bool network_life_cycle_in_target_session(c_network_session ** out_active_target_session);

/* ---------- globals */

/* ---------- public code */

#endif // __NETWORK_LIFE_CYCLE_H__

