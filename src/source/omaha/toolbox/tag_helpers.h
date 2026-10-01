#pragma once
#ifndef __TAG_HELPERS_H__
#define __TAG_HELPERS_H__

/* ---------- headers */

#include "omaha\tag_files\tag_groups.h"
#include "omaha\tag_files\tag_group_definitions.h"

/* ---------- constants */

/* ---------- definitions */

// fake single-element block wrapping a struct: s_tag_block @0x0, owned block definition @0xC
class c_tag_block_from_struct :
    public s_tag_block
{
public:
    c_tag_block_from_struct(void const * struct_data, s_tag_struct_definition const * struct_definition);

private:
    s_tag_block_definition m_block_definition; // 0xC
};
static_assert(sizeof(c_tag_block_from_struct) == 0x20, "c_tag_block_from_struct");

class c_auto_tag_reference :
    public s_tag_reference
{
public:
    c_auto_tag_reference(void);
    ~c_auto_tag_reference(void);
};
static_assert(sizeof(c_auto_tag_reference) == 0x10, "c_auto_tag_reference");

/* ---------- prototypes */

template<typename t_type> class c_wrapped_array;

__int64 tag_block_get_max_element_size(s_tag_block_definition const * block_definition);
__int64 tag_struct_get_max_size(s_tag_struct_definition const * struct_definition);
bool path_to_tag_name_and_group(char const * tag_path_plus_extension, unsigned long * out_group_tag, c_wrapped_array<char> out_tag_name);

/* ---------- globals */

/* ---------- public code */

#endif // __TAG_HELPERS_H__

