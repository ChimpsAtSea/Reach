#pragma once
#ifndef __FALLBACK_OPTIONAL_CACHE_BACKEND_H__
#define __FALLBACK_OPTIONAL_CACHE_BACKEND_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"
#include "omaha\cache\optional_cache_constants.h"
#include "omaha\cache\physical_memory_map.h"

/* ---------- constants */

/* ---------- definitions */

struct s_memory_pool;

class c_fallback_optional_cache_backend : public c_optional_cache_backend
{
public:
    c_fallback_optional_cache_backend(void);

    virtual void initialize(e_map_memory_configuration map_configuration, s_static_array<s_optional_cache_user_memory_configuration, k_number_of_optional_cache_users> const * memory_configurations);
    virtual void dispose(void);
    virtual void * try_to_allocate(e_optional_cache_user user, e_optional_cache_user_priority priority, char const * file, long line, long size, c_optional_cache_user_callback * callback);
    virtual void deallocate(e_optional_cache_user user, char const * file, long line, void * pointer);

private:
    c_physical_memory_allocation m_allocation;
    s_memory_pool * m_memory_pool;
};
static_assert(sizeof(c_fallback_optional_cache_backend) == 0x14, "c_fallback_optional_cache_backend");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __FALLBACK_OPTIONAL_CACHE_BACKEND_H__

