#pragma once
#ifndef __CACHE_FILE_RUNTIME_CODECS_H__
#define __CACHE_FILE_RUNTIME_CODECS_H__

/* ---------- headers */

#include "omaha\tag_files\tag_group_definitions.h"

/* ---------- constants */

/* ---------- definitions */

class c_cache_file_decompressor_service;

// vtable ??_7c_cache_file_decompressor_registry@@6B@ (0x82234118): 3 pure virtuals
class c_cache_file_decompressor_registry
{
public:
    virtual c_cache_file_decompressor_service * find_decompressor_service(s_tag_persistent_identifier const & decompressor_identifier) = 0;
    virtual long get_decompressor_service_count(void) = 0;
    virtual s_tag_persistent_identifier get_decompressor_service_identifier(long decompressor_service_index) = 0;
};

class c_cache_file_runtime_decompressor_registry :
    public c_cache_file_decompressor_registry
{
public:
    virtual c_cache_file_decompressor_service * find_decompressor_service(s_tag_persistent_identifier const & decompressor_identifier);
    virtual long get_decompressor_service_count(void);
    virtual s_tag_persistent_identifier get_decompressor_service_identifier(long decompressor_service_index);
};

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __CACHE_FILE_RUNTIME_CODECS_H__

