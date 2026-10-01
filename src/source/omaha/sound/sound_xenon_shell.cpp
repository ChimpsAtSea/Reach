#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\sound\\sound_xenon_shell.cpp"
/* ---------- headers */

#include "omaha\sound\sound_xenon_shell.h"
#include "baselib\platform_tracking_xenon.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "omaha\cache\physical_memory_regions.h"
#include "omaha\math\integer_math.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

static c_sound_allocation_override_xenon g_sound_allocation_override_xenon;

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// void shell_sound_memory_initialize(void);
// void shell_sound_memory_dispose(void);
// char const * xaudio_allocation_type_name(unsigned long);
// public: virtual void * c_sound_allocation_override_xenon::allocate(unsigned int, struct _XALLOC_ATTRIBUTES);
// public: virtual unsigned int c_sound_allocation_override_xenon::allocation_size(void *, struct _XALLOC_ATTRIBUTES);
// public: virtual void c_sound_allocation_override_xenon::deallocate(void *, struct _XALLOC_ATTRIBUTES);
// public: c_sound_allocation_override_xenon::c_sound_allocation_override_xenon(void);
// public: c_allocation_override_xenon::c_allocation_override_xenon(void);

void shell_sound_memory_initialize(void)
{
    mangled_ppc("?shell_sound_memory_initialize@@YAXXZ");

    allocation_override_xenon_register(eXALLOCAllocatorId_XAUDIO, &g_sound_allocation_override_xenon);
};

void shell_sound_memory_dispose(void)
{
    mangled_ppc("?shell_sound_memory_dispose@@YAXXZ");

    allocation_override_xenon_deregister(eXALLOCAllocatorId_XAUDIO, &g_sound_allocation_override_xenon);
};

// matching: the only diff is the "<unknown>" literal, which the target linker folded into network_utilities.obj's copy (shows as raw address)
char const * xaudio_allocation_type_name(unsigned long object_type)
{
    mangled_ppc("?xaudio_allocation_type_name@@YAPBDK@Z");

    char const * result = "<unknown>";

    switch (object_type)
    {
    case 0:
        result = "INTERNAL";
        break;
    case 1:
        result = "BATCH_ALLOCATOR";
        break;
    case 2:
        result = "FRAME_BUFFER";
        break;
    case 3:
        result = "EFFECT";
        break;
    case 4:
        result = "EFFECT_MANAGER";
        break;
    case 5:
        result = "ENGINE";
        break;
    case 6:
        result = "VOICE";
        break;
    case 7:
        result = "XMA_DRIVER";
        break;
    case 8:
        result = "EVENT";
        break;
    }

    return result;
};

void * c_sound_allocation_override_xenon::allocate(unsigned int size, XALLOC_ATTRIBUTES attributes)
{
    mangled_ppc("?allocate@c_sound_allocation_override_xenon@@UAAPAXIU_XALLOC_ATTRIBUTES@@@Z");

    void * retval = NULL;

    if (attributes.dwMemoryType == XALLOC_MEMTYPE_PHYSICAL && attributes.dwMemoryProtect == XALLOC_MEMPROTECT_READWRITE)
    {
        assert_tag_debug_untracked_jul_11_2011(99, !attributes.dwHeapTracksAttributes);

        retval = _physical_memory_region_allocate(
            _physical_memory_allocation_region_xaudio,
            size,
            attributes.dwMemoryType == XALLOC_MEMTYPE_HEAP ?
                (attributes.dwAlignment == XALLOC_ALIGNMENT_DEFAULT ? 2 : ceiling_log2(attributes.dwAlignment << 2)) :
                (attributes.dwAlignment == XALLOC_ALIGNMENT_DEFAULT ? 12 : attributes.dwAlignment),
            xaudio_allocation_type_name(attributes.dwObjectType));
        assert_tag_debug_untracked_jul_11_2011(113, retval);

        if (retval && attributes.dwZeroInitialize)
        {
            XMemSet(retval, 0, size);
        }
    }
    else
    {
        retval = XMemAlloc_tracked(size, reinterpret_cast<unsigned long &>(attributes));
    }

    return retval;
};

unsigned int c_sound_allocation_override_xenon::allocation_size(void * address, XALLOC_ATTRIBUTES attributes)
{
    mangled_ppc("?allocation_size@c_sound_allocation_override_xenon@@UAAIPAXU_XALLOC_ATTRIBUTES@@@Z");

    unsigned int result = 0;

    if (attributes.dwMemoryType == XALLOC_MEMTYPE_PHYSICAL && attributes.dwMemoryProtect == XALLOC_MEMPROTECT_READWRITE)
    {
        result = 0;
    }
    else
    {
        result = XMemSize_tracked(address, reinterpret_cast<unsigned long &>(attributes));
    }

    return result;
};

void c_sound_allocation_override_xenon::deallocate(void * address, XALLOC_ATTRIBUTES attributes)
{
    mangled_ppc("?deallocate@c_sound_allocation_override_xenon@@UAAXPAXU_XALLOC_ATTRIBUTES@@@Z");

    if (attributes.dwMemoryType == XALLOC_MEMTYPE_PHYSICAL && attributes.dwMemoryProtect == XALLOC_MEMPROTECT_READWRITE)
    {
        // physical memory region allocations are never freed individually
    }
    else
    {
        XMemFree_tracked(address, reinterpret_cast<unsigned long &>(attributes));
    }
};

