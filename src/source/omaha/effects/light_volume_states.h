#pragma once
#ifndef __LIGHT_VOLUME_STATES_H__
#define __LIGHT_VOLUME_STATES_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"

/* ---------- constants */

/* ---------- definitions */

class c_light_volume_system;
class c_light_volume_location;
class c_light_volume;

class c_light_volume_states
{
public:
    enum e_input
    {
        _profile_percentile = 0,
        _game_time = 1,
        _system_age = 2,
        _light_volume_random = 3,
        _light_volume_correlation_1 = 4,
        _light_volume_correlation_2 = 5,
        _system_lod = 6,
        _effect_a_scale = 7,
        _effect_b_scale = 8,
        _invalid = 9,
        k_total_count = 10,
        _light_volume_random_seed_1 = 4,
        _light_volume_random_seed_2 = 5,
        k_all_states = 0x3FF,
        k_virtual_states = 0x9,
        k_actual_states = 0x3F6,
        k_light_volume_random_seeds = 0x30,
        k_dependent_on_system_states = 0x1C4,
        k_independent_of_system_states = 0x232,
        k_dependent_on_location_states = 0x0,
        k_independent_of_location_states = 0x3F6,
        k_dependent_on_light_volume_states = 0x30,
        k_independent_of_light_volume_states = 0x3C6,
        k_dependent_on_profile_states = 0x1,
        k_independent_of_profile_states = 0x3F6,
        k_global_states = 0x202,
        k_changing_over_time_states = 0x1C6,
        k_static_over_time_states = -455,
    };

    static void allocate_random_seed(unsigned long * used_states, unsigned char * input);
    void update_states(unsigned long states);
    unsigned long get_light_volume_system_used_states() const;
    void set_light_volume_system(c_light_volume_system const * light_volume_system);
    void set_light_volume_location(c_light_volume_location const * light_volume_location);
    void set_light_volume(c_light_volume const * light_volume);

    void invalidate_states(unsigned long states)
    {
        mangled_ppc("?invalidate_states@c_light_volume_states@@QAAXK@Z");

        m_valid_states &= ~states;
    }

    static unsigned long x_force_used_states;

private:
    c_light_volume_system const * m_light_volume_system; // 0x0
    c_light_volume_location const * m_light_volume_location; // 0x4
    c_light_volume const * m_light_volume; // 0x8
    float m_state_values[k_total_count]; // 0xC
    unsigned long m_valid_states; // 0x34
    unsigned long m_used_states; // 0x38
};
static_assert(sizeof(c_light_volume_states) == 0x3C, "c_light_volume_states");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __LIGHT_VOLUME_STATES_H__

