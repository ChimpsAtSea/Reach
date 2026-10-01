#pragma once
#ifndef __LIGHTING_INTERFACE_H__
#define __LIGHTING_INTERFACE_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"
#include "omaha\math\real_math.h"

/* ---------- constants */

/* ---------- definitions */

// $TODO: Reach layout differs from H3; offsets verified in s_cinematic_sh_lighting_interface::apply_cinematic_lighting, member names guessed
struct s_render_lighting_vmf_light
{
    vector3d direction; // 0x0
    real intensity; // 0xC
    real color[3]; // 0x10
    real unknown1C; // 0x1C
};
static_assert(sizeof(s_render_lighting_vmf_light) == 0x20, "s_render_lighting_vmf_light");

// $TODO: member names guessed, see above
struct s_render_lighting_sample
{
    s_render_lighting_vmf_light vmf_lights[2]; // 0x0
    real analytical_values[6]; // 0x40
    bool analytical_valid; // 0x58
    unsigned long analytical_debug_color; // 0x5C
    real sampled_analytical_values[6]; // 0x60
};
static_assert(sizeof(s_render_lighting_sample) == 0x78, "s_render_lighting_sample");

// size from s_cinematic_light_globals::s_sh_light_state (final_render_lighting 0x8, next member 0x100)
struct render_lighting
{
    unsigned char unknown0[0x18]; // 0x0
    s_render_lighting_sample lightprobe_sample; // 0x18
    unsigned char unknown90[0x64]; // 0x90
    long cinematic_sh_light_index; // 0xF4
};
static_assert(sizeof(render_lighting) == 0xF8, "render_lighting");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __LIGHTING_INTERFACE_H__

