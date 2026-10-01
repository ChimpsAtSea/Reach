#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\effects\\beam_states.cpp"
/* ---------- headers */

#include "omaha\effects\beam_states.h"
#include "omaha\effects\beams.h"
#include "omaha\effects\beam_definitions.h"
#include "omaha\cseries\cseries.h"
#include "omaha\math\integer_math.h"
#include "graphicslib\render_time.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_events.h"
#include "core\corelib\cseries\cseries_macros.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

unsigned long c_beam_states::x_force_used_states = 0;

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// public: static unsigned long c_beam_states::x_force_used_states; // "?x_force_used_states@c_beam_states@@2KA"

// public: static void c_beam_states::allocate_random_seed(unsigned long *, unsigned char *);
// public: void c_beam_states::update_states(unsigned long);
// public: float c_beam_system::get_age(void) const;
// public: float c_beam_system::get_effect_scale_a(void) const;
// public: float c_beam_system::get_effect_scale_b(void) const;
// public: long c_beam_system::get_lod(void) const;
// public: float c_beam::get_random_seed(long) const;
// public: unsigned long c_beam_states::get_beam_system_used_states(void) const;
// public: void c_beam_states::set_beam_system(class c_beam_system const *);
// public: void c_beam_states::invalidate_states(unsigned long);
// public: void c_beam_states::set_beam_location(class c_beam_location const *);
// public: void c_beam_states::set_beam(class c_beam const *);

void c_beam_states::allocate_random_seed(unsigned long * used_states, unsigned char * input)
{
    mangled_ppc("?allocate_random_seed@c_beam_states@@SAXPAKPAE@Z");

    long new_input = _beam_random_seed_1;
    switch (*input)
    {
    case _beam_random:
        switch (highest_bit_set(*used_states & k_beam_random_seeds))
        {
        case NONE:
            new_input = _beam_random_seed_1;
            break;
        case _beam_random_seed_1:
            new_input = _beam_random_seed_2;
            break;
        case _beam_random_seed_2:
        {
            static long const k_random_seeds[] = { _beam_random_seed_1, _beam_random_seed_2 };
            static unsigned long x_random_seed_index = 0;

            event_wrapped(_event_message, "effects:beams:Ran out of random seeds!");
            new_input = k_random_seeds[x_random_seed_index++ % NUMBEROF(k_random_seeds)];
        }
            break;
        default:
            dassert_tag_debug_untracked_jul_11_2011(42, false, "unreachable");
            break;
        }
        *input = static_cast<unsigned char>(new_input);
        *used_states |= FLAG(new_input);
        break;
    }
};

void c_beam_states::update_states(unsigned long states)
{
    mangled_ppc("?update_states@c_beam_states@@QAAXK@Z");

    states = states & m_used_states & ~m_valid_states;
    if (states != 0)
    {
        if (TEST_MASK(states, k_dependent_on_profile_states))
        {
            dassert_tag_debug_untracked_jul_11_2011(62, false, "unreachable");
        }
        if (TEST_MASK(states, k_dependent_on_beam_states))
        {
            m_state_values[_beam_random_seed_1] = m_beam->get_random_seed(0);
            m_state_values[_beam_random_seed_2] = m_beam->get_random_seed(1);
            m_state_values[_beam_length] = m_beam->get_capped_length();
        }
        if (TEST_MASK(states, k_dependent_on_system_states))
        {
            m_state_values[_system_age] = m_beam_system->get_age();
            m_state_values[_system_lod] = static_cast<float>(m_beam_system->get_lod());
            m_state_values[_effect_a_scale] = m_beam_system->get_effect_scale_a();
            m_state_values[_effect_b_scale] = m_beam_system->get_effect_scale_b();
        }
        if (TEST_BIT(states, _game_time))
        {
            m_state_values[_game_time] = g_render_time.wrapped_seconds;
        }
        if (TEST_BIT(states, _beam_random))
        {
            event_wrapped(_event_error, "Called c_beam_states::update_states with state of '_beam_random'.  Need to first call allocate_random_seed, then clear this state.");
        }
    }
    m_valid_states |= states;
};

unsigned long c_beam_states::get_beam_system_used_states() const
{
    mangled_ppc("?get_beam_system_used_states@c_beam_states@@QBAKXZ");

    unsigned long states = 0;
    if (m_beam_system != NULL)
    {
        c_beam_system_definition const * beam_system_definition = m_beam_system->get_definition();
        for (long beam_index = 0; beam_index < beam_system_definition->get_beam_count(); beam_index++)
        {
            c_beam_definition const * beam_definition = beam_system_definition->get_beam_definition(beam_index);
            states |= beam_definition->get_used_states();
        }
    }
    return states;
};

void c_beam_states::set_beam_system(c_beam_system const * beam_system)
{
    mangled_ppc("?set_beam_system@c_beam_states@@QAAXPBVc_beam_system@@@Z");

    if (beam_system != m_beam_system)
    {
        m_used_states &= ~get_beam_system_used_states();
        m_beam_system = beam_system;
        invalidate_states(k_dependent_on_system_states);
        m_used_states |= get_beam_system_used_states();
        update_states(k_dependent_on_system_states | k_global_states);
    }
};

void c_beam_states::set_beam_location(c_beam_location const * beam_location)
{
    mangled_ppc("?set_beam_location@c_beam_states@@QAAXPBVc_beam_location@@@Z");

    if (beam_location != m_beam_location)
    {
        m_beam_location = beam_location;
        invalidate_states(k_dependent_on_location_states);
        update_states(k_dependent_on_location_states);
    }
};

void c_beam_states::set_beam(c_beam const * beam)
{
    mangled_ppc("?set_beam@c_beam_states@@QAAXPBVc_beam@@@Z");

    if (beam != m_beam)
    {
        m_beam = beam;
        invalidate_states(k_dependent_on_beam_states);
        update_states(k_dependent_on_beam_states);
    }
};

