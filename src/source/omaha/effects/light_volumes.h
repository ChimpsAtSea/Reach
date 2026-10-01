#ifndef __LIGHT_VOLUMES_H__
#define __LIGHT_VOLUMES_H__
#pragma once

/* ---------- headers */

#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_macros.h"

/* ---------- constants */

/* ---------- definitions */

class c_light_volume_system_definition;

// partial layout: only the members verified against the target so far
class c_light_volume_system
{
public:
    c_light_volume_system_definition const * get_definition() const;

    float get_age() const
    {
        mangled_ppc("?get_age@c_light_volume_system@@QBAMXZ");

        return m_age;
    }

    float get_effect_scale_a() const
    {
        mangled_ppc("?get_effect_scale_a@c_light_volume_system@@QBAMXZ");

        return m_effect_scale_a;
    }

    float get_effect_scale_b() const
    {
        mangled_ppc("?get_effect_scale_b@c_light_volume_system@@QBAMXZ");

        return m_effect_scale_b;
    }

    long get_lod() const
    {
        mangled_ppc("?get_lod@c_light_volume_system@@QBAJXZ");

        return m_lod;
    }

protected:
    unsigned char m_unknown0[0x20]; // 0x0 $TODO layout
    float m_age; // 0x20
    float m_effect_scale_a; // 0x24
    float m_effect_scale_b; // 0x28
    long m_lod; // 0x2C
};
static_assert(sizeof(c_light_volume_system) == 0x30, "c_light_volume_system");

// partial layout: only the members verified against the target so far
class c_light_volume
{
public:
    float get_random_seed(long index) const
    {
        mangled_ppc("?get_random_seed@c_light_volume@@QBAMJ@Z");

        assert_decomp(VALID_INDEX(index, NUMBEROF(m_random_seed)), "c:\sd\reach\publishing\main\shared\engine\source\omaha\effects\light_volumes.h", 344);
        return m_random_seed[index];
    }

protected:
    unsigned char m_unknown0[0x2C]; // 0x0 $TODO layout
    float m_random_seed[2]; // 0x2C
};
static_assert(sizeof(c_light_volume) == 0x34, "c_light_volume");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __LIGHT_VOLUMES_H__

