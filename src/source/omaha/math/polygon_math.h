#pragma once
#ifndef __POLYGON_MATH_H__
#define __POLYGON_MATH_H__

/* ---------- headers */

/* ---------- constants */

/* ---------- definitions */

union real_point2d;

/* ---------- prototypes */

bool point_in_polygon2d(real_point2d const * point, long point_count, real_point2d const * points);

/* ---------- globals */

/* ---------- public code */

#endif // __POLYGON_MATH_H__

