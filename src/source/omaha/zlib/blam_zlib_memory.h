#pragma once
#ifndef __BLAM_ZLIB_MEMORY_H__
#define __BLAM_ZLIB_MEMORY_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"

/* ---------- constants */

/* ---------- definitions */

struct s_memory_pool;
struct z_stream_s;

struct s_blam_zlib_memory
{
    s_memory_pool * heap;
};
static_assert(sizeof(s_blam_zlib_memory) == 0x4, "s_blam_zlib_memory");

/* ---------- prototypes */

void blam_zlib_initialize(s_memory_pool * heap, s_blam_zlib_memory * out_zlib_memory_tracker);
void blam_zlib_dispose(s_blam_zlib_memory * zlib_memory_tracker);
bool blam_zlib_stream_setup(z_stream_s * out_zlib_stream, s_blam_zlib_memory * zlib_memory_tracker);
void * blam_zlib_malloc(void * context, unsigned int count, unsigned int size);
void blam_zlib_free(void * context, void * pointer);

/* ---------- globals */

/* ---------- public code */

#endif // __BLAM_ZLIB_MEMORY_H__

