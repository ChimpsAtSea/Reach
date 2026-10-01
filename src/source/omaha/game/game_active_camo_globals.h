#pragma once
#ifndef __GAME_ACTIVE_CAMO_GLOBALS_H__
#define __GAME_ACTIVE_CAMO_GLOBALS_H__

/* ---------- headers */

/* ---------- constants */

// names from the format_active_camo_level strings
enum e_active_camo_level
{
    _active_camo_level_none = -1,
    _active_camo_level_poor,
    _active_camo_level_good,
    _active_camo_level_excellent,
    _active_camo_level_invisible,
    _active_camo_level_ai,

    k_active_camo_level_count
};

/* ---------- definitions */

struct s_tag_block;

/* ---------- prototypes */

extern char * format_active_camo_level(long block_index, __int64 flags, s_tag_block * block, long element_index, char * buffer, long buffer_size);

/* ---------- globals */

/* ---------- public code */

#endif // __GAME_ACTIVE_CAMO_GLOBALS_H__

