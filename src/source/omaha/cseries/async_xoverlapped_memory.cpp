#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\cseries\\async_xoverlapped_memory.cpp"
/* ---------- headers */

#include "omaha\cseries\async_xoverlapped_memory.h"
#include <string.h>
#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_events.h"
#include "core\corelib\cseries\cseries_macros.h"
#include "foundation\baselib\datatypes\data_array.h"
#include "foundation\baselib\datatypes\memory_pool.h"
#include "omaha\cseries\runtime_state.h"
#include "omaha\main\console.h"
#include "omaha\multithreading\synchronization_spasm.h"
#include "omaha\profiler\profiler.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

static void overlapped_out_of_memory(unsigned int size, char const * file, long line);
static void overlapped_memory_update_status_line(void);

/* ---------- globals */

static memory_pool_relocation_function const k_memory_pool_no_callback = NULL;

static s_memory_pool * g_overlapped_memory_pool = NULL;
static bool g_overlapped_memory_status_line_initialized = false;
bool g_display_overlapped_memory = false;
static long g_overlapped_memory_block_count = 0;
static long g_overlapped_memory_used_size = 0;
static c_overlapped_allocation g_overlapped_allocation;
c_status_line g_overlapped_memory_status_line;

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// bool g_display_overlapped_memory; // "?g_display_overlapped_memory@@3_NA"
// struct c_status_line g_overlapped_memory_status_line; // "?g_overlapped_memory_status_line@@3Uc_status_line@@A"
// long `public: virtual void * __cdecl c_overlapped_allocation::allocate(unsigned int, char const *, long, char const *, char const *, char const *)'::`2'::_unique_profile_definition_mem_xoverlapped_allocate; // "?_unique_profile_definition_mem_xoverlapped_allocate@?1??allocate@c_overlapped_allocation@@UAAPAXIPBDJ000@Z@4JA"
// `public: virtual void * __cdecl c_overlapped_allocation::allocate(unsigned int, char const *, long, char const *, char const *, char const *)'::`2'::`local static guard'{2}; // "??_B?1??allocate@c_overlapped_allocation@@UAAPAXIPBDJ000@Z@51"
// long `public: virtual void __cdecl c_overlapped_allocation::deallocate(void *, char const *, long)'::`2'::_unique_profile_definition_mem_xoverlapped_deallocate; // "?_unique_profile_definition_mem_xoverlapped_deallocate@?1??deallocate@c_overlapped_allocation@@UAAXPAXPBDJ@Z@4JA"
// `public: virtual void __cdecl c_overlapped_allocation::deallocate(void *, char const *, long)'::`2'::`local static guard'{2}; // "??_B?1??deallocate@c_overlapped_allocation@@UAAXPAXPBDJ@Z@51"

// void overlapped_memory_initialize(void);
// void overlapped_memory_dispose(void);
// void overlapped_memory_print_usage(void);
// class c_allocation_interface * overlapped_memory_allocation(void);
// void * overlapped_malloc_tracked(unsigned int, char const *, long);
// public: c_async_xoverlapped_memory_scope_lock::c_async_xoverlapped_memory_scope_lock(void);
// public: c_async_xoverlapped_memory_scope_lock::~c_async_xoverlapped_memory_scope_lock(void);
// void * overlapped_calloc_tracked(unsigned int, char const *, long);
// void * overlapped_realloc_tracked(void *, unsigned int, char const *, long);
// struct s_data_array * overlapped_data_new_tracked(char const *, long, long, char const *, long);
// void overlapped_free(void const *);
// void overlapped_memory_pool_verify(void);
// void overlapped_memory_dump(char const *);
// void overlapped_out_of_memory(unsigned int, char const *, long);
// class c_allocation_interface * get_overlapped_allocation(void);
// void overlapped_memory_update_status_line(void);
// public: c_overlapped_allocation::c_overlapped_allocation(void);
// public: virtual void * c_overlapped_allocation::allocate(unsigned int, char const *, long, char const *, char const *, char const *);
// public: virtual void c_overlapped_allocation::deallocate(void *, char const *, long);

void overlapped_memory_initialize(void)
{
    mangled_ppc("?overlapped_memory_initialize@@YAXXZ");

    assert_tag_debug_untracked_jul_11_2011(126, g_overlapped_memory_pool==NULL);
    g_overlapped_memory_pool = memory_pool_new("xoverlapped memory pool", 0x60000, k_memory_pool_no_callback, g_runtime_state_allocation, __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__, 128);
    if (g_overlapped_memory_pool)
    {
        memory_pool_set_reference_tracking(g_overlapped_memory_pool, false);
        memory_pool_set_allocation_from_anywhere_in_pool(g_overlapped_memory_pool, true);
    }

    if (!g_overlapped_memory_status_line_initialized)
    {
        status_lines_initialize(&g_overlapped_memory_status_line, &g_display_overlapped_memory, 1);
        g_overlapped_memory_status_line_initialized = true;
    }
};

void overlapped_memory_dispose(void)
{
    mangled_ppc("?overlapped_memory_dispose@@YAXXZ");

    if (g_overlapped_memory_pool)
    {
        overlapped_memory_print_usage();
        memory_pool_dispose(g_overlapped_memory_pool, __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__, 155);
        g_overlapped_memory_pool = NULL;
    }
};

void overlapped_memory_print_usage(void)
{
    mangled_ppc("?overlapped_memory_print_usage@@YAXXZ");

    event_wrapped(_event_status, "xoverlapped memory: #%ld blocks : %ld bytes used", g_overlapped_memory_block_count, g_overlapped_memory_used_size);
    if (g_overlapped_memory_block_count != 0)
    {
        overlapped_memory_dump("xoverlapped_leak");
    }
};

c_allocation_interface * overlapped_memory_allocation(void)
{
    mangled_ppc("?overlapped_memory_allocation@@YAPAVc_allocation_interface@@XZ");

    return &g_overlapped_allocation;
};

void * overlapped_malloc_tracked(unsigned int size, char const * file, long line)
{
    mangled_ppc("?overlapped_malloc_tracked@@YAPAXIPBDJ@Z");

    void * ptr;
    c_async_xoverlapped_memory_scope_lock __local_async_xoverlapped_memory_scope_lock;

    assert_tag_debug_untracked_jul_11_2011(193, g_overlapped_memory_pool != NULL);
    if (memory_pool_block_allocate_tracked(g_overlapped_memory_pool, &ptr, size, file, line))
    {
        g_overlapped_memory_block_count++;
        g_overlapped_memory_used_size += memory_pool_get_block_size(g_overlapped_memory_pool, &ptr);
    }
    else
    {
        event_wrapped(_event_error, "network:overlapped: out of memory, reclaim did not find enough to allocate %d.", size);
        overlapped_out_of_memory(size, file, line);
        ptr = NULL;
    }

    overlapped_memory_update_status_line();
    return ptr;
};

c_async_xoverlapped_memory_scope_lock::c_async_xoverlapped_memory_scope_lock(void)
{
    mangled_ppc("??0c_async_xoverlapped_memory_scope_lock@@QAA@XZ");

    critical_section_enter_internal(g_omaha_critical_sections[k_crit_section_async_xoverlapped_memory], _critical_section_non_recursive);
};

c_async_xoverlapped_memory_scope_lock::~c_async_xoverlapped_memory_scope_lock(void)
{
    mangled_ppc("??1c_async_xoverlapped_memory_scope_lock@@QAA@XZ");

    critical_section_leave_internal(g_omaha_critical_sections[k_crit_section_async_xoverlapped_memory], _critical_section_non_recursive);
};

void * overlapped_calloc_tracked(unsigned int size, char const * file, long line)
{
    mangled_ppc("?overlapped_calloc_tracked@@YAPAXIPBDJ@Z");

    void * ptr = overlapped_malloc_tracked(size, file, line);
    if (ptr)
    {
        memset(ptr, 0, size);
    }

    return ptr;
};

void * overlapped_realloc_tracked(void * ptr, unsigned int size, char const * file, long line)
{
    mangled_ppc("?overlapped_realloc_tracked@@YAPAXPAXIPBDJ@Z");

    c_async_xoverlapped_memory_scope_lock __local_async_xoverlapped_memory_scope_lock;

    assert_tag_debug_untracked_jul_11_2011(235, g_overlapped_memory_pool != NULL);
    if (!ptr)
    {
        ptr = overlapped_malloc_tracked(size, file, line);
    }
    else
    {
        g_overlapped_memory_block_count--;
        g_overlapped_memory_used_size -= memory_pool_get_block_size(g_overlapped_memory_pool, &ptr);
        if (memory_pool_block_reallocate_tracked(g_overlapped_memory_pool, &ptr, size, file, line))
        {
            g_overlapped_memory_block_count++;
            g_overlapped_memory_used_size += memory_pool_get_block_size(g_overlapped_memory_pool, &ptr);
        }
        else
        {
            event_wrapped(_event_error, "network:overlapped: out of memory, reclaim did not find enough to allocate %d.", size);
            overlapped_out_of_memory(size, file, line);
            ptr = NULL;
        }
    }

    overlapped_memory_update_status_line();
    return ptr;
};

s_data_array * overlapped_data_new_tracked(char const * name, long maximum_count, long size, char const * file, long line)
{
    mangled_ppc("?overlapped_data_new_tracked@@YAPAUs_data_array@@PBDJJ0J@Z");

    c_async_xoverlapped_memory_scope_lock __local_async_xoverlapped_memory_scope_lock;
    s_data_array * data = data_new(name, maximum_count, size, 0, file, line, &g_overlapped_allocation);
    return data;
};

void overlapped_free(void const * ptr)
{
    mangled_ppc("?overlapped_free@@YAXPBX@Z");

    void ** payload;
    c_async_xoverlapped_memory_scope_lock __local_async_xoverlapped_memory_scope_lock;

    assert_tag_debug_untracked_jul_11_2011(316, ptr!=NULL);
    assert_tag_debug_untracked_jul_11_2011(317, g_overlapped_memory_pool != NULL);

    payload = const_cast<void **>(&ptr);
    g_overlapped_memory_block_count--;
    g_overlapped_memory_used_size -= memory_pool_get_block_size(g_overlapped_memory_pool, payload);
    memory_pool_block_free(g_overlapped_memory_pool, payload);
    overlapped_memory_update_status_line();
};

void overlapped_memory_pool_verify(void)
{
    mangled_ppc("?overlapped_memory_pool_verify@@YAXXZ");

    memory_pool_verify(g_overlapped_memory_pool);
};

void overlapped_memory_dump(char const * prefix)
{
    mangled_ppc("?overlapped_memory_dump@@YAXPBD@Z");

    memory_pool_dump_to_file(g_overlapped_memory_pool, prefix);
};

static void overlapped_out_of_memory(unsigned int size, char const * file, long line)
{
    mangled_ppc("?overlapped_out_of_memory@@YAXIPBDJ@Z");

    event_wrapped(_event_critical, "network:overlapped: xoverlapped failed to allocate %d bytes at %s#%d", size, !file ? "NULL" : file, line);
    overlapped_memory_dump("xoverlapped_out_of_memory");
};

c_allocation_interface * get_overlapped_allocation(void)
{
    mangled_ppc("?get_overlapped_allocation@@YAPAVc_allocation_interface@@XZ");

    return &g_overlapped_allocation;
};

static void overlapped_memory_update_status_line(void)
{
    mangled_ppc("?overlapped_memory_update_status_line@@YAXXZ");

    status_line_printf(&g_overlapped_memory_status_line, "xov memory: #%ld blocks : %ld bytes used", g_overlapped_memory_block_count, g_overlapped_memory_used_size);
};

c_overlapped_allocation::c_overlapped_allocation(void)
{
    mangled_ppc("??0c_overlapped_allocation@@QAA@XZ");
};

void * c_overlapped_allocation::allocate(unsigned int size, char const * file, long line, char const * type, char const * subtype, char const * name)
{
    mangled_ppc("?allocate@c_overlapped_allocation@@UAAPAXIPBDJ000@Z");

    void * result;
    {
        PROFILER_UNIQUE_SCOPE_BEGIN(68, mem_xoverlapped_allocate, profile_instance);
        result = overlapped_malloc_tracked(size, file, line);
        profile_instance.end();
        return result;
    }
};

void c_overlapped_allocation::deallocate(void * pointer, char const * file, long line)
{
    mangled_ppc("?deallocate@c_overlapped_allocation@@UAAXPAXPBDJ@Z");

    PROFILER_UNIQUE_SCOPE_BEGIN(84, mem_xoverlapped_deallocate, profile_instance);
    overlapped_free(pointer);
    profile_instance.end();
};
