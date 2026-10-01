#pragma once
#ifndef __PARTICLE_SIMULATION_H__
#define __PARTICLE_SIMULATION_H__

/* ---------- headers */

/* ---------- constants */

/* ---------- definitions */

class c_particle;
class c_particle_emitter;
class c_particle_system;
class c_particle_emitter_definition;
class c_particle_system_definition;

/* ---------- prototypes */

bool particle_simulation_emitter_should_pulse(c_particle_emitter const * emitter, c_particle_system const * system, c_particle_emitter_definition const * emitter_def, c_particle_system_definition const * system_def);
bool particle_simulation_is_particle_spawn_valid(c_particle_emitter const * emitter, c_particle_system const * system, c_particle_emitter_definition const * emitter_def);
void particle_simulation_get_particle_state_values(c_particle const * particle, c_particle_system_definition const * system_def, float * values);
bool particle_simulation_initialize_particle(c_particle * particle, c_particle_emitter const * emitter, c_particle_system const * system, c_particle_emitter_definition const * emitter_def);

/* ---------- globals */

/* ---------- public code */

#endif // __PARTICLE_SIMULATION_H__

