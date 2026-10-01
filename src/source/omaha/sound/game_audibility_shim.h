#pragma once
#ifndef __GAME_AUDIBILITY_SHIM_H__
#define __GAME_AUDIBILITY_SHIM_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"
#include "foundation\baselib\datatypes\static_array.h"
#include "omaha\cseries\location.h"
#include "omaha\memory\wrapped_arrays.h"

/* ---------- constants */

/* ---------- definitions */

struct s_game_audibility;

class c_game_audibility
{
public:
    c_game_audibility(long scenario_index, long active_zone_set_index);
    bool valid() const;
    void get_room_potential_door_set(s_cluster_reference room_cluster_reference, c_wrapped_flags * out_door_flags) const;
    float get_cluster_distance(s_cluster_reference start_cluster_reference, s_cluster_reference end_cluster_reference) const;
    float get_room_distance(long start_room_index, long end_room_index) const;
    long get_room_index(s_cluster_reference room_cluster_reference) const;
    void get_game_portal_index(long door_occluder_index, long * out_structure_bsp_index, long * out_game_portal_index) const;
    long get_occluded_door_side_of_room(long door_occluder_index, s_cluster_reference room_cluster_reference) const;
    void get_door_room_pas(long door_occluder_index, c_wrapped_flags * front_side_rooms, c_wrapped_flags * back_side_rooms) const;
    long get_closest_door_occluder_room_index_index(long door_occluder_index, long source_room_index);
    long get_room_count() const;
    bool get_room_ai_deafening(s_cluster_reference start_cluster_reference, s_cluster_reference end_cluster_reference) const;

private:
    s_game_audibility const * m_new_audibility; // 0x0
    s_static_array<c_wrapped_array<short const>, 16> m_cluster_reference_to_room_index; // 0x4
};
static_assert(sizeof(c_game_audibility) == 0x84, "c_game_audibility");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __GAME_AUDIBILITY_SHIM_H__

