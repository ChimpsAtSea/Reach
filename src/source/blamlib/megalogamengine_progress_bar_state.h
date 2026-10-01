#pragma once
#ifndef __MEGALOGAMENGINE_PROGRESS_BAR_STATE_H__
#define __MEGALOGAMENGINE_PROGRESS_BAR_STATE_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"
#include "blamlib\megalogamengine_player_filter.h"

/* ---------- constants */

/* ---------- definitions */

class c_bitstream;

struct s_progress_bar_state
{
    s_progress_bar_state(void);
    void initialize(void);
    bool operator==(s_progress_bar_state const & other) const;
    bool operator!=(s_progress_bar_state const & other) const;
    void encode(c_bitstream * bitstream) const;
    void decode(c_bitstream * bitstream);

    c_player_filter filter;
    char timer_index;
};
static_assert(sizeof(s_progress_bar_state) == 0xC, "s_progress_bar_state");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __MEGALOGAMENGINE_PROGRESS_BAR_STATE_H__

