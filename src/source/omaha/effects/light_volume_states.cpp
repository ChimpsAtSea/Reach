#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\effects\\light_volume_states.cpp"
/* ---------- headers */

#include "omaha\effects\light_volume_states.h"
#include "omaha\effects\light_volumes.h"
#include "omaha\effects\light_volume_definitions.h"
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

unsigned long c_light_volume_states::x_force_used_states = 0;

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// public: static unsigned long c_light_volume_states::x_force_used_states; // "?x_force_used_states@c_light_volume_states@@2KA"

// public: static void c_light_volume_states::allocate_random_seed(unsigned long *, unsigned char *);
// public: void c_light_volume_states::update_states(unsigned long);
// public: float c_light_volume_system::get_age(void) const;
// public: float c_light_volume_system::get_effect_scale_a(void) const;
// public: float c_light_volume_system::get_effect_scale_b(void) const;
// public: long c_light_volume_system::get_lod(void) const;
// public: float c_light_volume::get_random_seed(long) const;
// public: unsigned long c_light_volume_states::get_light_volume_system_used_states(void) const;
// public: void c_light_volume_states::set_light_volume_system(class c_light_volume_system const *);
// public: void c_light_volume_states::invalidate_states(unsigned long);
// public: void c_light_volume_states::set_light_volume_location(class c_light_volume_location const *);
// public: void c_light_volume_states::set_light_volume(class c_light_volume const *);

void c_light_volume_states::allocate_random_seed(unsigned long * used_states, unsigned char * input)
{
    mangled_ppc("?allocate_random_seed@c_light_volume_states@@SAXPAKPAE@Z");

    long new_input = _light_volume_random_seed_1;
    switch (*input)
    {
    case _light_volume_random:
        switch (highest_bit_set(*used_states & k_light_volume_random_seeds))
        {
        case NONE:
            new_input = _light_volume_random_seed_1;
            break;
        case _light_volume_random_seed_1:
            new_input = _light_volume_random_seed_2;
            break;
        case _light_volume_random_seed_2:
        {
            static long const k_random_seeds[] = { _light_volume_random_seed_1, _light_volume_random_seed_2 };
            static unsigned long x_random_seed_index = 0;

            event_wrapped(_event_message, "effects:light_volumes:Ran out of random seeds!");
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

void c_light_volume_states::update_states(unsigned long states)
{
    mangled_ppc("?update_states@c_light_volume_states@@QAAXK@Z");

    states = states & m_used_states & ~m_valid_states;
    if (states != 0)
    {
        if (TEST_MASK(states, k_dependent_on_profile_states))
        {
            dassert_tag_debug_untracked_jul_11_2011(61, false, "unreachable");
        }
        if (TEST_MASK(states, k_light_volume_random_seeds))
        {
            m_state_values[_light_volume_random_seed_1] = m_light_volume->get_random_seed(0);
            m_state_values[_light_volume_random_seed_2] = m_light_volume->get_random_seed(1);
        }
        if (TEST_MASK(states, k_dependent_on_system_states))
        {
            m_state_values[_system_age] = m_light_volume_system->get_age();
            m_state_values[_system_lod] = static_cast<float>(m_light_volume_system->get_lod());
            m_state_values[_effect_a_scale] = m_light_volume_system->get_effect_scale_a();
            m_state_values[_effect_b_scale] = m_light_volume_system->get_effect_scale_b();
        }
        if (TEST_BIT(states, _game_time))
        {
            m_state_values[_game_time] = g_render_time.wrapped_seconds;
        }
        if (TEST_BIT(states, _light_volume_random))
        {
            event_wrapped(_event_error, "Called c_light_volume_states::update_states with state of '_profile_random' or '_light_volume_random'.  Need to first call allocate_random_seed, then clear this state.");
        }
    }
    m_valid_states |= states;
};

unsigned long c_light_volume_states::get_light_volume_system_used_states() const
{
    mangled_ppc("?get_light_volume_system_used_states@c_light_volume_states@@QBAKXZ");

    unsigned long states = 0;
    if (m_light_volume_system != NULL)
    {
        c_light_volume_system_definition const * light_volume_system_definition = m_light_volume_system->get_definition();
        for (long light_volume_index = 0; light_volume_index < light_volume_system_definition->get_light_volume_count(); light_volume_index++)
        {
            c_light_volume_definition const * light_volume_definition = light_volume_system_definition->get_light_volume_definition(light_volume_index);
            states |= light_volume_definition->get_used_states();
        }
    }
    return states;
};

void c_light_volume_states::set_light_volume_system(c_light_volume_system const * light_volume_system)
{
    mangled_ppc("?set_light_volume_system@c_light_volume_states@@QAAXPBVc_light_volume_system@@@Z");

    if (light_volume_system != m_light_volume_system)
    {
        m_used_states &= ~get_light_volume_system_used_states();
        m_light_volume_system = light_volume_system;
        invalidate_states(k_dependent_on_system_states);
        m_used_states |= get_light_volume_system_used_states();
        update_states(k_dependent_on_system_states | k_global_states);
    }
};

void c_light_volume_states::set_light_volume_location(c_light_volume_location const * light_volume_location)
{
    mangled_ppc("?set_light_volume_location@c_light_volume_states@@QAAXPBVc_light_volume_location@@@Z");

    if (light_volume_location != m_light_volume_location)
    {
        m_light_volume_location = light_volume_location;
        invalidate_states(k_dependent_on_location_states);
        update_states(k_dependent_on_location_states);
    }
};

void c_light_volume_states::set_light_volume(c_light_volume const * light_volume)
{
    mangled_ppc("?set_light_volume@c_light_volume_states@@QAAXPBVc_light_volume@@@Z");

    if (light_volume != m_light_volume)
    {
        m_light_volume = light_volume;
        invalidate_states(k_dependent_on_light_volume_states);
        update_states(k_dependent_on_light_volume_states);
    }
};

