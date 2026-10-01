#pragma once
#ifndef __RASTERIZER_DX9_DYNAMIC_GEOMETRY_H__
#define __RASTERIZER_DX9_DYNAMIC_GEOMETRY_H__

/* ---------- headers */

/* ---------- constants */

/* ---------- definitions */

union real_point3d;

class c_rasterizer_dynamic_geometry
{
public:
    static void draw_fullscreen_quad(int target_width, int target_height);
    static void draw_worldspace_polygon(real_point3d const * points, long point_count);
};

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __RASTERIZER_DX9_DYNAMIC_GEOMETRY_H__

