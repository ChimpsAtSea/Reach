#pragma once
#ifndef __GAME_AUDIBILITY_H__
#define __GAME_AUDIBILITY_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"
#include "omaha\tag_files\tag_groups.h"

/* ---------- constants */

/* ---------- definitions */

struct s_game_audibility_bsp_mapping
{
    long first_room_index_index; // 0x0
    long room_index_count; // 0x4
};
static_assert(sizeof(s_game_audibility_bsp_mapping) == 0x8, "s_game_audibility_bsp_mapping");

struct s_game_audibility
{
    long door_occluder_count; // 0x0
    long room_count; // 0x4
    float minimum_room_distance; // 0x8
    float maximum_room_distance; // 0xC
    s_tag_block door_portals_encoded_pas; // 0x10
    s_tag_block room_door_portal_encoded_pas; // 0x1C
    s_tag_block ai_deafening_encoded_pas; // 0x28
    s_tag_block room_to_room_encoded_distances; // 0x34
    s_tag_block game_portal_to_door_occluder_mapping; // 0x40
    s_tag_block bsp_cluster_to_room_index_bounds; // 0x4C s_game_audibility_bsp_mapping
    s_tag_block cluster_reference_to_room_index_storage; // 0x58 short
};
static_assert(sizeof(s_game_audibility) == 0x64, "s_game_audibility");

/* ---------- prototypes */

class c_wrapped_flags;

extern bool audibility_get_room_ai_deafening(s_game_audibility const * audibility, long listener_room_index, long source_room_index);
extern void audibility_get_door_room_pas(s_game_audibility const * audibility, long door_occluder_index, c_wrapped_flags * out_front_pas, c_wrapped_flags * out_back_pas);
extern void audibility_get_room_potential_door_set(s_game_audibility const * audibility, long room_index, c_wrapped_flags * out_room_door_flags);
extern float audibility_get_room_distance(s_game_audibility const * audibility, long start_room_index, long end_room_index);
extern void audibility_door_occluder_to_game_portal_index(s_game_audibility const * audibility, long door_occluder_index, long * out_structure_bsp_index, long * out_game_portal_index);
extern long audibility_get_closest_door_portal_room_index_index(s_game_audibility const * audibility, long door_occluder_index, long source_room_index);

/* ---------- globals */

/* ---------- public code */

#endif // __GAME_AUDIBILITY_H__

