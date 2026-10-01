#pragma once
#ifndef __RASTERIZER_PROJECTION_H__
#define __RASTERIZER_PROJECTION_H__

/* ---------- headers */

#include "omaha\math\real_math.h"

#include <xtl.h>
#include <xnamath.h>

/* ---------- constants */

/* ---------- definitions */

// $TODO: members not yet recovered
struct s_rasterizer_projection
{
    _XMMATRIX get_pixel_to_world_relative_to(real_point3d const * point) const;
};

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __RASTERIZER_PROJECTION_H__

