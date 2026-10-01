#pragma once
#ifndef __MEMORY_POOL_H__
#define __MEMORY_POOL_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"
#include "foundation\baselib\datatypes\flags.h"
#include "foundation\baselib\datatypes\static_string.h"

/* ---------- constants */

enum e_memory_pool_flags
{
    _memory_pool_initialized_bit = 0,
    _memory_pool_doesnt_track_references_bit,
    _memory_pool_no_block_pointers_bit,
    _memory_pool_allocate_from_anywhere_in_pool_bit,
    _memory_pool_allocate_from_anywhere_in_pool_on_failure_bit,
    _memory_pool_compact_on_allocate_bit,
    _memory_pool_no_verification_bit,
    _memory_pool_compacting_bit,

    k_memory_pool_flags_count
};

enum
{
    k_memory_pool_null_handle = 0,
};

/* ---------- definitions */

class c_allocation_interface;
class c_simple_file;

typedef void (*memory_pool_relocation_function)(long, unsigned long);

struct s_memory_pool
{
    unsigned long signature;
    s_flags<e_memory_pool_flags, unsigned long, k_memory_pool_flags_count> flags;
    s_static_string<32> name;
    c_allocation_interface * allocation;
    memory_pool_relocation_function relocation_function;
    unsigned int size;
    unsigned int free_size;
    unsigned long base_handle;
    unsigned long first_block_handle;
    unsigned long last_block_handle;
    unsigned long incremental_compact_block_handle;
};
static_assert(sizeof(s_memory_pool) == 0x48, "s_memory_pool");

struct s_memory_pool_block_info
{
    unsigned int total_size;
    long reference;
    unsigned long next_block_handle;
    unsigned long previous_block_handle;
};
static_assert(sizeof(s_memory_pool_block_info) == 0x10, "s_memory_pool_block_info");

struct s_memory_pool_block_header
{
    unsigned long header_signature;
    unsigned long timestamp;
    char const * file;
    long line;
};
static_assert(sizeof(s_memory_pool_block_header) == 0x10, "s_memory_pool_block_header");

/* ---------- prototypes */

s_memory_pool * memory_pool_new(char const * name, unsigned int size, memory_pool_relocation_function const relocation_function, c_allocation_interface * allocation, char const * file, long line);
void memory_pool_dispose(s_memory_pool * pool, char const * file, long line);
s_memory_pool * memory_pool_inplace_new(char const * name, void * buffer, unsigned int buffer_size, memory_pool_relocation_function const relocation_function);
void memory_pool_inplace_dispose(s_memory_pool * pool);
unsigned int memory_pool_allocation_size(unsigned int size);
void memory_pool_clear(s_memory_pool * pool);
void memory_pool_compact(s_memory_pool * pool);
void memory_pool_compact_incrementally(s_memory_pool * pool, long block_count);
void * memory_pool_get_base_address(s_memory_pool const * pool);
void memory_pool_verify(s_memory_pool const * pool);
void memory_pool_set_relocation_function(s_memory_pool * pool, memory_pool_relocation_function const relocation_function);
void memory_pool_set_reference_tracking(s_memory_pool * pool, bool track_references);
void memory_pool_set_allow_block_pointers(s_memory_pool * pool, bool allow_block_pointers);
void memory_pool_set_allocation_from_anywhere_in_pool(s_memory_pool * pool, bool allocate_from_anywhere);
void memory_pool_set_allocation_from_anywhere_in_pool_on_failure(s_memory_pool * pool, bool allocate_from_anywhere);
void memory_pool_set_allow_compact_on_allocate(s_memory_pool * pool, bool allow_compact);
void memory_pool_set_verification(s_memory_pool * pool, bool use_verification);
long memory_pool_get_number_of_blocks(s_memory_pool const * pool);
unsigned int memory_pool_get_free_size(s_memory_pool const * pool);
unsigned int memory_pool_get_used_size(s_memory_pool const * pool);
unsigned int memory_pool_get_contiguous_free_size(s_memory_pool const * pool);
void memory_pool_get_bounds(s_memory_pool const * pool, void ** out_begin, void ** out_end);
void * memory_pool_get_end_address(s_memory_pool const * pool);
unsigned long memory_pool_block_allocate_handle_tracked(s_memory_pool * pool, long reference, unsigned int size, char const * file, long line);
unsigned long memory_pool_block_reallocate_handle_tracked(s_memory_pool * pool, unsigned long payload_handle, unsigned int new_size, char const * file, long line);
void memory_pool_block_free_handle(s_memory_pool * pool, unsigned long payload_handle);
bool memory_pool_block_verify_handle(s_memory_pool const * pool, unsigned long payload_handle);
void * memory_pool_handle_get_address(s_memory_pool const * pool, unsigned long payload_handle);
unsigned int memory_pool_get_block_handle_size(s_memory_pool const * pool, unsigned long payload_handle);
bool memory_pool_block_allocate_tracked(s_memory_pool * pool, void ** payload_data, unsigned int size, char const * file, long line);
bool memory_pool_block_reallocate_tracked(s_memory_pool * pool, void ** payload_data, unsigned int new_size, char const * file, long line);
void memory_pool_block_free(s_memory_pool * pool, void ** payload_data);
bool memory_pool_block_verify(s_memory_pool * pool, void ** payload_data);
unsigned int memory_pool_get_block_size(s_memory_pool const * pool, void ** payload_data);
void memory_pool_dump_to_file(s_memory_pool const * pool, char const * dump_prefix);
void memory_pool_dump_to_debugger(s_memory_pool const * pool, char const * dump_prefix);
void memory_pool_dump(s_memory_pool const * pool, char const * dump_prefix, c_simple_file * file);
void memory_pool_initialize(s_memory_pool * pool, char const * name, unsigned int size, memory_pool_relocation_function const relocation_function, c_allocation_interface * allocation);

/* ---------- globals */

/* ---------- public code */

#endif // __MEMORY_POOL_H__

