#pragma once
#ifndef __CACHE_FILE_TAG_RESOURCE_CHECKSUM_H__
#define __CACHE_FILE_TAG_RESOURCE_CHECKSUM_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"
#include "omaha\cache\security_functions.h"

/* ---------- constants */

/* ---------- definitions */

struct s_cache_file_resource_checksum
{
    unsigned long crc_value; // 0x0
    s_network_http_request_hash hashes[3]; // 0x4
};
static_assert(sizeof(s_cache_file_resource_checksum) == 0x40, "s_cache_file_resource_checksum");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __CACHE_FILE_TAG_RESOURCE_CHECKSUM_H__

