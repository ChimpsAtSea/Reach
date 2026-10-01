#pragma once
#ifndef __GAME_ENGINE_EVENTS_H__
#define __GAME_ENGINE_EVENTS_H__

/* ---------- headers */

#include "omaha\game\incidents\incident_definitions.h"

/* ---------- constants */

/* ---------- definitions */

struct s_incident_metadata;

/* ---------- prototypes */

void game_engine_event_play(long event_name, c_flags<e_suppressed_incident_flags, unsigned char, k_suppressed_incident_flags_count> const & suppressed_flags, s_incident_metadata const & incident);

/* ---------- globals */

/* ---------- public code */

#endif // __GAME_ENGINE_EVENTS_H__

