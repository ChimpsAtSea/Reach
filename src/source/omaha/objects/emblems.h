#pragma once
#ifndef __EMBLEMS_H__
#define __EMBLEMS_H__

/* ---------- headers */

#include "omaha\game\game_globals.h"
#include "omaha\memory\static_arrays.h"

/* ---------- constants */

enum e_emblem_info_flags
{
    _emblem_info_flag_alternate_foreground_channel_off = 0,
    _emblem_info_flag_flip_foreground,
    _emblem_info_flag_flip_background,

    k_emblem_info_flags_count
};

long const k_emblem_foreground_index_count = 127;
long const k_emblem_background_index_count = 127;

/* ---------- definitions */

typedef c_flags_no_init<e_emblem_info_flags, unsigned char, k_emblem_info_flags_count> c_emblem_info_flags;

struct s_emblem_info
{
    unsigned char foreground_emblem_index; // 0x0
    unsigned char background_emblem_index; // 0x1
    c_emblem_info_flags emblem_info_flags; // 0x2
    c_player_color_index primary_color_index; // 0x3
    c_player_color_index secondary_color_index; // 0x4
    c_player_color_index background_color_index; // 0x5
    unsigned short pad; // 0x6
};
static_assert(sizeof(s_emblem_info) == 0x8, "s_emblem_info");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __EMBLEMS_H__

