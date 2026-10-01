#pragma once
#ifndef __CACHE_FILE_TAG_RESOURCE_CODEC_LIBRARY_H__
#define __CACHE_FILE_TAG_RESOURCE_CODEC_LIBRARY_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"
#include "omaha\cache\cache_file_tag_resource_definitions.h"
#include "omaha\memory\wrapped_arrays.h"

/* ---------- constants */

/* ---------- definitions */

class c_cache_file_tag_resource_codec_library
{
public:
    void add_codec(s_cache_file_codec_definition const & codec_definition);
    long create_uncompressed_identifier() const;
    bool is_uncompressed(long identifier) const;
    long get_codec_index(s_cache_file_codec_definition const & codec_definition) const;
    long create_codec_identifier(s_cache_file_codec_definition const & codec_definition) const;
    long get_codec_index(long decompressor_identifier) const;
    bool is_codec_index(long identifier) const;
    long create_sublocation_table_identifier() const;
    bool is_sublocation_table(long identifier) const;
    s_cache_file_codec_definition const & get_codec_definition(long codec_index) const;
    long get_codec_count() const;

private:
    c_static_sized_dynamic_array<s_cache_file_codec_definition, 127> m_codecs; // 0x0
};
static_assert(sizeof(c_cache_file_tag_resource_codec_library) == 0x7F4, "c_cache_file_tag_resource_codec_library");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __CACHE_FILE_TAG_RESOURCE_CODEC_LIBRARY_H__

