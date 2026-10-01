#ifndef __PARTICLE_SYSTEM_DEFINITIONS_H__
#define __PARTICLE_SYSTEM_DEFINITIONS_H__
#pragma once

/* ---------- headers */

#include "omaha\tag_files\tag_groups.h"
#include "core\corelib\cseries\cseries_macros.h"

/* ---------- constants */

/* ---------- definitions */

class c_particle_definition;

class c_particle_emitter_definition
{
public:
    enum e_emission_shape
    {
        _emission_shape_sprayer = 0,
        _emission_shape_disc,
        _emission_shape_globe,
        _emission_shape_implode,
        _emission_shape_tube,
        _emission_shape_halo,
        _emission_shape_impact_contour,
        _emission_shape_impact_area,
        _emission_shape_debris,
        _emission_shape_line,
        _emission_shape_breakable_surface,
        _emission_shape_custom_points,
        _emission_shape_boat_hull_surface,
        _emission_shape_cube,
        _emission_shape_cylinder,
        _emission_shape_unweighted_line,
        _emission_shape_plane,
        _emission_shape_jetwash,

        k_emission_shape_count
    };

    long get_emission_shape(void) const;
    unsigned long get_used_particle_states(void) const;
};

class c_particle_system_definition
{
public:
    c_particle_definition const * get_particle_definition(void) const;
    c_particle_emitter_definition const * get_emitter(long emitter_index) const;
    long get_location_index(void) const; // $TODO inline in the target (f i, effects.obj); body not reversed yet

    unsigned char m_unknown0[0x5C]; // 0x0 $TODO layout
    s_tag_block m_emitters; // 0x5C
};

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __PARTICLE_SYSTEM_DEFINITIONS_H__

