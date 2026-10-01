#pragma once
#ifndef __PARTICLE_EMITTER_CUSTOM_SHAPES_H__
#define __PARTICLE_EMITTER_CUSTOM_SHAPES_H__

/* ---------- headers */

#include "omaha\math\real_math.h"
#include "omaha\tag_files\tag_groups.h"
#include "core\corelib\cseries\cseries_macros.h"

/* ---------- constants */

/* ---------- definitions */

struct s_particle_emitter_custom_points
{
    static s_particle_emitter_custom_points * get(long tag_index);

    s_tag_reference source_reference; // 0x0
    vector3d compression_scale; // 0x10
    vector3d compression_offset; // 0x1C
    s_tag_block points; // 0x28
};
static_assert(sizeof(s_particle_emitter_custom_points) == 0x34, "s_particle_emitter_custom_points");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __PARTICLE_EMITTER_CUSTOM_SHAPES_H__

