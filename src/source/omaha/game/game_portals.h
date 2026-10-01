#pragma once
#ifndef __GAME_PORTALS_H__
#define __GAME_PORTALS_H__

/* ---------- headers */

#include "omaha\cseries\location.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

extern s_portal_reference game_get_machine_door_portal_reference(long zone_set_index, long structure_bsp_index, long machine_door_portal_index);
extern long game_get_machine_door_portal_references_count(long zone_set_index, long structure_bsp_index);
extern s_portal_reference game_get_occluding_portal_reference(long zone_set_index, long structure_bsp_index, long occluding_portal_index);
extern long game_get_occluding_portal_references_count(long zone_set_index, long structure_bsp_index);
extern void game_clear_machine_door_portal_indices_count(long zone_set_index);
extern bool game_add_machine_door_portal_index(long zone_set_index, long structure_bsp_index, long portal_index, unsigned short * out_game_portal_index);
extern void game_clear_occluding_portal_indices(long zone_set_index, long structure_bsp_index);
extern bool game_add_occluding_portal_index(long zone_set_index, long structure_bsp_index, long portal_index);

/* ---------- globals */

/* ---------- public code */

#endif // __GAME_PORTALS_H__

