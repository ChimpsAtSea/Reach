#pragma once
#ifndef __MEGALOGAMENGINE_BOUNDARY_STATE_H__
#define __MEGALOGAMENGINE_BOUNDARY_STATE_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"
#include "blamlib\megalogamengine_player_filter.h"

/* ---------- constants */

/* ---------- definitions */

class c_bitstream;

struct s_megalo_object_boundary_state
{
    void initialize(e_player_filter_type filter_type);
    void encode(c_bitstream * bitstream) const;
    void decode(c_bitstream * bitstream);
    bool build_update(s_megalo_object_boundary_state * update) const;
    void apply_update(s_megalo_object_boundary_state const * update);

    c_player_filter filter;
    char variable_index;
};
static_assert(sizeof(s_megalo_object_boundary_state) == 0xC, "s_megalo_object_boundary_state");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __MEGALOGAMENGINE_BOUNDARY_STATE_H__

