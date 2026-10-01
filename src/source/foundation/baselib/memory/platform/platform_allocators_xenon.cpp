#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\foundation\\baselib\\memory\\platform\\platform_allocators_xenon.cpp"
/* ---------- headers */

#include "foundation\baselib\memory\platform\platform_allocators_xenon.h"
#include "baselib\platform_tracking_xenon.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_events.h"
#include "core\corelib\cseries\cseries_macros.h"
#include "core\corelib\cseries\cseries_memory.h"
#include "foundation\baselib\datatypes\static_array.h"
#include "omaha\cseries\cseries.h"

/* ---------- constants */

enum
{
    k_maximum_xmemalloc_overrides = 4
};

/* ---------- definitions */

struct s_xenon_xmemalloc_override
{
    XALLOC_ALLOCATOR_IDS allocator_id;
    c_allocation_override_xenon * override;
};
static_assert(sizeof(s_xenon_xmemalloc_override) == 0x8, "s_xenon_xmemalloc_override");

struct s_xenon_xmemalloc_globals
{
    s_static_array<s_xenon_xmemalloc_override, k_maximum_xmemalloc_overrides> overrides;
    float failure_chance;
};

/* ---------- prototypes */

/* ---------- globals */

static s_xenon_xmemalloc_globals g_xenon_xmemalloc_globals;

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// public: static long const s_static_array<struct s_xenon_xmemalloc_override, 4>::k_element_count; // "?k_element_count@?$s_static_array@Us_xenon_xmemalloc_override@@$03@@2JB"

// public: c_buffer_allocation_override_xenon::c_buffer_allocation_override_xenon(unsigned int, void *);
// public: virtual void * c_buffer_allocation_override_xenon::allocate(unsigned int, struct _XALLOC_ATTRIBUTES);
// public: virtual void c_buffer_allocation_override_xenon::deallocate(void *, struct _XALLOC_ATTRIBUTES);
// public: virtual unsigned int c_buffer_allocation_override_xenon::allocation_size(void *, struct _XALLOC_ATTRIBUTES);
// void allocation_override_xenon_register(enum _XALLOC_ALLOCATOR_IDS, class c_allocation_override_xenon *);
// void allocation_override_xenon_deregister(enum _XALLOC_ALLOCATOR_IDS, class c_allocation_override_xenon *);
// float allocation_xenon_get_failure_chance(void);
// void allocation_xenon_set_failure_chance(float);
// void * XMemAlloc_baselib(unsigned long, unsigned long);
// void XMemFree_baselib(void *, unsigned long);
// unsigned long XMemSize_baselib(void *, unsigned long);
// public: static long s_static_array<struct s_xenon_xmemalloc_override, 4>::get_count(void);
// public: struct s_xenon_xmemalloc_override & s_static_array<struct s_xenon_xmemalloc_override, 4>::operator[]<long>(long);
// public: static bool s_static_array<struct s_xenon_xmemalloc_override, 4>::valid<long>(long);

c_buffer_allocation_override_xenon::c_buffer_allocation_override_xenon(unsigned int buffer_size, void * buffer)
{
    mangled_ppc("??0c_buffer_allocation_override_xenon@@QAA@IPAX@Z");

    m_buffer_size = buffer_size;
    m_buffer = buffer;
    m_offset = 0;
};

void * c_buffer_allocation_override_xenon::allocate(unsigned int size, XALLOC_ATTRIBUTES attributes)
{
    mangled_ppc("?allocate@c_buffer_allocation_override_xenon@@UAAPAXIU_XALLOC_ATTRIBUTES@@@Z");

    void * result = NULL;
    void * current = offset_pointer(m_buffer, m_offset);
    unsigned long address = address_from_pointer(current);

    assert_tag_debug_untracked_jul_11_2011(66, attributes.dwMemoryType == XALLOC_MEMTYPE_HEAP);
    assert_tag_debug_untracked_jul_11_2011(67, m_buffer);
    assert_tag_debug_untracked_jul_11_2011(68, m_buffer_size>0);

    address = (address + 15) & ~15;
    void * aligned = pointer_from_address(address);
    long new_offset = pointer_distance(m_buffer, aligned) + size;
    assert_tag_debug_untracked_jul_11_2011(75, new_offset>=0);

    if (new_offset <= m_buffer_size)
    {
        result = aligned;
        m_offset = new_offset;
    }
    else
    {
        event(_event_error, "memory:xenon: xmemalloc override failed to allocate %d bytes (buffer %d, currently allocated %d)", size, m_buffer_size, m_offset);
    }

    return result;
};

void c_buffer_allocation_override_xenon::deallocate(void * address, XALLOC_ATTRIBUTES attributes)
{
    mangled_ppc("?deallocate@c_buffer_allocation_override_xenon@@UAAXPAXU_XALLOC_ATTRIBUTES@@@Z");

    if (address == NULL)
    {
        return;
    }

    if (address >= m_buffer && address < offset_pointer(m_buffer, m_buffer_size))
    {
        return;
    }

    vassert_tag_debug_untracked_jul_11_2011(106, false, "memory:xenon: xmemalloc override trying to free invalid pointer@%p (buffer %d@%p, currently allocated %d)", address, m_buffer_size, m_buffer, m_offset);
};

unsigned int c_buffer_allocation_override_xenon::allocation_size(void * address, XALLOC_ATTRIBUTES attributes)
{
    mangled_ppc("?allocation_size@c_buffer_allocation_override_xenon@@UAAIPAXU_XALLOC_ATTRIBUTES@@@Z");

    return XMemSize_tracked(address, *reinterpret_cast<unsigned long *>(&attributes));
};

void allocation_override_xenon_register(XALLOC_ALLOCATOR_IDS allocator_id, c_allocation_override_xenon * override)
{
    mangled_ppc("?allocation_override_xenon_register@@YAXW4_XALLOC_ALLOCATOR_IDS@@PAVc_allocation_override_xenon@@@Z");

    long found_index = NONE;
    for (long override_index = 0; override_index < g_xenon_xmemalloc_globals.overrides.get_count(); override_index++)
    {
        if (g_xenon_xmemalloc_globals.overrides[override_index].override == NULL)
        {
            if (found_index == NONE)
            {
                found_index = override_index;
            }
        }
        else
        {
            assert_tag_debug_untracked_jul_11_2011(143, g_xenon_xmemalloc_globals.overrides[override_index].allocator_id!=allocator_id);
        }
    }

    vassert_tag_debug_untracked_jul_11_2011(148, g_xenon_xmemalloc_globals.overrides.valid(found_index), "exceeded maximum number of xmemalloc overrides (k_maximum_xmemalloc_overrides==%d)", k_maximum_xmemalloc_overrides);
    g_xenon_xmemalloc_globals.overrides[found_index].allocator_id = allocator_id;
    g_xenon_xmemalloc_globals.overrides[found_index].override = override;
};

void allocation_override_xenon_deregister(XALLOC_ALLOCATOR_IDS allocator_id, c_allocation_override_xenon * override)
{
    mangled_ppc("?allocation_override_xenon_deregister@@YAXW4_XALLOC_ALLOCATOR_IDS@@PAVc_allocation_override_xenon@@@Z");

    long found_index = NONE;
    for (long override_index = 0; override_index < g_xenon_xmemalloc_globals.overrides.get_count(); override_index++)
    {
        if (g_xenon_xmemalloc_globals.overrides[override_index].allocator_id == allocator_id)
        {
            assert_tag_debug_untracked_jul_11_2011(165, found_index==NONE);
            found_index = override_index;
            assert_tag_debug_untracked_jul_11_2011(168, g_xenon_xmemalloc_globals.overrides[override_index].override==override);
            g_xenon_xmemalloc_globals.overrides[override_index].override = NULL;
            g_xenon_xmemalloc_globals.overrides[override_index].allocator_id = eXALLOCAllocatorId_GameMin;
        }
    }

    dassert_tag_debug_untracked_jul_11_2011(174, found_index != NONE, "tried to deregister an unknown xmemalloc override");
};

// $TODO nonmatching: only diff is that the target object has no relocations for the 0.0f constant and the global (instruction bytes match)
float allocation_xenon_get_failure_chance(void)
{
    mangled_ppc("?allocation_xenon_get_failure_chance@@YAMXZ");

    float failure_chance = 0.0f;
    failure_chance = g_xenon_xmemalloc_globals.failure_chance;

    return failure_chance;
};

void allocation_xenon_set_failure_chance(float failure_chance)
{
    mangled_ppc("?allocation_xenon_set_failure_chance@@YAXM@Z");

    assert_tag_debug_untracked_jul_11_2011(193, IN_RANGE_INCLUSIVE(failure_chance, 0.0f, 1.0f));
    g_xenon_xmemalloc_globals.failure_chance = failure_chance;
};

void * XMemAlloc_baselib(unsigned long size, unsigned long attributes_value)
{
    mangled_ppc("?XMemAlloc_baselib@@YAPAXKK@Z");

    XALLOC_ATTRIBUTES * attributes = reinterpret_cast<XALLOC_ATTRIBUTES *>(&attributes_value);
    long allocator_id = attributes->dwAllocatorId;
    void * result = NULL;
    bool allow_allocation = true;

    if (g_xenon_xmemalloc_globals.failure_chance > 0.0f && false)
    {
        event(_event_message, "memory:xenon: simulating xmemalloc failure for %d bytes from id %d", size, allocator_id);
        allow_allocation = false;
    }

    if (allow_allocation)
    {
        bool found_override = false;
        for (long override_index = 0; override_index < g_xenon_xmemalloc_globals.overrides.get_count(); override_index++)
        {
            if (g_xenon_xmemalloc_globals.overrides[override_index].override != NULL && g_xenon_xmemalloc_globals.overrides[override_index].allocator_id == allocator_id)
            {
                assert_tag_debug_untracked_jul_11_2011(231, !found_override);
                result = g_xenon_xmemalloc_globals.overrides[override_index].override->allocate(size, *attributes);
                found_override = true;
            }
        }

        if (!found_override)
        {
            result = XMemAlloc_tracked(size, attributes_value);
        }
    }

    event(_event_verbose, "memory:xenon: xmemalloc %s %d bytes at location 0x%08X w/ attributes: dwObjectType %d, dwHeapTracksAttributes %d, dwMustSucceed %d, dwFixedSize %d, dwAllocatorId %d, dwAlignment %d, dwMemoryProtect %d, dwZeroInitialize %d, dwMemoryType %d",
        result == NULL ? "FAILED for" : "allocating",
        size,
        result,
        attributes->dwObjectType,
        attributes->dwHeapTracksAttributes,
        attributes->dwMustSucceed,
        attributes->dwFixedSize,
        attributes->dwAllocatorId,
        attributes->dwAlignment,
        attributes->dwMemoryProtect,
        attributes->dwZeroInitialize,
        attributes->dwMemoryType);

    return result;
};

void XMemFree_baselib(void * address, unsigned long attributes_value)
{
    mangled_ppc("?XMemFree_baselib@@YAXPAXK@Z");

    XALLOC_ATTRIBUTES * attributes = reinterpret_cast<XALLOC_ATTRIBUTES *>(&attributes_value);
    long allocator_id = attributes->dwAllocatorId;
    bool found_override = false;

    for (long override_index = 0; override_index < g_xenon_xmemalloc_globals.overrides.get_count(); override_index++)
    {
        if (g_xenon_xmemalloc_globals.overrides[override_index].override != NULL && g_xenon_xmemalloc_globals.overrides[override_index].allocator_id == allocator_id)
        {
            assert_tag_debug_untracked_jul_11_2011(269, !found_override);
            found_override = true;
            g_xenon_xmemalloc_globals.overrides[override_index].override->deallocate(address, *attributes);
        }
    }

    if (!found_override)
    {
        XMemFree_tracked(address, attributes_value);
    }

    event(_event_verbose, "memory:xenon: xmemalloc freeing location 0x%08X w/ attributes: dwObjectType %d, dwHeapTracksAttributes %d, dwMustSucceed %d, dwFixedSize %d, dwAllocatorId %d, dwAlignment %d, dwMemoryProtect %d, dwZeroInitialize %d, dwMemoryType %d",
        address,
        attributes->dwObjectType,
        attributes->dwHeapTracksAttributes,
        attributes->dwMustSucceed,
        attributes->dwFixedSize,
        attributes->dwAllocatorId,
        attributes->dwAlignment,
        attributes->dwMemoryProtect,
        attributes->dwZeroInitialize,
        attributes->dwMemoryType);
};

unsigned long XMemSize_baselib(void * address, unsigned long attributes_value)
{
    mangled_ppc("?XMemSize_baselib@@YAKPAXK@Z");

    XALLOC_ATTRIBUTES * attributes = reinterpret_cast<XALLOC_ATTRIBUTES *>(&attributes_value);
    long allocator_id = attributes->dwAllocatorId;
    bool found_override = false;
    unsigned long result = 0;

    for (long override_index = 0; override_index < g_xenon_xmemalloc_globals.overrides.get_count(); override_index++)
    {
        if (g_xenon_xmemalloc_globals.overrides[override_index].override != NULL && g_xenon_xmemalloc_globals.overrides[override_index].allocator_id == allocator_id)
        {
            assert_tag_debug_untracked_jul_11_2011(305, !found_override);
            found_override = true;
            result = g_xenon_xmemalloc_globals.overrides[override_index].override->allocation_size(address, *attributes);
            break;
        }
    }

    if (!found_override)
    {
        result = XMemSize_tracked(address, attributes_value);
    }

    return result;
};

