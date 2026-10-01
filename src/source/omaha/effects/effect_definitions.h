#pragma once
#ifndef __EFFECT_DEFINITIONS_H__
#define __EFFECT_DEFINITIONS_H__

/* ---------- headers */

#include "omaha\tag_files\tag_groups.h"
#include "omaha\math\real_math.h"
#include "core\corelib\cseries\cseries_macros.h"

/* ---------- constants */

enum
{
    EFFECT_DEFINITION_TAG = 'effe',
};

/* ---------- definitions */

// effect_locations_block
struct effect_location_definition
{
    long marker_name; // 0x0
    unsigned short flags; // 0x4
    char priority; // 0x6
    unsigned char pad7[1]; // 0x7
};
static_assert(sizeof(effect_location_definition) == 0x8, "effect_location_definition");

// layout from the Reach effect_block_struct tag definition; fields after looping_sounds not reversed
struct effect_definition
{
    unsigned long flags; // 0x0
    long fixed_random_seed; // 0x4
    real restart_if_within; // 0x8
    real continue_if_within; // 0xC
    real death_delay; // 0x10
    short loop_start_event; // 0x14
    short local_location0; // 0x16
    short local_location1; // 0x18
    char priority; // 0x1A
    unsigned char pad1B[1]; // 0x1B
    real runtime_danger_radius; // 0x1C
    s_tag_block locations; // 0x20
    s_tag_block events; // 0x2C
    s_tag_block looping_sounds; // 0x38
    unsigned char __unknown44[0x60 - 0x44]; // 0x44
};
static_assert(sizeof(effect_definition) == 0x60, "effect_definition");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __EFFECT_DEFINITIONS_H__

