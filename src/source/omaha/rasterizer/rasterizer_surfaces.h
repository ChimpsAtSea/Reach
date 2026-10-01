#pragma once
#ifndef __RASTERIZER_SURFACES_H__
#define __RASTERIZER_SURFACES_H__

/* ---------- headers */

/* ---------- constants */

/* ---------- definitions */

// $TODO: Reach surface list not yet recovered
enum e_surface
{
    _surface_none = 0,
};

class c_surface
{
public:
    static void resolve(e_surface surface, long resolve_index);
    static void set(long target_index, e_surface surface);
    static long get_surface_width(e_surface surface);
    static long get_surface_height(e_surface surface);
    static float get_alpha_multiplier(long target_index);
};

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __RASTERIZER_SURFACES_H__

