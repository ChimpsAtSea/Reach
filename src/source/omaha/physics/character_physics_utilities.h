#pragma once
#ifndef __CHARACTER_PHYSICS_UTILITIES_H__
#define __CHARACTER_PHYSICS_UTILITIES_H__

/* ---------- headers */

/* ---------- constants */

/* ---------- definitions */

union vector3d;
struct s_character_physics_flying_definition;

/* ---------- prototypes */

bool character_physics_flying_update_turning(vector3d const * forward, vector3d const * up, vector3d const * translational_velocity, vector3d const * angular_velocity, s_character_physics_flying_definition const * flying, float dt, vector3d const * desired_facing_vector, vector3d const * throttle, float turning_threshold, float * bank, vector3d * out_forward, vector3d * out_up, vector3d * out_angular_velocity);
bool character_physics_flying_update_turning(long object_index, s_character_physics_flying_definition const * flying, float dt, vector3d const * desired_facing_vector, vector3d const * throttle, float turning_threshold, float * bank);

/* ---------- globals */

/* ---------- public code */

#endif // __CHARACTER_PHYSICS_UTILITIES_H__

