#pragma once
#ifndef __BASE_MEMORY_WINDOWS_H__
#define __BASE_MEMORY_WINDOWS_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"

/* ---------- constants */

/* ---------- definitions */

enum e_base_memory_expanded_heap_status
{
    _base_memory_expanded_heap_uninitialized = 0,
    _base_memory_expanded_heap_unavailable,
    _base_memory_expanded_heap_available,

    k_base_memory_expanded_heap_status_count
};

struct s_base_memory_globals
{
    e_base_memory_expanded_heap_status expanded_heap_status;
};
static_assert(sizeof(s_base_memory_globals) == 0x4, "s_base_memory_globals");

struct s_base_memory_information
{
    unsigned int free; // unsigned: converted with rldicl in debug_report_memory_checkpoint / debug_dump_memory_for_file
    unsigned int total;
    unsigned int tracked_heap_allocations;
    unsigned int tracked_nonheap_allocations;
};
static_assert(sizeof(s_base_memory_information) == 0x10, "s_base_memory_information");

/* ---------- prototypes */

void * base_malloc(unsigned int size);
void base_free(void * pointer);
void * base_realloc(void * pointer, unsigned int size);
unsigned int base_memory_get_used_memory_size(void const * pointer);
long base_memory_get_alignment_bits(void);
void base_heap_validate(void);
void base_memory_information_get(s_base_memory_information * information);
e_base_memory_expanded_heap_status base_memory_get_expanded_heap_status(void);
bool expanded_heap_initialized(void);
bool expanded_heap_available(void);
bool expanded_heap_initialize(void);
unsigned int base_memory_get_page_size(void);
unsigned int base_memory_get_used_memory_size_internal(void * pointer);

/* ---------- globals */

/* ---------- public code */

#endif // __BASE_MEMORY_WINDOWS_H__

