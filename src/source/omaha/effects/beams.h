#ifndef __BEAMS_H__
#define __BEAMS_H__
#pragma once

/* ---------- headers */

/* ---------- constants */

/* ---------- definitions */

class c_beam_system_definition;

// partial layout: only the members verified against the target so far
class c_beam_system
{
public:
    c_beam_system_definition const * get_definition() const;

    float get_age() const
    {
        mangled_ppc("?get_age@c_beam_system@@QBAMXZ");

        return m_age;
    }

    float get_effect_scale_a() const
    {
        mangled_ppc("?get_effect_scale_a@c_beam_system@@QBAMXZ");

        return m_effect_scale_a;
    }

    float get_effect_scale_b() const
    {
        mangled_ppc("?get_effect_scale_b@c_beam_system@@QBAMXZ");

        return m_effect_scale_b;
    }

    long get_lod() const
    {
        mangled_ppc("?get_lod@c_beam_system@@QBAJXZ");

        return m_lod;
    }

protected:
    unsigned char m_unknown0[0x20]; // 0x0 $TODO layout
    float m_age; // 0x20
    float m_effect_scale_a; // 0x24
    float m_effect_scale_b; // 0x28
    long m_lod; // 0x2C
};

// partial layout: only the members verified against the target so far
class c_beam
{
public:
    float get_capped_length() const;

    float get_random_seed(long index) const
    {
        mangled_ppc("?get_random_seed@c_beam@@QBAMJ@Z");

        return m_random_seed[index];
    }

protected:
    unsigned char m_unknown0[0x2C]; // 0x0 $TODO layout
    float m_random_seed[2]; // 0x2C
};

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __BEAMS_H__

