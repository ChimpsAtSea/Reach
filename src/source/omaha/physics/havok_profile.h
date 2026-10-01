#pragma once
#ifndef __HAVOK_PROFILE_H__
#define __HAVOK_PROFILE_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"

/* ---------- constants */

/* ---------- definitions */

struct s_havok_statistics
{
    long active_island_count; // 0x0
    long total_island_count; // 0x4
    long active_entity_count; // 0x8
    long inactive_entity_count; // 0xC
    long fixed_entity_count; // 0x10
    long total_entity_count; // 0x14
};
static_assert(sizeof(s_havok_statistics) == 0x18, "s_havok_statistics");

/* ---------- prototypes */

extern void havok_profile_fetch(long * active_entity_count, long * inactive_entity_count, long * fixed_entity_count, long * total_entity_count, long * active_island_count, long * total_island_count);
extern void havok_profile_display(char * buffer, long buffer_size);
extern void havok_profile_start(void);
extern void havok_profile_update(void);
extern void havok_simulation_statistics_update(s_havok_statistics * statistics);
extern void havok_profile_stop(void);
extern void havok_profile_range(long tick_start, long tick_stop);

/* ---------- globals */

extern long g_havok_profile_start_tick;
extern long g_havok_profile_stop_tick;

/* ---------- public code */

#endif // __HAVOK_PROFILE_H__

