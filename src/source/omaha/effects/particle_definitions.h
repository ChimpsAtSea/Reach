#pragma once
#ifndef __PARTICLE_DEFINITIONS_H__
#define __PARTICLE_DEFINITIONS_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"

/* ---------- constants */

/* ---------- definitions */

class c_particle_definition
{
public:
    long get_used_particle_states(void) const
    {
        mangled_ppc("?get_used_particle_states@c_particle_definition@@QBAJXZ");

        return m_used_particle_states;
    }

private:
    unsigned char m_unknown0[0x1CC]; // 0x0 $TODO layout
    long m_used_particle_states; // 0x1CC
};

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __PARTICLE_DEFINITIONS_H__

