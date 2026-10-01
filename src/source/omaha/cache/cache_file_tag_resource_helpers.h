#pragma once
#ifndef __CACHE_FILE_TAG_RESOURCE_HELPERS_H__
#define __CACHE_FILE_TAG_RESOURCE_HELPERS_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"
#include "omaha\cache\cache_files.h"
#include "omaha\cache\cache_file_tag_resource_definitions.h"
#include "omaha\memory\wrapped_arrays.h"

/* ---------- constants */

/* ---------- definitions */

class c_cache_file_zone_resource_collector
{
public:
    c_cache_file_zone_resource_collector(c_wrapped_flags active_resources, c_wrapped_flags active_resource_owners, bool cache_streaming_data, s_cache_file_loaded_tags_header const * tags_header);
    c_cache_file_zone_resource_collector(c_wrapped_flags active_resources, c_wrapped_flags active_resource_owners, bool cache_streaming_data);
    void add_zone_mask(c_typed_tag_block<s_cache_file_zone_manifest> const * zone_block, unsigned long zone_mask);
    void add_all_zones(c_typed_tag_block<s_cache_file_zone_manifest> const * zone_block);
    void add_all_resources();

private:
    void add_single_zone(s_cache_file_zone_manifest const * zone_manifest);

    s_cache_file_tag_instance_bounds m_instance_bounds; // 0x0
    c_typed_opaque_data<c_wrapped_flags, 8, 4> m_active_resources; // 0x8
    c_typed_opaque_data<c_wrapped_flags, 8, 4> m_active_resource_owners; // 0x14
    bool m_cache_streaming_data; // 0x20
};
static_assert(sizeof(c_cache_file_zone_resource_collector) == 0x24, "c_cache_file_zone_resource_collector");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __CACHE_FILE_TAG_RESOURCE_HELPERS_H__
