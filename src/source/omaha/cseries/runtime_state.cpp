#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\cseries\\runtime_state.cpp"
/* ---------- headers */

#include "omaha\cseries\runtime_state.h"
#include <string.h>
#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_events.h"
#include "core\corelib\cseries\cseries_macros.h"
#include "core\corelib\cseries\cseries_memory.h"
#include "foundation\baselib\memory\debug_memory\debug_memory_allocators.h"
#include "omaha\cseries\cseries.h"
#include "omaha\memory\crc.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

c_allocation_interface * g_runtime_state_allocation = &g_actual_runtime_state_allocation;
s_runtime_state_globals g_runtime_state_globals;
c_runtime_state_allocation g_actual_runtime_state_allocation;

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// class c_allocation_interface *g_runtime_state_allocation; // "?g_runtime_state_allocation@@3PAVc_allocation_interface@@A"
// struct s_runtime_state_globals g_runtime_state_globals; // "?g_runtime_state_globals@@3Us_runtime_state_globals@@A"
// class c_runtime_state_allocation g_actual_runtime_state_allocation; // "?g_actual_runtime_state_allocation@@3Vc_runtime_state_allocation@@A"

// void runtime_state_shell_initialize(void);
// void runtime_state_shell_dispose(void);
// void runtime_state_adjust_available_region(unsigned long, unsigned long);
// void runtime_state_initialize(void);
// void runtime_state_dispose(void);
// void runtime_state_initialize_for_new_map(void);
// void runtime_state_dispose_from_old_map(void);
// void * runtime_state_malloc_verbose(char const *, long, char const *, char const *, long);
// void * runtime_state_malloc_aligned_verbose(char const *, long, char const *, char const *, long, long);
// void const * runtime_state_get_buffer_address(long *);
// void * align_pointer(void *, long);
// unsigned long align_address(unsigned long, long);
// public: c_runtime_state_allocation::c_runtime_state_allocation(void);
// public: virtual void * c_runtime_state_allocation::allocate(unsigned int, char const *, long, char const *, char const *, char const *);
// public: virtual void c_runtime_state_allocation::deallocate(void *, char const *, long);

void runtime_state_shell_initialize(void)
{
    mangled_ppc("?runtime_state_shell_initialize@@YAXXZ");

    assert_tag_debug_untracked_jul_11_2011(83, !g_runtime_state_globals.base_address);
    g_runtime_state_globals.base_address = runtime_state_allocate_buffer(k_runtime_state_size);
    assert_tag_debug_untracked_jul_11_2011(85, g_runtime_state_globals.base_address);
    debug_track_nonheap_alloc(g_runtime_state_globals.base_address, k_runtime_state_size, static_cast<e_debug_memory_flags>(0), __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__, 87, NONE, "available runtime state", NULL, NULL);
    g_runtime_state_globals.allocated_size = 0;
};

void runtime_state_shell_dispose(void)
{
    mangled_ppc("?runtime_state_shell_dispose@@YAXXZ");

    if (g_runtime_state_globals.base_address)
    {
        debug_track_nonheap_free(offset_pointer(g_runtime_state_globals.base_address, g_runtime_state_globals.allocated_size), __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__, 99);
        runtime_state_free_buffer(g_runtime_state_globals.base_address);
        memset(&g_runtime_state_globals, 0, sizeof(g_runtime_state_globals));
    }
};

void runtime_state_adjust_available_region(unsigned long old_allocated_size, unsigned long new_allocated_size)
{
    mangled_ppc("?runtime_state_adjust_available_region@@YAXKK@Z");

    debug_track_nonheap_free(offset_pointer(g_runtime_state_globals.base_address, old_allocated_size), __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__, 111);
    debug_track_nonheap_alloc(offset_pointer(g_runtime_state_globals.base_address, new_allocated_size), k_runtime_state_size - new_allocated_size, static_cast<e_debug_memory_flags>(0), __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__, 112, NONE, "available runtime state", NULL, NULL);
};

void runtime_state_initialize(void)
{
    mangled_ppc("?runtime_state_initialize@@YAXXZ");

    assert_tag_debug_untracked_jul_11_2011(119, g_runtime_state_globals.base_address);
};

void runtime_state_dispose(void)
{
    mangled_ppc("?runtime_state_dispose@@YAXXZ");
};

void runtime_state_initialize_for_new_map(void)
{
    mangled_ppc("?runtime_state_initialize_for_new_map@@YAXXZ");

    g_runtime_state_globals.locked = true;
};

void runtime_state_dispose_from_old_map(void)
{
    mangled_ppc("?runtime_state_dispose_from_old_map@@YAXXZ");
};

void * runtime_state_malloc_verbose(char const * file, long line, char const * name, char const * type, long size)
{
    mangled_ppc("?runtime_state_malloc_verbose@@YAPAXPBDJ00J@Z");

    return runtime_state_malloc_aligned_verbose(file, line, name, type, size, 2);
};

void * runtime_state_malloc_aligned_verbose(char const * file, long line, char const * name, char const * type, long size, long alignment_bits)
{
    mangled_ppc("?runtime_state_malloc_aligned_verbose@@YAPAXPBDJ00JJ@Z");

    assert_tag_debug_untracked_jul_11_2011(158, !g_runtime_state_globals.locked);

    void * result = NULL;
    void * pointer = offset_pointer(g_runtime_state_globals.base_address, g_runtime_state_globals.allocated_size);
    void * aligned_pointer = align_pointer(pointer, alignment_bits);
    long true_size = size + pointer_distance32(pointer, aligned_pointer);
    long original_size = g_runtime_state_globals.allocated_size;

    if (g_runtime_state_globals.allocated_size + true_size <= k_runtime_state_size)
    {
        result = aligned_pointer;
        g_runtime_state_globals.allocated_size += true_size;

        long new_size = g_runtime_state_globals.allocated_size;
        runtime_state_adjust_available_region(original_size, new_size);
        debug_track_nonheap_alloc(aligned_pointer, true_size, _debug_memory_pretrack_nonheap_bit, file, line, NONE, "runtime state", type, name);

        event_wrapped(_event_message, "system:runtime_state: runtime_state_malloc %s: %d (total: %d, remaining: %d)",
            name,
            true_size,
            g_runtime_state_globals.allocated_size,
            k_runtime_state_size - g_runtime_state_globals.allocated_size);

        g_runtime_state_globals.size_checksum = crc_checksum_buffer(g_runtime_state_globals.size_checksum, &true_size, sizeof(true_size));
    }
    else
    {
        event_wrapped(_event_critical, "system:runtime_state: runtime_state_malloc FAILED %s: %d (total: %d, remaining: %d)",
            name,
            true_size,
            g_runtime_state_globals.allocated_size,
            k_runtime_state_size - g_runtime_state_globals.allocated_size);

        dassert_tag_debug_untracked_jul_11_2011(190, false, "runtime_state_malloc failed, increase k_runtime_state_size");
    }

    return result;
};

void const * runtime_state_get_buffer_address(long * buffer_size)
{
    mangled_ppc("?runtime_state_get_buffer_address@@YAPBXPAJ@Z");

    assert_tag_debug_untracked_jul_11_2011(199, buffer_size);

    *buffer_size = g_runtime_state_globals.allocated_size;
    return g_runtime_state_globals.base_address;
};

