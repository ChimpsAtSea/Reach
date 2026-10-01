#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\foundation\\baselib\\multithreading\\primitives\\thread_local_storage.cpp"
/* ---------- headers */

#include "foundation\baselib\multithreading\primitives\thread_local_storage.h"
#include "foundation\baselib\memory\base\base_memory_windows.h"
#include "core\corelib\cseries\cseries_asserts.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// void thread_local_storage_initialize(void);
// void thread_local_storage_dispose(void);
// void * thread_local_storage_allocate(unsigned int);
// void thread_local_storage_free(void *);

void thread_local_storage_initialize(void)
{
    mangled_ppc("?thread_local_storage_initialize@@YAXXZ");
};

void thread_local_storage_dispose(void)
{
    mangled_ppc("?thread_local_storage_dispose@@YAXXZ");
};

void * thread_local_storage_allocate(unsigned int size)
{
    mangled_ppc("?thread_local_storage_allocate@@YAPAXI@Z");

    void * data = base_malloc(size);
    dassert_tag_debug_untracked_jul_11_2011(42, data, "out of memory allocating thread-local storage data");

    return data;
};

void thread_local_storage_free(void * data)
{
    mangled_ppc("?thread_local_storage_free@@YAXPAX@Z");

    base_free(data);
};

