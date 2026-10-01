#pragma once
#ifndef __TAG_FIELD_SCAN_H__
#define __TAG_FIELD_SCAN_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"

/* ---------- constants */

/* ---------- definitions */

struct s_tag_block_definition;
struct s_tag_struct_definition;
struct s_tag_field;

// offsets from tag_field_scan_state_new / tag_field_scan; names from assert strings where available, the rest unverified
struct tag_field_scan_state
{
    s_tag_struct_definition const * aggregate_definition; // 0x0
    s_tag_field const * fields; // 0x4
    void const * address; // 0x8
    unsigned long flags; // 0xC
    unsigned long field_types[2]; // 0x10
    __int64 external_element_locator_base; // 0x18
    long field_index; // 0x20
    long field_size; // 0x24
    long base_address_offset; // 0x28
    long cache_file_address_offset; // 0x2C
    bool done; // 0x30
    short stack_count; // 0x32
    unsigned char stack[0x80]; // 0x34 $TODO layout
    s_tag_field const * field; // 0xB4
    void * field_address; // 0xB8
    long field_base_address_offset; // 0xBC
    long field_cache_file_address_offset; // 0xC0
    long pad_C4; // 0xC4
    __int64 field_external_element_locator_base; // 0xC8
};
static_assert(sizeof(tag_field_scan_state) == 0xD0, "tag_field_scan_state");

enum e_tag_field;

struct s_tag_block;

// the constructors are thin wrappers over tag_field_scan_state_new (state at offset 0)
class c_tag_field_scanner
{
public:
    c_tag_field_scanner(s_tag_struct_definition const * definition, void const * address);
    c_tag_field_scanner(s_tag_block_definition const * definition, void const * address);
    c_tag_field_scanner(s_tag_block const * block, long element_index);
    c_tag_field_scanner(long tag_index);
    c_tag_field_scanner(tag_field_scan_state const * state);

    void set_scan_flags(unsigned long flags);
    void add_all_external_aggregate_types(void);
    void add_all_map_specific_types(void);
    void add_scan_type(e_tag_field field_type);
    void add_all_scan_types(void);
    bool any_fields_set_exist_recursively(void) const;
    bool next(void);
    s_tag_field const * field(void) const;
    void const * address(void) const;
    char const * name(void) const;
    void const * definition(void) const;
    e_tag_field type(void) const;
    unsigned long id(void) const;
    long base_address_offset(void) const;
    long cache_file_address_offset(void) const;
    unsigned long size(void) const;
    __int64 external_element_locator_base(void) const;
    __int64 try_to_get_external_element_locator_base(void) const;
    s_tag_field const * extract_field_from_stack(long stack_index) const;

protected:
    tag_field_scan_state m_state; // 0x0
};
static_assert(sizeof(c_tag_field_scanner) == 0xD0, "c_tag_field_scanner");

/* ---------- prototypes */

void tag_field_scan_state_new(tag_field_scan_state * state, s_tag_block_definition const * definition, void const * address);
void tag_field_scan_state_new(tag_field_scan_state * state, s_tag_struct_definition const * definition, void const * address);
bool tag_field_scan(tag_field_scan_state * state);
void tag_field_scan_state_add_field_type(tag_field_scan_state * state, e_tag_field field_type);

/* ---------- globals */

/* ---------- public code */

#endif // __TAG_FIELD_SCAN_H__

