#ifndef __BEAM_STATES_H__
#define __BEAM_STATES_H__
#pragma once

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"

/* ---------- constants */

/* ---------- definitions */

class c_beam_system;
class c_beam_location;
class c_beam;

class c_beam_states
{
public:
    enum e_input
    {
        _profile_capped_percentile = 0,
        _profile_uncapped_percentile = 1,
        _game_time = 2,
        _system_age = 3,
        _beam_random = 4,
        _beam_correlation_1 = 5,
        _beam_correlation_2 = 6,
        _beam_length = 7,
        _system_lod = 8,
        _effect_a_scale = 9,
        _effect_b_scale = 10,
        _invalid = 11,
        k_total_count = 12,
        _beam_random_seed_1 = 5,
        _beam_random_seed_2 = 6,
        k_all_states = 0xFFF,
        k_virtual_states = 0x13,
        k_actual_states = 0xFEC,
        k_beam_random_seeds = 0x60,
        k_dependent_on_system_states = 0x708,
        k_independent_of_system_states = 0x8E4,
        k_dependent_on_location_states = 0x0,
        k_independent_of_location_states = 0xFEC,
        k_dependent_on_beam_states = 0x60,
        k_independent_of_beam_states = 0xF8C,
        k_dependent_on_profile_states = 0x3,
        k_independent_of_profile_states = 0xFEC,
        k_global_states = 0x884,
        k_changing_over_time_states = 0x70C,
        k_static_over_time_states = -1805,
    };

    static void allocate_random_seed(unsigned long * used_states, unsigned char * input);
    void update_states(unsigned long states);
    unsigned long get_beam_system_used_states() const;
    void set_beam_system(c_beam_system const * beam_system);
    void set_beam_location(c_beam_location const * beam_location);
    void set_beam(c_beam const * beam);

    void invalidate_states(unsigned long states)
    {
        mangled_ppc("?invalidate_states@c_beam_states@@QAAXK@Z");

        m_valid_states &= ~states;
    }

    static unsigned long x_force_used_states;

private:
    c_beam_system const * m_beam_system; // 0x0
    c_beam_location const * m_beam_location; // 0x4
    c_beam const * m_beam; // 0x8
    float m_state_values[k_total_count]; // 0xC
    unsigned long m_valid_states; // 0x3C
    unsigned long m_used_states; // 0x40
};
static_assert(sizeof(c_beam_states) == 0x44, "c_beam_states");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __BEAM_STATES_H__

