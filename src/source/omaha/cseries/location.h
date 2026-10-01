#pragma once
#ifndef __LOCATION_H__
#define __LOCATION_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"
#include "omaha\cseries\cseries.h"

/* ---------- constants */

/* ---------- definitions */

// Reach layout per portal_reference_set (two halfwords; H3 packed both into one short)
struct s_portal_reference
{
    short bsp_index; // 0x0
    short portal_index; // 0x2
};
static_assert(sizeof(s_portal_reference) == 0x4, "s_portal_reference");

struct s_cluster_reference
{
    union
    {
        struct
        {
            char bsp_index; // 0x0
            unsigned char cluster_index; // 0x1
        };
        short packed; // copied as a halfword in the target
    };
};
static_assert(sizeof(s_cluster_reference) == 0x2, "s_cluster_reference");

/* ---------- prototypes */

// f i (owned by game_sound.obj)
inline s_portal_reference const * portal_reference_set(s_portal_reference * portal_reference, long bsp_index, long portal_index)
{
    portal_reference->bsp_index = static_cast<short>(bsp_index);
    portal_reference->portal_index = static_cast<short>(portal_index);

    return portal_reference;
};

// f i (owned by render_view.obj)
inline bool cluster_reference_valid(s_cluster_reference cluster_reference)
{
    return cluster_reference.bsp_index != NONE;
};

/* ---------- globals */

/* ---------- public code */

#endif // __LOCATION_H__
