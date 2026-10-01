#pragma once
#ifndef __PARTICLE_EVENT_DEFINITIONS_H__
#define __PARTICLE_EVENT_DEFINITIONS_H__

/* ---------- headers */

#include "omaha\math\real_math.h"
#include "omaha\game\materials.h"
#include "core\corelib\cseries\cseries_macros.h"

/* ---------- constants */

/* ---------- definitions */

class c_particle_collision_event
{
public:
    void initialize(real_point3d const * position, vector3d const * direction, vector3d const * normal, c_global_material_type material_type);

protected:
    real_point3d m_collision_point; // 0x0
    vector3d m_collision_forward; // 0xC
    vector3d m_collision_normal; // 0x18
    c_global_material_type m_material_type; // 0x24
};
static_assert(sizeof(c_particle_collision_event) == 0x28, "c_particle_collision_event");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __PARTICLE_EVENT_DEFINITIONS_H__

