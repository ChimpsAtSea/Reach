#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\foundation\\baselib\\algorithms\\binary_search.cpp"
/* ---------- headers */

#include "foundation\baselib\algorithms\binary_search.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_memory.h"
#include "omaha\cseries\cseries.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// ?binary_search_4byte@@YAJJPBJJQ6AJJJPBX@Z1@Z;
// ?binary_search_elements@@YAJPBX0JIQ6AJ000@Z0@Z;

long binary_search_4byte(long key_val, long const * base, long count, long (* const compare)(long, long, void const *), void const * compare_data)
{
    mangled_ppc("?binary_search_4byte@@YAJJPBJJQ6AJJJPBX@Z1@Z");

    long limit;
    long cmp_val;
    long const key = key_val;
    long const * base_ptr = base;
    long const * ptr;

    for (limit = count; limit != 0; limit >>= 1)
    {
        ptr = base_ptr + (limit >> 1);
        cmp_val = compare(key, *ptr, compare_data);
        if (cmp_val == 0)
        {
            assert_tag_debug_untracked_jul_11_2011(70, ptr>=base && ptr<base+count);
            return pointer_distance32(base, ptr) / sizeof(long);
        }
        else if (cmp_val > 0)
        {
            base_ptr = ptr + 1;
            limit--;
        }
    }

    return NONE;
};

long binary_search_elements(void const * key_val, void const * base, long count, unsigned int element_size, long (* const compare)(void const *, void const *, void const *), void const * compare_data)
{
    mangled_ppc("?binary_search_elements@@YAJPBX0JIQ6AJ000@Z0@Z");

    long limit;
    long cmp_val;
    unsigned char const * base_ptr = static_cast<unsigned char const *>(base);
    unsigned char const * ptr;

    for (limit = count; limit != 0; limit >>= 1)
    {
        ptr = base_ptr + (limit >> 1) * element_size;
        cmp_val = compare(key_val, ptr, compare_data);
        if (cmp_val == 0)
        {
            assert_tag_debug_untracked_jul_11_2011(142, ptr>=base && ptr<base_ptr+count*element_size);
            return pointer_distance(base, ptr) / element_size;
        }
        else if (cmp_val > 0)
        {
            base_ptr = ptr + element_size;
            limit--;
        }
    }

    return NONE;
};

