#pragma once
#ifndef __SOUND_EFFECT_DEFINITION_H__
#define __SOUND_EFFECT_DEFINITION_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"
#include "omaha\math\function_definitions.h"

/* ---------- constants */

/* ---------- definitions */

struct s_tag_field;

struct s_sound_effect_override_parameter_v1
{
    long name; // 0x0 string_id
    long integer_value; // 0x4
    float real_value; // 0x8
};
static_assert(sizeof(s_sound_effect_override_parameter_v1) == 0xC, "s_sound_effect_override_parameter_v1");

struct s_sound_effect_override_parameter
{
    long name; // 0x0 string_id
    long input; // 0x4 string_id
    long range; // 0x8 string_id
    float time_period; // 0xC
    long integer_value; // 0x10
    float real_value; // 0x14
    c_function_definition function_value; // 0x18
};
static_assert(sizeof(s_sound_effect_override_parameter) == 0x2C, "s_sound_effect_override_parameter");

struct s_sound_effect_template_parameter_definition
{
    long name; // 0x0 string_id
    short type; // 0x4
    unsigned short flags; // 0x6
    long hardware_offset; // 0x8
    long default_enum_integer_value; // 0xC
    float default_scalar_value; // 0x10
    c_function_definition default_function; // 0x14
    float minimum_scalar_value; // 0x28
    float maximum_scalar_value; // 0x2C
};
static_assert(sizeof(s_sound_effect_template_parameter_definition) == 0x30, "s_sound_effect_template_parameter_definition");

struct s_sound_effect_template_sound_input_definition
{
    long dsp_effect; // 0x0 string_id
    c_function_definition low_frequency_sound; // 0x4
    float time_period; // 0x18
};
static_assert(sizeof(s_sound_effect_template_sound_input_definition) == 0x1C, "s_sound_effect_template_sound_input_definition");

/* ---------- prototypes */

bool convert_legacy_sound_effect_override(unsigned long group_tag, s_tag_field const * old_fields, long old_count, long old_element_size, void * old_element, s_tag_field const * new_fields, long new_count, long new_element_size, void * new_element);
bool create_default_sound_effect_override(void * element);
bool create_sound_effect_template_parameter(void * element);
bool create_sound_effect_template_sound_input(void * element);

/* ---------- globals */

extern s_tag_field g_sound_effect_override_parameters_fields_v1[];
extern s_tag_field g_sound_effect_override_parameters_fields_v2[];

/* ---------- public code */

#endif // __SOUND_EFFECT_DEFINITION_H__

