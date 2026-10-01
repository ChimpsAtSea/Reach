#pragma once
#ifndef __MEGALOGAMENGINE_PLAYER_OBJECTIVE_DATA_H__
#define __MEGALOGAMENGINE_PLAYER_OBJECTIVE_DATA_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"
#include "omaha\game\megalogamengine\megalogamengine_text.h"

/* ---------- constants */

/* ---------- definitions */

class c_bitstream;

struct s_player_objective_data
{
    void initialize(void);
    bool build_update(s_player_objective_data * update) const;
    void apply_update(s_player_objective_data const * update);
    void encode(c_bitstream * bitstream) const;
    void decode(c_bitstream * bitstream);

    c_dynamic_string primary_string;
    long allegiance_icon_index;
    c_dynamic_string secondary_string;
    long last_update_time; // not networked; stamped by apply_update
};
static_assert(sizeof(s_player_objective_data) == 0x20, "s_player_objective_data");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __MEGALOGAMENGINE_PLAYER_OBJECTIVE_DATA_H__

