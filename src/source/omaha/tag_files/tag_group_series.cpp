#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\tag_files\\tag_group_series.cpp"
/* ---------- headers */

#include "omaha\tag_files\tag_group_series.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "omaha\cseries\cseries.h"
#include "omaha\tag_files\tag_api_interop.h"
#include "omaha\tag_files\tag_group_definitions.h"
#include "omaha\tag_files\tag_group_editing.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// bool tag_field_is_non_custom_block_reference(struct s_tag_field const *);
// bool tag_field_is_block_reference(struct s_tag_field const *);
// struct s_tag_block_definition const * tag_field_get_block_reference_definition(struct s_tag_field const *);
// bool tag_field_is_aggregate(struct s_tag_field const *);
// bool tag_field_is_inlined_aggregate(struct s_tag_field const *);
// bool tag_field_is_external_aggregate(struct s_tag_field const *);
// long tag_field_get_inline_aggregate_count(struct s_tag_field const *);
// struct s_tag_struct_definition const * tag_field_get_aggregate_definition(struct s_tag_field const *);
// struct s_string_list_definition const * tag_field_get_string_list_definition(struct s_tag_field const *);
// struct s_tag_block_definition const * get_field_definition<5>(struct s_tag_field const *);
// struct s_tag_block_definition const * get_field_definition<1>(struct s_tag_field const *);
// struct s_string_list_definition const * get_field_definition<4>(struct s_tag_field const *);
// struct s_string_list_definition const * get_field_definition<7>(struct s_tag_field const *);

bool tag_field_is_non_custom_block_reference(s_tag_field const * field)
{
    mangled_ppc("?tag_field_is_non_custom_block_reference@@YA_NPBUs_tag_field@@@Z");

    assert_tag_debug_untracked_jul_11_2011(16, field);

    bool result = false;
    switch (tag_field_get_base_type(field))
    {
    case _field_base_type_block_index:
    case _field_base_type_block_flags:
        result = true;
        break;
    }

    return result;
};

bool tag_field_is_block_reference(s_tag_field const * field)
{
    mangled_ppc("?tag_field_is_block_reference@@YA_NPBUs_tag_field@@@Z");

    assert_tag_debug_untracked_jul_11_2011(33, field);

    bool result = false;
    switch (tag_field_get_base_type(field))
    {
    case _field_base_type_block_index:
    case _field_base_type_custom_block_index:
    case _field_base_type_block_flags:
        result = true;
        break;
    }

    return result;
};

s_tag_block_definition const * tag_field_get_block_reference_definition(s_tag_field const * field)
{
    mangled_ppc("?tag_field_get_block_reference_definition@@YAPBUs_tag_block_definition@@PBUs_tag_field@@@Z");

    assert_tag_debug_untracked_jul_11_2011(51, field);

    s_tag_block_definition const * result = NULL;
    switch (tag_field_get_base_type(field))
    {
    case _field_base_type_block_flags:
        result = get_field_definition<_field_base_type_block_flags>(field);
        break;
    case _field_base_type_block_index:
        result = get_field_definition<_field_base_type_block_index>(field);
        break;
    default:
        dassert_tag_debug_untracked_jul_11_2011(65, false, "can't get a block definition from a non-block reference field");
        break;
    }

    return result;
};

bool tag_field_is_aggregate(s_tag_field const * field)
{
    mangled_ppc("?tag_field_is_aggregate@@YA_NPBUs_tag_field@@@Z");

    assert_tag_debug_untracked_jul_11_2011(74, field);

    bool result = false;
    switch (field->type)
    {
    case _field_block:
    case _field_struct:
    case _field_array:
    case _field_pageable_resource:
    case _field_api_interop:
        result = true;
        break;
    }

    return result;
};

bool tag_field_is_inlined_aggregate(s_tag_field const * field)
{
    mangled_ppc("?tag_field_is_inlined_aggregate@@YA_NPBUs_tag_field@@@Z");

    assert_tag_debug_untracked_jul_11_2011(94, field);

    bool result = false;
    switch (field->type)
    {
    case _field_struct:
    case _field_array:
        result = true;
        break;
    }

    return result;
};

bool tag_field_is_external_aggregate(s_tag_field const * field)
{
    mangled_ppc("?tag_field_is_external_aggregate@@YA_NPBUs_tag_field@@@Z");

    assert_tag_debug_untracked_jul_11_2011(111, field);

    bool result = false;
    switch (field->type)
    {
    case _field_block:
    case _field_pageable_resource:
    case _field_api_interop:
        result = true;
        break;
    }

    return result;
};

long tag_field_get_inline_aggregate_count(s_tag_field const * field)
{
    mangled_ppc("?tag_field_get_inline_aggregate_count@@YAJPBUs_tag_field@@@Z");

    assert_tag_debug_untracked_jul_11_2011(129, field);

    long result = NONE;
    switch (field->type)
    {
    case _field_struct:
        result = 1;
        break;
    case _field_array:
        result = get_field_definition<_field_array>(field)->count;
        break;
    default:
        dassert_tag_debug_untracked_jul_11_2011(143, false, "unreachable");
        break;
    }

    return result;
};

// only diffs: unrelocated jump table in the target (objdiff artifact); table entries verified to point at the same case bodies
s_tag_struct_definition const * tag_field_get_aggregate_definition(s_tag_field const * field)
{
    mangled_ppc("?tag_field_get_aggregate_definition@@YAPBUs_tag_struct_definition@@PBUs_tag_field@@@Z");

    assert_tag_debug_untracked_jul_11_2011(152, field);

    s_tag_struct_definition const * result = NULL;
    switch (field->type)
    {
    case _field_struct:
        result = get_field_definition<_field_struct>(field);
        break;
    case _field_block:
        result = get_field_definition<_field_block>(field)->struct_definition;
        break;
    case _field_array:
        result = get_field_definition<_field_array>(field)->struct_definition;
        break;
    case _field_pageable_resource:
        result = get_field_definition<_field_pageable_resource>(field)->struct_definition;
        break;
    case _field_api_interop:
        result = get_field_definition<_field_api_interop>(field)->get_descriptor_definition();
        break;
    default:
        dassert_tag_debug_untracked_jul_11_2011(180, false, "attempting to get aggregate definition from a non-aggregate field");
        break;
    }

    return result;
};

s_string_list_definition const * tag_field_get_string_list_definition(s_tag_field const * field)
{
    mangled_ppc("?tag_field_get_string_list_definition@@YAPBUs_string_list_definition@@PBUs_tag_field@@@Z");

    assert_tag_debug_untracked_jul_11_2011(189, field);

    s_string_list_definition const * result = NULL;
    switch (tag_field_get_base_type(field))
    {
    case _field_base_type_flags:
        result = get_field_definition<_field_base_type_flags>(field);
        break;
    case _field_base_type_enum:
        result = get_field_definition<_field_base_type_enum>(field);
        break;
    default:
        dassert_tag_debug_untracked_jul_11_2011(203, false, "attempting to get string list definition from non-string-list typed field");
        break;
    }

    return result;
};
