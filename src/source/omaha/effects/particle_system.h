#ifndef __PARTICLE_SYSTEM_H__
#define __PARTICLE_SYSTEM_H__
#pragma once

/* ---------- headers */

#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_macros.h"

/* ---------- constants */

long const k_random_seed_count_per_particle_system = 4;

/* ---------- definitions */

class c_particle_system_definition;

// layout from the H3 type; Reach offsets verified: m_age, m_random_seeds
class c_particle_system
{
public:
    c_particle_system_definition const * get_particle_system_definition(void) const;
    float get_exported_function(unsigned long function_index) const;
    long get_effect_index(void) const; // $TODO inline in the target (f i, particle_block.obj); body not reversed yet
    float real_internal_random_range(float lower_bound, float upper_bound) const; // $TODO inline in the target (f i); body not reversed yet

    long get_object_index(void) const
    {
        mangled_ppc("?get_object_index@c_particle_system@@QBAJXZ");

        return m_object_index;
    }

    float get_age(void) const
    {
        mangled_ppc("?get_age@c_particle_system@@QBAMXZ");

        return m_age;
    }

    float get_random_seed(unsigned long index) const
    {
        mangled_ppc("?get_random_seed@c_particle_system@@QBAMK@Z");

        assert_decomp(index < k_random_seed_count_per_particle_system, "c:\\sd\\reach\\publishing\\main\\shared\\engine\\source\\omaha\\effects\\particle_system.h", 325);
        return m_random_seeds[index];
    }

private:
    short identifier; // 0x0
    float m_age; // 0x4
    unsigned short m_flags; // 0x8
    unsigned short m_particle_system_definition_index; // 0xA
    long m_definition_index; // 0xC
    unsigned char m_event_block_index; // 0x10
    unsigned char m_priority; // 0x11
    unsigned short m_event_counter; // 0x12
    long m_effect_index; // 0x14
    long m_lightprobe_index; // 0x18
    long m_breakable_surface_event_index; // 0x1C
    long m_location; // 0x20
    float m_effect_scale_a; // 0x24
    float m_effect_scale_b; // 0x28
    unsigned long m_random_seed; // 0x2C
    float m_random_seeds[k_random_seed_count_per_particle_system]; // 0x30
    // Reach offsets verified from the inline getters: first_location_index 0x44, object_index 0x4C,
    // first_person_user_mask (byte) 0x50, particle_count 0x52
    long m_unknown40; // 0x40 $TODO
    long m_first_location_index; // 0x44
    long m_unknown48; // 0x48 $TODO (H3: last location / sibling index)
    long m_object_index; // 0x4C
    char m_first_person_user_mask; // 0x50
    unsigned char m_pad51; // 0x51
    short m_particle_count; // 0x52
};

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __PARTICLE_SYSTEM_H__

