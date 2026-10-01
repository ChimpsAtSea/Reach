#pragma once
#ifndef __CACHE_FILE_TAG_RESOURCE_LOCATION_HANDLER_H__
#define __CACHE_FILE_TAG_RESOURCE_LOCATION_HANDLER_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"
#include "omaha\memory\wrapped_arrays.h"
#include "omaha\tag_files\tag_resource_cache_interfaces.h"

/* ---------- constants */

/* ---------- definitions */

struct s_tag_resource_location_handle_struct;
struct s_indirect_cache_file_sub_location;
struct s_cache_file_resource_checksum;
struct s_cache_file_resource_physical_location;
struct s_cache_file_resource_streaming_sublocation_table;

class c_cache_file_resource_uber_location_table;

class c_cache_file_tag_resource_location_handler :
    public c_tag_resource_cache_file_location_handler
{
public:
    void initialize_for_new_map(c_cache_file_resource_uber_location_table const * location_table);
    void dispose_from_old_map();
    virtual bool get_location_sub_location(s_tag_resource_location_handle_struct * location_handle, s_indirect_cache_file_sub_location * out_sub_location);
    virtual unsigned long get_location_memory_size(s_tag_resource_location_handle_struct * location_handle);
    virtual bool try_to_get_location_checksum(s_tag_resource_location_handle_struct * location_handle, s_cache_file_resource_checksum * out_checksum);
    virtual unsigned __int64 get_location_indirect_identifier(s_tag_resource_location_handle_struct * location_handle);
    virtual unsigned long get_location_file_sort_key(s_tag_resource_location_handle_struct * location_handle);
    virtual bool allow_non_checksumed_resources();
    virtual bool describe_location(s_tag_resource_location_handle_struct * location_handle, c_wrapped_array<char> out_description_storage);
    void get_physical_location(unsigned __int64 indirect_location_identifier, s_cache_file_resource_physical_location * out_physical_location) const;
    void get_sublocation_table_entry(unsigned __int64 indirect_location_identifier, s_cache_file_resource_streaming_sublocation_table const ** out_sublocation_table) const;

private:
    c_cache_file_resource_uber_location_table const * m_location_table; // 0x4
};
static_assert(sizeof(c_cache_file_tag_resource_location_handler) == 0x8, "c_cache_file_tag_resource_location_handler");

/* ---------- prototypes */

/* ---------- globals */

extern bool allow_insecure_resources;

/* ---------- public code */

#endif // __CACHE_FILE_TAG_RESOURCE_LOCATION_HANDLER_H__
