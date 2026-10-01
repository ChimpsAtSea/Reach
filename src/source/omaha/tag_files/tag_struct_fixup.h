#pragma once
#ifndef __TAG_STRUCT_FIXUP_H__
#define __TAG_STRUCT_FIXUP_H__

/* ---------- headers */

#include "foundation\baselib\datatypes\static_array.h"
#include "omaha\memory\wrapped_arrays.h"
#include "omaha\tag_files\tag_group_definitions.h"

/* ---------- constants */

/* ---------- definitions */

class c_tag_struct_fixup_iterator
{
public:
    c_tag_struct_fixup_iterator(c_basic_buffer<void> & source_struct, s_tag_struct_definition const * source_struct_definition, c_basic_buffer<void> & dest_struct, s_tag_struct_definition const * dest_struct_definition, c_tag_allocator * allocator);
    ~c_tag_struct_fixup_iterator(void);

    bool next(void);
    s_tag_struct_definition const * get_dest_struct_definition(void) const;
    s_tag_struct_definition const * get_source_struct_definition(void) const;
    c_basic_buffer<void> & get_source_struct(void);
    c_basic_buffer<void> & get_dest_struct(void);
    bool can_dispose_source_struct(void) const;

private:
    s_tag_struct_definition const * m_source_struct_definition; // 0x0
    s_tag_struct_definition const * m_dest_struct_definition; // 0x4
    c_tag_allocator * m_allocator; // 0x8
    s_tag_struct_definition const * m_current_source_struct_definition; // 0xC
    s_tag_struct_definition const * m_current_dest_struct_definition; // 0x10
    long m_intermediate_alignment_bits; // 0x14
    c_basic_buffer<void> m_source_struct; // 0x18
    c_basic_buffer<void> m_dest_struct; // 0x20
    s_static_array<c_basic_buffer<void>, 2> m_intermediate_structs; // 0x28
    long m_step_index; // 0x38
};
static_assert(sizeof(c_tag_struct_fixup_iterator) == 0x3C, "c_tag_struct_fixup_iterator");

/* ---------- prototypes */

void tag_struct_initialize(c_basic_buffer<void> & struct_buffer, s_tag_struct_definition const * struct_definition);
void tag_struct_dispose(c_basic_buffer<void> & struct_buffer, s_tag_struct_definition const * struct_definition, c_tag_allocator * allocator);
bool tag_struct_fixup_manually(s_tag_struct_definition const * original_struct_definition, c_basic_buffer<void> & source_struct, s_tag_struct_definition const * source_struct_definition, c_basic_buffer<void> & dest_struct, s_tag_struct_definition const * dest_struct_definition, c_tag_allocator * allocator, bool first_fixup);

/* ---------- globals */

/* ---------- public code */

#endif // __TAG_STRUCT_FIXUP_H__

