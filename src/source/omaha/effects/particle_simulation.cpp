#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\effects\\particle_simulation.cpp"
/* ---------- headers */

#include "omaha\effects\particle_simulation.h"
#include "omaha\effects\jetwash.h"
#include "omaha\effects\particle.h"
#include "omaha\effects\particle_emitter.h"
#include "omaha\effects\particle_system.h"
#include "omaha\effects\particle_system_definitions.h"
#include "omaha\physics\boat_effects.h"
#include "omaha\cseries\cseries.h"
#include "omaha\math\real_math.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_macros.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// bool particle_simulation_emitter_should_pulse(class c_particle_emitter const *, class c_particle_system const *, class c_particle_emitter_definition const *, class c_particle_system_definition const *);
// bool particle_simulation_is_particle_spawn_valid(class c_particle_emitter const *, class c_particle_system const *, class c_particle_emitter_definition const *);
// void particle_simulation_get_particle_state_values(class c_particle const *, class c_particle_system_definition const *, float *);
// bool particle_simulation_initialize_particle(class c_particle *, class c_particle_emitter const *, class c_particle_system const *, class c_particle_emitter_definition const *);
// public: struct c_particle_emitter::s_property_values const * c_particle_emitter::get_property_values(void) const;

bool particle_simulation_emitter_should_pulse(c_particle_emitter const * emitter, c_particle_system const * system, c_particle_emitter_definition const * emitter_def, c_particle_system_definition const * system_def)
{
    mangled_ppc("?particle_simulation_emitter_should_pulse@@YA_NPBVc_particle_emitter@@PBVc_particle_system@@PBVc_particle_emitter_definition@@PBVc_particle_system_definition@@@Z");

    bool result = true;
    switch (emitter_def->get_emission_shape())
    {
        break; // unreachable; reproduces the extra branch in the target
    case c_particle_emitter_definition::_emission_shape_jetwash:
        result = jetwash_emitter_should_pulse(emitter, system, emitter_def, system_def);
        break;
    }

    return result;
};

bool particle_simulation_is_particle_spawn_valid(c_particle_emitter const * emitter, c_particle_system const * system, c_particle_emitter_definition const * emitter_def)
{
    mangled_ppc("?particle_simulation_is_particle_spawn_valid@@YA_NPBVc_particle_emitter@@PBVc_particle_system@@PBVc_particle_emitter_definition@@@Z");

    bool result = true;
    switch (emitter_def->get_emission_shape())
    {
    case c_particle_emitter_definition::_emission_shape_boat_hull_surface:
        result = boat_effects_particle_spawn_has_begun(emitter_def, system);
        break;
    case c_particle_emitter_definition::_emission_shape_jetwash:
        result = jetwash_prepare_for_particle_spawn(emitter, system, emitter_def);
        break;
    }

    return result;
};

void particle_simulation_get_particle_state_values(c_particle const * particle, c_particle_system_definition const * system_def, float * values)
{
    mangled_ppc("?particle_simulation_get_particle_state_values@@YAXPBVc_particle@@PBVc_particle_system_definition@@PAM@Z");

    assert_tag_debug_untracked_jul_11_2011(67, values);

    if (system_def && particle && particle->m_parent_emitter_index != NONE)
    {
        c_particle_emitter * emitter = c_particle_emitter::get(particle->m_parent_emitter_index);
        long definition_block_index = emitter->get_definition_block_index();
        c_particle_emitter_definition const * emitter_def = system_def->get_emitter(definition_block_index);
        switch (emitter_def->get_emission_shape())
        {
        case c_particle_emitter_definition::_emission_shape_boat_hull_surface:
            boat_effects_get_particle_simulation_values(values);
            break;
        case c_particle_emitter_definition::_emission_shape_jetwash:
            jetwash_get_particle_simulation_values(values);
            break;
        }
    }
};

bool particle_simulation_initialize_particle(c_particle * particle, c_particle_emitter const * emitter, c_particle_system const * system, c_particle_emitter_definition const * emitter_def)
{
    mangled_ppc("?particle_simulation_initialize_particle@@YA_NPAVc_particle@@PBVc_particle_emitter@@PBVc_particle_system@@PBVc_particle_emitter_definition@@@Z");

    bool result = false;
    assert_tag_debug_untracked_jul_11_2011(96, emitter_def);
    assert_tag_debug_untracked_jul_11_2011(97, emitter);
    assert_tag_debug_untracked_jul_11_2011(98, system);
    assert_tag_debug_untracked_jul_11_2011(99, particle);

    switch (emitter_def->get_emission_shape())
    {
    case c_particle_emitter_definition::_emission_shape_boat_hull_surface:
        result = boat_effects_boat_hull_compute_particle_position_and_velocity(system->get_object_index(), emitter->get_property_values()->m_emission_angle * k_degrees_to_radians, &particle->m_position, &particle->m_velocity);
        break;
    case c_particle_emitter_definition::_emission_shape_jetwash:
        result = jetwash_compute_particle_position_and_velocity(system->get_object_index(), emitter->get_property_values()->m_emission_angle * k_degrees_to_radians, &particle->m_position, &particle->m_velocity);
        break;
    }

    return result;
};

