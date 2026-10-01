#pragma once
#ifndef __HAVOK_COLLISION_FILTER_DEFINITIONS_H__
#define __HAVOK_COLLISION_FILTER_DEFINITIONS_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"
#include "omaha\physics\havok_collision_filter.h"
#include "omaha\tag_files\tag_groups.h"

/* ---------- constants */

enum
{
    k_havok_collision_filter_definition_tag = 'hcfd',
};

/* ---------- definitions */

struct s_havok_collision_filter_group
{
    unsigned long flags; // 0x0 collision_filter_enum
};
static_assert(sizeof(s_havok_collision_filter_group) == 0x4, "s_havok_collision_filter_group");

struct s_havok_collision_filter_definition
{
    s_tag_block groups; // 0x0 s_havok_collision_filter_group, k_havok_group_count
    unsigned char alignment_pad[0x4]; // 0xC
    unsigned char group_filter[0x100]; // 0x10 hkpGroupFilter
};
static_assert(sizeof(s_havok_collision_filter_definition) == 0x110, "s_havok_collision_filter_definition");

/* ---------- prototypes */

bool havok_collision_filter_postprocess(long tag_index, bool for_editor);
char * havok_collision_filter_group_format(long block_index, __int64 flags, s_tag_block * block, long element_index, char * buffer, long buffer_size);
void havok_collision_filter_fixup(long havok_collision_filter_definition_index);

/* ---------- globals */

extern char const * collision_filter_enum_strings[k_havok_group_count];

/* ---------- public code */

#endif // __HAVOK_COLLISION_FILTER_DEFINITIONS_H__

