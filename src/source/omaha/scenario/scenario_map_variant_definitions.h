#pragma once
#ifndef __SCENARIO_MAP_VARIANT_DEFINITIONS_H__
#define __SCENARIO_MAP_VARIANT_DEFINITIONS_H__

/* ---------- headers */

#include "omaha\tag_files\tag_groups.h"
#include "core\corelib\cseries\cseries_macros.h"

/* ---------- constants */

/* ---------- definitions */

struct s_map_variant_object_variant
{
    long display_name; // 0x0
    s_tag_reference object; // 0x4
    long variant_name; // 0x14
};
static_assert(sizeof(s_map_variant_object_variant) == 0x18, "s_map_variant_object_variant");

struct s_map_variant_palette_entry
{
    long name; // 0x0
    s_tag_block variants; // 0x4
    long maximum_allowed; // 0x10
    long price_per_instance; // 0x14
};
static_assert(sizeof(s_map_variant_palette_entry) == 0x18, "s_map_variant_palette_entry");

struct s_map_variant_palette
{
    long name; // 0x0
    unsigned char flags; // 0x4
    unsigned char pad[3]; // 0x5
    s_tag_block entries; // 0x8
};
static_assert(sizeof(s_map_variant_palette) == 0x14, "s_map_variant_palette");

/* ---------- prototypes */

bool postprocess_map_variant_object_variant(long tag_index, void * element, bool for_editor);

/* ---------- globals */

/* ---------- public code */

#endif // __SCENARIO_MAP_VARIANT_DEFINITIONS_H__

