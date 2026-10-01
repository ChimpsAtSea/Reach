#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\effects\\contrail_states.cpp"
/* ---------- headers */

#include "omaha\effects\contrail_states.h"
#include "omaha\effects\contrails.h"
#include "omaha\effects\contrail_definitions.h"
#include "omaha\cseries\cseries.h"
#include "omaha\math\integer_math.h"
#include "omaha\math\real_math.h"
#include "graphicslib\render_time.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_events.h"
#include "core\corelib\cseries\cseries_macros.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

unsigned long c_contrail_states::x_force_used_states = 0;

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// public: static unsigned long c_contrail_states::x_force_used_states; // "?x_force_used_states@c_contrail_states@@2KA"

// public: static void c_contrail_states::allocate_random_seed(unsigned long *, unsigned char *);
// public: void c_contrail_states::update_states(unsigned long);
// public: float c_contrail_system::get_effect_scale_b(void) const;
// public: long c_contrail_system::get_lod(void) const;
// public: union vector3d const * c_contrail_location::get_velocity(void) const;
// public: float c_contrail::get_random_seed(long) const;
// public: float c_contrail_profile::get_random_seed(long) const;
// public: unsigned long c_contrail_states::get_contrail_system_used_states(void) const;
// public: void c_contrail_states::set_contrail_system(class c_contrail_system const *);
// public: void c_contrail_states::set_contrail_location(class c_contrail_location const *);
// public: void c_contrail_states::set_contrail(class c_contrail const *);

void c_contrail_states::allocate_random_seed(unsigned long * used_states, unsigned char * input)
{
    mangled_ppc("?allocate_random_seed@c_contrail_states@@SAXPAKPAE@Z");

    static unsigned long x_random_seed_index = 0;

    long new_input = _profile_random_seed_1;
    switch (*input)
    {
    case _profile_random:
        switch (highest_bit_set(*used_states & k_profile_random_seeds))
        {
        case NONE:
            new_input = _profile_random_seed_1;
            break;
        case _profile_random_seed_1:
            new_input = _profile_random_seed_2;
            break;
        case _profile_random_seed_2:
            new_input = _profile_random_seed_3;
            break;
        case _profile_random_seed_3:
            new_input = _profile_random_seed_4;
            break;
        case _profile_random_seed_4:
        {
            static long const k_random_seeds[] = { _profile_random_seed_1, _profile_random_seed_2, _profile_random_seed_3, _profile_random_seed_4 };

            event_wrapped(_event_message, "effects:contrails:Ran out of random seeds!");
            new_input = k_random_seeds[x_random_seed_index++ % NUMBEROF(k_random_seeds)];
        }
            break;
        default:
            dassert_tag_debug_untracked_jul_11_2011(55, false, "unreachable");
            break;
        }
        *input = static_cast<unsigned char>(new_input);
        *used_states |= FLAG(new_input);
        break;
    case _contrail_random:
        switch (highest_bit_set(*used_states & k_contrail_random_seeds))
        {
        case NONE:
            new_input = _contrail_random_seed_1;
            break;
        case _contrail_random_seed_1:
            new_input = _contrail_random_seed_2;
            break;
        case _contrail_random_seed_2:
        {
            static long const k_random_seeds[] = { _contrail_random_seed_1, _contrail_random_seed_2 };

            event_wrapped(_event_message, "effects:contrails:Ran out of random seeds!");
            new_input = k_random_seeds[x_random_seed_index++ % NUMBEROF(k_random_seeds)];
        }
            break;
        default:
            dassert_tag_debug_untracked_jul_11_2011(74, false, "unreachable");
            break;
        }
        *input = static_cast<unsigned char>(new_input);
        *used_states |= FLAG(new_input);
        break;
    }
};

void c_contrail_states::update_states(unsigned long states)
{
    mangled_ppc("?update_states@c_contrail_states@@QAAXK@Z");

    states = states & m_used_states & ~m_valid_states;
    if (states != 0)
    {
        if (TEST_MASK(states, k_dependent_on_profile_states))
        {
            m_state_values[_profile_age] = m_contrail_profile->get_age();
            m_state_values[_profile_random_seed_1] = m_contrail_profile->get_random_seed(0);
            m_state_values[_profile_random_seed_2] = m_contrail_profile->get_random_seed(1);
            m_state_values[_profile_random_seed_3] = m_contrail_profile->get_random_seed(2);
            m_state_values[_profile_random_seed_4] = m_contrail_profile->get_random_seed(3);
        }
        if (TEST_MASK(states, k_dependent_on_contrail_states))
        {
            m_state_values[_contrail_random_seed_1] = m_contrail->get_random_seed(0);
            m_state_values[_contrail_random_seed_2] = m_contrail->get_random_seed(1);
        }
        if (TEST_MASK(states, k_dependent_on_location_states))
        {
            m_state_values[_location_speed] = magnitude3d(m_contrail_location->get_velocity());
        }
        if (TEST_MASK(states, k_dependent_on_system_states))
        {
            m_state_values[_system_age] = m_contrail_system->get_age();
            m_state_values[_system_lod] = static_cast<float>(m_contrail_system->get_lod());
            m_state_values[_effect_a_scale] = m_contrail_system->get_effect_scale_a();
            m_state_values[_effect_b_scale] = m_contrail_system->get_effect_scale_b();
        }
        if (TEST_BIT(states, _game_time))
        {
            m_state_values[_game_time] = g_render_time.wrapped_seconds;
        }
        if (TEST_BIT(states, _profile_random) || TEST_BIT(states, _contrail_random))
        {
            event_wrapped(_event_error, "Called c_contrail_states::update_states with state of '_profile_random' or '_contrail_random'.  Need to first call allocate_random_seed, then clear this state.");
        }
    }
    m_valid_states |= states;
};

unsigned long c_contrail_states::get_contrail_system_used_states() const
{
    mangled_ppc("?get_contrail_system_used_states@c_contrail_states@@QBAKXZ");

    unsigned long states = 0;
    if (m_contrail_system != NULL)
    {
        c_contrail_system_definition const * contrail_system_definition = m_contrail_system->get_definition();
        for (long contrail_index = 0; contrail_index < contrail_system_definition->get_contrail_count(); contrail_index++)
        {
            c_contrail_definition const * contrail_definition = contrail_system_definition->get_contrail_definition(contrail_index);
            states |= contrail_definition->get_used_states();
        }
    }
    return states;
};

void c_contrail_states::set_contrail_system(c_contrail_system const * contrail_system)
{
    mangled_ppc("?set_contrail_system@c_contrail_states@@QAAXPBVc_contrail_system@@@Z");

    if (contrail_system != m_contrail_system)
    {
        m_used_states &= ~get_contrail_system_used_states();
        m_contrail_system = contrail_system;
        invalidate_states(k_dependent_on_system_states);
        m_used_states |= get_contrail_system_used_states();
        update_states(k_dependent_on_system_states | k_global_states);
    }
};

void c_contrail_states::set_contrail_location(c_contrail_location const * contrail_location)
{
    mangled_ppc("?set_contrail_location@c_contrail_states@@QAAXPBVc_contrail_location@@@Z");

    if (contrail_location != m_contrail_location)
    {
        m_contrail_location = contrail_location;
        invalidate_states(k_dependent_on_location_states);
        update_states(k_dependent_on_location_states);
    }
};

void c_contrail_states::set_contrail(c_contrail const * contrail)
{
    mangled_ppc("?set_contrail@c_contrail_states@@QAAXPBVc_contrail@@@Z");

    if (contrail != m_contrail)
    {
        m_contrail = contrail;
        invalidate_states(k_dependent_on_contrail_states);
        update_states(k_dependent_on_contrail_states);
    }
};

