#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\zlib\\blam_zlib_memory.cpp"
/* ---------- headers */

#include "omaha\zlib\blam_zlib_memory.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "foundation\baselib\datatypes\memory_pool.h"
#include "zlib\zlib.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

void blam_zlib_initialize(s_memory_pool * heap, s_blam_zlib_memory * out_zlib_memory_tracker)
{
    mangled_ppc("?blam_zlib_initialize@@YAXPAUs_memory_pool@@PAUs_blam_zlib_memory@@@Z");

    assert_tag_debug_untracked_jul_11_2011(17, heap);
    assert_tag_debug_untracked_jul_11_2011(18, out_zlib_memory_tracker);
    memory_pool_set_reference_tracking(heap, false);
    memory_pool_set_allocation_from_anywhere_in_pool(heap, true);
    out_zlib_memory_tracker->heap = heap;
};

void blam_zlib_dispose(s_blam_zlib_memory * zlib_memory_tracker)
{
    mangled_ppc("?blam_zlib_dispose@@YAXPAUs_blam_zlib_memory@@@Z");

    assert_tag_debug_untracked_jul_11_2011(30, zlib_memory_tracker);
    zlib_memory_tracker->heap = NULL;
};

bool blam_zlib_stream_setup(z_stream_s * out_zlib_stream, s_blam_zlib_memory * zlib_memory_tracker)
{
    mangled_ppc("?blam_zlib_stream_setup@@YA_NPAUz_stream_s@@PAUs_blam_zlib_memory@@@Z");

    bool success = true;
    assert_tag_debug_untracked_jul_11_2011(42, out_zlib_stream);
    assert_tag_debug_untracked_jul_11_2011(43, zlib_memory_tracker);
    out_zlib_stream->zalloc = blam_zlib_malloc;
    out_zlib_stream->zfree = blam_zlib_free;
    out_zlib_stream->opaque = zlib_memory_tracker;
    return success;
};

void * blam_zlib_malloc(void * context, unsigned int count, unsigned int size)
{
    mangled_ppc("?blam_zlib_malloc@@YAPAXPAXII@Z");

    assert_tag_debug_untracked_jul_11_2011(57, context);
    s_blam_zlib_memory * zlib_memory = static_cast<s_blam_zlib_memory *>(context);
    assert_tag_debug_untracked_jul_11_2011(59, zlib_memory->heap);
    void * pointer;
    bool success = memory_pool_block_allocate_tracked(zlib_memory->heap, &pointer, count * size, __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__, 61);
    assert_tag_debug_untracked_jul_11_2011(64, success);
    assert_tag_debug_untracked_jul_11_2011(65, pointer);
    return pointer;
};

void blam_zlib_free(void * context, void * pointer)
{
    mangled_ppc("?blam_zlib_free@@YAXPAX0@Z");

    assert_tag_debug_untracked_jul_11_2011(73, context);
    s_blam_zlib_memory * zlib_memory = static_cast<s_blam_zlib_memory *>(context);
    assert_tag_debug_untracked_jul_11_2011(75, zlib_memory->heap);
    memory_pool_block_free(zlib_memory->heap, &pointer);
};

