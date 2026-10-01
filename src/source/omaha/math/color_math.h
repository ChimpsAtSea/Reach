#pragma once
#ifndef __COLOR_MATH_H__
#define __COLOR_MATH_H__

/* ---------- headers */

#include "omaha\math\real_math.h"
#include "core\corelib\cseries\cseries_macros.h"

/* ---------- constants */

/* ---------- definitions */

union rgb_color
{
    real n[3];
    struct
    {
        real red;
        real green;
        real blue;
    };
};
typedef rgb_color real_rgb_color;

// Reach's real argb color (the IDA type claims 8 bytes of shorts, but the target code copies 16 bytes
// from global_real_argb_* and reads the rgb part at +0x4, e.g. lens_flare_reflection_new_block_proc)
union argb_color
{
    real n[4];
    struct
    {
        real alpha;
        union
        {
            real_rgb_color rgb;
            struct
            {
                real red;
                real green;
                real blue;
            };
        };
    };
};
static_assert(sizeof(argb_color) == 0x10, "argb_color");

// target mangling is ?global_real_argb_white@@3PBTargb_color@@B (non-const pointer to const)
extern argb_color const * global_real_argb_white;
extern argb_color const * global_real_argb_black;
extern argb_color const * global_real_argb_grey;
extern argb_color const * global_real_argb_red;
extern argb_color const * global_real_argb_blue;
extern argb_color const * global_real_argb_yellow;
extern argb_color const * global_real_argb_magenta;
extern argb_color const * global_real_argb_cyan;
extern argb_color const * global_real_argb_lightblue;
extern argb_color const * global_real_argb_color_table;
extern long const global_real_argb_color_table_size;

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __COLOR_MATH_H__

