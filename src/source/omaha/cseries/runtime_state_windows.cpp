#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\cseries\\runtime_state_windows.cpp"
/* ---------- headers */

#include "omaha\cseries\runtime_state_windows.h"
#include "core\corelib\cseries\cseries_macros.h"
#include "omaha\cache\physical_memory_map.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// void * runtime_state_allocate_buffer(long);
// void runtime_state_free_buffer(void *);

void * runtime_state_allocate_buffer(long size)
{
    mangled_ppc("?runtime_state_allocate_buffer@@YAPAXJ@Z");

    return _physical_memory_malloc(_memory_stage_game_initialize, "runtime state (not game state)", size, FLAG(_physical_memory_minidump_bit) | FLAG(_physical_memory_allocation_tracked_externally_bit), __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__, 12);
};

void runtime_state_free_buffer(void * buffer)
{
    mangled_ppc("?runtime_state_free_buffer@@YAXPAX@Z");

    physical_memory_free(buffer);
};
