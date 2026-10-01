#ifndef __HAVOK_SHAPES_H__
#define __HAVOK_SHAPES_H__
#pragma once

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"
#include "havok\hkbase\hkBaseTypes.h"
#include "havok\hkpcollide\hkpShapeCollection.h"
#include "omaha\physics\collision_bsp_references.h"

/* ---------- constants */

/* ---------- definitions */

class hkVector4;

// $TODO: layout only partially reversed (hkVector4 m_center / m_half_extent at 0x20 / 0x30 per H3)
class c_collision_geometry_shape :
    public hkpShapeCollection
{
public:
    enum e_collision_geometry_shape_type
    {
        _collision_geometry_shape_type_none = 0,
        _collision_geometry_shape_type_object,
        _collision_geometry_shape_type_instance,

        k_collision_geometry_shape_type_count
    };

    c_collision_geometry_shape(hkFinishLoadedObjectFlag halo, c_collision_bsp_reference bsp_reference);
    c_collision_geometry_shape(e_collision_geometry_shape_type collision_geometry_shape_type, c_collision_bsp_reference bsp_reference, long structure_bsp_index, long instance_index, long model_definition_index, float scale, bool physics_model_shape, hkVector4 const * center, hkVector4 const * half_extent);

    unsigned char unknown18[0x40 - 0x18]; // 0x18
    long m_model_definition_index; // 0x40 (collision_bsp_physics_fixup)
    unsigned char unknown44[0x60 - 0x44]; // 0x44
};
static_assert(sizeof(c_collision_geometry_shape) == 0x60, "c_collision_geometry_shape");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __HAVOK_SHAPES_H__

