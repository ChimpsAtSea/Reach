#pragma once
#ifndef __TAG_RESOURCE_CACHE_INTERFACES_H__
#define __TAG_RESOURCE_CACHE_INTERFACES_H__

/* ---------- headers */

#include "omaha\memory\wrapped_arrays.h"
#include "omaha\tag_files\tag_resource_internals.h"

/* ---------- constants */

/* ---------- definitions */

struct s_tag_resource_location_handle_struct;
struct s_indirect_cache_file_sub_location;
struct s_cache_file_resource_checksum;
struct s_tag_resource_definition;
struct s_tag_resource_cache_file_location;
enum e_tag_resource_lod;

class c_tag_resource_cache_file_location_handler
{
public:
    virtual bool get_location_sub_location(s_tag_resource_location_handle_struct * location_handle, s_indirect_cache_file_sub_location * out_sub_location) = 0;
    virtual unsigned long get_location_memory_size(s_tag_resource_location_handle_struct * location_handle) = 0;
    virtual bool try_to_get_location_checksum(s_tag_resource_location_handle_struct * location_handle, s_cache_file_resource_checksum * out_checksum) = 0;
    virtual unsigned __int64 get_location_indirect_identifier(s_tag_resource_location_handle_struct * location_handle) = 0;
    virtual unsigned long get_location_file_sort_key(s_tag_resource_location_handle_struct * location_handle) = 0;
    virtual bool allow_non_checksumed_resources() = 0;
    virtual bool describe_location(s_tag_resource_location_handle_struct * location_handle, c_wrapped_array<char> out_description_storage) = 0;
};
static_assert(sizeof(c_tag_resource_cache_file_location_handler) == 0x4, "c_tag_resource_cache_file_location_handler");

class c_tag_resource_cache_file_datum_handler
{
public:
    virtual c_basic_buffer<void> get_control_data(long resource_handle, bool is_optional) = 0;
    virtual c_tag_resource_fixup get_root_address_fixup(long resource_handle) = 0;
    virtual bool is_streamed(long resource_handle) = 0;
    virtual void * get_permanent_resource_root_address(long resource_handle, bool is_optional);
    virtual s_tag_resource_definition const * get_resource_definition(long resource_handle) = 0;
    virtual long get_resource_owner(long resource_handle) = 0;
    virtual c_wrapped_array<s_tag_resource_fixup_location const> get_control_fixups(long resource_handle) = 0;
    virtual long get_control_data_alignment(long resource_handle) = 0;
    virtual bool has_valid_interop_locations(long resource_handle) = 0;
    virtual bool describe_resource_cache_location(long resource_handle, e_tag_resource_lod resource_lod, s_tag_resource_cache_file_location * out_location) = 0;
    virtual c_basic_buffer<void> get_interop_buffer(long resource_handle, bool is_optional) = 0;
    virtual c_wrapped_array<s_tag_resource_interop_location const> get_interop_locations(long resource_handle) = 0;
    virtual bool describe_resource(long resource_handle, c_wrapped_array<char> out_description_storage) = 0;
    virtual bool any_pageable_data(long resource_handle) = 0;
    virtual bool any_optional_data(long resource_handle) = 0;
    virtual s_tag_resource_location_handle_struct * get_pageable_location_handle(long resource_handle) = 0;
    virtual s_tag_resource_location_handle_struct * get_optional_location_handle(long resource_handle) = 0;

    virtual unsigned long get_pageable_location_offset(long resource_handle)
    {
        return 0;
    };

    virtual unsigned long get_optional_location_offset(long resource_handle)
    {
        return 0;
    };
};
static_assert(sizeof(c_tag_resource_cache_file_datum_handler) == 0x4, "c_tag_resource_cache_file_datum_handler");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __TAG_RESOURCE_CACHE_INTERFACES_H__

