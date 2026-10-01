#pragma once
#ifndef __VISIBILITY_TEST_H__
#define __VISIBILITY_TEST_H__

/* ---------- headers */

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

struct visibility_volume;
union real_point3d;
union real_rectangle3d;

long visibility_volume_test_point(visibility_volume const * volume, real_point3d const * point);
long visibility_volume_build_vertex_flags(visibility_volume const * volume, real_point3d const * point, bool test_against_all_planes);
long visibility_volume_test_box(visibility_volume const * volume, real_rectangle3d const * bounds, bool test_frustum_against_cube);
long visibility_volume_test_triangle(visibility_volume const * volume, real_point3d const * p0, real_point3d const * p1, real_point3d const * p2);
long visibility_volume_test_sphere_old(visibility_volume const * volume, real_point3d const * point, float radius);

/* ---------- globals */

/* ---------- public code */

#endif // __VISIBILITY_TEST_H__

