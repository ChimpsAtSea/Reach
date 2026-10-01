#pragma once
#ifndef __TAG_GROUP_EDITING_H__
#define __TAG_GROUP_EDITING_H__

/* ---------- headers */

/* ---------- constants */

// values from tag_field_type_get_base_type (names guessed from the e_tag_field types mapped to each value)
enum e_tag_field_base_type
{
    _field_base_type_integer = 0, // char/short/long integer, short bounds
    _field_base_type_block_index, // char/short/long block index
    _field_base_type_custom_block_index, // custom char/short/long block index
    _field_base_type_color, // rgb/argb, real rgb/argb/hsv/ahsv colors
    _field_base_type_flags, // long/word/byte flags (string list definition)
    _field_base_type_block_flags, // long/word/byte block flags
    _field_base_type_real, // real, real fraction, real bounds
    _field_base_type_enum, // char/short/long enum (string list definition)
    _field_base_type_string, // string, long string, string ids
};

/* ---------- definitions */

/* ---------- prototypes */

struct s_tag_field;

long tag_field_get_external_maximum_element_count(s_tag_field const * field);
e_tag_field_base_type tag_field_get_base_type(s_tag_field const * field);

/* ---------- globals */

/* ---------- public code */

#endif // __TAG_GROUP_EDITING_H__

