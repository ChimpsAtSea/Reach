#pragma once
#ifndef __MEGALOGAMENGINE_H__
#define __MEGALOGAMENGINE_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"
#include "foundation\baselib\datatypes\static_stack.h"
#include "omaha\game\megalogamengine\megalogamengine_trigger.h"
#include "omaha\game\megalogamengine\megalogamengine_variable_metadata.h"
#include "omaha\game\megalogamengine\megalogamengine_variable_values.h"

/* ---------- constants */

/* ---------- definitions */

struct s_custom_game_engine_definition
{
    // $TODO remaining members (per ??0s_custom_game_engine_definition@@QAA@XZ):
    // c_static_stack<c_condition, 512> @ 0xF04, c_static_stack<c_action, 1024> @ 0x2F08,
    // c_static_stack<c_megalo_game_statistic, 4> @ 0x7F0C, s_variable_metadata<...> @ 0x7F20.., ...
    c_static_stack<c_trigger, 320> triggers; // 0x0
    unsigned char unknownF04[0x7F20 - 0xF04]; // $TODO conditions, actions, statistics (see above)
    s_variable_metadata<s_global_variable_traits> global_variable_metadata; // 0x7F20
};

/* ---------- prototypes */

/* ---------- globals */

extern char const * const k_megalogamengine_directory;

/* ---------- public code */

#endif // __MEGALOGAMENGINE_H__

