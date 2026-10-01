#ifndef __CONTRAILS_H__
#define __CONTRAILS_H__
#pragma once

/* ---------- headers */

#include "omaha\math\real_math.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_macros.h"

/* ---------- constants */

/* ---------- definitions */

class c_contrail_system_definition;

// partial layout: only the members verified against the target so far
class c_contrail_system
{
public:
    c_contrail_system_definition const * get_definition() const;
    float get_age() const; // $TODO inline in the target ("f i")
    float get_effect_scale_a() const; // $TODO inline in the target ("f i")

    float get_effect_scale_b() const
    {
        mangled_ppc("?get_effect_scale_b@c_contrail_system@@QBAMXZ");

        return m_effect_scale_b;
    }

    long get_lod() const
    {
        mangled_ppc("?get_lod@c_contrail_system@@QBAJXZ");

        return m_lod;
    }

protected:
    unsigned char m_unknown0[0x2C]; // 0x0 $TODO layout
    float m_effect_scale_b; // 0x2C
    long m_lod; // 0x30
};

// partial layout: only the members verified against the target so far
class c_contrail_location
{
public:
    vector3d const * get_velocity() const
    {
        mangled_ppc("?get_velocity@c_contrail_location@@QBAPBTvector3d@@XZ");

        return &m_velocity;
    }

protected:
    unsigned char m_unknown0[0x48]; // 0x0 $TODO layout
    vector3d m_velocity; // 0x48
};

// partial layout: only the members verified against the target so far
class c_contrail
{
public:
    float get_random_seed(long index) const
    {
        mangled_ppc("?get_random_seed@c_contrail@@QBAMJ@Z");

        assert_decomp(VALID_INDEX(index, NUMBEROF(m_random_seed)), "c:\\sd\\reach\\publishing\\main\\shared\\engine\\source\\omaha\\effects\\contrails.h", 345);
        return m_random_seed[index];
    }

protected:
    unsigned char m_unknown0[0x20]; // 0x0 $TODO layout
    float m_random_seed[2]; // 0x20
};

// partial layout: only the members verified against the target so far
class c_contrail_profile
{
public:
    float get_age() const; // $TODO inline in the target ("f i")

    float get_random_seed(long index) const
    {
        mangled_ppc("?get_random_seed@c_contrail_profile@@QBAMJ@Z");

        assert_decomp(VALID_INDEX(index, NUMBEROF(m_random_seed)), "c:\\sd\\reach\\publishing\\main\\shared\\engine\\source\\omaha\\effects\\contrails.h", 440);
        return static_cast<float>(m_random_seed[index]);
    }

protected:
    unsigned char m_unknown0[0x14]; // 0x0 $TODO layout
    unsigned short m_random_seed[4]; // 0x14
};

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __CONTRAILS_H__

