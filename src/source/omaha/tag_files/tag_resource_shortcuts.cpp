#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\tag_files\\tag_resource_shortcuts.cpp"
/* ---------- headers */

#include "omaha\tag_files\tag_resource_shortcuts.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_macros.h"

/* ---------- constants */

// $TODO: replace with `k_registered_thread_count` from `e_registered_threads` once that enum exists in src
enum
{
    k_tag_resource_shortcuts_thread_count = 17
};

/* ---------- definitions */

/* ---------- prototypes */

extern long get_current_thread_index(void);
extern void scenario_handle_tag_resource_lock(long thread_index);
extern void scenario_handle_tag_resource_unlock(long thread_index);

/* ---------- globals */

/* ---------- public code */

void tag_resource_shortcuts_handle_lock(void)
{
    mangled_ppc("?tag_resource_shortcuts_handle_lock@@YAXXZ");

    long thread_index = get_current_thread_index();
    vassert_tag_debug_untracked_jul_11_2011(17, VALID_INDEX(thread_index, k_tag_resource_shortcuts_thread_count), "invalid thread index");

    scenario_handle_tag_resource_lock(thread_index);
};

void tag_resource_shortcuts_handle_unlock(void)
{
    mangled_ppc("?tag_resource_shortcuts_handle_unlock@@YAXXZ");

    long thread_index = get_current_thread_index();
    vassert_tag_debug_untracked_jul_11_2011(25, VALID_INDEX(thread_index, k_tag_resource_shortcuts_thread_count), "invalid thread index");

    scenario_handle_tag_resource_unlock(thread_index);
};

/* ---------- private code */

/* ---------- reverse engineering */
