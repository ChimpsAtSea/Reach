#ifndef __CONTRAIL_STATES_H__
#define __CONTRAIL_STATES_H__
#pragma once

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"

/* ---------- constants */

/* ---------- definitions */

class c_contrail_system;
class c_contrail_location;
class c_contrail;
class c_contrail_profile;

class c_contrail_states
{
public:
    enum e_input
    {
        _profile_age = 0,
        _profile_random = 1,
        _profile_correlation_1 = 2,
        _profile_correlation_2 = 3,
        _profile_correlation_3 = 4,
        _profile_correlation_4 = 5,
        _game_time = 6,
        _system_age = 7,
        _contrail_random = 8,
        _contrail_correlation_1 = 9,
        _contrail_correlation_2 = 10,
        _location_speed = 11,
        _system_lod = 12,
        _effect_a_scale = 13,
        _effect_b_scale = 14,
        _invalid = 15,
        k_total_count = 16,
        _profile_random_seed_1 = 2,
        _profile_random_seed_2 = 3,
        _profile_random_seed_3 = 4,
        _profile_random_seed_4 = 5,
        _contrail_random_seed_1 = 9,
        _contrail_random_seed_2 = 10,
        k_all_states = 0xFFFF,
        k_virtual_states = 0x102,
        k_actual_states = 0xFEFD,
        k_profile_random_seeds = 0x3C,
        k_contrail_random_seeds = 0x600,
        k_dependent_on_system_states = 0x7080,
        k_independent_of_system_states = 0x8E7D,
        k_dependent_on_location_states = 0x800,
        k_independent_of_location_states = 0xF6FD,
        k_dependent_on_contrail_states = 0x600,
        k_independent_of_contrail_states = 0xF8FD,
        k_dependent_on_profile_states = 0x3D,
        k_independent_of_profile_states = 0xFEC0,
        k_global_states = 0x8040,
        k_changing_over_time_states = 0x70C1,
        k_static_over_time_states = -28866,
    };

    static void allocate_random_seed(unsigned long * used_states, unsigned char * input);
    void update_states(unsigned long states);
    unsigned long get_contrail_system_used_states() const;
    void set_contrail_system(c_contrail_system const * contrail_system);
    void set_contrail_location(c_contrail_location const * contrail_location);
    void set_contrail(c_contrail const * contrail);

    void invalidate_states(unsigned long states)
    {
        mangled_ppc("?invalidate_states@c_contrail_states@@QAAXK@Z");

        m_valid_states &= ~states;
    }

    static unsigned long x_force_used_states;

private:
    c_contrail_system const * m_contrail_system; // 0x0
    c_contrail_location const * m_contrail_location; // 0x4
    c_contrail const * m_contrail; // 0x8
    c_contrail_profile const * m_contrail_profile; // 0xC
    float m_state_values[k_total_count]; // 0x10
    unsigned long m_valid_states; // 0x50
    unsigned long m_used_states; // 0x54
};
static_assert(sizeof(c_contrail_states) == 0x58, "c_contrail_states");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __CONTRAIL_STATES_H__

