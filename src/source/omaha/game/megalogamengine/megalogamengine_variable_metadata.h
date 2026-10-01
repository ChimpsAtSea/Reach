#ifndef __MEGALOGAMENGINE_VARIABLE_METADATA_H__
#define __MEGALOGAMENGINE_VARIABLE_METADATA_H__
#pragma once

/* ---------- headers */

#include "omaha\game\megalogamengine\megalogamengine_variant_variable.h"

/* ---------- constants */

// $TODO enumerator names unverified (c_enum<e_megalo_variable_network_state, unsigned char, 0, 3>)
enum e_megalo_variable_network_state
{
    _megalo_variable_network_state_none = 0,
    _megalo_variable_network_state_low,
    _megalo_variable_network_state_high,

    k_megalo_variable_network_state_count
};

/* ---------- definitions */

// $TODO layout not yet reversed (global traits: 0x7C bytes, network state arrays @ 0x50/0x5C/0x64/0x74)
template<typename t_variable_traits>
struct s_variable_metadata
{
    // f i: asserts VALID_INDEX(variable_index, get_variable_count(variable_type)) at megalogamengine_variable_metadata.h:167
    e_megalo_variable_network_state get_variable_network_state(e_variable_type variable_type, unsigned char variable_index) const;
};

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __MEGALOGAMENGINE_VARIABLE_METADATA_H__

