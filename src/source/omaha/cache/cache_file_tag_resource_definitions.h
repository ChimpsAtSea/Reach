#pragma once
#ifndef __CACHE_FILE_TAG_RESOURCE_DEFINITIONS_H__
#define __CACHE_FILE_TAG_RESOURCE_DEFINITIONS_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"
#include "omaha\memory\wrapped_arrays.h"

/* ---------- constants */

/* ---------- definitions */

class c_tag_block_bit_vector :
    public c_bit_vector_operator_interface<c_tag_block_bit_vector>
{
public:
    friend class c_bit_vector_operator_interface<c_tag_block_bit_vector>;

    long bit_count() const;

private:
    unsigned long const * get_bit_storage() const;
    unsigned long * get_bit_storage();

    c_typed_tag_block<unsigned long> m_bits; // 0x0
};
static_assert(sizeof(c_tag_block_bit_vector) == 0xC, "c_tag_block_bit_vector");

struct s_cache_file_zone_manifest
{
    c_tag_block_bit_vector required_resources_bitvector; // 0x0
    c_tag_block_bit_vector deferred_resources_bitvector; // 0xC
    c_tag_block_bit_vector optional_resources_bitvector; // 0x18
    c_tag_block_bit_vector streamed_resources_bitvector; // 0x24
    long name; // 0x30
    unsigned long required_resource_size; // 0x34
    unsigned long deferred_required_size; // 0x38
    unsigned long optional_resource_size; // 0x3C
    unsigned long streamed_resource_size; // 0x40
    unsigned long dvd_in_memory_resource_size; // 0x44
    s_tag_block resource_usage; // 0x48
    s_tag_block budget_usage; // 0x54
    s_tag_block unique_budget_usage; // 0x60
    c_tag_block_bit_vector active_resource_owners; // 0x6C
    c_tag_block_bit_vector top_level_resource_owners; // 0x78
    s_tag_block attachment_hierarchy; // 0x84
    long asdf; // 0x90
    long sdf; // 0x94
    long df; // 0x98
    long f; // 0x9C
};
static_assert(sizeof(s_cache_file_zone_manifest) == 0xA0, "s_cache_file_zone_manifest");

struct s_cache_file_codec_definition
{
    s_tag_persistent_identifier identifier; // 0x0
};
static_assert(sizeof(s_cache_file_codec_definition) == 0x10, "s_cache_file_codec_definition");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __CACHE_FILE_TAG_RESOURCE_DEFINITIONS_H__
