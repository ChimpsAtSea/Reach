#pragma once
#ifndef __OBJECT_EARLY_MOVERS_H__
#define __OBJECT_EARLY_MOVERS_H__

/* ---------- headers */

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

union vector3d;

bool object_get_early_mover_local_space_velocity(long moving_object_index, vector3d * linear_local_space_velocity, vector3d * angular_local_space_velocity, bool localized_physics_early_movers_only, bool current);

/* ---------- globals */

/* ---------- public code */

#endif // __OBJECT_EARLY_MOVERS_H__

