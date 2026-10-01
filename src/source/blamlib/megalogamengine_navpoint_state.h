#pragma once
#ifndef __MEGALOGAMENGINE_NAVPOINT_STATE_H__
#define __MEGALOGAMENGINE_NAVPOINT_STATE_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"
#include "blamlib\megalogamengine_player_filter.h"
#include "omaha\game\megalogamengine\megalogamengine_text.h"
#include "omaha\interface\chud\chud_navpoints.h"
#include "omaha\memory\static_arrays.h"

/* ---------- constants */

// $TODO names unverified (megalo navpoint priority: initialize() uses 1)
enum e_navpoint_priority
{
    _navpoint_priority_low = 0,
    _navpoint_priority_normal,
    _navpoint_priority_high,
    _navpoint_priority_blink,

    k_navpoint_priority_count
};

enum
{
    k_navpoint_timer_index_count = 4,
    k_navpoint_distance_count = 101,
};

/* ---------- definitions */

class c_bitstream;

struct s_megalogamengine_navpoint_state
{
    void initialize(void);
    bool operator==(s_megalogamengine_navpoint_state const & other) const;
    bool operator!=(s_megalogamengine_navpoint_state const & other) const;
    void encode(c_bitstream * bitstream) const;
    void decode(c_bitstream * bitstream);

    c_dynamic_string text; // 0x0
    c_enum<e_chud_navpoint_icon_type, char, _chud_navpoint_icon_type_none, k_chud_navpoint_icon_type_count> icon; // 0xA
    c_player_filter filter; // 0xC
    c_enum<e_navpoint_priority, unsigned char, _navpoint_priority_low, k_navpoint_priority_count> priority; // 0x14
    char timer_index; // 0x15
    unsigned char min_distance; // 0x16
    unsigned char max_distance; // 0x17
};
static_assert(sizeof(s_megalogamengine_navpoint_state) == 0x18, "s_megalogamengine_navpoint_state");

/* ---------- prototypes */

/* ---------- globals */

extern char const * navpoint_icon_names[k_chud_navpoint_icon_type_count + 1];

/* ---------- public code */

#endif // __MEGALOGAMENGINE_NAVPOINT_STATE_H__

