#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\foundation\\baselib\\memory\\allocation_interface.cpp"
/* ---------- headers */

#include "foundation\baselib\memory\allocation_interface.h"
#include "foundation\baselib\memory\base\base_memory_windows.h"
#include "foundation\baselib\memory\debug_memory\debug_memory_allocators.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "omaha\cseries\cseries.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

static c_base_allocation g_base_allocation_instance;
static c_heap_allocation g_heap_allocation_instance;
static c_null_allocation g_null_allocation_instance;

c_base_allocation * g_base_allocation = &g_base_allocation_instance;
c_heap_allocation * g_heap_allocation = &g_heap_allocation_instance;
c_null_allocation * g_null_allocation = &g_null_allocation_instance;

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// class c_base_allocation *g_base_allocation; // "?g_base_allocation@@3PAVc_base_allocation@@A"
// class c_heap_allocation *g_heap_allocation; // "?g_heap_allocation@@3PAVc_heap_allocation@@A"
// class c_null_allocation *g_null_allocation; // "?g_null_allocation@@3PAVc_null_allocation@@A"

// public: virtual void * c_base_allocation::allocate(unsigned int, char const *, long, char const *, char const *, char const *);
// public: virtual void c_base_allocation::deallocate(void *, char const *, long);
// public: virtual void * c_heap_allocation::allocate(unsigned int, char const *, long, char const *, char const *, char const *);
// public: virtual void c_heap_allocation::deallocate(void *, char const *, long);
// public: virtual void * c_null_allocation::allocate(unsigned int, char const *, long, char const *, char const *, char const *);
// public: virtual void c_null_allocation::deallocate(void *, char const *, long);
// public: c_base_allocation::c_base_allocation(void);
// public: c_heap_allocation::c_heap_allocation(void);
// public: c_null_allocation::c_null_allocation(void);

void * c_base_allocation::allocate(unsigned int size, char const * file, long line, char const * type, char const * subtype, char const * name)
{
    mangled_ppc("?allocate@c_base_allocation@@UAAPAXIPBDJ000@Z");

    return base_malloc(size);
};

void c_base_allocation::deallocate(void * pointer, char const * file, long line)
{
    mangled_ppc("?deallocate@c_base_allocation@@UAAXPAXPBDJ@Z");

    base_free(pointer);
};

void * c_heap_allocation::allocate(unsigned int size, char const * file, long line, char const * type, char const * subtype, char const * name)
{
    mangled_ppc("?allocate@c_heap_allocation@@UAAPAXIPBDJ000@Z");

    return debug_malloc(size, static_cast<e_debug_memory_flags>(0), file, line, NONE, type, subtype, name);
};

void c_heap_allocation::deallocate(void * pointer, char const * file, long line)
{
    mangled_ppc("?deallocate@c_heap_allocation@@UAAXPAXPBDJ@Z");

    debug_free(pointer, file, line);
};

void * c_null_allocation::allocate(unsigned int size, char const * file, long line, char const * type, char const * subtype, char const * name)
{
    mangled_ppc("?allocate@c_null_allocation@@UAAPAXIPBDJ000@Z");

    dassert_tag_debug_untracked_jul_11_2011(91, false, "g_null_allocation::allocate");

    return NULL;
};

void c_null_allocation::deallocate(void * pointer, char const * file, long line)
{
    mangled_ppc("?deallocate@c_null_allocation@@UAAXPAXPBDJ@Z");
};

// c_base_allocation::c_base_allocation(void), c_heap_allocation::c_heap_allocation(void) and
// c_null_allocation::c_null_allocation(void) are implicit (compiler-generated) and are emitted
// by the static instance definitions above ("??0c_base_allocation@@QAA@XZ" etc.)
