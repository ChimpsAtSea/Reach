#pragma once
#ifndef __PARTICLE_LOCATION_H__
#define __PARTICLE_LOCATION_H__

/* ---------- headers */

#include "omaha\math\real_math.h"
#include "core\corelib\cseries\cseries_macros.h"

/* ---------- constants */

/* ---------- definitions */

// layout from the H3 type; Reach offsets verified: m_random_seed, m_lod_amount
class c_particle_location
{
public:
    float get_lod_amount(void) const
    {
        mangled_ppc("?get_lod_amount@c_particle_location@@QBAMXZ");

        return m_lod_amount;
    }

    float get_random_seed(void) const
    {
        mangled_ppc("?get_random_seed@c_particle_location@@QBAMXZ");

        return (1.0f / UNSIGNED_CHAR_MAX) * static_cast<float>(m_random_seed);
    }

private:
    short identifier; // 0x0
    unsigned char m_random_seed; // 0x2
    long m_flags; // 0x4
    long m_emitter_list_head; // 0x8
    long m_emitter_list_tail; // 0xC
    long m_next_sibling_index; // 0x10
    long m_parent_system_index; // 0x14
    real_matrix4x3 m_matrix; // 0x18
    float m_lod_amount; // 0x4C
    real_point3d m_bounding_sphere_center; // 0x50
    float m_bounding_sphere_radius; // 0x5C
};

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __PARTICLE_LOCATION_H__

