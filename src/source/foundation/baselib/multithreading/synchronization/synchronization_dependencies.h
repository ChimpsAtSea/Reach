#pragma once
#ifndef __SYNCHRONIZATION_DEPENDENCIES_H__
#define __SYNCHRONIZATION_DEPENDENCIES_H__

/* ---------- headers */

#include "foundation\baselib\multithreading\synchronization\critical_section_windows.h"
#include "foundation\baselib\multithreading\synchronization\mutex_windows.h"
#include "foundation\baselib\multithreading\synchronization\semaphore_windows.h"
#include "foundation\baselib\multithreading\synchronization\virtual_guard_block.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

extern void critical_section_dependency(s_critical_section parent_critical_section, s_critical_section child_critical_section);
extern void critical_section_mutex_dependency(s_critical_section parent_critical_section, s_mutex child_mutex);
extern void critical_section_semaphore_dependency(s_critical_section parent_critical_section, s_semaphore child_semaphore);
extern void critical_section_virtual_guard_block_dependency(s_critical_section parent_critical_section, s_virtual_guard_block child_guard_block);
extern void virtual_guard_block_critical_section_dependency(s_virtual_guard_block parent_guard_block, s_critical_section child_critical_section);
extern void virtual_guard_block_semaphore_dependency(s_virtual_guard_block parent_guard_block, s_semaphore child_semaphore);
extern void critical_section_optional_dependency(s_critical_section parent_critical_section, s_critical_section optional_child_critical_section);
extern void critical_section_reverse_dependency(s_critical_section child_critical_section, s_critical_section reverse_parent_critical_section);
extern void synchronization_object_set_dependency(unsigned long parent_object_id, unsigned long child_object_id);
extern void synchronization_object_set_optional_dependency(unsigned long parent_object_id, unsigned long optional_child_object_id);
extern void synchronization_object_set_reverse_dependency(unsigned long child_object_id, unsigned long reverse_parent_object_id);

/* ---------- globals */

/* ---------- public code */

#endif // __SYNCHRONIZATION_DEPENDENCIES_H__

