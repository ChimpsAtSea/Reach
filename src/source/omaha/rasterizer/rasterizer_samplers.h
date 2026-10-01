#pragma once
#ifndef __RASTERIZER_SAMPLERS_H__
#define __RASTERIZER_SAMPLERS_H__

/* ---------- headers */

#include "omaha\rasterizer\rasterizer_textures.h"

/* ---------- constants */

enum e_sampler_address_mode
{
    _sampler_address_wrap = 0,
    _sampler_address_clamp,
    _sampler_address_mirror,
    _sampler_address_border,

    k_number_of_sampler_address_modes
};

enum e_sampler_filter_mode
{
    _sampler_filter_trilinear = 0,
    _sampler_filter_point,
    _sampler_filter_bilinear,
};

/* ---------- definitions */

class c_rasterizer_samplers
{
public:
    static void set_sampler_texture(long sampler_index, c_rasterizer_texture_ref texture_ref);
    static void set_sampler_address_mode(long sampler_index, e_sampler_address_mode address_mode);
    static void set_sampler_filter_mode(long sampler_index, e_sampler_filter_mode filter_mode);
};

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __RASTERIZER_SAMPLERS_H__

