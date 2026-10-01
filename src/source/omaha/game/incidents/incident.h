#pragma once
#ifndef __INCIDENT_H__
#define __INCIDENT_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_events.h"
#include "omaha\game\incidents\incident_definitions.h"

/* ---------- constants */

/* ---------- definitions */

// $TODO partial: 0x12 s_damage_reporting_info, 0x14 c_flags<e_incident_special_kill_type, unsigned long, 11> special kill flags; full size unknown
struct s_incident_metadata
{
    long cause_player_index; // 0x0
    long cause_object_index; // 0x4
    long effect_player_index; // 0x8
    long effect_object_index; // 0xC
};

/* ---------- prototypes */

void incident_initialize_for_saved_game(long game_state_proc_flags);
s_incident_definition const * incident_globals_find_incident_by_name(long incident_name);
void incident_event_with_information(e_event_level event_level, char const * information, long incident_name, s_incident_metadata const & incident);

/* ---------- globals */

/* ---------- public code */

#endif // __INCIDENT_H__

