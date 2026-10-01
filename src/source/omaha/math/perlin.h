#pragma once
#ifndef __PERLIN_H__
#define __PERLIN_H__

/* ---------- headers */

#include "omaha\math\real_math.h"
#include "core\corelib\cseries\cseries_macros.h"

/* ---------- constants */

/* ---------- definitions */

struct s_perlin_state
{
    short random_offset_total_ticks;
    short random_offset_ticks;
    real_point3d random_offset;
    real_point3d previous_random_offset;
};
static_assert(sizeof(s_perlin_state) == 0x1C, "s_perlin_state");

struct s_compressed_perlin_state
{
    unsigned char random_offset_total_ticks;
    unsigned char random_offset_ticks;
    unsigned long random_offset;
    unsigned long previous_random_offset;
};
static_assert(sizeof(s_compressed_perlin_state) == 0xC, "s_compressed_perlin_state");

/* ---------- prototypes */

void perlin_state_reset(s_perlin_state * perlin);
void perlin_state_update(s_perlin_state * perlin, long ticks, real offset_scale, real offset_period_min, real offset_period_max, bool ground_based, real_point3d * offset_ref);
void perlin_state_compress(s_perlin_state const * perlin, real scale, s_compressed_perlin_state * out_compressed_perlin);
void perlin_state_decompress(s_compressed_perlin_state const * compressed_perlin, real scale, s_perlin_state * out_perlin);

/* ---------- globals */

/* ---------- public code */

#endif // __PERLIN_H__

