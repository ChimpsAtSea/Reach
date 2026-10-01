#pragma once
#ifndef __CHARACTER_PHYSICS_MODE_FLYING_H__
#define __CHARACTER_PHYSICS_MODE_FLYING_H__

/* ---------- headers */

#include "omaha\math\real_math.h"
#include "core\corelib\cseries\cseries_macros.h"

/* ---------- constants */

/* ---------- definitions */

struct s_character_physics_update_output_datum;
struct s_character_physics_update_input_datum;
struct s_character_physics_move_output_datum;
struct s_character_physics_move_input_datum;

class c_character_physics_mode_flying_datum
{
public:
    void initialize();
    void dispose();
    void update(s_character_physics_update_output_datum * physics_output, s_character_physics_update_input_datum const * physics_input);
    void snap_facing(vector3d * forward, vector3d * up, s_character_physics_update_input_datum const * physics_input);
    static void update_animation(s_character_physics_update_output_datum * character_physics_update_output_datum, s_character_physics_update_input_datum const * character_physics_update_input_datum);
    static void move(s_character_physics_move_output_datum * character_physics_move_output_datum, s_character_physics_move_input_datum const * character_physics_move_input_datum);
    void disable_turning();
    bool is_turning_disabled() const;

    long m_turning_disabled_counter; // 0x0
    vector3d m_uprighting_angular_velocity; // 0x4
};
static_assert(sizeof(c_character_physics_mode_flying_datum) == 0x10, "c_character_physics_mode_flying_datum");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __CHARACTER_PHYSICS_MODE_FLYING_H__

