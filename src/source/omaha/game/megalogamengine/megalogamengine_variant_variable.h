#ifndef __MEGALOGAMENGINE_VARIANT_VARIABLE_H__
#define __MEGALOGAMENGINE_VARIANT_VARIABLE_H__
#pragma once

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"
#include "omaha\memory\static_arrays.h"
#include "omaha\game\megalogamengine\megalogamengine_custom_variable_reference.h"
#include "omaha\game\megalogamengine\megalogamengine_player_reference.h"
#include "omaha\game\megalogamengine\megalogamengine_object_reference.h"
#include "omaha\game\megalogamengine\megalogamengine_team_reference.h"
#include "omaha\game\megalogamengine\megalogamengine_custom_timer_reference.h"

/* ---------- constants */

enum e_variable_type
{
    _variable_type_number = 0,
    _variable_type_player,
    _variable_type_object,
    _variable_type_team,
    _variable_type_timer,

    k_variable_type_count
};

/* ---------- definitions */

class c_bitstream;

struct s_variant_variable
{
    void encode(c_bitstream * bitstream) const;
    void decode(c_bitstream * bitstream);

    // $TODO: reference layouts not yet reversed; every reference lives at offset 0
    // c_custom_variable_reference is 2-byte aligned (sizeof 4) but type sits at 0x3, so the numeric
    // reference is accessed through `storage` instead of being a union member
    union
    {
        c_player_reference player;
        c_object_reference object;
        c_team_reference team;
        c_custom_timer_reference timer;
        unsigned char storage[3];
    };
    c_enum<e_variable_type, unsigned char, _variable_type_number, k_variable_type_count> type;
};
static_assert(sizeof(s_variant_variable) == 0x4, "s_variant_variable");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __MEGALOGAMENGINE_VARIANT_VARIABLE_H__

