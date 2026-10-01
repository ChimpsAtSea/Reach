#pragma once
#ifndef __RENDER_DEBUG_H__
#define __RENDER_DEBUG_H__

/* ---------- headers */

#include "omaha\math\real_math.h"
#include "omaha\math\color_math.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

void render_debug_vector(bool draw_immediately, real_point3d const * point, vector3d const * vector, real scale, argb_color const * color);
void render_debug_sphere(bool draw_immediately, real_point3d const * center, real radius, argb_color const * color);
void render_debug_string(char const * string);
void render_debug_line(bool draw_immediately, real_point3d const * point0, real_point3d const * point1, argb_color const * color);
void render_debug_polygon_edges(real_point3d const * points, short point_count, argb_color const * color);
void render_debug_point(bool draw_immediately, real_point3d const * point, real scale, argb_color const * color);
void render_debug_string_at_point(real_point3d const * point, char const * string, argb_color const * color);

/* ---------- globals */

/* ---------- public code */

#endif // __RENDER_DEBUG_H__

