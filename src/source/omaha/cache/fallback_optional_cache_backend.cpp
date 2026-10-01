#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\cache\\fallback_optional_cache_backend.cpp"
/* ---------- headers */

#include "omaha\cache\fallback_optional_cache_backend.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_events.h"
#include "core\corelib\cseries\cseries_macros.h"
#include "foundation\baselib\datatypes\memory_pool.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

static memory_pool_relocation_function const k_memory_pool_no_callback = NULL;

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// public: c_fallback_optional_cache_backend::c_fallback_optional_cache_backend(void);
// public: virtual void c_fallback_optional_cache_backend::initialize(enum e_map_memory_configuration, class s_static_array<struct s_optional_cache_user_memory_configuration, 6> const *);
// public: virtual void c_fallback_optional_cache_backend::dispose(void);
// public: virtual void * c_fallback_optional_cache_backend::try_to_allocate(enum e_optional_cache_user, enum e_optional_cache_user_priority, char const *, long, long, class c_optional_cache_user_callback *);
// public: virtual void c_fallback_optional_cache_backend::deallocate(enum e_optional_cache_user, char const *, long, void *);

c_fallback_optional_cache_backend::c_fallback_optional_cache_backend(void) :
    m_allocation(_memory_stage_map_configuration, "fallback optional cache backend"),
    m_memory_pool(NULL)
{
    mangled_ppc("??0c_fallback_optional_cache_backend@@QAA@XZ");
};

void c_fallback_optional_cache_backend::initialize(e_map_memory_configuration map_configuration, s_static_array<s_optional_cache_user_memory_configuration, k_number_of_optional_cache_users> const * memory_configurations)
{
    mangled_ppc("?initialize@c_fallback_optional_cache_backend@@UAAXW4e_map_memory_configuration@@PBV?$s_static_array@Us_optional_cache_user_memory_configuration@@$05@@@Z");

    s_optional_cache_priority_sizes cache_sizes;
    long optional_cache_memory_pool_size;

    optional_cache_calculate_priority_sizes(memory_configurations, &cache_sizes);

    optional_cache_memory_pool_size = MAX(cache_sizes.minimum_no_fail_size, cache_sizes.minimum_can_fail_size);
    optional_cache_memory_pool_size += 1024;

    m_memory_pool = memory_pool_new("fallback optional cache memory pool", optional_cache_memory_pool_size, k_memory_pool_no_callback, &m_allocation, __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__, 47);
    memory_pool_set_allocation_from_anywhere_in_pool(m_memory_pool, true);
};

void c_fallback_optional_cache_backend::dispose(void)
{
    mangled_ppc("?dispose@c_fallback_optional_cache_backend@@UAAXXZ");

    dassert_tag_debug_untracked_jul_11_2011(58, memory_pool_get_used_size(m_memory_pool) == 0, "optional cache leakage!");
    memory_pool_dispose(m_memory_pool, __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__, 61);
    m_memory_pool = NULL;
};

void * c_fallback_optional_cache_backend::try_to_allocate(e_optional_cache_user user, e_optional_cache_user_priority priority, char const * file, long line, long size, c_optional_cache_user_callback * callback)
{
    mangled_ppc("?try_to_allocate@c_fallback_optional_cache_backend@@UAAPAXW4e_optional_cache_user@@W4e_optional_cache_user_priority@@PBDJJPAVc_optional_cache_user_callback@@@Z");

    void * result = NULL;

    if (m_memory_pool != NULL)
    {
        memory_pool_block_allocate_tracked(m_memory_pool, &result, size, __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__, 78);

        if (result == NULL)
        {
            event_wrapped(_event_warning, "optional_cache:fallback: allocation failed for optional cache [req size %d / contig. free size %d]", size, memory_pool_get_contiguous_free_size(m_memory_pool));
        }
    }

    return result;
};

void c_fallback_optional_cache_backend::deallocate(e_optional_cache_user user, char const * file, long line, void * pointer)
{
    mangled_ppc("?deallocate@c_fallback_optional_cache_backend@@UAAXW4e_optional_cache_user@@PBDJPAX@Z");

    assert_tag_debug_untracked_jul_11_2011(96, m_memory_pool);
    memory_pool_block_free(m_memory_pool, &pointer);
};

