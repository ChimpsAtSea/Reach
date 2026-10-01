#pragma once
#ifndef __EFFECT_SCENERY_H__
#define __EFFECT_SCENERY_H__

/* ---------- headers */

/* ---------- constants */

/* ---------- definitions */

struct s_scenario_effect_scenery;
struct s_object_placement_data;
struct real_matrix4x3;

/* ---------- prototypes */

void effect_scenery_initialize_for_new_structure_bsp(long structure_bsp_index);
void effect_scenery_place(long effect_scenery_index, s_scenario_effect_scenery * scenario_effect_scenery);
bool effect_scenery_new(long effect_scenery_index, s_object_placement_data * placement_data, bool * out_of_memory);
void effect_scenery_delete(long effect_scenery_index);
bool effect_scenery_update(long effect_scenery_index);
void effect_scenery_preprocess_root_node_matrix(long effect_scenery_index, real_matrix4x3 * matrix);
void effect_scenery_render_debug(long effect_scenery_index);

/* ---------- globals */

extern bool g_debug_objects_effect_scenery;

/* ---------- public code */

#endif // __EFFECT_SCENERY_H__

