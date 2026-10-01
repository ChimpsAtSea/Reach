#ifndef __SCREEN_EFFECT_H__
#define __SCREEN_EFFECT_H__
#pragma once

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"

/* ---------- constants */

enum
{
    k_maximum_screen_effect_shaders = 8,
};

/* ---------- definitions */

struct s_screen_effect_shader_sample
{
    long shader_index; // 0x0
    float alpha; // 0x4
    float value; // 0x8
    long sort_order; // 0xC
    long object_index; // 0x10
};
static_assert(sizeof(s_screen_effect_shader_sample) == 0x14, "s_screen_effect_shader_sample");

struct s_screen_effect_shader_sample_result
{
    s_screen_effect_shader_sample shaders[k_maximum_screen_effect_shaders]; // 0x0
    long shader_count; // 0xA0
};
static_assert(sizeof(s_screen_effect_shader_sample_result) == 0xA4, "s_screen_effect_shader_sample_result");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __SCREEN_EFFECT_H__

