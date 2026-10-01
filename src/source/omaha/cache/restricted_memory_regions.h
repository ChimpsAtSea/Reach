#ifndef __RESTRICTED_MEMORY_REGIONS_H__
#define __RESTRICTED_MEMORY_REGIONS_H__
#pragma once

/* ---------- headers */

#include "omaha\multithreading\synchronization_spasm.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "foundation\baselib\memory\allocation_interface.h"
#include "omaha\cseries\cseries.h"
#include "omaha\multithreading\threads.h"

/* ---------- constants */

// only the values below are verified (shared_region.obj); names unverified
enum e_restricted_memory_region
{
    k_global_shared_region = 7,
    k_global_audio_region = 8
};

/* ---------- definitions */

class c_restricted_section;
class c_restricted_memory_callbacks;

// Reach: template args are <region, pre_copy_fixup, post_copy_fixup, tls_update_callback>; the two fixup
// callbacks mangle as integer 0 ($0A@) in every instantiation seen so far, so they are plain long here
template<long region, long pre_copy_fixup_callback, long post_copy_fixup_callback, void (*tls_update_callback)(void *)>
class t_restricted_allocation_manager : public c_allocation_interface
{
public:
    t_restricted_allocation_manager(void) :
        m_member_index(NONE),
        m_thread_id(NONE)
    {
    }

    ~t_restricted_allocation_manager(void)
    {
    }

    bool valid(void) const
    {
        return m_member_index != NONE && m_thread_id != NONE;
    }

    void * reserve_memory(char const * name, char const * type_name, unsigned int size, long alignment_bits)
    {
        assert_decomp(!valid(), "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\cache\\restricted_memory_regions.h", 177);
        m_member_index = restricted_region_add_member(region, name, type_name, size, alignment_bits, tls_update_callback, NULL, NULL);
        m_thread_id = get_current_thread_index();
        return restricted_region_get_member_address(region, m_member_index);
    }

    void free_memory(void)
    {
        assert_decomp(valid(), "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\cache\\restricted_memory_regions.h", 186);
        assert_decomp(m_thread_id== get_current_thread_index(), "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\cache\\restricted_memory_regions.h", 187);
        tls_update_callback(NULL);
        restricted_region_free_member(region, m_member_index);
    }

    virtual void * allocate(unsigned int size, char const * file, long line, char const * type, char const * subtype, char const * name)
    {
        return reserve_memory(name, type, size, 0);
    }

    virtual void deallocate(void * pointer, char const * file, long line)
    {
        free_memory();
    }

protected:
    long m_member_index; // 0x4
    long m_thread_id; // 0x8
};

/* ---------- prototypes */

void restricted_region_create(long region_index, c_restricted_section * primary_section, e_critical_sections critical_section_index, c_restricted_memory_callbacks * callbacks);
void restricted_region_add_mirror(long region_index, c_restricted_section * mirror_section);
void restricted_region_destroy(long region_index);
void restricted_region_lock_primary(long region_index);
void restricted_region_unlock_primary(long region_index);
long restricted_region_add_member(long region_index, char const * name, char const * type_name, unsigned int size, long alignment_bits, void (*tls_update_callback)(void *), void (*pre_copy_fixup_callback)(void *), void (*post_copy_fixup_callback)(void *));
void restricted_region_free_member(long region_index, long member_index);
void * restricted_region_get_member_address(long region_index, long member_index);

/* ---------- globals */

/* ---------- public code */

#endif // __RESTRICTED_MEMORY_REGIONS_H__

