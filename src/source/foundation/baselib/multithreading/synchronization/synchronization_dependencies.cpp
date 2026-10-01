#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\foundation\\baselib\\multithreading\\synchronization\\synchronization_dependencies.cpp"
/* ---------- headers */

#include "foundation\baselib\multithreading\synchronization\synchronization_dependencies.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "foundation\baselib\multithreading\synchronization\lock_hierarchy.h"
#include "foundation\baselib\multithreading\synchronization\synchronization_manager.h"
#include "omaha\cseries\cseries.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// void critical_section_dependency(struct s_critical_section, struct s_critical_section);
// void critical_section_mutex_dependency(struct s_critical_section, struct s_mutex);
// void critical_section_semaphore_dependency(struct s_critical_section, struct s_semaphore);
// void critical_section_virtual_guard_block_dependency(struct s_critical_section, struct s_virtual_guard_block);
// void virtual_guard_block_critical_section_dependency(struct s_virtual_guard_block, struct s_critical_section);
// void virtual_guard_block_semaphore_dependency(struct s_virtual_guard_block, struct s_semaphore);
// void critical_section_optional_dependency(struct s_critical_section, struct s_critical_section);
// void critical_section_reverse_dependency(struct s_critical_section, struct s_critical_section);
// void synchronization_object_set_dependency(unsigned long, unsigned long);
// void synchronization_object_set_optional_dependency(unsigned long, unsigned long);
// void synchronization_object_set_reverse_dependency(unsigned long, unsigned long);

void critical_section_dependency(s_critical_section parent_critical_section, s_critical_section child_critical_section)
{
    mangled_ppc("?critical_section_dependency@@YAXUs_critical_section@@0@Z");

    synchronization_object_set_dependency(parent_critical_section.object_id, child_critical_section.object_id);
};

void critical_section_mutex_dependency(s_critical_section parent_critical_section, s_mutex child_mutex)
{
    mangled_ppc("?critical_section_mutex_dependency@@YAXUs_critical_section@@Us_mutex@@@Z");

    synchronization_object_set_dependency(parent_critical_section.object_id, child_mutex.object_id);
};

void critical_section_semaphore_dependency(s_critical_section parent_critical_section, s_semaphore child_semaphore)
{
    mangled_ppc("?critical_section_semaphore_dependency@@YAXUs_critical_section@@Us_semaphore@@@Z");

    synchronization_object_set_dependency(parent_critical_section.object_id, child_semaphore.object_id);
};

void critical_section_virtual_guard_block_dependency(s_critical_section parent_critical_section, s_virtual_guard_block child_guard_block)
{
    mangled_ppc("?critical_section_virtual_guard_block_dependency@@YAXUs_critical_section@@Us_virtual_guard_block@@@Z");

    synchronization_object_set_dependency(parent_critical_section.object_id, child_guard_block.object_id);
};

void virtual_guard_block_critical_section_dependency(s_virtual_guard_block parent_guard_block, s_critical_section child_critical_section)
{
    mangled_ppc("?virtual_guard_block_critical_section_dependency@@YAXUs_virtual_guard_block@@Us_critical_section@@@Z");

    synchronization_object_set_dependency(parent_guard_block.object_id, child_critical_section.object_id);
};

void virtual_guard_block_semaphore_dependency(s_virtual_guard_block parent_guard_block, s_semaphore child_semaphore)
{
    mangled_ppc("?virtual_guard_block_semaphore_dependency@@YAXUs_virtual_guard_block@@Us_semaphore@@@Z");

    synchronization_object_set_dependency(parent_guard_block.object_id, child_semaphore.object_id);
};

void critical_section_optional_dependency(s_critical_section parent_critical_section, s_critical_section optional_child_critical_section)
{
    mangled_ppc("?critical_section_optional_dependency@@YAXUs_critical_section@@0@Z");

    synchronization_object_set_optional_dependency(parent_critical_section.object_id, optional_child_critical_section.object_id);
};

void critical_section_reverse_dependency(s_critical_section child_critical_section, s_critical_section reverse_parent_critical_section)
{
    mangled_ppc("?critical_section_reverse_dependency@@YAXUs_critical_section@@0@Z");

    synchronization_object_set_reverse_dependency(child_critical_section.object_id, reverse_parent_critical_section.object_id);
};

void synchronization_object_set_dependency(unsigned long parent_object_id, unsigned long child_object_id)
{
    mangled_ppc("?synchronization_object_set_dependency@@YAXKK@Z");

    long child_lock_node_index;
    long parent_lock_node_index = synchronization_object_get_lock_node_index(parent_object_id);
    child_lock_node_index = synchronization_object_get_lock_node_index(child_object_id);
    dassert_tag_debug_untracked_jul_11_2011(97, parent_lock_node_index != NONE, "parent synchronization object not part of hierarchy (only the base group is tracked in the hierarchy)");
    dassert_tag_debug_untracked_jul_11_2011(98, child_lock_node_index != NONE, "child synchronization object not part of hierarchy (only the base group is tracked in the hierarchy)");

    synchronization_get_lock_hierarchy()->declare_blocking_dependency(parent_lock_node_index, child_lock_node_index);
};

void synchronization_object_set_optional_dependency(unsigned long parent_object_id, unsigned long optional_child_object_id)
{
    mangled_ppc("?synchronization_object_set_optional_dependency@@YAXKK@Z");

    long parent_lock_node_index = synchronization_object_get_lock_node_index(parent_object_id);
    long child_lock_node_index = synchronization_object_get_lock_node_index(optional_child_object_id);
    dassert_tag_debug_untracked_jul_11_2011(110, parent_lock_node_index != NONE, "parent synchronization object not part of hierarchy (only the base group is tracked in the hierarchy)");
    dassert_tag_debug_untracked_jul_11_2011(111, child_lock_node_index != NONE, "optional-child synchronization object not part of hierarchy (only the base group is tracked in the hierarchy)");

    synchronization_get_lock_hierarchy()->declare_optional_dependency(parent_lock_node_index, child_lock_node_index);
};

void synchronization_object_set_reverse_dependency(unsigned long child_object_id, unsigned long reverse_parent_object_id)
{
    mangled_ppc("?synchronization_object_set_reverse_dependency@@YAXKK@Z");

    long child_lock_node_index = synchronization_object_get_lock_node_index(child_object_id);
    long reverse_parent_lock_node_index = synchronization_object_get_lock_node_index(reverse_parent_object_id);
    dassert_tag_debug_untracked_jul_11_2011(123, child_lock_node_index != NONE, "child synchronization object not part of hierarchy (only the base group is tracked in the hierarchy)");
    dassert_tag_debug_untracked_jul_11_2011(124, reverse_parent_lock_node_index != NONE, "reverse-parent synchronization object not part of hierarchy (only the base group is tracked in the hierarchy)");

    synchronization_get_lock_hierarchy()->declare_reverse_dependency(child_lock_node_index, reverse_parent_lock_node_index);
};

