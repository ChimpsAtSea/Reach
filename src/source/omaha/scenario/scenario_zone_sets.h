#pragma once
#ifndef __SCENARIO_ZONE_SETS_H__
#define __SCENARIO_ZONE_SETS_H__

/* ---------- headers */

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

struct scenario;
struct s_scenario_game_state;

unsigned long scenario_zone_set_bsp_active_mask_get(long zone_set_index);
unsigned long scenario_zone_set_designer_zone_required_mask_get(long zone_set_index);
unsigned long scenario_zone_set_designer_zone_forbidden_mask_get(long zone_set_index);
unsigned long scenario_zone_set_cinematic_zone_required_mask_get(long zone_set_index);
unsigned long scenario_zone_set_get_valid_designer_zones(long zone_set_index, unsigned long designer_zone_mask);
unsigned long scenario_zone_set_compute_new_designer_zone_mask(unsigned long current_designer_zone_mask, unsigned long required_designer_zone_mask, unsigned long forbidden_designer_zone_mask);
bool scenario_zone_set_switch_loads_anything(s_scenario_game_state const * scenario_game_state, long pending_zone_set_index);
long scenario_get_designer_zone_index_by_name(scenario const * scenario, char const * designer_zone_name);
char const * scenario_get_designer_zone_name(scenario const * scenario, long designer_zone_index);
char const * scenario_get_cinematic_zone_name(scenario const * scenario, long cinematic_zone_index);

/* ---------- globals */

/* ---------- public code */

#endif // __SCENARIO_ZONE_SETS_H__

