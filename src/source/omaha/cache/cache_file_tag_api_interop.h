#pragma once
#ifndef __CACHE_FILE_TAG_API_INTEROP_H__
#define __CACHE_FILE_TAG_API_INTEROP_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"
#include "omaha\memory\wrapped_arrays.h"
#include "omaha\tag_files\tag_groups.h"

/* ---------- constants */

/* ---------- definitions */

class c_tag_interop_verifier;

struct s_cache_file_tag_interop_vtable
{
    char const * type_name; // 0x0
    s_tag_persistent_identifier interop_identifier; // 0x4
    s_tag_persistent_identifier mat_was_dumb_interop_identifier; // 0x14
    unsigned long interop_object_size; // 0x24
    unsigned long interop_object_alignment_bits; // 0x28
    bool (*on_fixup_interop)(s_tag_interop *, c_tag_interop_verifier *); // 0x2C
    bool (*on_teardown_interop)(s_tag_interop *); // 0x30
    bool (*check_if_interop_locked)(s_tag_interop *); // 0x34
};
static_assert(sizeof(s_cache_file_tag_interop_vtable) == 0x38, "s_cache_file_tag_interop_vtable");

class c_tag_interop_object_type_info
{
public:
    c_tag_interop_object_type_info(s_tag_persistent_identifier const & type_identifier);
    c_tag_interop_object_type_info(long type_index);
    bool valid(void) const;
    unsigned long size(void) const;
    unsigned long alignment_bits(void) const;

private:
    long m_type_index; // 0x0
    unsigned long m_size; // 0x4
    unsigned long m_alignment_bits; // 0x8
};
static_assert(sizeof(c_tag_interop_object_type_info) == 0xC, "c_tag_interop_object_type_info");

class c_cache_file_tag_interop_bulk_sizer
{
public:
    c_cache_file_tag_interop_bulk_sizer(void);
    bool add_type_with_identifier(s_tag_persistent_identifier const & identifier);
    void add_type_with_type_index(long type_index);
    void add_type_manually(unsigned long size, unsigned long alignment_bits);
    unsigned long get_size(void) const;
    unsigned long get_alignment_bits(void) const;
    unsigned long get_unaligned_total_allocation_size(void) const;
    unsigned long get_next_offset(long type_index) const;
    unsigned long get_next_offset_manual(unsigned long alignment_bits) const;

private:
    unsigned long m_alignment_bits; // 0x0
    unsigned long m_total_size; // 0x4
};
static_assert(sizeof(c_cache_file_tag_interop_bulk_sizer) == 0x8, "c_cache_file_tag_interop_bulk_sizer");

class c_cache_file_tag_inteorp_bulk_allocator
{
public:
    c_cache_file_tag_inteorp_bulk_allocator(void * base_address, unsigned long total_size);
    bool allocate_and_fixup(long cache_file_interop_type, s_tag_interop * in_out_interop, c_tag_interop_verifier * interop_verifier);

private:
    c_basic_buffer<void> m_interop_buffer; // 0x0
    unsigned long m_next_interop_offset; // 0x8
};
static_assert(sizeof(c_cache_file_tag_inteorp_bulk_allocator) == 0xC, "c_cache_file_tag_inteorp_bulk_allocator");

/* ---------- prototypes */

long cache_file_tag_interop_get_type_count(void);
char const * cache_file_tag_interop_get_type_name(long type_index);
s_cache_file_tag_interop_vtable const * cache_file_get_interop_vtable(long type_index);
s_tag_persistent_identifier cache_file_tag_interop_get_type_identifier(long type_index);
long cache_file_tag_interop_get_type_index(s_tag_persistent_identifier const & identifier);
unsigned long cache_file_tag_interop_get_object_size(long type_index, unsigned long * out_alignment_bits);
bool cache_file_tag_interop_fixup(long type_index, s_tag_interop * in_out_interop, c_tag_interop_verifier * interop_verifier);
bool cache_file_tag_interop_teardown(long type_index, s_tag_interop * in_out_interop);
bool cache_file_tag_interop_locked(long type_index, s_tag_interop * in_out_interop);

/* ---------- globals */

extern s_cache_file_tag_interop_vtable const * g_cache_file_tag_interop_vtable[6];

/* ---------- public code */

#endif // __CACHE_FILE_TAG_API_INTEROP_H__

