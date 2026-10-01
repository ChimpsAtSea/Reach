#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\foundation\\baselib\\memory\\platform\\platform_memory_windows.cpp"
/* ---------- headers */

#include "foundation\baselib\memory\platform\platform_memory_windows.h"
#include "foundation\baselib\memory\memory_interface.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_events.h"
#include "core\corelib\cseries\cseries_macros.h"
#include "core\corelib\cseries\cseries_memory.h"

#include <xtl.h>

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// bool memory_is_bad_read_pointer(void const *, unsigned int);
// void memory_set_protection(void *, unsigned int, enum e_memory_protection);

bool memory_is_bad_read_pointer(void const * pointer, unsigned int size)
{
    mangled_ppc("?memory_is_bad_read_pointer@@YA_NPBXI@Z");

    bool result = false;
    result = IsBadReadPtr(pointer, size) != FALSE;

    return result;
};

void memory_set_protection(void * address, unsigned int size, e_memory_protection protection)
{
    mangled_ppc("?memory_set_protection@@YAXPAXIW4e_memory_protection@@@Z");

    unsigned long protection_flags;

    assert_tag_debug_untracked_jul_11_2011(38, VALID_INDEX(protection, k_memory_protection_count));
    assert_tag_debug_untracked_jul_11_2011(39, size>=0);
    assert_tag_debug_untracked_jul_11_2011(40, (size&k_physical_memory_page_mask)==0);

    if (size > 0)
    {
        bool is_physical_address = memory_is_physical_address(address);
        protection_flags = 0;

        assert_tag_debug_untracked_jul_11_2011(47, (address_from_pointer(address)&k_physical_memory_page_mask)==0);

        switch (protection)
        {
        case _memory_protection_noaccess:
            if (is_physical_address)
            {
                // physical memory cannot be made inaccessible
            }
            else
            {
                protection_flags = PAGE_NOACCESS;
                break;
            }
        case _memory_protection_readonly:
            protection_flags = PAGE_READONLY;
            break;
        case _memory_protection_readwrite:
            protection_flags = PAGE_READWRITE;
            break;
        default:
            dassert_tag_debug_untracked_jul_11_2011(69, false, "unreachable");
            break;
        }

        if (is_physical_address)
        {
            XPhysicalProtect(address, size, protection_flags);
        }
        else
        {
            unsigned long old_protection;
            if (VirtualProtect(address, size, protection_flags, &old_protection))
            {
                // success
            }
            else
            {
                event(_event_error, "memory:platform:windows: VirtualProtect %d@%p failed", size, address);
            }
        }
    }
};

