#pragma once
#ifndef __RASTERIZER_STATES_H__
#define __RASTERIZER_STATES_H__

/* ---------- headers */

/* ---------- constants */

// names from H3 rasterizer.h; Reach values from the target (only verified entries listed)
enum e_cull_mode
{
    _cull_mode_off = 0,
    _cull_mode_cw,
    _cull_mode_ccw,
};

enum e_z_buffer_mode
{
    _z_buffer_mode_write = 0,
    _z_buffer_mode_read,
};

enum e_alpha_blend_mode
{
    _alpha_blend_opaque = 0,
    _alpha_blend_additive,
    _alpha_blend_multiply,
    _alpha_blend_alpha_blend,
};

/* ---------- definitions */

union short_rectangle2d;

class c_rasterizer_states
{
public:
    static void begin_high_quality_blend(void);
    static void end_high_quality_blend(void);
    static void set_color_write_enable(long target_index, long enable);
    static void set_cull_mode(e_cull_mode cull_mode);
    static void set_scissor_rect(short_rectangle2d const * scissor_rect);
    static void set_z_buffer_mode(e_z_buffer_mode z_buffer_mode);
    static void set_alpha_blend_mode(e_alpha_blend_mode alpha_blend_mode);
};

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __RASTERIZER_STATES_H__

