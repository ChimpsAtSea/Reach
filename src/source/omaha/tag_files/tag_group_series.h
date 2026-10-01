#ifndef __TAG_GROUP_SERIES_H__
#define __TAG_GROUP_SERIES_H__
#pragma once

/* ---------- headers */

#include "core\corelib\cseries\cseries_asserts.h"
#include "omaha\tag_files\tag_group_definitions.h"
#include "omaha\tag_files\tag_group_editing.h"

/* ---------- constants */

/* ---------- definitions */

// maps a field base type to the type of s_tag_field::definition (return type of get_field_definition<k_field_base_type>)
template<e_tag_field_base_type k_field_base_type>
struct s_tag_field_base_type_definition_type;

template<>
struct s_tag_field_base_type_definition_type<_field_base_type_block_index>
{
    typedef s_tag_block_definition type;
};

template<>
struct s_tag_field_base_type_definition_type<_field_base_type_flags>
{
    typedef s_string_list_definition type;
};

template<>
struct s_tag_field_base_type_definition_type<_field_base_type_block_flags>
{
    typedef s_tag_block_definition type;
};

template<>
struct s_tag_field_base_type_definition_type<_field_base_type_enum>
{
    typedef s_string_list_definition type;
};

/* ---------- prototypes */

struct s_tag_field;
struct s_tag_struct_definition;

bool tag_field_is_non_custom_block_reference(s_tag_field const * field);
bool tag_field_is_block_reference(s_tag_field const * field);
s_tag_block_definition const * tag_field_get_block_reference_definition(s_tag_field const * field);
bool tag_field_is_aggregate(s_tag_field const * field);
bool tag_field_is_inlined_aggregate(s_tag_field const * field);
bool tag_field_is_external_aggregate(s_tag_field const * field);
long tag_field_get_inline_aggregate_count(s_tag_field const * field);
s_tag_struct_definition const * tag_field_get_aggregate_definition(s_tag_field const * field);
s_string_list_definition const * tag_field_get_string_list_definition(s_tag_field const * field);

/* ---------- public code */

template<e_tag_field_base_type k_field_base_type>
typename s_tag_field_base_type_definition_type<k_field_base_type>::type const * get_field_definition(s_tag_field const * field)
{
    assert_decomp(field, "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\tag_files\\tag_group_series.h", 61);
    assert_decomp(tag_field_get_base_type(field)==k_field_base_type, "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\tag_files\\tag_group_series.h", 62);

    return static_cast<typename s_tag_field_base_type_definition_type<k_field_base_type>::type const *>(field->definition);
}

/* ---------- globals */

#endif // __TAG_GROUP_SERIES_H__

