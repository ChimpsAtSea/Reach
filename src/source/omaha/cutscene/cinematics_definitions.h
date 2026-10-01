#pragma once
#ifndef __CINEMATICS_DEFINITIONS_H__
#define __CINEMATICS_DEFINITIONS_H__

/* ---------- headers */

#include "omaha\tag_files\tag_groups.h"
#include "core\corelib\cseries\cseries_macros.h"

/* ---------- constants */

/* ---------- definitions */

// scenario_cinematics_block (Reach tag layout)
struct s_cinematic_reference
{
    unsigned char flags; // 0x0
    unsigned char pad[3]; // 0x1
    s_tag_reference name; // 0x4
};
static_assert(sizeof(s_cinematic_reference) == 0x14, "s_cinematic_reference");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __CINEMATICS_DEFINITIONS_H__

