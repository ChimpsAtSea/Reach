#pragma once
#ifndef __RASTERIZER_MAIN_H__
#define __RASTERIZER_MAIN_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"

/* ---------- constants */

/* ---------- definitions */

struct D3DDevice;

struct s_rasterizer_render_globals
{
    long k_render_resolution_x;
    long k_render_resolution_y;
    long k_display_offset_x;
    long k_display_offset_y;
    long k_shadow_resolution;
    long k_resolution_hint_wide_x;
    long k_resolution_hint_wide_y;
    long k_resolution_hint_x;
    long k_resolution_hint_y;
};
static_assert(sizeof(s_rasterizer_render_globals) == 0x24, "s_rasterizer_render_globals");

// $TODO: most members not yet declared; render_globals is owned by rasterizer_globals.obj
class c_rasterizer
{
public:
    static D3DDevice * get_device(void);
    static void block_on_last_fence(void);
    static unsigned long rasterizer_insert_fence(void);
    static void rasterizer_block_on_fence(unsigned long fence);
    static bool rasterizer_is_fence_pending(unsigned long fence);

    static s_rasterizer_render_globals render_globals;
};

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __RASTERIZER_MAIN_H__

