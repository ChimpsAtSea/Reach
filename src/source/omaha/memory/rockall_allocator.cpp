#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\memory\\rockall_allocator.cpp"
/* ---------- headers */

#include "omaha\memory\rockall_allocator.h"
#include "omaha\memory\rockall_heap.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_macros.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// public: c_rockall_allocator::c_rockall_allocator(class c_rockall_heap *);
// public: virtual void * c_rockall_allocator::allocate(unsigned int, char const *, long, char const *, char const *, char const *);
// public: virtual void c_rockall_allocator::deallocate(void *, char const *, long);

c_rockall_allocator::c_rockall_allocator(c_rockall_heap * rockall_heap) :
    m_rockall_heap(rockall_heap)
{
    mangled_ppc("??0c_rockall_allocator@@QAA@PAVc_rockall_heap@@@Z");

    assert_tag_debug_untracked_jul_11_2011(8, m_rockall_heap);
};

void * c_rockall_allocator::allocate(unsigned int size, char const * file, long line, char const * type, char const * subtype, char const * name)
{
    mangled_ppc("?allocate@c_rockall_allocator@@UAAPAXIPBDJ000@Z");

    assert_tag_debug_untracked_jul_11_2011(19, m_rockall_heap);

    return m_rockall_heap->allocate(size);
};

void c_rockall_allocator::deallocate(void * pointer, char const * file, long line)
{
    mangled_ppc("?deallocate@c_rockall_allocator@@UAAXPAXPBDJ@Z");

    m_rockall_heap->deallocate(pointer);
};

