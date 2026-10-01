#ifndef __PARTICLE_STATES_H__
#define __PARTICLE_STATES_H__
#pragma once

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"

/* ---------- constants */

/* ---------- definitions */

class c_particle_system;
class c_particle_system_definition;
class c_particle_location;
class c_particle;

class c_particle_state_list
{
public:
    enum e_particle_state_input
    {
        _particle_age = 0,
        _system_age,
        _particle_random_seed,
        _system_random_seed,
        _particle_correlation_1,
        _particle_correlation_2,
        _particle_correlation_3,
        _particle_correlation_4,
        _system_correlation_1,
        _system_correlation_2,
        _particle_emit_time,
        _location_lod,
        _game_time,
        _object_a_out,
        _object_b_out,
        _particle_rotation,
        _location_random_seed_1,
        _particle_distance_from_emitter,
        _particle_simulation_a,
        _particle_simulation_b,
        _particle_velocity,
        _invalid,
        k_static_count,

        _particle_random_seed_1 = _particle_correlation_1,
        _particle_random_seed_2 = _particle_correlation_2,
        _particle_random_seed_3 = _particle_correlation_3,
        _particle_random_seed_4 = _particle_correlation_4,
        _system_random_seed_1 = _system_correlation_1,
        _system_random_seed_2 = _system_correlation_2,
        _particle_random_seed_5 = k_static_count,
        _particle_random_seed_6,
        _particle_random_seed_7,
        _particle_random_seed_8,
        _system_random_seed_3,
        _system_random_seed_4,
        k_total_count,

        k_particle_random_seeds = 0x03C000F0,
        k_system_random_seeds = 0x0C000300,
        k_pseudo_states = 0x0000000C,
        k_particle_states = 0x03DE84F1,
        k_system_states = 0x0C006302,
        k_location_states = 0x00010800,
        k_global_states = 0x00201000,
        k_need_particle_states = 0x03DE84F5,
        k_need_system_states = 0x0C00630A,
        k_need_location_states = 0x00030800,
    };

    void update_states(unsigned long states);
    unsigned long get_particle_system_used_states(void) const;
    void set_particle_system(c_particle_system const * system);
    void set_particle_location(c_particle_location const * location);
    static void allocate_random_seed(unsigned long * used_states, unsigned char * state);

private:
    void update_states_internal(unsigned long states);

    static unsigned long x_force_used_states;

    float m_state_values[k_total_count]; // 0x0
    unsigned long m_used_states; // 0x70
    unsigned long m_updated_states; // 0x74
    c_particle_system const * m_particle_system; // 0x78
    c_particle_system_definition const * m_particle_system_definition; // 0x7C
    c_particle_location const * m_particle_location; // 0x80
    c_particle const * m_particle; // 0x84
};
static_assert(sizeof(c_particle_state_list) == 0x88, "c_particle_state_list");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __PARTICLE_STATES_H__

