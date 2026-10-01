#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\effects\\particle_states.cpp"
/* ---------- headers */

#include "omaha\effects\particle_states.h"
#include "omaha\effects\particle.h"
#include "omaha\effects\particle_definitions.h"
#include "omaha\effects\particle_location.h"
#include "omaha\effects\particle_simulation.h"
#include "omaha\effects\particle_system.h"
#include "omaha\effects\particle_system_definitions.h"
#include "omaha\cseries\cseries.h"
#include "omaha\math\integer_math.h"
#include "graphicslib\render_time.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_events.h"
#include "core\corelib\cseries\cseries_macros.h"

/* ---------- constants */

// a const variable (not a literal) keeps /Od from folding the division below
static float const k_unsigned_short_max_real = UNSIGNED_SHORT_MAX;

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

unsigned long c_particle_state_list::x_force_used_states = 0;

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// private: static unsigned long c_particle_state_list::x_force_used_states; // "?x_force_used_states@c_particle_state_list@@0KA"

// private: void c_particle_state_list::update_states_internal(unsigned long);
// public: float c_particle_system::get_age(void) const;
// public: float c_particle_system::get_random_seed(unsigned long) const;
// public: float c_particle_location::get_lod_amount(void) const;
// public: float c_particle_location::get_random_seed(void) const;
// public: unsigned long c_particle_state_list::get_particle_system_used_states(void) const;
// public: long c_particle_definition::get_used_particle_states(void) const;
// public: void c_particle_state_list::set_particle_system(class c_particle_system const *);
// public: void c_particle_state_list::update_states(unsigned long);
// public: void c_particle_state_list::set_particle_location(class c_particle_location const *);
// public: static void c_particle_state_list::allocate_random_seed(unsigned long *, unsigned char *);

void c_particle_state_list::update_states_internal(unsigned long states)
{
    mangled_ppc("?update_states_internal@c_particle_state_list@@AAAXK@Z");

    if ((m_particle == NULL && TEST_MASK(states, k_need_particle_states))
        || (m_particle_location == NULL && TEST_MASK(states, k_need_location_states))
        || (m_particle_system == NULL && TEST_MASK(states, k_need_system_states)))
    {
        event_wrapped(_event_error, "effects:particles:Missing necessary information for particle state evaluation.");
    }
    else
    {
        if (TEST_MASK(states, k_particle_states))
        {
            float short_to_real_scale = 1.0f / k_unsigned_short_max_real;
            m_state_values[_particle_age] = m_particle->m_age;
            m_state_values[_particle_emit_time] = m_particle->m_emission_time;
            m_state_values[_particle_random_seed_1] = m_particle->m_random_seed[0] * short_to_real_scale;
            m_state_values[_particle_random_seed_2] = m_particle->m_random_seed[1] * short_to_real_scale;
            m_state_values[_particle_random_seed_3] = m_particle->m_random_seed[2] * short_to_real_scale;
            m_state_values[_particle_random_seed_4] = m_particle->m_random_seed[3] * short_to_real_scale;
            m_state_values[_particle_random_seed_5] = m_particle->m_random_seed[4] * short_to_real_scale;
            m_state_values[_particle_random_seed_6] = m_particle->m_random_seed[5] * short_to_real_scale;
            m_state_values[_particle_random_seed_7] = m_particle->m_random_seed[6] * short_to_real_scale;
            m_state_values[_particle_random_seed_8] = m_particle->m_random_seed[7] * short_to_real_scale;
        }
        if (TEST_MASK(states, k_system_states))
        {
            m_state_values[_system_age] = m_particle_system->get_age();
            m_state_values[_system_random_seed_1] = m_particle_system->get_random_seed(0);
            m_state_values[_system_random_seed_2] = m_particle_system->get_random_seed(1);
            m_state_values[_system_random_seed_3] = m_particle_system->get_random_seed(2);
            m_state_values[_system_random_seed_4] = m_particle_system->get_random_seed(3);
        }
        if (TEST_MASK(states, k_location_states))
        {
            m_state_values[_location_lod] = m_particle_location->get_lod_amount();
            m_state_values[_location_random_seed_1] = m_particle_location->get_random_seed();
        }
        if (TEST_BIT(states, _game_time))
        {
            m_state_values[_game_time] = g_render_time.wrapped_periods[2];
        }
        if (TEST_BIT(states, _object_a_out))
        {
            m_state_values[_object_a_out] = m_particle_system->get_exported_function(0);
        }
        if (TEST_BIT(states, _object_b_out))
        {
            m_state_values[_object_b_out] = m_particle_system->get_exported_function(1);
        }
        if (TEST_MASK(states, FLAG(_particle_simulation_a) | FLAG(_particle_simulation_b)))
        {
            particle_simulation_get_particle_state_values(m_particle, m_particle_system_definition, &m_state_values[_particle_simulation_a]);
        }
        if (TEST_BIT(states, _particle_rotation))
        {
            m_state_values[_particle_rotation] = 0.0f;
        }
        if (TEST_BIT(states, _particle_random_seed) || TEST_BIT(states, _system_random_seed))
        {
            event_wrapped(_event_error, "Called c_particle_state_list::update_states_internal with state of '_particle_random_seed' or '_system_random_seed'.  Need to first call allocate_random_seed, then clear this state.");
        }
    }
};

unsigned long c_particle_state_list::get_particle_system_used_states(void) const
{
    mangled_ppc("?get_particle_system_used_states@c_particle_state_list@@QBAKXZ");

    unsigned long states = 0;
    if (m_particle_system_definition != NULL)
    {
        c_particle_definition const * particle_def = m_particle_system_definition->get_particle_definition();
        states |= particle_def->get_used_particle_states();
        for (long emitter_index = 0; emitter_index < m_particle_system_definition->m_emitters.count; emitter_index++)
        {
            c_particle_emitter_definition const * emitter_def = m_particle_system_definition->get_emitter(emitter_index);
            states |= emitter_def->get_used_particle_states();
        }
    }

    return states;
};

void c_particle_state_list::set_particle_system(c_particle_system const * system)
{
    mangled_ppc("?set_particle_system@c_particle_state_list@@QAAXPBVc_particle_system@@@Z");

    if (system != m_particle_system)
    {
        m_used_states &= ~get_particle_system_used_states();
        m_particle_system = system;
        m_particle_system_definition = system->get_particle_system_definition();
        m_updated_states &= ~k_system_states;
        m_used_states |= get_particle_system_used_states();
        update_states(k_system_states | k_global_states);
    }
};

void c_particle_state_list::update_states(unsigned long states)
{
    mangled_ppc("?update_states@c_particle_state_list@@QAAXK@Z");

    unsigned long actual_states = states & m_used_states & ~m_updated_states & ~k_pseudo_states;
    if (actual_states != 0)
    {
        update_states_internal(actual_states);
        m_updated_states |= actual_states;
    }
};

void c_particle_state_list::set_particle_location(c_particle_location const * location)
{
    mangled_ppc("?set_particle_location@c_particle_state_list@@QAAXPBVc_particle_location@@@Z");

    if (location != m_particle_location)
    {
        m_particle_location = location;
        m_updated_states &= ~k_location_states;
        update_states(k_location_states);
    }
};

void c_particle_state_list::allocate_random_seed(unsigned long * used_states, unsigned char * state)
{
    mangled_ppc("?allocate_random_seed@c_particle_state_list@@SAXPAKPAE@Z");

    static unsigned long x_random_seed_index = 0;

    switch (*state)
    {
    case _particle_random_seed:
    {
        long state_index = highest_bit_set(~*used_states & k_particle_random_seeds);
        if (state_index == NONE)
        {
            static long const k_random_seeds[] = { _particle_random_seed_5, _particle_random_seed_4, _particle_random_seed_6, _particle_random_seed_3, _particle_random_seed_7, _particle_random_seed_2, _particle_random_seed_8, _particle_random_seed_1 };

            event_wrapped(_event_message, "effects:particles:Ran out of random seeds!");
            *state = static_cast<unsigned char>(k_random_seeds[x_random_seed_index++ % NUMBEROF(k_random_seeds)]);
        }
        else
        {
            *state = static_cast<unsigned char>(state_index);
        }
        *used_states |= FLAG(*state);
    }
        break;
    case _system_random_seed:
    {
        long state_index = highest_bit_set(~*used_states & k_system_random_seeds);
        if (state_index == NONE)
        {
            static long const k_random_seeds[] = { _system_random_seed_4, _system_random_seed_3, _system_random_seed_2, _system_random_seed_1 };

            event_wrapped(_event_message, "effects:particles:Ran out of random seeds!");
            *state = static_cast<unsigned char>(k_random_seeds[x_random_seed_index++ % NUMBEROF(k_random_seeds)]);
        }
        else
        {
            *state = static_cast<unsigned char>(state_index);
        }
        *used_states |= FLAG(*state);
    }
        break;
    }
};

