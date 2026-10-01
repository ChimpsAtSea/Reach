#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\foundation\\baselib\\datatypes\\memory_pool.cpp"
/* ---------- headers */

#include "foundation\baselib\datatypes\memory_pool.h"
#include "foundation\baselib\files\simple_file.h"
#include "foundation\baselib\memory\allocation_interface.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_macros.h"
#include "core\corelib\cseries\cseries_memory.h"
#include "core\corelib\cseries\cseries_events.h"

/* ---------- constants */

enum
{
    k_pool_signature = 'pool',
    k_block_header_signature = 'head',
};

/* ---------- definitions */

/* ---------- prototypes */

unsigned long system_milliseconds();

s_memory_pool_block_info * memory_pool_get_block(s_memory_pool const * pool, unsigned long handle);
void * memory_pool_address_from_handle(s_memory_pool const * pool, unsigned long handle);
unsigned long memory_pool_handle_from_address(s_memory_pool const * pool, void const * pointer);
s_memory_pool_block_info * memory_pool_compact_block(s_memory_pool * pool, s_memory_pool_block_info * block);
s_memory_pool_block_info const * memory_pool_get_block_const(s_memory_pool const * pool, unsigned long handle);
void const * memory_pool_block_get_end_of_block_const(s_memory_pool const * pool, s_memory_pool_block_info const * block);
unsigned long memory_pool_payload_handle_from_block_handle(unsigned long block_handle);
unsigned long memory_pool_block_handle_from_payload_handle(unsigned long payload_handle);
void const * memory_pool_payload_from_block_const(s_memory_pool_block_info const * block);
unsigned int memory_pool_block_compute_actual_size(s_memory_pool const * pool, unsigned int size);
unsigned int memory_pool_overhead_size(s_memory_pool const * pool);
unsigned int memory_pool_compute_available_inplace_size(unsigned int buffer_size);
s_memory_pool_block_info * memory_pool_block_new(s_memory_pool * pool, unsigned int actual_size, char const * file, long line);
s_memory_pool_block_info * memory_pool_block_new_from_end_of_pool(s_memory_pool * pool, unsigned int actual_size, char const * file, long line);
void * memory_pool_block_get_end_of_block(s_memory_pool const * pool, s_memory_pool_block_info * block);
s_memory_pool_block_info * memory_pool_block_new_from_front_of_pool(s_memory_pool * pool, unsigned int actual_size, char const * file, long line);
s_memory_pool_block_info * memory_pool_block_new_from_in_between_blocks(s_memory_pool * pool, unsigned int actual_size, char const * file, long line);
s_memory_pool_block_info * memory_pool_block_initialize(s_memory_pool * pool, void * base_address, unsigned int size, char const * file, long line, s_memory_pool_block_info * next_block, s_memory_pool_block_info * previous_block);
void * memory_pool_payload_from_block(s_memory_pool_block_info * block);
bool memory_pool_block_valid(s_memory_pool const * pool, s_memory_pool_block_info const * block);
void memory_block_notify_reference(s_memory_pool const * pool, s_memory_pool_block_info * block);
s_memory_pool_block_info * memory_pool_block_base_get_block(s_memory_pool const * pool, void * base);
void * memory_pool_block_get_base(s_memory_pool const * pool, s_memory_pool_block_info * block);
void const * memory_pool_block_get_base_const(s_memory_pool const * pool, s_memory_pool_block_info const * block);
s_memory_pool_block_header * memory_pool_block_get_header(s_memory_pool const * pool, s_memory_pool_block_info * block);
s_memory_pool_block_header const * memory_pool_block_get_header_const(s_memory_pool const * pool, s_memory_pool_block_info const * block);
s_memory_pool_block_info * memory_pool_payload_get_block(s_memory_pool * pool, unsigned long payload_handle);
s_memory_pool_block_info const * memory_pool_payload_get_block_const(s_memory_pool const * pool, unsigned long payload_handle);

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// ?memory_pool_new@@YAPAUs_memory_pool@@PBDIQ6AXJK@ZPAVc_allocation_interface@@0J@Z;
// void memory_pool_dispose(struct s_memory_pool *, char const *, long);
// ?memory_pool_inplace_new@@YAPAUs_memory_pool@@PBDPAXIQ6AXJK@Z@Z;
// void memory_pool_inplace_dispose(struct s_memory_pool *);
// unsigned int memory_pool_allocation_size(unsigned int);
// void memory_pool_clear(struct s_memory_pool *);
// void memory_pool_compact(struct s_memory_pool *);
// struct s_memory_pool_block_info * memory_pool_get_block(struct s_memory_pool const *, unsigned long);
// void * memory_pool_address_from_handle(struct s_memory_pool const *, unsigned long);
// void memory_pool_compact_incrementally(struct s_memory_pool *, long);
// unsigned long memory_pool_handle_from_address(struct s_memory_pool const *, void const *);
// struct s_memory_pool_block_info * memory_pool_compact_block(struct s_memory_pool *, struct s_memory_pool_block_info *);
// void * memory_pool_get_base_address(struct s_memory_pool const *);
// void memory_pool_verify(struct s_memory_pool const *);
// struct s_memory_pool_block_info const * memory_pool_get_block_const(struct s_memory_pool const *, unsigned long);
// ?memory_pool_set_relocation_function@@YAXPAUs_memory_pool@@Q6AXJK@Z@Z;
// void memory_pool_set_reference_tracking(struct s_memory_pool *, bool);
// void memory_pool_set_allow_block_pointers(struct s_memory_pool *, bool);
// void memory_pool_set_allocation_from_anywhere_in_pool(struct s_memory_pool *, bool);
// void memory_pool_set_allocation_from_anywhere_in_pool_on_failure(struct s_memory_pool *, bool);
// void memory_pool_set_allow_compact_on_allocate(struct s_memory_pool *, bool);
// void memory_pool_set_verification(struct s_memory_pool *, bool);
// long memory_pool_get_number_of_blocks(struct s_memory_pool const *);
// unsigned int memory_pool_get_free_size(struct s_memory_pool const *);
// unsigned int memory_pool_get_used_size(struct s_memory_pool const *);
// void const * memory_pool_block_get_end_of_block_const(struct s_memory_pool const *, struct s_memory_pool_block_info const *);
// unsigned int memory_pool_get_contiguous_free_size(struct s_memory_pool const *);
// void memory_pool_get_bounds(struct s_memory_pool const *, void **, void **);
// void * memory_pool_get_end_address(struct s_memory_pool const *);
// unsigned long memory_pool_block_allocate_handle_tracked(struct s_memory_pool *, long, unsigned int, char const *, long);
// unsigned long memory_pool_payload_handle_from_block_handle(unsigned long);
// unsigned long memory_pool_block_reallocate_handle_tracked(struct s_memory_pool *, unsigned long, unsigned int, char const *, long);
// unsigned long memory_pool_block_handle_from_payload_handle(unsigned long);
// void memory_pool_block_free_handle(struct s_memory_pool *, unsigned long);
// bool memory_pool_block_verify_handle(struct s_memory_pool const *, unsigned long);
// void * memory_pool_handle_get_address(struct s_memory_pool const *, unsigned long);
// unsigned int memory_pool_get_block_handle_size(struct s_memory_pool const *, unsigned long);
// bool memory_pool_block_allocate_tracked(struct s_memory_pool *, void **, unsigned int, char const *, long);
// bool memory_pool_block_reallocate_tracked(struct s_memory_pool *, void **, unsigned int, char const *, long);
// void memory_pool_block_free(struct s_memory_pool *, void **);
// bool memory_pool_block_verify(struct s_memory_pool *, void **);
// unsigned int memory_pool_get_block_size(struct s_memory_pool const *, void **);
// void memory_pool_dump_to_file(struct s_memory_pool const *, char const *);
// void memory_pool_dump_to_debugger(struct s_memory_pool const *, char const *);
// void memory_pool_dump(struct s_memory_pool const *, char const *, class c_simple_file *);
// void const * memory_pool_payload_from_block_const(struct s_memory_pool_block_info const *);
// ?memory_pool_initialize@@YAXPAUs_memory_pool@@PBDIQ6AXJK@ZPAVc_allocation_interface@@@Z;
// unsigned int memory_pool_block_compute_actual_size(struct s_memory_pool const *, unsigned int);
// unsigned int memory_pool_overhead_size(struct s_memory_pool const *);
// unsigned int memory_pool_compute_available_inplace_size(unsigned int);
// struct s_memory_pool_block_info * memory_pool_block_new(struct s_memory_pool *, unsigned int, char const *, long);
// struct s_memory_pool_block_info * memory_pool_block_new_from_end_of_pool(struct s_memory_pool *, unsigned int, char const *, long);
// void * memory_pool_block_get_end_of_block(struct s_memory_pool const *, struct s_memory_pool_block_info *);
// struct s_memory_pool_block_info * memory_pool_block_new_from_front_of_pool(struct s_memory_pool *, unsigned int, char const *, long);
// struct s_memory_pool_block_info * memory_pool_block_new_from_in_between_blocks(struct s_memory_pool *, unsigned int, char const *, long);
// struct s_memory_pool_block_info * memory_pool_block_initialize(struct s_memory_pool *, void *, unsigned int, char const *, long, struct s_memory_pool_block_info *, struct s_memory_pool_block_info *);
// void * memory_pool_payload_from_block(struct s_memory_pool_block_info *);
// bool memory_pool_block_valid(struct s_memory_pool const *, struct s_memory_pool_block_info const *);
// void memory_block_notify_reference(struct s_memory_pool const *, struct s_memory_pool_block_info *);
// struct s_memory_pool_block_info * memory_pool_block_base_get_block(struct s_memory_pool const *, void *);
// void * memory_pool_block_get_base(struct s_memory_pool const *, struct s_memory_pool_block_info *);
// void const * memory_pool_block_get_base_const(struct s_memory_pool const *, struct s_memory_pool_block_info const *);
// struct s_memory_pool_block_header * memory_pool_block_get_header(struct s_memory_pool const *, struct s_memory_pool_block_info *);
// struct s_memory_pool_block_header const * memory_pool_block_get_header_const(struct s_memory_pool const *, struct s_memory_pool_block_info const *);
// struct s_memory_pool_block_info * memory_pool_payload_get_block(struct s_memory_pool *, unsigned long);
// struct s_memory_pool_block_info const * memory_pool_payload_get_block_const(struct s_memory_pool const *, unsigned long);
// public: bool s_flags<enum e_memory_pool_flags, unsigned long, 8>::test(enum e_memory_pool_flags) const;
// public: void s_flags<enum e_memory_pool_flags, unsigned long, 8>::set(enum e_memory_pool_flags, bool);
// public: static bool s_flags<enum e_memory_pool_flags, unsigned long, 8>::valid_bit(enum e_memory_pool_flags);
// public: bool s_flags<enum e_memory_pool_flags, unsigned long, 8>::valid(void) const;
// private: static unsigned long s_flags<enum e_memory_pool_flags, unsigned long, 8>::flag_size_type(enum e_memory_pool_flags);
// private: static unsigned long s_flags<enum e_memory_pool_flags, unsigned long, 8>::make_mask_with_all_valid_bits_on_size_type(void);
// private: static unsigned long s_flags<enum e_memory_pool_flags, unsigned long, 8>::make_N_bit_mask_size_type(enum e_memory_pool_flags);

s_memory_pool * memory_pool_new(char const * name, unsigned int size, memory_pool_relocation_function const relocation_function, c_allocation_interface * allocation, char const * file, long line)
{
    mangled_ppc("?memory_pool_new@@YAPAUs_memory_pool@@PBDIQ6AXJK@ZPAVc_allocation_interface@@0J@Z");

    assert_tag_debug_untracked_jul_11_2011(237, name);
    assert_tag_debug_untracked_jul_11_2011(238, allocation);
    assert_tag_debug_untracked_jul_11_2011(239, size>0);

    s_memory_pool * pool = static_cast<s_memory_pool *>(allocation->allocate(memory_pool_allocation_size(size), file, line, "memory_pool", name, "pool"));
    if (pool)
    {
        memory_pool_initialize(pool, name, size, relocation_function, allocation);
    }

    return pool;
};

void memory_pool_dispose(s_memory_pool * pool, char const * file, long line)
{
    mangled_ppc("?memory_pool_dispose@@YAXPAUs_memory_pool@@PBDJ@Z");

    memory_pool_verify(pool);

    c_allocation_interface * allocation = pool->allocation;
    csmemset(pool, 0, sizeof(s_memory_pool));
    allocation->deallocate(pool, file, line);
};

s_memory_pool * memory_pool_inplace_new(char const * name, void * buffer, unsigned int buffer_size, memory_pool_relocation_function const relocation_function)
{
    mangled_ppc("?memory_pool_inplace_new@@YAPAUs_memory_pool@@PBDPAXIQ6AXJK@Z@Z");

    unsigned int size = memory_pool_compute_available_inplace_size(buffer_size);
    s_memory_pool * pool = NULL;
    if (size > 0)
    {
        pool = static_cast<s_memory_pool *>(buffer);
        memory_pool_initialize(pool, name, size, relocation_function, NULL);
    }
    else
    {
        event(_event_error, "memory_pool: can't allocate inplace (buffer %d@%p), requires at least %d bytes", buffer_size, buffer, memory_pool_allocation_size(0));
    }

    return pool;
};

void memory_pool_inplace_dispose(s_memory_pool * pool)
{
    mangled_ppc("?memory_pool_inplace_dispose@@YAXPAUs_memory_pool@@@Z");

    memory_pool_verify(pool);

    assert_tag_debug_untracked_jul_11_2011(292, memory_pool_get_number_of_blocks(pool)==0);
    assert_tag_debug_untracked_jul_11_2011(293, pool->free_size==pool->size);

    csmemset(pool, 0, sizeof(s_memory_pool));
};

unsigned int memory_pool_allocation_size(unsigned int size)
{
    mangled_ppc("?memory_pool_allocation_size@@YAII@Z");

    return size + sizeof(s_memory_pool) + sizeof(s_memory_pool_block_info);
};

void memory_pool_clear(s_memory_pool * pool)
{
    mangled_ppc("?memory_pool_clear@@YAXPAUs_memory_pool@@@Z");

    memory_pool_verify(pool);

    pool->first_block_handle = k_memory_pool_null_handle;
    pool->last_block_handle = k_memory_pool_null_handle;
    pool->incremental_compact_block_handle = k_memory_pool_null_handle;
    pool->free_size = pool->size;
};

void memory_pool_compact(s_memory_pool * pool)
{
    mangled_ppc("?memory_pool_compact@@YAXPAUs_memory_pool@@@Z");

    dassert_tag_debug_untracked_jul_11_2011(318, !pool->flags.test(_memory_pool_doesnt_track_references_bit), "can't compact memory pools unless they use tracked references");

    memory_pool_verify(pool);

    unsigned long block_handle = pool->first_block_handle;
    while (block_handle != k_memory_pool_null_handle)
    {
        s_memory_pool_block_info * block = memory_pool_get_block(pool, block_handle);
        block = memory_pool_compact_block(pool, block);
        block_handle = block->next_block_handle;
    }

    pool->incremental_compact_block_handle = k_memory_pool_null_handle;

    memory_pool_verify(pool);
};

s_memory_pool_block_info * memory_pool_get_block(s_memory_pool const * pool, unsigned long handle)
{
    mangled_ppc("?memory_pool_get_block@@YAPAUs_memory_pool_block_info@@PBUs_memory_pool@@K@Z");

    return static_cast<s_memory_pool_block_info *>(memory_pool_address_from_handle(pool, handle));
};

void * memory_pool_address_from_handle(s_memory_pool const * pool, unsigned long handle)
{
    mangled_ppc("?memory_pool_address_from_handle@@YAPAXPBUs_memory_pool@@K@Z");

    assert_tag_debug_untracked_jul_11_2011(153, handle!=k_memory_pool_null_handle);
    assert_tag_debug_untracked_jul_11_2011(154, handle>=sizeof(*pool));
    assert_tag_debug_untracked_jul_11_2011(155, handle<=memory_pool_allocation_size(pool->size));

    return const_cast<void *>(offset_pointer(static_cast<void const *>(pool), handle));
};

void memory_pool_compact_incrementally(s_memory_pool * pool, long block_count)
{
    mangled_ppc("?memory_pool_compact_incrementally@@YAXPAUs_memory_pool@@J@Z");

    for (long block_index = 0; block_index < block_count; block_index++)
    {
        unsigned long block_handle;
        if (pool->incremental_compact_block_handle == k_memory_pool_null_handle)
        {
            block_handle = pool->first_block_handle;
        }
        else
        {
            block_handle = memory_pool_get_block(pool, pool->incremental_compact_block_handle)->next_block_handle;
        }

        if (block_handle != k_memory_pool_null_handle)
        {
            s_memory_pool_block_info * block = memory_pool_get_block(pool, block_handle);
            block_handle = memory_pool_handle_from_address(pool, memory_pool_compact_block(pool, block));
            pool->incremental_compact_block_handle = block_handle;
        }
        else
        {
            pool->incremental_compact_block_handle = k_memory_pool_null_handle;
            break;
        }
    }

    memory_pool_verify(pool);
};

unsigned long memory_pool_handle_from_address(s_memory_pool const * pool, void const * pointer)
{
    mangled_ppc("?memory_pool_handle_from_address@@YAKPBUs_memory_pool@@PBX@Z");

    assert_tag_debug_untracked_jul_11_2011(143, pointer);
    assert_tag_debug_untracked_jul_11_2011(144, pointer>=offset_pointer(pool, sizeof(*pool)));
    assert_tag_debug_untracked_jul_11_2011(145, pointer<offset_pointer(pool, sizeof(*pool)+pool->size));

    return pointer_distance(pool, pointer);
};

s_memory_pool_block_info * memory_pool_compact_block(s_memory_pool * pool, s_memory_pool_block_info * block)
{
    mangled_ppc("?memory_pool_compact_block@@YAPAUs_memory_pool_block_info@@PAUs_memory_pool@@PAU1@@Z");

    void * destination_address;
    void * base = memory_pool_block_get_base(pool, block);
    s_memory_pool_block_info * previous_block;

    pool->flags.set(_memory_pool_compacting_bit, true);

    dassert_tag_debug_untracked_jul_11_2011(385, !pool->flags.test(_memory_pool_doesnt_track_references_bit), "can't compact memory pools unless they use tracked references");

    if (block->previous_block_handle != k_memory_pool_null_handle)
    {
        previous_block = memory_pool_get_block(pool, block->previous_block_handle);
        void * previous_base = memory_pool_block_get_base(pool, previous_block);
        destination_address = offset_pointer(previous_base, previous_block->total_size);
    }
    else
    {
        previous_block = NULL;
        destination_address = memory_pool_get_base_address(pool);
    }

    assert_tag_debug_untracked_jul_11_2011(401, memory_pool_block_valid(pool, block));

    if (base > destination_address)
    {
        csmemmove(destination_address, base, block->total_size);
        base = destination_address;
        block = memory_pool_block_base_get_block(pool, base);
        memory_block_notify_reference(pool, block);

        if (previous_block)
        {
            previous_block->next_block_handle = memory_pool_handle_from_address(pool, block);
        }
        else
        {
            pool->first_block_handle = memory_pool_handle_from_address(pool, block);
        }

        if (block->next_block_handle != k_memory_pool_null_handle)
        {
            s_memory_pool_block_info * next_block = memory_pool_get_block(pool, block->next_block_handle);
            next_block->previous_block_handle = memory_pool_handle_from_address(pool, block);
        }
        else
        {
            pool->last_block_handle = memory_pool_handle_from_address(pool, block);
        }
    }

    pool->flags.set(_memory_pool_compacting_bit, false);

    assert_tag_debug_untracked_jul_11_2011(441, memory_pool_block_valid(pool, block));

    return block;
};

void * memory_pool_get_base_address(s_memory_pool const * pool)
{
    mangled_ppc("?memory_pool_get_base_address@@YAPAXPBUs_memory_pool@@@Z");

    return memory_pool_address_from_handle(pool, pool->base_handle);
};

void memory_pool_verify(s_memory_pool const * pool)
{
    mangled_ppc("?memory_pool_verify@@YAXPBUs_memory_pool@@@Z");

    assert_tag_debug_untracked_jul_11_2011(450, pool!=NULL);
    assert_tag_debug_untracked_jul_11_2011(451, pool->signature==k_pool_signature);
    assert_tag_debug_untracked_jul_11_2011(452, pool->size>=0);

    if (!pool->flags.test(_memory_pool_no_verification_bit) && !pool->flags.test(_memory_pool_compacting_bit))
    {
        unsigned long current_block_handle = pool->first_block_handle;
        s_memory_pool_block_info const * previous_block = NULL;
        long max_blocks = pool->size / memory_pool_overhead_size(pool);
        long num_blocks = 0;
        bool found_incremental_compact_block_handle = false;
        void const * expected_base = memory_pool_get_base_address(pool);

        while (current_block_handle != k_memory_pool_null_handle)
        {
            s_memory_pool_block_info const * block = memory_pool_get_block_const(pool, current_block_handle);

            assert_tag_debug_untracked_jul_11_2011(472, memory_pool_block_valid(pool, block));
            assert_tag_debug_untracked_jul_11_2011(474, (block->previous_block_handle==k_memory_pool_null_handle && previous_block==NULL) || (block->previous_block_handle!=k_memory_pool_null_handle && memory_pool_get_block(pool, block->previous_block_handle)==previous_block));
            assert_tag_debug_untracked_jul_11_2011(475, block->next_block_handle || memory_pool_get_block(pool, pool->last_block_handle)==block);

            if (current_block_handle == pool->incremental_compact_block_handle)
            {
                found_incremental_compact_block_handle = true;
            }

            num_blocks++;
            dassert_tag_debug_untracked_jul_11_2011(483, num_blocks < max_blocks, "infinite loop in memory pool");

            previous_block = block;
            current_block_handle = block->next_block_handle;
            expected_base = offset_pointer(memory_pool_block_get_base_const(pool, previous_block), previous_block->total_size);
        }

        assert_tag_debug_untracked_jul_11_2011(490, pool->incremental_compact_block_handle==k_memory_pool_null_handle || found_incremental_compact_block_handle);
    }
};

s_memory_pool_block_info const * memory_pool_get_block_const(s_memory_pool const * pool, unsigned long handle)
{
    mangled_ppc("?memory_pool_get_block_const@@YAPBUs_memory_pool_block_info@@PBUs_memory_pool@@K@Z");

    return static_cast<s_memory_pool_block_info const *>(memory_pool_address_from_handle(pool, handle));
};

void memory_pool_set_relocation_function(s_memory_pool * pool, memory_pool_relocation_function const relocation_function)
{
    mangled_ppc("?memory_pool_set_relocation_function@@YAXPAUs_memory_pool@@Q6AXJK@Z@Z");

    assert_tag_debug_untracked_jul_11_2011(499, pool);
    dassert_tag_debug_untracked_jul_11_2011(500, relocation_function == NULL || !pool->flags.test(_memory_pool_doesnt_track_references_bit), "this pool does not track references so it can't use a relocation function");

    pool->relocation_function = relocation_function;
};

void memory_pool_set_reference_tracking(s_memory_pool * pool, bool track_references)
{
    mangled_ppc("?memory_pool_set_reference_tracking@@YAXPAUs_memory_pool@@_N@Z");

    assert_tag_debug_untracked_jul_11_2011(508, pool);
    dassert_tag_debug_untracked_jul_11_2011(509, pool->first_block_handle == k_memory_pool_null_handle, "can't change memory pool behavior after allocations commence");
    dassert_tag_debug_untracked_jul_11_2011(510, track_references || pool->relocation_function == NULL, "pools with a relocation function must track references");

    pool->flags.set(_memory_pool_doesnt_track_references_bit, !track_references);
};

void memory_pool_set_allow_block_pointers(s_memory_pool * pool, bool allow_block_pointers)
{
    mangled_ppc("?memory_pool_set_allow_block_pointers@@YAXPAUs_memory_pool@@_N@Z");

    assert_tag_debug_untracked_jul_11_2011(518, pool);
    dassert_tag_debug_untracked_jul_11_2011(519, pool->first_block_handle == k_memory_pool_null_handle, "can't change memory pool behavior after allocations commence");

    pool->flags.set(_memory_pool_no_block_pointers_bit, !allow_block_pointers);
};

void memory_pool_set_allocation_from_anywhere_in_pool(s_memory_pool * pool, bool allocate_from_anywhere)
{
    mangled_ppc("?memory_pool_set_allocation_from_anywhere_in_pool@@YAXPAUs_memory_pool@@_N@Z");

    assert_tag_debug_untracked_jul_11_2011(527, pool);

    pool->flags.set(_memory_pool_allocate_from_anywhere_in_pool_bit, allocate_from_anywhere);
};

void memory_pool_set_allocation_from_anywhere_in_pool_on_failure(s_memory_pool * pool, bool allocate_from_anywhere)
{
    mangled_ppc("?memory_pool_set_allocation_from_anywhere_in_pool_on_failure@@YAXPAUs_memory_pool@@_N@Z");

    assert_tag_debug_untracked_jul_11_2011(536, pool);

    pool->flags.set(_memory_pool_allocate_from_anywhere_in_pool_on_failure_bit, allocate_from_anywhere);
};

void memory_pool_set_allow_compact_on_allocate(s_memory_pool * pool, bool allow_compact)
{
    mangled_ppc("?memory_pool_set_allow_compact_on_allocate@@YAXPAUs_memory_pool@@_N@Z");

    assert_tag_debug_untracked_jul_11_2011(544, pool);

    pool->flags.set(_memory_pool_compact_on_allocate_bit, allow_compact);
};

void memory_pool_set_verification(s_memory_pool * pool, bool use_verification)
{
    mangled_ppc("?memory_pool_set_verification@@YAXPAUs_memory_pool@@_N@Z");

    assert_tag_debug_untracked_jul_11_2011(552, pool);

    pool->flags.set(_memory_pool_no_verification_bit, !use_verification);
};

long memory_pool_get_number_of_blocks(s_memory_pool const * pool)
{
    mangled_ppc("?memory_pool_get_number_of_blocks@@YAJPBUs_memory_pool@@@Z");

    long block_count = 0;

    assert_tag_debug_untracked_jul_11_2011(561, pool);

    for (unsigned long block_handle = pool->first_block_handle; block_handle != k_memory_pool_null_handle; block_handle = memory_pool_get_block(pool, block_handle)->next_block_handle)
    {
        block_count++;
    }

    return block_count;
};

unsigned int memory_pool_get_free_size(s_memory_pool const * pool)
{
    mangled_ppc("?memory_pool_get_free_size@@YAIPBUs_memory_pool@@@Z");

    assert_tag_debug_untracked_jul_11_2011(573, pool);

    return pool->free_size;
};

unsigned int memory_pool_get_used_size(s_memory_pool const * pool)
{
    mangled_ppc("?memory_pool_get_used_size@@YAIPBUs_memory_pool@@@Z");

    unsigned int used_size = 0;

    assert_tag_debug_untracked_jul_11_2011(582, pool);

    if (pool->last_block_handle != k_memory_pool_null_handle)
    {
        s_memory_pool_block_info * last_block = memory_pool_get_block(pool, pool->last_block_handle);
        void const * end_of_block = memory_pool_block_get_end_of_block_const(pool, last_block);
        long distance = pointer_distance(memory_pool_get_base_address(pool), end_of_block);

        assert_tag_debug_untracked_jul_11_2011(589, distance>=0 && distance<=static_cast<intptr>(pool->size));

        used_size = distance;
    }

    return used_size;
};

void const * memory_pool_block_get_end_of_block_const(s_memory_pool const * pool, s_memory_pool_block_info const * block)
{
    mangled_ppc("?memory_pool_block_get_end_of_block_const@@YAPBXPBUs_memory_pool@@PBUs_memory_pool_block_info@@@Z");

    return offset_pointer(memory_pool_block_get_base_const(pool, block), block->total_size);
};

unsigned int memory_pool_get_contiguous_free_size(s_memory_pool const * pool)
{
    mangled_ppc("?memory_pool_get_contiguous_free_size@@YAIPBUs_memory_pool@@@Z");

    assert_tag_debug_untracked_jul_11_2011(599, pool);

    return pool->size - memory_pool_get_used_size(pool);
};

void memory_pool_get_bounds(s_memory_pool const * pool, void ** out_low_bound, void ** out_high_bound)
{
    mangled_ppc("?memory_pool_get_bounds@@YAXPBUs_memory_pool@@PAPAX1@Z");

    assert_tag_debug_untracked_jul_11_2011(608, pool);
    assert_tag_debug_untracked_jul_11_2011(609, out_low_bound);
    assert_tag_debug_untracked_jul_11_2011(610, out_high_bound);

    *out_low_bound = memory_pool_get_base_address(pool);
    *out_high_bound = memory_pool_get_end_address(pool);
};

void * memory_pool_get_end_address(s_memory_pool const * pool)
{
    mangled_ppc("?memory_pool_get_end_address@@YAPAXPBUs_memory_pool@@@Z");

    return memory_pool_address_from_handle(pool, pool->base_handle + pool->size);
};

unsigned long memory_pool_block_allocate_handle_tracked(s_memory_pool * pool, long reference, unsigned int size, char const * file, long line)
{
    mangled_ppc("?memory_pool_block_allocate_handle_tracked@@YAKPAUs_memory_pool@@JIPBDJ@Z");

    unsigned int actual_size = memory_pool_block_compute_actual_size(pool, size);
    unsigned long payload_handle = k_memory_pool_null_handle;

    assert_tag_debug_untracked_jul_11_2011(625, pool);
    assert_tag_debug_untracked_jul_11_2011(626, size>0);

    memory_pool_verify(pool);

    s_memory_pool_block_info * new_block = memory_pool_block_new(pool, actual_size, file, line);
    if (!new_block && pool->flags.test(_memory_pool_compact_on_allocate_bit))
    {
        memory_pool_compact(pool);
        new_block = memory_pool_block_new(pool, actual_size, file, line);
    }

    if (new_block)
    {
        assert_tag_debug_untracked_jul_11_2011(645, memory_pool_block_valid(pool, new_block));

        new_block->reference = reference;
        pool->free_size -= new_block->total_size;

        assert_tag_debug_untracked_jul_11_2011(652, pool->free_size>=0);

        unsigned long block_handle = memory_pool_handle_from_address(pool, new_block);
        payload_handle = memory_pool_payload_handle_from_block_handle(block_handle);
    }

    memory_pool_verify(pool);

    return payload_handle;
};

unsigned long memory_pool_payload_handle_from_block_handle(unsigned long block_handle)
{
    mangled_ppc("?memory_pool_payload_handle_from_block_handle@@YAKK@Z");

    return block_handle + sizeof(s_memory_pool_block_info);
};

unsigned long memory_pool_block_reallocate_handle_tracked(s_memory_pool * pool, unsigned long payload_handle, unsigned int new_size, char const * file, long line)
{
    mangled_ppc("?memory_pool_block_reallocate_handle_tracked@@YAKPAUs_memory_pool@@KIPBDJ@Z");

    unsigned int actual_new_size = memory_pool_block_compute_actual_size(pool, new_size);
    s_memory_pool_block_info * block = memory_pool_get_block(pool, memory_pool_block_handle_from_payload_handle(payload_handle));
    unsigned long block_handle = memory_pool_block_handle_from_payload_handle(payload_handle);
    unsigned long result = k_memory_pool_null_handle;

    if (block_handle == pool->incremental_compact_block_handle)
    {
        assert_tag_debug_untracked_jul_11_2011(676, pool->incremental_compact_block_handle!=k_memory_pool_null_handle);

        pool->incremental_compact_block_handle = block->previous_block_handle;
    }

    memory_pool_verify(pool);

    assert_tag_debug_untracked_jul_11_2011(683, new_size>=0);
    assert_tag_debug_untracked_jul_11_2011(684, memory_pool_block_valid(pool, block));

    if (actual_new_size == block->total_size)
    {
        result = payload_handle;
    }
    else if (new_size == 0)
    {
        memory_pool_block_free_handle(pool, payload_handle);
    }
    else
    {
        void * end_address;
        if (block->next_block_handle != k_memory_pool_null_handle)
        {
            end_address = memory_pool_get_block(pool, block->next_block_handle);
        }
        else
        {
            end_address = memory_pool_get_end_address(pool);
        }

        if (offset_pointer(block, actual_new_size) <= end_address)
        {
            pool->free_size += block->total_size - actual_new_size;

            assert_tag_debug_untracked_jul_11_2011(715, pool->free_size>=0 && pool->free_size<=pool->size);

            block->total_size = actual_new_size;

            s_memory_pool_block_header * header = memory_pool_block_get_header(pool, block);
            if (header)
            {
                header->file = file;
                header->line = line;
                header->timestamp = system_milliseconds();
            }

            assert_tag_debug_untracked_jul_11_2011(736, memory_pool_block_valid(pool, block));

            result = payload_handle;
        }

        if (result == k_memory_pool_null_handle)
        {
            unsigned long allocated_handle = memory_pool_block_allocate_handle_tracked(pool, block->reference, new_size, file, line);
            if (allocated_handle != k_memory_pool_null_handle)
            {
                void * new_buffer = memory_pool_address_from_handle(pool, allocated_handle);
                void * old_buffer = memory_pool_address_from_handle(pool, payload_handle);

                assert_tag_debug_untracked_jul_11_2011(752, actual_new_size>block->total_size);

                csmemcpy(new_buffer, old_buffer, block->total_size - memory_pool_overhead_size(pool));
                memory_pool_block_free_handle(pool, payload_handle);

                s_memory_pool_block_info * new_block = memory_pool_payload_get_block(pool, allocated_handle);
                memory_block_notify_reference(pool, new_block);

                assert_tag_debug_untracked_jul_11_2011(764, memory_pool_block_valid(pool, new_block));

                result = allocated_handle;
            }
        }
    }

    memory_pool_verify(pool);

    return result;
};

unsigned long memory_pool_block_handle_from_payload_handle(unsigned long payload_handle)
{
    mangled_ppc("?memory_pool_block_handle_from_payload_handle@@YAKK@Z");

    return payload_handle - sizeof(s_memory_pool_block_info);
};

void memory_pool_block_free_handle(s_memory_pool * pool, unsigned long payload_handle)
{
    mangled_ppc("?memory_pool_block_free_handle@@YAXPAUs_memory_pool@@K@Z");

    s_memory_pool_block_info * block = memory_pool_payload_get_block(pool, payload_handle);
    unsigned long block_handle = memory_pool_block_handle_from_payload_handle(payload_handle);

    if (pool->incremental_compact_block_handle == block_handle)
    {
        assert_tag_debug_untracked_jul_11_2011(786, pool->incremental_compact_block_handle!=k_memory_pool_null_handle);

        pool->incremental_compact_block_handle = block->previous_block_handle;
    }

    assert_tag_debug_untracked_jul_11_2011(791, memory_pool_block_valid(pool, block));

    memory_pool_verify(pool);

    pool->free_size += block->total_size;

    assert_tag_debug_untracked_jul_11_2011(796, pool->free_size<=pool->size);

    if (block->previous_block_handle != k_memory_pool_null_handle)
    {
        memory_pool_get_block(pool, block->previous_block_handle)->next_block_handle = block->next_block_handle;
    }
    else
    {
        pool->first_block_handle = block->next_block_handle;
    }

    if (block->next_block_handle != k_memory_pool_null_handle)
    {
        memory_pool_get_block(pool, block->next_block_handle)->previous_block_handle = block->previous_block_handle;
    }
    else
    {
        pool->last_block_handle = block->previous_block_handle;
    }

    csmemset(memory_pool_block_get_base(pool, block), 0xDD, block->total_size);

    memory_pool_verify(pool);
};

bool memory_pool_block_verify_handle(s_memory_pool const * pool, unsigned long payload_handle)
{
    mangled_ppc("?memory_pool_block_verify_handle@@YA_NPBUs_memory_pool@@K@Z");

    bool valid = true;
    s_memory_pool_block_info const * block = memory_pool_payload_get_block_const(pool, payload_handle);
    valid = memory_pool_block_valid(pool, block);

    return valid;
};

void * memory_pool_handle_get_address(s_memory_pool const * pool, unsigned long payload_handle)
{
    mangled_ppc("?memory_pool_handle_get_address@@YAPAXPBUs_memory_pool@@K@Z");

    void * address = NULL;

    if (payload_handle != k_memory_pool_null_handle)
    {
        assert_tag_debug_untracked_jul_11_2011(849, memory_pool_block_valid(pool, memory_pool_payload_get_block_const(pool, payload_handle)));

        address = memory_pool_address_from_handle(pool, payload_handle);
    }

    return address;
};

unsigned int memory_pool_get_block_handle_size(s_memory_pool const * pool, unsigned long payload_handle)
{
    mangled_ppc("?memory_pool_get_block_handle_size@@YAIPBUs_memory_pool@@K@Z");

    s_memory_pool_block_info const * block = memory_pool_payload_get_block_const(pool, payload_handle);
    unsigned int overhead_size = memory_pool_overhead_size(pool);
    unsigned int payload_size = block->total_size - overhead_size;

    memory_pool_verify(pool);

    assert_tag_debug_untracked_jul_11_2011(865, memory_pool_block_valid(pool, block));
    assert_tag_debug_untracked_jul_11_2011(867, payload_size>0 && payload_size<=pool->size);

    return payload_size;
};

bool memory_pool_block_allocate_tracked(s_memory_pool * pool, void ** pointer, unsigned int size, char const * file, long line)
{
    mangled_ppc("?memory_pool_block_allocate_tracked@@YA_NPAUs_memory_pool@@PAPAXIPBDJ@Z");

    bool success = false;

    assert_tag_debug_untracked_jul_11_2011(880, pool);
    assert_tag_debug_untracked_jul_11_2011(881, pointer);
    assert_tag_debug_untracked_jul_11_2011(882, size>0);
    dassert_tag_debug_untracked_jul_11_2011(883, !pool->flags.test(_memory_pool_no_block_pointers_bit), "can't use this method on this pool, use handle based allocation");

    unsigned long new_handle = memory_pool_block_allocate_handle_tracked(pool, 0, size, file, line);
    if (new_handle != k_memory_pool_null_handle)
    {
        *pointer = memory_pool_handle_get_address(pool, new_handle);
        success = true;
    }

    return success;
};

bool memory_pool_block_reallocate_tracked(s_memory_pool * pool, void ** pointer, unsigned int new_size, char const * file, long line)
{
    mangled_ppc("?memory_pool_block_reallocate_tracked@@YA_NPAUs_memory_pool@@PAPAXIPBDJ@Z");

    bool success = false;

    assert_tag_debug_untracked_jul_11_2011(905, pool);
    assert_tag_debug_untracked_jul_11_2011(906, pointer);
    assert_tag_debug_untracked_jul_11_2011(907, *pointer);
    dassert_tag_debug_untracked_jul_11_2011(908, !pool->flags.test(_memory_pool_no_block_pointers_bit), "can't use this method on this pool, use handle based allocation");

    unsigned long current_handle = memory_pool_handle_from_address(pool, *pointer);
    unsigned long new_handle = memory_pool_block_reallocate_handle_tracked(pool, current_handle, new_size, file, line);
    if (new_handle != k_memory_pool_null_handle)
    {
        *pointer = memory_pool_handle_get_address(pool, new_handle);
        success = true;
    }

    return success;
};

void memory_pool_block_free(s_memory_pool * pool, void ** pointer)
{
    mangled_ppc("?memory_pool_block_free@@YAXPAUs_memory_pool@@PAPAX@Z");

    assert_tag_debug_untracked_jul_11_2011(927, pool);
    assert_tag_debug_untracked_jul_11_2011(928, pointer);
    assert_tag_debug_untracked_jul_11_2011(929, *pointer);

    unsigned long payload_handle = memory_pool_handle_from_address(pool, *pointer);
    memory_pool_block_free_handle(pool, payload_handle);
};

bool memory_pool_block_verify(s_memory_pool * pool, void ** pointer)
{
    mangled_ppc("?memory_pool_block_verify@@YA_NPAUs_memory_pool@@PAPAX@Z");

    assert_tag_debug_untracked_jul_11_2011(941, pool);
    assert_tag_debug_untracked_jul_11_2011(942, pointer);
    assert_tag_debug_untracked_jul_11_2011(943, *pointer);

    unsigned long payload_handle = memory_pool_handle_from_address(pool, *pointer);
    return memory_pool_block_verify_handle(pool, payload_handle);
};

unsigned int memory_pool_get_block_size(s_memory_pool const * pool, void ** pointer)
{
    mangled_ppc("?memory_pool_get_block_size@@YAIPBUs_memory_pool@@PAPAX@Z");

    assert_tag_debug_untracked_jul_11_2011(955, pool);
    assert_tag_debug_untracked_jul_11_2011(956, pointer);
    assert_tag_debug_untracked_jul_11_2011(957, *pointer);

    unsigned long payload_handle = memory_pool_handle_from_address(pool, *pointer);
    return memory_pool_get_block_handle_size(pool, payload_handle);
};

void memory_pool_dump_to_file(s_memory_pool const * pool, char const * dump_prefix)
{
    mangled_ppc("?memory_pool_dump_to_file@@YAXPBUs_memory_pool@@PBD@Z");

    assert_tag_debug_untracked_jul_11_2011(968, pool);
    assert_tag_debug_untracked_jul_11_2011(969, dump_prefix);

    if (pool->flags.test(_memory_pool_initialized_bit))
    {
        c_simple_file file;
        s_static_string<256> filename;

        filename.print("%s_memory_dump.txt", dump_prefix);
        file.set_debug_filename(filename);
        if (file.open(FLAG(_simple_file_open_write_bit)))
        {
            memory_pool_dump(pool, dump_prefix, &file);
        }
    }
    else
    {
        event(_event_warning, "memory_pool: %s does not have tracked headers, cannot dump to file", pool->name.get_string());
    }
};

void memory_pool_dump_to_debugger(s_memory_pool const * pool, char const * dump_prefix)
{
    mangled_ppc("?memory_pool_dump_to_debugger@@YAXPBUs_memory_pool@@PBD@Z");
};

void memory_pool_dump(s_memory_pool const * pool, char const * dump_prefix, c_simple_file * file)
{
    mangled_ppc("?memory_pool_dump@@YAXPBUs_memory_pool@@PBDPAVc_simple_file@@@Z");

    s_memory_pool_block_info const * last_oldest_block = NULL;
    s_memory_pool_block_header const * last_header = NULL;
    long block_count = 0;
    unsigned int total_size = 0;
    unsigned int min_block_size = 0xFFFFFFFF;
    unsigned int max_size = 0;
    unsigned int average;

    file->printf("MEMORY POOL DUMP FOR '%s'\n", dump_prefix);
    file->printf("=========================\n");
    file->printf("\n\n");
    file->printf("pool '%s' size %d free %d\n", pool->name.get_string(), pool->size, pool->free_size);
    file->printf("\n");

    while (true)
    {
        unsigned long block_handle = pool->first_block_handle;
        s_memory_pool_block_info const * next_oldest_block = NULL;
        unsigned long oldest_timestamp = 0xFFFFFFFF;

        while (block_handle != k_memory_pool_null_handle)
        {
            s_memory_pool_block_info const * block = memory_pool_get_block(pool, block_handle);
            s_memory_pool_block_header const * header = memory_pool_block_get_header_const(pool, block);

            if ((!last_oldest_block || header->timestamp > last_header->timestamp || (header->timestamp == last_header->timestamp && block > last_oldest_block)) && header->timestamp < oldest_timestamp)
            {
                next_oldest_block = block;
                oldest_timestamp = header->timestamp;
            }

            block_handle = block->next_block_handle;
        }

        if (next_oldest_block)
        {
            unsigned int size = next_oldest_block->total_size - memory_pool_overhead_size(pool);
            char const * file_name = "NULL";
            s_memory_pool_block_header const * block_header = memory_pool_block_get_header_const(pool, next_oldest_block);
            void const * payload = memory_pool_payload_from_block_const(next_oldest_block);

            if (block_header->file)
            {
                char const * separator = strrchr_debug(block_header->file, '\\');
                file_name = separator ? separator + 1 : block_header->file;
            }

            file->printf("block@0x%08p size: %7d time: %10d from: %s(%d)\n", payload, size, block_header->timestamp, file_name, block_header->line);

            block_count++;
            total_size += size;
            min_block_size = int_min(min_block_size, size);
            max_size = int_max(max_size, size);
            last_oldest_block = next_oldest_block;
            last_header = block_header;
        }
        else
        {
            break;
        }
    }

    {
        long test_block_count = 0;
        for (unsigned long block_handle = pool->first_block_handle; block_handle != k_memory_pool_null_handle; block_handle = memory_pool_get_block(pool, block_handle)->next_block_handle)
        {
            test_block_count++;
        }

        assert_tag_debug_untracked_jul_11_2011(1105, block_count==test_block_count);
    }

    average = block_count == 0 ? 0 : total_size / block_count;

    file->printf("\n");
    file->printf("%d blocks %d bytes (min/avg/max %d/%d/%d)\n", block_count, total_size, min_block_size, average, max_size);
};

void const * memory_pool_payload_from_block_const(s_memory_pool_block_info const * block)
{
    mangled_ppc("?memory_pool_payload_from_block_const@@YAPBXPBUs_memory_pool_block_info@@@Z");

    return offset_pointer(block, sizeof(s_memory_pool_block_info));
};

void memory_pool_initialize(s_memory_pool * pool, char const * name, unsigned int size, memory_pool_relocation_function const relocation_function, c_allocation_interface * allocation)
{
    mangled_ppc("?memory_pool_initialize@@YAXPAUs_memory_pool@@PBDIQ6AXJK@ZPAVc_allocation_interface@@@Z");

    csmemset(pool, 0, sizeof(s_memory_pool));

    pool->signature = k_pool_signature;
    pool->name.set(name);
    pool->allocation = allocation;
    pool->relocation_function = relocation_function;
    pool->size = size;
    pool->free_size = size;
    pool->first_block_handle = k_memory_pool_null_handle;
    pool->last_block_handle = k_memory_pool_null_handle;
    pool->incremental_compact_block_handle = k_memory_pool_null_handle;

    void * base_address = offset_pointer(pool, sizeof(s_memory_pool));
    void * aligned_base_address = align_pointer(base_address, 4);

    assert_tag_debug_untracked_jul_11_2011(1143, offset_pointer(aligned_base_address, size)<=offset_pointer(pool, memory_pool_allocation_size(size)));

    pool->base_handle = memory_pool_handle_from_address(pool, aligned_base_address);
    pool->flags.set(_memory_pool_initialized_bit, true);

    csmemset(memory_pool_get_base_address(pool), 0xFE, pool->size);
};

unsigned int memory_pool_block_compute_actual_size(s_memory_pool const * pool, unsigned int size)
{
    mangled_ppc("?memory_pool_block_compute_actual_size@@YAIPBUs_memory_pool@@I@Z");

    unsigned int actual_size = size + memory_pool_overhead_size(pool);
    actual_size = (actual_size + 15) & ~15;

    return actual_size;
};

unsigned int memory_pool_overhead_size(s_memory_pool const * pool)
{
    mangled_ppc("?memory_pool_overhead_size@@YAIPBUs_memory_pool@@@Z");

    unsigned int overhead_size = sizeof(s_memory_pool_block_info);
    if (pool->flags.test(_memory_pool_initialized_bit))
    {
        overhead_size += sizeof(s_memory_pool_block_header);
    }

    return overhead_size;
};

unsigned int memory_pool_compute_available_inplace_size(unsigned int buffer_size)
{
    mangled_ppc("?memory_pool_compute_available_inplace_size@@YAII@Z");

    unsigned int available_size = 0;
    unsigned int overhead_size = memory_pool_allocation_size(0);
    if (buffer_size > overhead_size)
    {
        available_size = buffer_size - overhead_size;
    }

    return available_size;
};

s_memory_pool_block_info * memory_pool_block_new(s_memory_pool * pool, unsigned int actual_size, char const * file, long line)
{
    mangled_ppc("?memory_pool_block_new@@YAPAUs_memory_pool_block_info@@PAUs_memory_pool@@IPBDJ@Z");

    s_memory_pool_block_info * new_block = NULL;

    if (pool->flags.test(_memory_pool_allocate_from_anywhere_in_pool_bit))
    {
        new_block = memory_pool_block_new_from_in_between_blocks(pool, actual_size, file, line);
        if (!new_block)
        {
            new_block = memory_pool_block_new_from_front_of_pool(pool, actual_size, file, line);
            if (!new_block)
            {
                new_block = memory_pool_block_new_from_end_of_pool(pool, actual_size, file, line);
            }
        }
    }
    else
    {
        new_block = memory_pool_block_new_from_end_of_pool(pool, actual_size, file, line);
        if (!new_block && pool->flags.test(_memory_pool_allocate_from_anywhere_in_pool_on_failure_bit))
        {
            new_block = memory_pool_block_new_from_in_between_blocks(pool, actual_size, file, line);
            if (!new_block)
            {
                new_block = memory_pool_block_new_from_front_of_pool(pool, actual_size, file, line);
            }
        }
    }

    return new_block;
};

s_memory_pool_block_info * memory_pool_block_new_from_end_of_pool(s_memory_pool * pool, unsigned int actual_size, char const * file, long line)
{
    mangled_ppc("?memory_pool_block_new_from_end_of_pool@@YAPAUs_memory_pool_block_info@@PAUs_memory_pool@@IPBDJ@Z");

    s_memory_pool_block_info * available_block = NULL;
    s_memory_pool_block_info * previous_block;
    void * end_of_last_block;

    if (pool->last_block_handle == k_memory_pool_null_handle)
    {
        previous_block = NULL;
        end_of_last_block = memory_pool_get_base_address(pool);
    }
    else
    {
        previous_block = memory_pool_get_block(pool, pool->last_block_handle);
        end_of_last_block = memory_pool_block_get_end_of_block(pool, previous_block);
    }

    if (offset_pointer(end_of_last_block, actual_size) <= memory_pool_get_end_address(pool))
    {
        available_block = memory_pool_block_initialize(pool, end_of_last_block, actual_size, file, line, NULL, previous_block);
    }

    return available_block;
};

void * memory_pool_block_get_end_of_block(s_memory_pool const * pool, s_memory_pool_block_info * block)
{
    mangled_ppc("?memory_pool_block_get_end_of_block@@YAPAXPBUs_memory_pool@@PAUs_memory_pool_block_info@@@Z");

    return offset_pointer(memory_pool_block_get_base(pool, block), block->total_size);
};

s_memory_pool_block_info * memory_pool_block_new_from_front_of_pool(s_memory_pool * pool, unsigned int actual_size, char const * file, long line)
{
    mangled_ppc("?memory_pool_block_new_from_front_of_pool@@YAPAUs_memory_pool_block_info@@PAUs_memory_pool@@IPBDJ@Z");

    s_memory_pool_block_info * available_block = NULL;
    void * base_address = memory_pool_get_base_address(pool);
    s_memory_pool_block_info * next_block;
    void * start_of_first_block;

    if (pool->first_block_handle == k_memory_pool_null_handle)
    {
        next_block = NULL;
        start_of_first_block = memory_pool_get_end_address(pool);
    }
    else
    {
        next_block = memory_pool_get_block(pool, pool->first_block_handle);
        start_of_first_block = memory_pool_block_get_base(pool, next_block);
    }

    if (offset_pointer(base_address, actual_size) <= start_of_first_block)
    {
        available_block = memory_pool_block_initialize(pool, base_address, actual_size, file, line, next_block, NULL);
    }

    return available_block;
};

s_memory_pool_block_info * memory_pool_block_new_from_in_between_blocks(s_memory_pool * pool, unsigned int actual_size, char const * file, long line)
{
    mangled_ppc("?memory_pool_block_new_from_in_between_blocks@@YAPAUs_memory_pool_block_info@@PAUs_memory_pool@@IPBDJ@Z");

    s_memory_pool_block_info * available_block = NULL;
    unsigned long block_handle = pool->first_block_handle;

    while (block_handle != k_memory_pool_null_handle)
    {
        s_memory_pool_block_info * block = memory_pool_get_block(pool, block_handle);
        if (block->next_block_handle != k_memory_pool_null_handle)
        {
            s_memory_pool_block_info * next_block = memory_pool_get_block(pool, block->next_block_handle);
            void * start_of_next_block = memory_pool_block_get_base(pool, next_block);
            void * end_of_block = memory_pool_block_get_end_of_block(pool, block);

            if (offset_pointer(end_of_block, actual_size) <= start_of_next_block)
            {
                available_block = memory_pool_block_initialize(pool, end_of_block, actual_size, file, line, next_block, block);
                break;
            }
        }

        block_handle = block->next_block_handle;
    }

    return available_block;
};

s_memory_pool_block_info * memory_pool_block_initialize(s_memory_pool * pool, void * base_address, unsigned int size, char const * file, long line, s_memory_pool_block_info * next_block, s_memory_pool_block_info * previous_block)
{
    mangled_ppc("?memory_pool_block_initialize@@YAPAUs_memory_pool_block_info@@PAUs_memory_pool@@PAXIPBDJPAU1@3@Z");

    s_memory_pool_block_info * new_block = memory_pool_block_base_get_block(pool, base_address);
    s_memory_pool_block_header * header = memory_pool_block_get_header(pool, new_block);

    if (header)
    {
        csmemset(header, 0, sizeof(s_memory_pool_block_header));
        header->header_signature = k_block_header_signature;
        header->file = file;
        header->line = line;
        header->timestamp = system_milliseconds();
    }

    csmemset(new_block, 0, sizeof(s_memory_pool_block_info));
    new_block->total_size = size;
    new_block->next_block_handle = next_block == NULL ? k_memory_pool_null_handle : memory_pool_handle_from_address(pool, next_block);
    new_block->previous_block_handle = previous_block == NULL ? k_memory_pool_null_handle : memory_pool_handle_from_address(pool, previous_block);

    if (previous_block == NULL)
    {
        assert_tag_debug_untracked_jul_11_2011(1364, (pool->first_block_handle==k_memory_pool_null_handle && next_block==NULL) || memory_pool_get_block(pool, pool->first_block_handle)==next_block);

        pool->first_block_handle = memory_pool_handle_from_address(pool, new_block);
    }
    else
    {
        previous_block->next_block_handle = memory_pool_handle_from_address(pool, new_block);
    }

    if (next_block == NULL)
    {
        assert_tag_debug_untracked_jul_11_2011(1375, (pool->last_block_handle==k_memory_pool_null_handle && previous_block==NULL) || memory_pool_get_block(pool, pool->last_block_handle)==previous_block);

        pool->last_block_handle = memory_pool_handle_from_address(pool, new_block);
    }
    else
    {
        next_block->previous_block_handle = memory_pool_handle_from_address(pool, new_block);
    }

    csmemset(memory_pool_payload_from_block(new_block), 0xCD, new_block->total_size - memory_pool_overhead_size(pool));

    assert_tag_debug_untracked_jul_11_2011(1388, memory_pool_block_valid(pool, new_block));

    return new_block;
};

void * memory_pool_payload_from_block(s_memory_pool_block_info * block)
{
    mangled_ppc("?memory_pool_payload_from_block@@YAPAXPAUs_memory_pool_block_info@@@Z");

    return offset_pointer(block, sizeof(s_memory_pool_block_info));
};

bool memory_pool_block_valid(s_memory_pool const * pool, s_memory_pool_block_info const * block)
{
    mangled_ppc("?memory_pool_block_valid@@YA_NPBUs_memory_pool@@PBUs_memory_pool_block_info@@@Z");

    bool valid = true;
    s_memory_pool_block_header const * header = memory_pool_block_get_header_const(pool, block);

    if (!block)
    {
        valid = false;
    }
    else if (header && header->header_signature != k_block_header_signature)
    {
        valid = false;
    }
    else if (block->total_size <= memory_pool_overhead_size(pool) || block->total_size > pool->size)
    {
        valid = false;
    }
    else if (block < memory_pool_get_base_address(pool))
    {
        valid = false;
    }
    else if (memory_pool_block_get_end_of_block_const(pool, block) > memory_pool_get_end_address(pool))
    {
        valid = false;
    }

    return valid;
};

void memory_block_notify_reference(s_memory_pool const * pool, s_memory_pool_block_info * block)
{
    mangled_ppc("?memory_block_notify_reference@@YAXPBUs_memory_pool@@PAUs_memory_pool_block_info@@@Z");

    assert_tag_debug_untracked_jul_11_2011(1431, pool);
    assert_tag_debug_untracked_jul_11_2011(1432, block);
    dassert_tag_debug_untracked_jul_11_2011(1434, pool->relocation_function == NULL || !pool->flags.test(_memory_pool_doesnt_track_references_bit), "this pool does not track references so it can't use a relocation function");

    if (pool->relocation_function)
    {
        unsigned long block_handle = memory_pool_handle_from_address(pool, block);
        unsigned long payload_handle = memory_pool_payload_handle_from_block_handle(block_handle);

        assert_tag_debug_untracked_jul_11_2011(1440, !pool->flags.test(_memory_pool_doesnt_track_references_bit));

        pool->relocation_function(block->reference, payload_handle);
    }
};

s_memory_pool_block_info * memory_pool_block_base_get_block(s_memory_pool const * pool, void * base)
{
    mangled_ppc("?memory_pool_block_base_get_block@@YAPAUs_memory_pool_block_info@@PBUs_memory_pool@@PAX@Z");

    void * block = base;
    if (pool->flags.test(_memory_pool_initialized_bit))
    {
        block = offset_pointer(block, sizeof(s_memory_pool_block_header));
    }

    return static_cast<s_memory_pool_block_info *>(block);
};

void * memory_pool_block_get_base(s_memory_pool const * pool, s_memory_pool_block_info * block)
{
    mangled_ppc("?memory_pool_block_get_base@@YAPAXPBUs_memory_pool@@PAUs_memory_pool_block_info@@@Z");

    void * base = block;
    if (pool->flags.test(_memory_pool_initialized_bit))
    {
        base = offset_pointer(base, -static_cast<long>(sizeof(s_memory_pool_block_header)));
    }

    return base;
};

void const * memory_pool_block_get_base_const(s_memory_pool const * pool, s_memory_pool_block_info const * block)
{
    mangled_ppc("?memory_pool_block_get_base_const@@YAPBXPBUs_memory_pool@@PBUs_memory_pool_block_info@@@Z");

    return memory_pool_block_get_base(pool, const_cast<s_memory_pool_block_info *>(block));
};

s_memory_pool_block_header * memory_pool_block_get_header(s_memory_pool const * pool, s_memory_pool_block_info * block)
{
    mangled_ppc("?memory_pool_block_get_header@@YAPAUs_memory_pool_block_header@@PBUs_memory_pool@@PAUs_memory_pool_block_info@@@Z");

    s_memory_pool_block_header * header = NULL;
    if (pool->flags.test(_memory_pool_initialized_bit))
    {
        header = static_cast<s_memory_pool_block_header *>(offset_pointer(block, -static_cast<long>(sizeof(s_memory_pool_block_header))));
    }

    return header;
};

s_memory_pool_block_header const * memory_pool_block_get_header_const(s_memory_pool const * pool, s_memory_pool_block_info const * block)
{
    mangled_ppc("?memory_pool_block_get_header_const@@YAPBUs_memory_pool_block_header@@PBUs_memory_pool@@PBUs_memory_pool_block_info@@@Z");

    return memory_pool_block_get_header(pool, const_cast<s_memory_pool_block_info *>(block));
};

s_memory_pool_block_info * memory_pool_payload_get_block(s_memory_pool * pool, unsigned long payload_handle)
{
    mangled_ppc("?memory_pool_payload_get_block@@YAPAUs_memory_pool_block_info@@PAUs_memory_pool@@K@Z");

    assert_tag_debug_untracked_jul_11_2011(1520, pool);
    assert_tag_debug_untracked_jul_11_2011(1521, payload_handle);

    memory_pool_verify(pool);

    unsigned long block_handle = memory_pool_block_handle_from_payload_handle(payload_handle);
    s_memory_pool_block_info * block = memory_pool_get_block(pool, block_handle);

    assert_tag_debug_untracked_jul_11_2011(1528, memory_pool_block_valid(pool, block));

    if (!pool->flags.test(_memory_pool_no_verification_bit) && !pool->flags.test(_memory_pool_compacting_bit))
    {
        unsigned long current_block_handle;
        for (current_block_handle = pool->first_block_handle; current_block_handle != k_memory_pool_null_handle && current_block_handle != block_handle; current_block_handle = memory_pool_get_block(pool, current_block_handle)->next_block_handle)
        {
        }

        dassert_tag_debug_untracked_jul_11_2011(1541, current_block_handle == block_handle, "memory_pool: can't find block in pool - accessing a freed block?");
    }

    return block;
};

s_memory_pool_block_info const * memory_pool_payload_get_block_const(s_memory_pool const * pool, unsigned long payload_handle)
{
    mangled_ppc("?memory_pool_payload_get_block_const@@YAPBUs_memory_pool_block_info@@PBUs_memory_pool@@K@Z");

    return memory_pool_payload_get_block(const_cast<s_memory_pool *>(pool), payload_handle);
};

