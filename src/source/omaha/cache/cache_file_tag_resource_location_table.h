#pragma once
#ifndef __CACHE_FILE_TAG_RESOURCE_LOCATION_TABLE_H__
#define __CACHE_FILE_TAG_RESOURCE_LOCATION_TABLE_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"
#include "omaha\memory\wrapped_arrays.h"

/* ---------- constants */

/* ---------- definitions */

struct s_tag_resource_location_handle_struct;
struct s_network_http_request_hash;
struct s_cache_file_resource_checksum;
struct s_cache_file_resource_streaming_sublocation_table;

struct s_cache_file_resource_physical_location
{
    long file_index; // 0x0
    unsigned long file_offset; // 0x4
    unsigned long file_size; // 0x8
    unsigned long memory_size; // 0xC
};
static_assert(sizeof(s_cache_file_resource_physical_location) == 0x10, "s_cache_file_resource_physical_location");

class c_cache_file_resource_uber_location_table
{
public:
    unsigned long get_location_sort_key(s_tag_resource_location_handle_struct * location_handle) const;
    long get_location_decompressor_identifier(s_tag_resource_location_handle_struct * location_handle) const;
    bool get_physical_location_from_handle(s_tag_resource_location_handle_struct * location_handle, s_cache_file_resource_physical_location * out_physical_location) const;
    bool get_streaming_sublocation_table_from_handle(s_tag_resource_location_handle_struct * location_handle, s_cache_file_resource_streaming_sublocation_table const ** out_sublocation_table) const;
    s_network_http_request_hash const * try_to_get_location_checksum_from_handle(s_tag_resource_location_handle_struct * location_handle) const;
    s_cache_file_resource_checksum const * try_to_get_location_full_checksum_from_handle(s_tag_resource_location_handle_struct * location_handle) const;
    bool describe_location(s_tag_resource_location_handle_struct * location_handle, c_wrapped_array<char> out_description_storage) const;
};

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __CACHE_FILE_TAG_RESOURCE_LOCATION_TABLE_H__

