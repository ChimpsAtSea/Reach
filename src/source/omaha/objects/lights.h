#pragma once
#ifndef __LIGHTS_H__
#define __LIGHTS_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"
#include "omaha\memory\static_arrays.h"

/* ---------- constants */

/* ---------- definitions */

union real_point3d;
union vector3d;

// only the count is verified (c_enum<e_change_color_reference, char, 0, 5>)
enum e_change_color_reference
{
    k_change_color_reference_count = 5
};

// $TODO partially reversed; layout from the Reach target (determinism_debug_consumer_lights.obj: sizeof 0xC0,
// ctor member offsets, deterministic reset of the trailing 0x44 bytes); the IDA type is the H3 layout (0xE4) and is stale
struct light_datum
{
    short identifier; // 0x0
    unsigned char unknown2[0x5A - 0x2]; // 0x2 $TODO
    c_enum<e_change_color_reference, char, 0, k_change_color_reference_count> object_change_color_reference; // 0x5A
    unsigned char unknown5B[0x7C - 0x5B]; // 0x5B $TODO
    unsigned char state[0x44]; // 0x7C $TODO light_state
};
static_assert(sizeof(light_datum) == 0xC0, "light_datum");

/* ---------- prototypes */

long light_new_unattached(long definition_index, long object_index, short node_index, real_point3d const * position, vector3d const * forward, vector3d const * up, float scale, long unknown0, long unknown1);

/* ---------- globals */

/* ---------- public code */

#endif // __LIGHTS_H__

