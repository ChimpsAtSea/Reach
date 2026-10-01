#pragma once
#ifndef __RENDER_TIME_H__
#define __RENDER_TIME_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"

/* ---------- constants */

/* ---------- definitions */

// layout from s_render_time::init/update; field names are descriptive guesses
struct s_render_time
{
    float game_seconds; // 0x0
    float frame_seconds; // 0x4
    float delta_seconds; // 0x8
    float wrapped_seconds; // 0xC  (fractional part of accumulated delta)
    float wrapped_periods[4]; // 0x10
    unsigned long period_counters[5]; // 0x20

    void init();
    void update(float dt);
};
static_assert(sizeof(s_render_time) == 0x34, "s_render_time");

/* ---------- prototypes */

/* ---------- globals */

extern s_render_time g_render_time;

/* ---------- public code */

#endif // __RENDER_TIME_H__

