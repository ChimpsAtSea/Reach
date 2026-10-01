#pragma once
#ifndef __JETWASH_H__
#define __JETWASH_H__

/* ---------- headers */

#include "omaha\math\real_math.h"
#include "core\corelib\cseries\cseries_macros.h"

/* ---------- constants */

/* ---------- definitions */

// jetwash_definition_block
struct s_jetwash_definition
{
    long marker_name; // 0x0
    float radius; // 0x4
    long maximum_traces; // 0x8
    float maximum_emission_length; // 0xC
    real_bounds trace_yaw_angle; // 0x10
    real_bounds trace_pitch_angle; // 0x18
    float particle_offset; // 0x20
};
static_assert(sizeof(s_jetwash_definition) == 0x24, "s_jetwash_definition");

class c_particle_emitter;
class c_particle_system;
class c_particle_emitter_definition;
class c_particle_system_definition;
union real_point3d;
union vector3d;

/* ---------- prototypes */

bool jetwash_emitter_should_pulse(c_particle_emitter const * emitter, c_particle_system const * system, c_particle_emitter_definition const * emitter_def, c_particle_system_definition const * system_def);
bool jetwash_prepare_for_particle_spawn(c_particle_emitter const * emitter, c_particle_system const * system, c_particle_emitter_definition const * emitter_def);
void jetwash_get_particle_simulation_values(float * values);
bool jetwash_compute_particle_position_and_velocity(long object_index, float emission_angle, real_point3d * position, vector3d * velocity);

/* ---------- globals */

/* ---------- public code */

#endif // __JETWASH_H__

