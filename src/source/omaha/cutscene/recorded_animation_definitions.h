#pragma once
#ifndef __RECORDED_ANIMATION_DEFINITIONS_H__
#define __RECORDED_ANIMATION_DEFINITIONS_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"
#include "omaha\tag_files\tag_groups.h"

/* ---------- constants */

/* ---------- definitions */

struct scenario;

struct recorded_animation_definition
{
    char name[32]; // 0x0
    unsigned char version; // 0x20
    unsigned char flags; // 0x21
    unsigned char unit_control_data_version; // 0x22
    unsigned char pad0; // 0x23
    short length_of_animation; // 0x24
    unsigned char pad1[2]; // 0x26
    unsigned char pad2[4]; // 0x28
    s_tag_data animation_data; // 0x2C
};
static_assert(sizeof(recorded_animation_definition) == 0x40, "recorded_animation_definition");

/* ---------- prototypes */

void byte_swap_recording(void * element, void * data, long data_size, bool for_writing);
short scenario_get_animation_by_name(scenario const * scenario, char const * animation_name);

/* ---------- globals */

/* ---------- public code */

#endif // __RECORDED_ANIMATION_DEFINITIONS_H__

