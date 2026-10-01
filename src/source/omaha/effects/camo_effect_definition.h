#pragma once
#ifndef __CAMO_EFFECT_DEFINITION_H__
#define __CAMO_EFFECT_DEFINITION_H__

/* ---------- headers */

#include "omaha\math\function_definitions.h"
#include "core\corelib\cseries\cseries_macros.h"

/* ---------- constants */

/* ---------- definitions */

// s_camo_scalar_function_struct in the tag layout
struct s_camo_function
{
    long input_variable; // 0x0 string_id
    long range_variable; // 0x4 string_id
    c_function_definition function; // 0x8
};
static_assert(sizeof(s_camo_function) == 0x1C, "s_camo_function");

struct s_camo_function_state
{
    long object_index; // 0x0
    float time; // 0x4
    float camo_value; // 0x8

    float eval_string_id(long name, float default_value) const;
};
static_assert(sizeof(s_camo_function_state) == 0xC, "s_camo_function_state");

// s_camo_struct_definition in the tag layout
struct s_camo_effect_definition
{
    unsigned short flags; // 0x0
    unsigned char pad[2]; // 0x2
    s_camo_function active_camo_amount; // 0x4
    s_camo_function shadow_amount; // 0x20

    static bool on_new(void * element);
    static bool postprocess(long tag_index, void * element, bool for_editor);
    void evaluate(long object_index, float camo_value, long * active_camo_amount_out, long * shadow_amount_out) const;
};
static_assert(sizeof(s_camo_effect_definition) == 0x3C, "s_camo_effect_definition");

/* ---------- prototypes */

void init_scalar_function(s_camo_function * function, float clamp_range_min, float clamp_range_max);
float eval_scalar_function(s_camo_function const * function, s_camo_function_state const * state);

/* ---------- globals */

/* ---------- public code */

#endif // __CAMO_EFFECT_DEFINITION_H__

