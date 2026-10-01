#pragma once
#ifndef __CACHE_FILE_BUILDER_STREAM_H__
#define __CACHE_FILE_BUILDER_STREAM_H__

/* ---------- headers */

/* ---------- constants */

/* ---------- definitions */

struct s_tag_block;
struct s_tag_struct_definition;
struct s_tag_interop_definition;
class c_tag_memory_attributes;
class c_cache_file_tracer;

// vtable order from ??_7c_tag_resource_cache_scratch_allocator@@6B@ (slot 4 is this class's own commit_tag_allocation)
class c_cache_file_scratch_allocator
{
public:
    virtual void * allocate_scratch(unsigned long size, long alignment_bits, c_tag_memory_attributes const & memory_attributes, void ** out_address) = 0; // 0x0
    virtual void discard_duplicate_scratch(void ** address, void * duplicate, void * original) = 0; // 0x4
    virtual void prepare_allocation_for_commitment(void * address) = 0; // 0x8
    virtual void track_allocation(void ** address) = 0; // 0xC
    virtual void commit_tag_allocation(void ** address, unsigned long * out_offset, s_tag_struct_definition const * struct_definition, unsigned long size, void const * data); // 0x10
    virtual void commit_allocation(void ** address, unsigned long * out_offset, void const * data) = 0; // 0x14
    virtual void commit_custom_allocation(void ** address, unsigned long * out_offset, void const * data, c_cache_file_tracer * tracer, long size, long memory_type) = 0; // 0x18 ($todo memory_type is e_tag_memory_type)
    virtual bool allow_allocation_aliasing(void * address) const = 0; // 0x1C
    virtual unsigned long get_aliasable_space_from_allocation(void * address) const = 0; // 0x20
    virtual bool byte_swap_destination(void) const = 0; // 0x24
    virtual void track_interop(void * address, s_tag_interop_definition const * interop_definition) = 0; // 0x28
    virtual unsigned long get_alignment_padding(void) const = 0; // 0x2C
    virtual void reset_allocation_checksum(void) = 0; // 0x30
};

// $todo remaining fields/size unknown
struct s_cache_file_builder_stream_context
{
    long unknown0; // 0x0
    c_cache_file_scratch_allocator * cache_file_allocator; // 0x4
};

/* ---------- prototypes */

void cache_file_builder_stream_tag_block_default(long tag_index, s_tag_block * block, s_cache_file_builder_stream_context const * context, void ** out_virtual_base_address);

/* ---------- globals */

/* ---------- public code */

#endif // __CACHE_FILE_BUILDER_STREAM_H__

