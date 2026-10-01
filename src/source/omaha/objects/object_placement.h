#pragma once
#ifndef __OBJECT_PLACEMENT_H__
#define __OBJECT_PLACEMENT_H__

/* ---------- headers */

/* ---------- constants */

/* ---------- definitions */

struct s_object_placement_data;
struct s_damage_owner;

/* ---------- prototypes */

void object_placement_data_new(s_object_placement_data * data, long definition_index, long owner_object_index, s_damage_owner const * damage_owner);
void object_placement_restore(long game_state_proc_flags);
void object_placement_synchronize_for_designer_zone_debugger(bool force);

/* ---------- globals */

/* ---------- public code */

#endif // __OBJECT_PLACEMENT_H__

