#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\foundation\\baselib\\memory\\base\\base_memory_windows.cpp"
/* ---------- headers */

#include "foundation\baselib\memory\base\base_memory_windows.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_events.h"
#include "core\corelib\cseries\cseries_macros.h"
#include "core\corelib\cseries\cseries_memory.h"
#include "foundation\baselib\memory\debug_memory\debug_memory_globals.h"
#include "foundation\baselib\multithreading\datatypes\initialization_lock.h"
#include <xtl.h>
#include <xbdm.h>

/* ---------- constants */

// allocations come from the process heap (or the devkit expanded heap); the VirtualAlloc path is compiled but disabled
bool const k_base_memory_use_process_heap = true;
// guard pages around VirtualAlloc allocations
bool const k_base_memory_use_guard_pages = false;

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

static t_initialization_lock<s_base_memory_globals> g_base_memory_globals;

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// long base_memory_get_alignment_bits(void);
// void base_heap_validate(void);
// void * base_malloc(unsigned int);
// void base_free(void *);
// void * base_realloc(void *, unsigned int);
// unsigned int base_memory_get_used_memory_size(void const *);
// void base_memory_information_get(struct s_base_memory_information *);
// enum e_base_memory_expanded_heap_status base_memory_get_expanded_heap_status(void);
// bool expanded_heap_initialized(void);
// bool expanded_heap_available(void);
// bool expanded_heap_initialize(void);
// unsigned int base_memory_get_page_size(void);
// unsigned int base_memory_get_used_memory_size_internal(void *);
// public: struct s_base_memory_globals const * t_initialization_lock<struct s_base_memory_globals>::get_const(void) const;
// public: struct s_base_memory_globals * t_initialization_lock<struct s_base_memory_globals>::get_writable(void);

long base_memory_get_alignment_bits(void)
{
    mangled_ppc("?base_memory_get_alignment_bits@@YAJXZ");

    long alignment_bits = 0;
    if (k_base_memory_use_process_heap)
    {
        alignment_bits = 4;
    }
    else
    {
        alignment_bits = 12;
    }
    assert_tag_debug_untracked_jul_11_2011(121, alignment_bits>0);

    return alignment_bits;
};

void base_heap_validate(void)
{
    mangled_ppc("?base_heap_validate@@YAXXZ");

    assert_tag_debug_untracked_jul_11_2011(131, HeapValidate(GetProcessHeap(), 0, NULL));
};

void * base_malloc(unsigned int size)
{
    mangled_ppc("?base_mallocYAPAXI@Z");

    void * result = NULL;
    assert_tag_debug_untracked_jul_11_2011(142, size>=0);

    if (k_base_memory_use_process_heap)
    {
        if (expanded_heap_available())
        {
            result = DmDebugAlloc(size);
        }
        else
        {
            result = HeapAlloc(GetProcessHeap(), 0, size);
        }
    }
    else
    {
        DWORD const allocation_flags = MEM_TOP_DOWN;
        DWORD const protection_flags = PAGE_READWRITE;
        DWORD const commit_flags = MEM_COMMIT;
        unsigned int guard_page_size = base_memory_get_page_size();
        unsigned int guard_total_size;
        unsigned int interior_allocation_size;
        void * base_pointer;

        guard_total_size = 0;
        interior_allocation_size = size;
        if (k_base_memory_use_guard_pages)
        {
            guard_total_size = guard_page_size * 2;
            interior_allocation_size = (size + (guard_page_size - 1)) & ~(guard_page_size - 1);
        }

        base_pointer = VirtualAlloc(NULL, interior_allocation_size + guard_total_size, allocation_flags | commit_flags, protection_flags);
        if (base_pointer)
        {
            if (k_base_memory_use_guard_pages)
            {
                result = offset_pointer(base_pointer, guard_page_size);
                result = VirtualAlloc(result, interior_allocation_size, commit_flags, protection_flags);
            }
            else
            {
                result = base_pointer;
            }

            if (result)
            {
                assert_tag_debug_untracked_jul_11_2011(193, base_memory_get_used_memory_size(result)>=interior_allocation_size);
            }
        }
        else
        {
            DWORD error = GetLastError();
        }

        if (!result && base_pointer)
        {
            VirtualFree(base_pointer, 0, MEM_RELEASE);
        }
    }

    return result;
};

void base_free(void * pointer)
{
    mangled_ppc("?base_free@@YAXPAX@Z");

    void * base_pointer = pointer;
    unsigned int guard_page_size = base_memory_get_page_size();
    if (pointer)
    {
        if (k_base_memory_use_guard_pages)
        {
            base_pointer = offset_pointer(base_pointer, -static_cast<long>(guard_page_size));
        }

        if (k_base_memory_use_process_heap)
        {
            if (expanded_heap_initialized())
            {
                DmDebugFree(pointer);
            }
            else
            {
                HeapFree(GetProcessHeap(), 0, base_pointer);
            }
        }
        else
        {
            BOOL success = VirtualFree(base_pointer, 0, MEM_RELEASE);
            if (!success)
            {
                DWORD error = GetLastError();
            }
        }
    }
};

void * base_realloc(void * pointer, unsigned int size)
{
    mangled_ppc("?base_realloc@@YAPAXPAXI@Z");

    void * result = NULL;
    unsigned int guard_page_size = base_memory_get_page_size();
    if (size > 0 && pointer && !expanded_heap_initialized())
    {
        void * base_pointer = pointer;
        unsigned int allocation_size = size;
        if (k_base_memory_use_guard_pages)
        {
            allocation_size = (allocation_size + (guard_page_size - 1)) & ~(guard_page_size - 1);
            allocation_size += guard_page_size * 2;
        }

        if (k_base_memory_use_guard_pages)
        {
            base_pointer = offset_pointer(base_pointer, -static_cast<long>(guard_page_size));
        }

        if (k_base_memory_use_process_heap)
        {
            result = HeapReAlloc(GetProcessHeap(), 0, base_pointer, size);
        }
        else
        {
            MEMORY_BASIC_INFORMATION memory_basic_information;
            VirtualQuery(base_pointer, &memory_basic_information, sizeof(memory_basic_information));
            if (allocation_size == memory_basic_information.RegionSize)
            {
                result = base_pointer;
            }
        }

        if (k_base_memory_use_guard_pages)
        {
            result = offset_pointer(result, guard_page_size);
        }
    }

    if (!result)
    {
        if (size > 0)
        {
            void * new_pointer = base_malloc(size);
            if (pointer && new_pointer)
            {
                unsigned int used_size = base_memory_get_used_memory_size(pointer);
                csmemcpy_inline(new_pointer, pointer, int_min(used_size, size));
            }

            result = new_pointer;
            if (result)
            {
                base_free(pointer);
            }
        }
        else if (pointer)
        {
            base_free(pointer);
        }
    }

    return result;
};

unsigned int base_memory_get_used_memory_size(void const * pointer)
{
    mangled_ppc("?base_memory_get_used_memory_size@@YAIPBX@Z");

    unsigned int result = 0;
    if (pointer)
    {
        void * base_pointer = const_cast<void *>(pointer);
        unsigned int guard_page_size = base_memory_get_page_size();
        if (k_base_memory_use_guard_pages)
        {
            base_pointer = offset_pointer(base_pointer, -static_cast<long>(guard_page_size));
        }

        result = base_memory_get_used_memory_size_internal(base_pointer);
    }

    return result;
};

void base_memory_information_get(s_base_memory_information * information)
{
    mangled_ppc("?base_memory_information_get@@YAXPAUs_base_memory_information@@@Z");

    csmemset(information, 0, sizeof(*information));

    s_debug_memory_information debug_information;
    debug_memory_get_memory_information(&debug_information);
    information->tracked_heap_allocations = debug_information.current_heap_size;
    information->tracked_nonheap_allocations = debug_information.current_nonheap_size;

    if (k_base_memory_use_process_heap)
    {
        MEMORYSTATUS memory_status;
        csmemset(&memory_status, 0, sizeof(memory_status));
        memory_status.dwLength = sizeof(memory_status);
        GlobalMemoryStatus(&memory_status);
        information->free = memory_status.dwAvailPhys;
        information->total = memory_status.dwTotalPhys;
    }
    else
    {
        information->free = 0x20000000;
        information->total = 0x40000000;
    }
};

e_base_memory_expanded_heap_status base_memory_get_expanded_heap_status(void)
{
    mangled_ppc("?base_memory_get_expanded_heap_status@@YA?AW4e_base_memory_expanded_heap_status@@XZ");

    s_base_memory_globals const * base_memory_globals = g_base_memory_globals.get_const();
    return base_memory_globals->expanded_heap_status;
};

bool expanded_heap_initialized(void)
{
    mangled_ppc("?expanded_heap_initialized@@YA_NXZ");

    s_base_memory_globals const * base_memory_globals = g_base_memory_globals.get_const();
    return base_memory_globals->expanded_heap_status == _base_memory_expanded_heap_available;
};

bool expanded_heap_available(void)
{
    mangled_ppc("?expanded_heap_available@@YA_NXZ");

    s_base_memory_globals const * base_memory_globals = g_base_memory_globals.get_const();
    if (base_memory_globals->expanded_heap_status == _base_memory_expanded_heap_uninitialized)
    {
        s_base_memory_globals * writable_base_memory_globals = g_base_memory_globals.get_writable();
        if (expanded_heap_initialize())
        {
            writable_base_memory_globals->expanded_heap_status = _base_memory_expanded_heap_available;
            event(_event_message, "memory:base: expanded heap initialized");
        }
        else
        {
            writable_base_memory_globals->expanded_heap_status = _base_memory_expanded_heap_unavailable;
            event(_event_message, "memory:base: expanded heap is unavailable");
        }
    }

    return base_memory_globals->expanded_heap_status == _base_memory_expanded_heap_available;
};

bool expanded_heap_initialize(void)
{
    mangled_ppc("?expanded_heap_initialize@@YA_NXZ");

    DWORD console_info;
    bool result = false;
    if (DmGetConsoleType(&console_info) == XBDM_NOERR && console_info == DMCT_DEVELOPMENT_KIT &&
        DmGetConsoleFeatures(&console_info) == XBDM_NOERR && (console_info & 0x4) != 0 &&
        DmGetDebugMemorySize(&console_info) == XBDM_NOERR && console_info > 384)
    {
        result = true;
    }

    return result;
};

unsigned int base_memory_get_page_size(void)
{
    mangled_ppc("?base_memory_get_page_size@@YAIXZ");

    unsigned int size = 0;
    size = 0x10000;
    assert_tag_debug_untracked_jul_11_2011(510, size>0);

    return size;
};

unsigned int base_memory_get_used_memory_size_internal(void * pointer)
{
    mangled_ppc("?base_memory_get_used_memory_size_internal@@YAIPAX@Z");

    unsigned int result = 0;
    unsigned int guard_page_size = base_memory_get_page_size();
    if (k_base_memory_use_process_heap)
    {
        result = HeapSize(GetProcessHeap(), 0, pointer);
    }
    else if (k_base_memory_use_guard_pages)
    {
        unsigned int structure_size;
        MEMORY_BASIC_INFORMATION memory_basic_information;
        void * local_pointer = pointer;

        structure_size = VirtualQuery(local_pointer, &memory_basic_information, sizeof(memory_basic_information));
        assert_tag_debug_untracked_jul_11_2011(535, structure_size==sizeof(memory_basic_information));
        assert_tag_debug_untracked_jul_11_2011(536, memory_basic_information.RegionSize==guard_page_size);
        assert_tag_debug_untracked_jul_11_2011(537, memory_basic_information.State==MEM_RESERVE);

        local_pointer = offset_pointer(local_pointer, guard_page_size);
        structure_size = VirtualQuery(local_pointer, &memory_basic_information, sizeof(memory_basic_information));
        assert_tag_debug_untracked_jul_11_2011(545, structure_size==sizeof(memory_basic_information));
        assert_tag_debug_untracked_jul_11_2011(546, memory_basic_information.State==MEM_COMMIT);
        assert_tag_debug_untracked_jul_11_2011(547, memory_basic_information.BaseAddress==local_pointer);
        result = memory_basic_information.RegionSize;

        local_pointer = offset_pointer(local_pointer, memory_basic_information.RegionSize);
        structure_size = VirtualQuery(local_pointer, &memory_basic_information, sizeof(memory_basic_information));
        assert_tag_debug_untracked_jul_11_2011(556, structure_size==sizeof(memory_basic_information));
        assert_tag_debug_untracked_jul_11_2011(557, memory_basic_information.RegionSize==guard_page_size);
        assert_tag_debug_untracked_jul_11_2011(558, memory_basic_information.State==MEM_RESERVE);
    }
    else
    {
        MEMORY_BASIC_INFORMATION memory_basic_information;
        unsigned int structure_size = VirtualQuery(pointer, &memory_basic_information, sizeof(memory_basic_information));
        assert_tag_debug_untracked_jul_11_2011(566, structure_size==sizeof(memory_basic_information));
        result = memory_basic_information.RegionSize;
    }

    return result;
};
