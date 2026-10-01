#pragma once
#ifndef __BOAT_EFFECTS_H__
#define __BOAT_EFFECTS_H__

/* ---------- headers */

/* ---------- constants */

/* ---------- definitions */

class c_particle_system;
class c_particle_emitter_definition;
union real_point3d;
union vector3d;

/* ---------- prototypes */

bool boat_effects_particle_spawn_has_begun(c_particle_emitter_definition const * emitter_def, c_particle_system const * system);
void boat_effects_get_particle_simulation_values(float * values);
bool boat_effects_boat_hull_compute_particle_position_and_velocity(long object_index, float emission_angle, real_point3d * position, vector3d * velocity);

/* ---------- globals */

/* ---------- public code */

#endif // __BOAT_EFFECTS_H__

