#pragma once
#ifndef __COLLISIONS_SIMPLE_H__
#define __COLLISIONS_SIMPLE_H__

/* ---------- headers */

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

union real_point3d;
union vector3d;
struct real_matrix4x3;

bool collision_point_in_sphere(real_point3d const * point, real_point3d const * sphere_center, float sphere_radius);
bool collision_point_in_cylinder(real_point3d const * point, real_matrix4x3 const * cylinder_matrix, float cylinder_radius, float cylinder_height, float * out_distance_from_axis);
bool collision_point_in_pill(real_point3d const * point, real_matrix4x3 const * pill_matrix, float pill_radius, float height, float * out_distance_from_axis);
bool collision_point_in_box(real_point3d const * point, real_matrix4x3 const * box_matrix, float width, float length, float height);
bool collision_point_in_cone(real_point3d const * point, real_matrix4x3 const * cone_matrix, vector3d const * cone_axis, float cone_length, float base_radius, float * out_axial_distance_from_endpoint, float * out_radial_distance_from_cone_axis);

/* ---------- globals */

/* ---------- public code */

#endif // __COLLISIONS_SIMPLE_H__

