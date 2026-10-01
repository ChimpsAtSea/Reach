#pragma once
#ifndef __DEBUG_MEMORY_ALLOCATORS_H__
#define __DEBUG_MEMORY_ALLOCATORS_H__

/* ---------- headers */

#include "foundation\baselib\memory\debug_memory\debug_memory_globals.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

struct s_base_memory_information;

extern void * debug_malloc(unsigned int size, e_debug_memory_flags flags, char const * file, long line, long type_identifier, char const * type, char const * subtype, char const * name);
extern void debug_free(void * pointer, char const * file, long line);
extern void * debug_realloc(void * pointer, unsigned int new_size, e_debug_memory_flags flags, char const * file, long line, long type_identifier, char const * type, char const * subtype, char const * name);
extern void * debug_malloc_aligned(unsigned int size, long alignment_bits, e_debug_memory_flags flags, char const * file, long line, long type_identifier, char const * type, char const * subtype, char const * name);
extern void debug_free_aligned(void * pointer, char const * file, long line);
extern void * debug_realloc_aligned(void * pointer, unsigned int new_size, long alignment_bits, e_debug_memory_flags flags, char const * file, long line, long type_identifier, char const * type, char const * subtype, char const * name);
extern void debug_pretrack_nonheap_alloc_static(void const * nonheap_resource, unsigned int size);
extern void debug_track_nonheap_alloc(void const * nonheap_resource, unsigned int size, e_debug_memory_flags flags, char const * file, long line, long type_identifier, char const * type, char const * subtype, char const * name);
extern void debug_track_nonheap_free(void const * nonheap_resource, char const * file, long line);
extern void debug_begin_tracking_nonheap_allocation(s_base_memory_information * start_information);
extern void debug_end_tracking_nonheap_allocation(s_base_memory_information const * start_information, s_base_memory_information const * end_information, void const * nonheap_resource, char const * file, long line, long type_identifier, char const * type, char const * subtype, char const * name);
extern void debug_initialize_memory(void * pointer, long value, unsigned int size);

/* ---------- globals */

/* ---------- public code */

#endif // __DEBUG_MEMORY_ALLOCATORS_H__

