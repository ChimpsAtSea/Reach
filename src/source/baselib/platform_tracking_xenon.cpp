/* ---------- headers */

#include "baselib\platform_tracking_xenon.h"
#include "core\corelib\cseries\cseries_events.h"
#include "core\corelib\cseries\cseries_macros.h"
#include "foundation\baselib\memory\debug_memory\debug_memory_allocators.h"
#include "foundation\baselib\memory\debug_memory\debug_memory_globals.h"
#include "foundation\baselib\multithreading\primitives\thread_local_storage.h"
#include "omaha\cseries\cseries.h"

#include <xtl.h>

/* ---------- constants */

/* ---------- definitions */

struct s_platform_memory_tracking_thread_globals
{
    bool tracking_enabled;
    long line;
    char const * file;
    char const * consumer;
};
static_assert(sizeof(s_platform_memory_tracking_thread_globals) == 0x10, "s_platform_memory_tracking_thread_globals");

/* ---------- prototypes */

/* ---------- globals */

static __declspec(thread) s_platform_memory_tracking_thread_globals g_platform_memory_tracking_thread_globals;

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// void debug_platform_memory_consumer(char const *, char const *, long);
// void debug_platform_memory_tracking_thread_enable(bool);
// void * XMemAlloc_tracked(unsigned long, unsigned long);
// void XMemFree_tracked(void *, unsigned long);
// unsigned long XMemSize_tracked(void *, unsigned long);
// bool xenon_allocator_tracking_enabled(void);
// char const * xenon_allocator_type(unsigned long, unsigned long);

void debug_platform_memory_consumer(char const * consumer, char const * file, long line)
{
    mangled_ppc("?debug_platform_memory_consumer@@YAXPBD0J@Z");
    TLS_DATA_GET_VALUE_REFERENCE(g_platform_memory_tracking_thread_globals).consumer = consumer;
    TLS_DATA_GET_VALUE_REFERENCE(g_platform_memory_tracking_thread_globals).file = file;
    TLS_DATA_GET_VALUE_REFERENCE(g_platform_memory_tracking_thread_globals).line = line;
};

void debug_platform_memory_tracking_thread_enable(bool enable)
{
    mangled_ppc("?debug_platform_memory_tracking_thread_enable@@YAX_N@Z");
    TLS_DATA_GET_VALUE_REFERENCE(g_platform_memory_tracking_thread_globals).tracking_enabled = enable;
};

void * XMemAlloc_tracked(unsigned long size, unsigned long attributes)
{
    mangled_ppc("?XMemAlloc_tracked@@YAPAXKK@Z");
    XALLOC_ATTRIBUTES xalloc_attributes = *reinterpret_cast<XALLOC_ATTRIBUTES *>(&attributes);
    char const * allocator_type = xenon_allocator_type(xalloc_attributes.dwAllocatorId, xalloc_attributes.dwObjectType);
    void * block = XMemAllocDefault(size, attributes);
    event(_event_message, "memory:platform:xenon: XMemAlloc %s %s(%d) %ld (really %ld) at 0x%08X",
        xenon_allocator_tracking_enabled() ? "tracked" : "UNTRACKED",
        allocator_type,
        xalloc_attributes.dwObjectType,
        size,
        block != NULL ? XMemSize(block, attributes) : 0,
        block);
    if (block != NULL && xenon_allocator_tracking_enabled())
    {
        unsigned long actual_size = XMemSizeDefault(block, attributes);
        char const * file = TLS_DATA_GET_VALUE_REFERENCE(g_platform_memory_tracking_thread_globals).file;
        long line = TLS_DATA_GET_VALUE_REFERENCE(g_platform_memory_tracking_thread_globals).line;
        char const * subtype = TLS_DATA_GET_VALUE_REFERENCE(g_platform_memory_tracking_thread_globals).consumer;
        if (file == NULL || *file == '\0')
        {
            file = allocator_type;
            line = 0;
        }
        debug_track_nonheap_alloc(block, actual_size, static_cast<e_debug_memory_flags>(0), file, line, NONE, allocator_type, subtype, "");
    }
    return block;
};

void XMemFree_tracked(void * address, unsigned long attributes)
{
    mangled_ppc("?XMemFree_tracked@@YAXPAXK@Z");
    if (address != NULL)
    {
        XALLOC_ATTRIBUTES xalloc_attributes = *reinterpret_cast<XALLOC_ATTRIBUTES *>(&attributes);
        char const * allocator_type = xenon_allocator_type(xalloc_attributes.dwAllocatorId, xalloc_attributes.dwObjectType);
        event(_event_message, "memory:platform:xenon: XMemFree %s %s(%d) (really %ld) at 0x%08X",
            xenon_allocator_tracking_enabled() ? "tracked" : "UNTRACKED",
            allocator_type,
            xalloc_attributes.dwObjectType,
            XMemSize(address, attributes),
            address);
    }
    XMemFreeDefault(address, attributes);
    if (address != NULL && xenon_allocator_tracking_enabled())
    {
        debug_track_nonheap_free(address, TLS_DATA_GET_VALUE_REFERENCE(g_platform_memory_tracking_thread_globals).file, TLS_DATA_GET_VALUE_REFERENCE(g_platform_memory_tracking_thread_globals).line);
    }
};

unsigned long XMemSize_tracked(void * address, unsigned long attributes)
{
    mangled_ppc("?XMemSize_tracked@@YAKPAXK@Z");
    unsigned long size = XMemSizeDefault(address, attributes);
    return size;
};

bool xenon_allocator_tracking_enabled(void)
{
    mangled_ppc("?xenon_allocator_tracking_enabled@@YA_NXZ");
    return TLS_DATA_GET_VALUE_REFERENCE(g_platform_memory_tracking_thread_globals).tracking_enabled;
};

char const * xenon_allocator_type(unsigned long allocator_id, unsigned long object_type)
{
    mangled_ppc("?xenon_allocator_type@@YAPBDKK@Z");
    char const * type = "<unknown xmemory-alloc>";
    switch (allocator_id)
    {
    case eXALLOCAllocatorId_D3D:
        type = "D3D";
        break;
    case eXALLOCAllocatorId_D3DX:
        type = "D3DX";
        break;
    case eXALLOCAllocatorId_XAUDIO:
        type = "XAUDIO";
        break;
    case eXALLOCAllocatorId_XAUDIO2:
        type = "XAUDIO2";
        break;
    case eXALLOCAllocatorId_XAPI:
        type = "XAPI";
        break;
    case eXALLOCAllocatorId_XACT:
        type = "XACT";
        break;
    case eXALLOCAllocatorId_XBOXKERNEL:
        type = "XBOXKERNEL";
        break;
    case eXALLOCAllocatorId_XBDM:
        type = "XBDM";
        break;
    case eXALLOCAllocatorId_XGRAPHICS:
        type = "XGRAPHICS";
        break;
    case eXALLOCAllocatorId_XONLINE:
        type = "XONLINE";
        break;
    case eXALLOCAllocatorId_XVOICE:
        type = "XVOICE";
        break;
    case eXALLOCAllocatorId_XHV:
        type = "XHV";
        break;
    case eXALLOCAllocatorId_USB:
        type = "USB";
        break;
    case eXALLOCAllocatorId_XMV:
        type = "XMV";
        break;
    case eXALLOCAllocatorId_SHADERCOMPILER:
        type = "shader compiler";
        break;
    case eXALLOCAllocatorId_XUI:
        type = "XUI";
        break;
    case eXALLOCAllocatorId_XASYNC:
        type = "XASYNC";
        break;
    case eXALLOCAllocatorId_XCAM:
        type = "XCAM";
        break;
    }
    return type;
};
