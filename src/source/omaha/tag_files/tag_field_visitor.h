#pragma once
#ifndef __TAG_FIELD_VISITOR_H__
#define __TAG_FIELD_VISITOR_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"

/* ---------- constants */

/* ---------- definitions */

template<typename t_type> class c_basic_buffer;
class c_tag_field_scanner;
struct s_tag_field;
struct s_tag_block;
struct s_tag_struct_definition;
struct s_tag_array_definition;
struct s_tag_resource;
struct s_tag_interop;

// vtable order from ??_7c_tag_field_visitor@@6B@ (0x822526A4, slot 0 is _purecall); size from c_tag_recursive_resource_visitor (first member at 0xB68)
class c_tag_field_visitor
{
public:
    c_tag_field_visitor(void);

    bool visit_tag_struct(s_tag_struct_definition const * struct_definition, c_basic_buffer<void> & buffer);
    bool visit_tag_block(s_tag_block * block);
    bool visit_tag_array(s_tag_array_definition const * array_definition, c_basic_buffer<void> & buffer);
    bool visit_tag_resource(s_tag_resource * resource);
    bool visit_tag_interop(s_tag_interop * interop);

protected:
    virtual void initialize_tag_scanner(c_tag_field_scanner * scanner) = 0;
    virtual bool visit_field(s_tag_field const * field, c_basic_buffer<void> & buffer);
    virtual bool visit_struct_head(s_tag_struct_definition const * struct_definition, c_basic_buffer<void> & buffer);
    virtual bool visit_struct_tail(s_tag_struct_definition const * struct_definition, c_basic_buffer<void> & buffer);
    virtual bool visit_block_element_head(s_tag_block const * block, long element_index);
    virtual bool visit_block_element_tail(s_tag_block const * block, long element_index);
    virtual bool visit_tag_resource_recursive(s_tag_resource * resource);
    virtual bool visit_tag_interop_recursive(s_tag_interop * interop);

    char const * get_scope_string(void);
    __int64 get_field_locator(void);
    unsigned long get_field_depth(void);
    long get_element_index(void);
    bool visit_field_default(s_tag_field const * field, c_basic_buffer<void> & buffer);

private:
    bool visit_tag_struct_recursive(s_tag_struct_definition const * struct_definition, c_basic_buffer<void> & buffer);
    bool visit_tag_block_recursive(s_tag_block * block);
    bool visit_tag_array_recursive(s_tag_array_definition const * array_definition, c_basic_buffer<void> & buffer);
    bool visit_tag_struct_recursive_internal(s_tag_struct_definition const * struct_definition, long element_index, c_basic_buffer<void> & buffer);

protected:
    // $TODO layout: c_static_stack<s_tag_field_scope_definition, 16> at 0x8, c_tag_field_location at 0x4D0, bool at 0xB60 (from the constructor)
    // 8-byte aligned: c_tag_recursive_resource_visitor (0xB7C of members) occupies 0xB80 bytes of stack in visit_field
    __int64 m_opaque_data8[(0xB68 - 0x8) / sizeof(__int64)]; // 0x8
};
static_assert(sizeof(c_tag_field_visitor) == 0xB68, "c_tag_field_visitor");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __TAG_FIELD_VISITOR_H__

