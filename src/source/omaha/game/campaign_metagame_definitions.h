#pragma once
#ifndef __CAMPAIGN_METAGAME_DEFINITIONS_H__
#define __CAMPAIGN_METAGAME_DEFINITIONS_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"
#include "omaha\tag_files\tag_groups.h"

/* ---------- constants */

/* ---------- definitions */

// Reach layout from campaign_metagame_globals_block (tag json), size 0x38
struct s_campaign_metagame_globals
{
    s_tag_block styles; // 0x0
    s_tag_block difficulty; // 0xC
    s_tag_block skulls; // 0x18
    long friendly_death_point_count; // 0x24
    long player_death_point_count; // 0x28
    long player_betrayal_point_count; // 0x2C
    float transient_score_time; // 0x30
    float emp_kill_window; // 0x34
};
static_assert(sizeof(s_campaign_metagame_globals) == 0x38, "s_campaign_metagame_globals");

/* ---------- prototypes */

extern char * campaign_metagame_difficulty_format(long block_index, __int64 flags, s_tag_block * block, long element_index, char * buffer, long buffer_size);
extern char * campaign_metagame_skull_format(long block_index, __int64 flags, s_tag_block * block, long element_index, char * buffer, long buffer_size);
extern s_campaign_metagame_globals * campaign_metagame_globals_get();

/* ---------- globals */

/* ---------- public code */

#endif // __CAMPAIGN_METAGAME_DEFINITIONS_H__

