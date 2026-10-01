#pragma once
#ifndef __CINEMATIC_LIGHTING_H__
#define __CINEMATIC_LIGHTING_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"
#include "foundation\baselib\datatypes\static_array.h"
#include "omaha\render\lighting_interface.h"

/* ---------- constants */

/* ---------- definitions */

struct s_cinematic_light_globals
{
    // $TODO: layout not reversed (size from the sh_light_count offset)
    struct s_dynamic_light_state
    {
        unsigned char unknown0[0xC]; // 0x0
    };
    static_assert(sizeof(s_dynamic_light_state) == 0xC, "s_dynamic_light_state");

    // element size 0x148 from s_static_array<s_sh_light_state, 64>::operator[]
    struct s_sh_light_state
    {
        void initialize(void);

        unsigned char unknown0[0x4]; // 0x0
        long object_index; // 0x4
        render_lighting final_render_lighting; // 0x8
        real sampled_lighting_weight; // 0x100
        real analytical_lighting_weight; // 0x104
        unsigned char unknown108[0x40]; // 0x108
    };
    static_assert(sizeof(s_sh_light_state) == 0x148, "s_sh_light_state");

    long sh_light_get(long object_index, bool allocate);
    s_sh_light_state * get_sh_light_state(long state_index);

    long dynamic_light_count; // 0x0
    s_static_array<s_dynamic_light_state, 16> dynamic_lights; // 0x4
    long sh_light_count; // 0xC4
    s_static_array<s_sh_light_state, 64> sh_lights; // 0xC8
};
static_assert(sizeof(s_cinematic_light_globals) == 0x52C8, "s_cinematic_light_globals");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __CINEMATIC_LIGHTING_H__

