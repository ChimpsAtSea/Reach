#ifndef __HAVOK_COMPONENT_H__
#define __HAVOK_COMPONENT_H__
#pragma once

/* ---------- headers */

/* ---------- constants */

/* ---------- definitions */

struct real_matrix4x3;
union real_rectangle3d;

// $TODO layout not reversed; only used through pointers so far
class c_havok_component
{
public:
    short const get_object_postion_controlling_rigid_body_index(void) const;
    bool calculate_local_space_physics_bounding_box(long rigid_body_index, real_rectangle3d * bounds) const;
    void get_rigid_body_transform(long rigid_body_index, real_matrix4x3 * transform) const;
    long const get_object_index(void) const; // $TODO inline in the target (f i); body not reversed yet
};

/* ---------- prototypes */

class hkpWorldObject;

long havok_entity_get_havok_component_index(hkpWorldObject const * world_object);

extern inline c_havok_component * get_havok_component(long havok_component_index); // $TODO inline in the target (f i); body not reversed yet

/* ---------- globals */

/* ---------- public code */

#endif // __HAVOK_COMPONENT_H__

