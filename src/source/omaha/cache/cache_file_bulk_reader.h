#pragma once
#ifndef __CACHE_FILE_BULK_READER_H__
#define __CACHE_FILE_BULK_READER_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"
#include "omaha\cache\security_functions.h"

/* ---------- constants */

/* ---------- definitions */

struct s_indirect_cache_file_sub_location
{
    unsigned long offset; // 0x0
    unsigned long unaligned_read_size; // 0x4
    unsigned long used_storage_size; // 0x8
    long decompressor_identifier; // 0xC
    bool valid_checksum; // 0x10
    s_network_http_request_hash checksum; // 0x11
};
static_assert(sizeof(s_indirect_cache_file_sub_location) == 0x28, "s_indirect_cache_file_sub_location");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __CACHE_FILE_BULK_READER_H__

