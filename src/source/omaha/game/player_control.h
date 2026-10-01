#pragma once
#ifndef __PLAYER_CONTROL_H__
#define __PLAYER_CONTROL_H__

/* ---------- headers */

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

enum e_output_user_index;
union vector3d;

void player_control_get_aiming_vector(e_output_user_index output_user_index, vector3d * aiming_vector);

/* ---------- globals */

/* ---------- public code */

#endif // __PLAYER_CONTROL_H__

