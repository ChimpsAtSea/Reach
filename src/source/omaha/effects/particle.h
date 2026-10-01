#pragma once
#ifndef __PARTICLE_H__
#define __PARTICLE_H__

/* ---------- headers */

#include "omaha\math\real_math.h"
#include "core\corelib\cseries\cseries_macros.h"

/* ---------- constants */

/* ---------- definitions */

// layout from the H3 type; Reach offsets verified up to m_velocity
class c_particle
{
public:
    short identifier; // 0x0
    unsigned short m_flags; // 0x2
    long m_next_particle; // 0x4
    long m_parent_emitter_index; // 0x8
    unsigned long m_gpu_address; // 0xC
    float m_age; // 0x10
    float m_inverse_lifespan; // 0x14
    float m_emission_time; // 0x18
    unsigned short m_random_seed[8]; // 0x1C
    real_point3d m_position; // 0x2C
    vector3d m_velocity; // 0x38
};

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __PARTICLE_H__

