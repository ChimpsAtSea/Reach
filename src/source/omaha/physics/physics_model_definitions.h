#ifndef __PHYSICS_MODEL_DEFINITIONS_H__
#define __PHYSICS_MODEL_DEFINITIONS_H__
#pragma once

/* ---------- headers */

#include "omaha\tag_files\tag_groups.h"
#include "core\corelib\cseries\cseries_macros.h"
#include "havok\hkbase\hkBaseTypes.h"
#include "havok\hkpcollide\hkpMoppBvTreeShape.h"
#include "omaha\math\real_math.h"

/* ---------- constants */

enum
{
    k_physics_model_definition_tag = 'phmo',
};

enum
{
    k_minimum_physics_model_shape_reference_count = 128,
};

/* ---------- definitions */

class hkpShapeCollection;
class hkpMoppCode;

class c_mopp_bv_tree_shape :
    public hkpMoppBvTreeShape
{
public:
    c_mopp_bv_tree_shape(hkpShapeCollection const * collection, hkpMoppCode const * code, real scale, bool physics_model_shape); // $TODO inline in the target (f i, instanced_geometry_definitions.obj); body not reversed yet
    c_mopp_bv_tree_shape(hkFinishLoadedObjectFlag halo, long user_data, hkpShapeCollection const * collection, hkpMoppCode const * code); // $TODO inline in the target (f i, instanced_geometry_definitions.obj); body not reversed yet

    real m_scale; // 0x40
    unsigned char pad44[0xC]; // 0x44
};
static_assert(sizeof(c_mopp_bv_tree_shape) == 0x50, "c_mopp_bv_tree_shape");

// physics_model_struct_definition; $TODO: only the leading fields are reversed
struct s_physics_model_definition
{
    unsigned long flags; // 0x0
    float mass_scale; // 0x4
    float mass; // 0x8
    float low_frequency_deactivation_scale; // 0xC
    float high_frequency_deactivation_scale; // 0x10
    float custom_shape_radius; // 0x14
    float maximum_penetration_depth_scale; // 0x18
    char import_version; // 0x1C
    unsigned char pad0[3]; // 0x1D
    s_tag_block damped_spring_motors; // 0x20
    s_tag_block position_motors; // 0x2C
    s_tag_block phantom_types; // 0x38
    s_tag_block powered_chains; // 0x44
    s_tag_block node_edges; // 0x50
    s_tag_block rigid_bodies; // 0x5C
    unsigned char unknown68[0x19C - 0x68]; // 0x68
};
static_assert(sizeof(s_physics_model_definition) == 0x19C, "s_physics_model_definition");

/* ---------- prototypes */

void physics_model_fixup(long physics_model_definition_index, bool vtables_only);
void physics_model_teardown(long physics_model_definition_index);
hkFinishLoadedObjectFlag const finish_loaded_object_flag_get(bool finishing);

/* ---------- globals */

/* ---------- public code */

#endif // __PHYSICS_MODEL_DEFINITIONS_H__

