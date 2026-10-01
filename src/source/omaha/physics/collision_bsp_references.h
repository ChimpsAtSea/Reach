#pragma once
#ifndef __COLLISION_BSP_REFERENCES_H__
#define __COLLISION_BSP_REFERENCES_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"

/* ---------- constants */

/* ---------- definitions */

struct collision_bsp;
struct large_collision_bsp;

// passed by value in a single 64-bit register (collision_bsp_physics_definitions.cpp)
class c_collision_bsp_reference
{
public:
    long get_surface_count() const;
    bool is_small() const;

private:
    collision_bsp const * m_small_bsp; // 0x0 (get_surface_count)
    large_collision_bsp const * m_large_bsp; // 0x4 (get_surface_count)
};
static_assert(sizeof(c_collision_bsp_reference) == 0x8, "c_collision_bsp_reference");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __COLLISION_BSP_REFERENCES_H__

