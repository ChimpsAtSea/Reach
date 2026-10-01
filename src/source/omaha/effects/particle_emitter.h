#pragma once
#ifndef __PARTICLE_EMITTER_H__
#define __PARTICLE_EMITTER_H__

/* ---------- headers */

#include "omaha\math\real_math.h"
#include "core\corelib\cseries\cseries_macros.h"

/* ---------- constants */

/* ---------- definitions */

class c_particle_emitter
{
public:
    // Reach order follows the emitter definition properties; H3 names
    struct s_property_values
    {
        real_point3d m_translational_offset; // 0x0
        vector3d m_direction; // 0xC
        float m_emission_radius; // 0x18
        float m_emission_angle; // 0x1C
        float m_particle_axis_angle; // 0x20
    };

    static c_particle_emitter * get(long emitter_index);
    long get_definition_block_index(void);
    real_matrix4x3 const * get_matrix(void) const; // $TODO inline in the target (f i, particle_location.obj); body not reversed yet

    s_property_values const * get_property_values(void) const
    {
        mangled_ppc("?get_property_values@c_particle_emitter@@QBAPBUs_property_values@1@XZ");

        return &m_property_values;
    }

private:
    short identifier; // 0x0
    unsigned char m_unknown2[0x1A]; // 0x2 $TODO layout
    long m_definition_block_index; // 0x1C
    s_property_values m_property_values; // 0x20
};

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __PARTICLE_EMITTER_H__

