#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\memory\\wrapped_arrays.cpp"
/* ---------- headers */

#include "omaha\memory\wrapped_arrays.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_macros.h"
#include "foundation\baselib\memory\allocation_interface.h"
#include "foundation\baselib\memory\debug_memory\debug_memory_globals.h"

#include <string.h>

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// class c_basic_buffer<void> allocate_scratch_buffer(class c_allocation_interface *, unsigned long);
// class c_basic_buffer<void> allocate_tracked_scratch_buffer(class c_allocation_interface *, unsigned long, char const *);
// void free_scratch_buffer(class c_allocation_interface *, class c_basic_buffer<void> *);
// bool address_in_buffer(void const *, class c_basic_buffer<void const>);
// bool buffer_in_buffer(class c_basic_buffer<void const>, class c_basic_buffer<void const>);
// bool buffer_contents_equal(class c_basic_buffer<void const>, class c_basic_buffer<void const>);
// void copy_buffer(class c_basic_buffer<void>, class c_basic_buffer<void const>);
// void move_buffer(class c_basic_buffer<void>, class c_basic_buffer<void const>);

c_basic_buffer<void> allocate_scratch_buffer(c_allocation_interface * allocator, unsigned long size)
{
    mangled_ppc("?allocate_scratch_buffer@@YA?AV?$c_basic_buffer@X@@PAVc_allocation_interface@@K@Z");

    return allocate_tracked_scratch_buffer(allocator, size, NULL);
};

c_basic_buffer<void> allocate_tracked_scratch_buffer(c_allocation_interface * allocator, unsigned long size, char const * name)
{
    mangled_ppc("?allocate_tracked_scratch_buffer@@YA?AV?$c_basic_buffer@X@@PAVc_allocation_interface@@KPBD@Z");

    c_basic_buffer<void> scratch_buffer(allocator->allocate(size, __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__, 22, NULL, NULL, name), size);
    if (!(scratch_buffer.empty() || scratch_buffer.begin()))
    {
        debug_notify_out_of_memory(__FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__, 24);
        assert_tag_debug_untracked_jul_11_2011(24, scratch_buffer.empty() || scratch_buffer.begin());
    }

    return scratch_buffer;
};

void free_scratch_buffer(c_allocation_interface * allocator, c_basic_buffer<void> * buffer)
{
    mangled_ppc("?free_scratch_buffer@@YAXPAVc_allocation_interface@@PAV?$c_basic_buffer@X@@@Z");

    assert_tag_debug_untracked_jul_11_2011(31, buffer);

    allocator->deallocate(buffer->begin(), __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__, 32);
    buffer->clear();
};

bool address_in_buffer(void const * address, c_basic_buffer<void const> buffer)
{
    mangled_ppc("?address_in_buffer@@YA_NPBXV?$c_basic_buffer@$$CBX@@@Z");

    return address >= buffer.begin() && address <= buffer.end();
};

bool buffer_in_buffer(c_basic_buffer<void const> inner_buffer, c_basic_buffer<void const> outer_buffer)
{
    mangled_ppc("?buffer_in_buffer@@YA_NV?$c_basic_buffer@$$CBX@@0@Z");

    return inner_buffer.begin() >= outer_buffer.begin() && inner_buffer.begin() <= outer_buffer.end() && inner_buffer.end() >= outer_buffer.begin() && inner_buffer.end() <= outer_buffer.end();
};

bool buffer_contents_equal(c_basic_buffer<void const> lhs_buffer, c_basic_buffer<void const> rhs_buffer)
{
    mangled_ppc("?buffer_contents_equal@@YA_NV?$c_basic_buffer@$$CBX@@0@Z");

    return lhs_buffer.size() == rhs_buffer.size() && memcmp(lhs_buffer.begin(), rhs_buffer.begin(), lhs_buffer.size()) == 0;
};

void copy_buffer(c_basic_buffer<void> dest_buffer, c_basic_buffer<void const> source_buffer)
{
    mangled_ppc("?copy_buffer@@YAXV?$c_basic_buffer@X@@V?$c_basic_buffer@$$CBX@@@Z");

    assert_tag_debug_untracked_jul_11_2011(65, dest_buffer.size()==source_buffer.size());
    memcpy(dest_buffer.begin(), source_buffer.begin(), source_buffer.size());
};

void move_buffer(c_basic_buffer<void> dest_buffer, c_basic_buffer<void const> source_buffer)
{
    mangled_ppc("?move_buffer@@YAXV?$c_basic_buffer@X@@V?$c_basic_buffer@$$CBX@@@Z");

    assert_tag_debug_untracked_jul_11_2011(76, dest_buffer.size()==source_buffer.size());
    memmove(dest_buffer.begin(), source_buffer.begin(), source_buffer.size());
};

