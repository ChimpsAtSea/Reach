#pragma once
#ifndef __SCENARIO_SKY_H__
#define __SCENARIO_SKY_H__

/* ---------- headers */

/* ---------- constants */

/* ---------- definitions */

struct scenario;
struct s_game_cluster_bit_vectors;

class c_scenerio_sky_objects_helper
{
public:
    static void create_sky_objects(scenario const * scenario);
    static long create_sky_object(long scenario_sky_index);
    static s_game_cluster_bit_vectors const * calculate_sky_object_cluster_visibility(long object_index, s_game_cluster_bit_vectors * cluster_visibility);
};

/* ---------- prototypes */

void scenario_sky_objects_initialize(void);
void scenario_sky_objects_dispose(void);
void scenario_sky_objects_initialize_for_new_map(void);
void scenario_sky_objects_dispose_from_old_map(void);
long scenario_cluster_get_attached_sky_reference_index(long scenario_index, long structure_bsp_index, long cluster_index);

/* ---------- globals */

/* ---------- public code */

#endif // __SCENARIO_SKY_H__

