/* ---------- headers */

#include "blamlib\cseries_xenon.h"
#include <xtl.h>
#include "core\corelib\cseries\cseries_events.h"
#include "foundation\baselib\memory\debug_memory\debug_memory_allocators.h"
#include "omaha\cache\physical_memory_map.h"
#include "omaha\cseries\cseries.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// void * allocate_contiguous_memory_untracked(unsigned long, void const *, long, unsigned long);
// void free_contiguous_memory_untracked(void *);
// void * allocate_contiguous_memory_tracked_verbose(unsigned long, void const *, long, unsigned long, unsigned long, char const *, long, char const *, char const *, char const *);
// void free_contiguous_memory_tracked_verbose(void *, char const *, long);

void * allocate_contiguous_memory_untracked(unsigned long size, void const * address, long alignment_bits, unsigned long protect)
{
    mangled_ppc("?allocate_contiguous_memory_untracked@@YAPAXKPBXJK@Z");

    unsigned long alignment = alignment_bits == NONE ? 0 : 1 << alignment_bits;
    unsigned long physical_address = address ? reinterpret_cast<unsigned long>(address) : 0xFFFFFFFF;
    unsigned long page_size = physical_memory_get_page_size(address);
    unsigned long page_flags = page_size == 0x1000 ? 0 : page_size == 0x10000 ? MEM_LARGE_PAGES : page_size == 0x1000000 ? MEM_16MB_PAGES : 0;
    void * base = XPhysicalAlloc(size, physical_address, alignment | page_flags, protect);

    return base;
};

void free_contiguous_memory_untracked(void * address)
{
    mangled_ppc("?free_contiguous_memory_untracked@@YAXPAX@Z");

    XPhysicalFree(address);
};

void * allocate_contiguous_memory_tracked_verbose(unsigned long size, void const * address, long alignment_bits, unsigned long protect, unsigned long flags, char const * file, long line, char const * type, char const * subtype, char const * name)
{
    mangled_ppc("?allocate_contiguous_memory_tracked_verbose@@YAPAXKPBXJKKPBDJ111@Z");

    void * result = allocate_contiguous_memory_untracked(size, address, alignment_bits, protect);
    if (result)
    {
        debug_track_nonheap_alloc(result, XPhysicalSize(result), static_cast<e_debug_memory_flags>(flags), file, line, NONE, type, subtype, name);
        event_wrapped(_event_message, "system:contiguous_memory:allocate: %s %ld at 0x%08X", name, size, result);
    }

    return result;
};

void free_contiguous_memory_tracked_verbose(void * address, char const * file, long line)
{
    mangled_ppc("?free_contiguous_memory_tracked_verbose@@YAXPAXPBDJ@Z");

    if (address)
    {
        event_wrapped(_event_message, "system:contiguous_memory:free: at 0x%08X", address);
        debug_track_nonheap_free(address, file, line);
    }
    free_contiguous_memory_untracked(address);
};

