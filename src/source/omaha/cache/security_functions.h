#pragma once
#ifndef __SECURITY_FUNCTIONS_H__
#define __SECURITY_FUNCTIONS_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"

/* ---------- constants */

/* ---------- definitions */

struct s_network_http_request_hash
{
    unsigned char hash[20]; // 0x0
};
static_assert(sizeof(s_network_http_request_hash) == 0x14, "s_network_http_request_hash");

/* ---------- prototypes */

extern bool security_incremental_hash_begin(void * working_memory, long working_memory_size, bool use_secret_hash_salt, void * salt, long salt_size);
extern void security_incremental_hash_update(void * working_memory, long working_memory_size, void const * buffer, unsigned long buffer_size);
extern void security_incremental_hash_finish(void * working_memory, long working_memory_size, s_network_http_request_hash * hash);

/* ---------- globals */

/* ---------- public code */

#endif // __SECURITY_FUNCTIONS_H__

