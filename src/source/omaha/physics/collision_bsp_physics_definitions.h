#pragma once
#ifndef __COLLISION_BSP_PHYSICS_DEFINITIONS_H__
#define __COLLISION_BSP_PHYSICS_DEFINITIONS_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"
#include "omaha\physics\collision_bsp_references.h"
#include "omaha\physics\havok_shapes.h"
#include "omaha\physics\physics_model_definitions.h"

/* ---------- constants */

/* ---------- definitions */

struct s_tag_block;
class hkpMoppCode;

struct s_collision_bsp_physics_definition
{
    c_collision_geometry_shape collision_geometry_shape; // 0x0
    c_mopp_bv_tree_shape mopp_bv_tree_shape; // 0x60
};
static_assert(sizeof(s_collision_bsp_physics_definition) == 0xB0, "s_collision_bsp_physics_definition");

/* ---------- prototypes */

bool collision_bsp_physics_build(s_collision_bsp_physics_definition * collision_bsp_physics_definition, bool build_mopp_codes, long mopp_code_index, s_tag_block * mopp_codes, c_collision_bsp_reference bsp_reference, float scale, long model_definition_index);
bool collision_bsp_physics_fixup(s_collision_bsp_physics_definition * collision_bsp_physics_definition, long model_definition_index, long mopp_code_index, s_tag_block * mopp_codes, c_collision_bsp_reference bsp_reference);
void collision_bsp_physics_fixup(s_collision_bsp_physics_definition * collision_bsp_physics_definition, long model_definition_index, hkpMoppCode const * mopp_code, c_collision_bsp_reference bsp_reference);

/* ---------- globals */

/* ---------- public code */

#endif // __COLLISION_BSP_PHYSICS_DEFINITIONS_H__

