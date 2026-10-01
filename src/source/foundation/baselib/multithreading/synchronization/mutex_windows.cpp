#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\foundation\\baselib\\multithreading\\synchronization\\mutex_windows.cpp"
/* ---------- headers */

#include "foundation\baselib\multithreading\synchronization\mutex_windows.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_macros.h"
#include "foundation\baselib\multithreading\synchronization\lock_hierarchy.h"
#include "foundation\baselib\multithreading\synchronization\lock_tracker.h"
#include "foundation\baselib\multithreading\synchronization\synchronization_manager.h"
#include "omaha\cseries\cseries.h"

#include <xtl.h>

/* ---------- constants */

#define VALID_HANDLE(handle) ((handle) != NULL && (handle) != INVALID_HANDLE_VALUE)

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// struct s_mutex mutex_declare(long, struct s_mutex_definition const *);
// void mutex_dependency(struct s_mutex, struct s_mutex);
// void mutex_critical_section_dependency(struct s_mutex, unsigned long);
// void mutex_create(class c_synchronization_handle *, unsigned long, long, struct s_mutex_definition const *);
// public: void c_synchronization_object::set_lock_count(long, long);
// void mutex_destroy(class c_synchronization_handle *);
// void mutex_take_internal(struct s_mutex, enum e_mutex_recursive);
// bool mutex_take_timeout_internal(struct s_mutex, long);
// void mutex_release_internal(struct s_mutex, enum e_mutex_recursive);
// void mutex_force_release_if_owned_by_thread(class c_synchronization_handle *, long);
// public: long c_synchronization_object::get_lock_count(void) const;

s_mutex mutex_declare(long synchronization_group_index, s_mutex_definition const * definition)
{
    mangled_ppc("?mutex_declare@@YA?AUs_mutex@@JPBUs_mutex_definition@@@Z");

    assert_tag_debug_untracked_jul_11_2011(23, definition);
    assert_tag_debug_untracked_jul_11_2011(24, definition->name);

    s_mutex mutex;
    mutex.object_id = synchronization_declare_mutex(synchronization_group_index, definition);
    dassert_tag_debug_untracked_jul_11_2011(27, mutex.object_id != NONE, "too many mutexes, increase k_maximum_mutexes");

    return mutex;
};

void mutex_dependency(s_mutex parent_mutex, s_mutex child_mutex)
{
    mangled_ppc("?mutex_dependency@@YAXUs_mutex@@0@Z");

    long parent_node_index = synchronization_object_get_lock_node_index(parent_mutex.object_id);
    long child_node_index = synchronization_object_get_lock_node_index(child_mutex.object_id);
    dassert_tag_debug_untracked_jul_11_2011(39, parent_node_index != NONE, "parent mutex not part of hierarchy (only the base group is tracked in the hierarchy)");
    dassert_tag_debug_untracked_jul_11_2011(40, child_node_index != NONE, "child mutex not part of hierarchy (only the base group is tracked in the hierarchy)");

    synchronization_get_lock_hierarchy()->declare_blocking_dependency(parent_node_index, child_node_index);
};

void mutex_critical_section_dependency(s_mutex parent_mutex, unsigned long child_critical_section_id)
{
    mangled_ppc("?mutex_critical_section_dependency@@YAXUs_mutex@@K@Z");

    long parent_node_index = synchronization_object_get_lock_node_index(parent_mutex.object_id);
    long child_node_index = synchronization_object_get_lock_node_index(child_critical_section_id);
    dassert_tag_debug_untracked_jul_11_2011(52, parent_node_index != NONE, "parent mutex not part of hierarchy (only the base group is tracked in the hierarchy)");
    dassert_tag_debug_untracked_jul_11_2011(53, child_node_index != NONE, "child critical section not part of hierarchy (only the base group is tracked in the hierarchy)");

    synchronization_get_lock_hierarchy()->declare_blocking_dependency(parent_node_index, child_node_index);
};

// $TODO nonmatching: only the TLS offset of g_synchronization_lock_tracker differs (target li 0x4C0 is link-resolved)
void mutex_create(c_synchronization_handle * mutex, unsigned long object_id, long lock_node_index, s_mutex_definition const * definition)
{
    mangled_ppc("?mutex_create@@YAXPAVc_synchronization_handle@@KJPBUs_mutex_definition@@@Z");

    assert_tag_debug_untracked_jul_11_2011(66, object_id!=k_synchronization_object_id_invalid);
    assert_tag_debug_untracked_jul_11_2011(67, !(SYNCHRONIZATION_OBJECT_GROUP(object_id)==k_synchronization_group_base && lock_node_index==NONE));
    assert_tag_debug_untracked_jul_11_2011(68, definition);
    assert_tag_debug_untracked_jul_11_2011(69, definition->name);
    assert_tag_debug_untracked_jul_11_2011(70, mutex);

    void * handle = CreateMutexA(NULL, definition->initial_owner, NULL);
    dassert_tag_debug_untracked_jul_11_2011(73, VALID_HANDLE(handle), "failed to create mutex");

    mutex->initialize(object_id);
    mutex->set_lock_node_index(lock_node_index);
    mutex->set_handle(handle);

    if (definition->initial_owner)
    {
        long current_thread_index = synchronization_get_current_thread_index();
        g_synchronization_lock_tracker->verify_push(mutex);
        mutex->set_lock_count(current_thread_index, 1);
        g_synchronization_lock_tracker->push(mutex);
    }
};

void c_synchronization_object::set_lock_count(long locking_thread, long lock_count)
{
    mangled_ppc("?set_lock_count@c_synchronization_object@@QAAXJJ@Z");

    m_locking_thread.set(locking_thread);
    m_lock_count.set(lock_count);
};

void mutex_destroy(c_synchronization_handle * mutex)
{
    mangled_ppc("?mutex_destroy@@YAXPAVc_synchronization_handle@@@Z");

    assert_tag_debug_untracked_jul_11_2011(96, mutex);

    void * handle = mutex->get_handle();
    assert_tag_debug_untracked_jul_11_2011(99, VALID_HANDLE(handle));

    mutex->set_handle(INVALID_HANDLE_VALUE);
    BOOL result = CloseHandle(handle);
    dassert_tag_debug_untracked_jul_11_2011(103, result, "failed to close mutex handle");
};

// $TODO nonmatching: only the TLS offset of g_synchronization_lock_tracker differs (target li 0x4C0 is link-resolved)
void mutex_take_internal(s_mutex mutex, e_mutex_recursive recursive)
{
    mangled_ppc("?mutex_take_internal@@YAXUs_mutex@@W4e_mutex_recursive@@@Z");

    c_synchronization_handle * mutex_handle = synchronization_get_mutex(mutex.object_id);
    long current_thread_index = synchronization_get_current_thread_index();
    assert_tag_debug_untracked_jul_11_2011(114, VALID_INDEX(recursive, k_mutex_recursive_count));

    c_synchronization_block_timer block_timer(mutex.object_id, mutex_handle->get_locking_thread());
    if (recursive != _mutex_recursive)
    {
        mutex_handle->acquire_prerequisites();
    }

    g_synchronization_lock_tracker->verify_push(mutex_handle);
    {
        bool success = wait_for_single_object_internal(mutex_handle->get_handle(), -1);
        dassert_tag_debug_untracked_jul_11_2011(129, success, "failed to take mutex");

        if (success)
        {
            mutex_handle->increment_lock_count(current_thread_index);
            g_synchronization_lock_tracker->push(mutex_handle);
        }
    }
};

// $TODO nonmatching: only the TLS offset of g_synchronization_lock_tracker differs (target li 0x4C0 is link-resolved)
bool mutex_take_timeout_internal(s_mutex mutex, long timeout_milliseconds)
{
    mangled_ppc("?mutex_take_timeout_internal@@YA_NUs_mutex@@J@Z");

    c_synchronization_handle * mutex_handle = synchronization_get_mutex(mutex.object_id);
    long current_thread_index = synchronization_get_current_thread_index();
    bool result = false;

    {
        c_synchronization_block_timer block_timer(mutex.object_id, mutex_handle->get_locking_thread());
        g_synchronization_lock_tracker->verify_push(mutex_handle);
        result = wait_for_single_object_internal(mutex_handle->get_handle(), timeout_milliseconds);

        if (result)
        {
            mutex_handle->increment_lock_count(current_thread_index);
            g_synchronization_lock_tracker->push(mutex_handle);
        }
    }

    return result;
};

// $TODO nonmatching: only the TLS offset of g_synchronization_lock_tracker differs (target li 0x4C0 is link-resolved)
void mutex_release_internal(s_mutex mutex, e_mutex_recursive recursive)
{
    mangled_ppc("?mutex_release_internal@@YAXUs_mutex@@W4e_mutex_recursive@@@Z");

    c_synchronization_handle * mutex_handle = synchronization_get_mutex(mutex.object_id);
    assert_tag_debug_untracked_jul_11_2011(169, VALID_INDEX(recursive, k_mutex_recursive_count));

    g_synchronization_lock_tracker->pop(mutex_handle);
    mutex_handle->decrement_lock_count();
    BOOL success = ReleaseMutex(mutex_handle->get_handle());
    assert_tag_debug_untracked_jul_11_2011(175, success!=0);

    if (recursive != _mutex_recursive)
    {
        mutex_handle->release_prerequisites();
    }
};

void mutex_force_release_if_owned_by_thread(c_synchronization_handle * mutex, long thread_index)
{
    mangled_ppc("?mutex_force_release_if_owned_by_thread@@YAXPAVc_synchronization_handle@@J@Z");

    if (mutex->get_locking_thread() == thread_index)
    {
        s_mutex owned_mutex;
        owned_mutex.object_id = mutex->get_object_id();
        while (mutex->get_lock_count() > 0)
        {
            mutex_release_internal(owned_mutex, _mutex_non_recursive);
        }
    }
};

long c_synchronization_object::get_lock_count(void) const
{
    mangled_ppc("?get_lock_count@c_synchronization_object@@QBAJXZ");

    return m_lock_count.peek();
};

