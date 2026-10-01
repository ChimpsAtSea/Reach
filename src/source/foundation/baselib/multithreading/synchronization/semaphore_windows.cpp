#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\foundation\\baselib\\multithreading\\synchronization\\semaphore_windows.cpp"
/* ---------- headers */

#include "foundation\baselib\multithreading\synchronization\semaphore_windows.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_events.h"
#include "core\corelib\cseries\cseries_macros.h"
#include "foundation\baselib\multithreading\synchronization\lock_tracker.h"
#include "foundation\baselib\multithreading\synchronization\synchronization_manager.h"
#include "omaha\cseries\cseries.h"

#include <xtl.h>

/* ---------- constants */

#define VALID_HANDLE(handle) ((handle) != NULL && (handle) != INVALID_HANDLE_VALUE)

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

s_semaphore const k_semaphore_invalid = { k_synchronization_object_id_invalid };

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// public: static long const s_static_array<long, 23>::k_element_count; // "?k_element_count@?$s_static_array@J$0BH@@@2JB"
// struct s_semaphore const k_semaphore_invalid; // "?k_semaphore_invalid@@3Us_semaphore@@B"

// struct s_semaphore semaphore_declare(long, struct s_semaphore_definition const *);
// void semaphore_create(class c_semaphore_instance *, unsigned long, long, struct s_semaphore_definition const *);
// public: void c_synchronization_handle::set_handle(void *);
// void semaphore_destroy(class c_semaphore_instance *);
// public: void * c_synchronization_handle::get_handle(void) const;
// long semaphore_release_internal(struct s_semaphore, bool *);
// public: bool c_semaphore_instance::is_universal(void) const;
// void semaphore_take_internal(struct s_semaphore);
// bool semaphore_try_and_take_internal(struct s_semaphore);
// bool semaphore_is_valid(struct s_semaphore);
// long semaphore_get_initial_count(struct s_semaphore);
// long semaphore_get_maximum_count(struct s_semaphore);
// long semaphore_get_current_thread_reference_count(struct s_semaphore);
// public: void c_semaphore_instance::reset_reference_counts(bool);
// public: void c_semaphore_instance::force_release_if_owned_by_thread(long);
// public: unsigned long c_synchronization_object::get_object_id(void) const;
// public: long c_semaphore_instance::get_reference_count(void) const;
// public: void c_semaphore_instance::add_reference(void);
// public: void c_semaphore_instance::remove_reference(void);
// public: void s_static_array<long, 23>::set_all(long const &);
// public: long const & s_static_array<long, 23>::operator[]<long>(long) const;
// public: long & s_static_array<long, 23>::operator[]<long>(long);
// public: static bool s_static_array<long, 23>::valid<long>(long);

s_semaphore semaphore_declare(long synchronization_group_index, s_semaphore_definition const * definition)
{
    mangled_ppc("?semaphore_declare@@YA?AUs_semaphore@@JPBUs_semaphore_definition@@@Z");

    assert_tag_debug_untracked_jul_11_2011(27, definition);
    assert_tag_debug_untracked_jul_11_2011(28, definition->name);
    assert_tag_debug_untracked_jul_11_2011(29, definition->maximum_count>0);
    assert_tag_debug_untracked_jul_11_2011(30, definition->initial_count>=0 && definition->initial_count<=definition->maximum_count);

    s_semaphore semaphore;
    semaphore.object_id = synchronization_declare_semaphore(synchronization_group_index, definition);
    dassert_tag_debug_untracked_jul_11_2011(33, semaphore.object_id != NONE, "too many semaphores, increase k_maximum_semaphores");

    return semaphore;
};

void semaphore_create(c_semaphore_instance * semaphore, unsigned long object_id, long lock_node_index, s_semaphore_definition const * definition)
{
    mangled_ppc("?semaphore_create@@YAXPAVc_semaphore_instance@@KJPBUs_semaphore_definition@@@Z");

    assert_tag_debug_untracked_jul_11_2011(46, object_id!=k_synchronization_object_id_invalid);
    assert_tag_debug_untracked_jul_11_2011(47, !(SYNCHRONIZATION_OBJECT_GROUP(object_id)==k_synchronization_group_base && lock_node_index==NONE));
    assert_tag_debug_untracked_jul_11_2011(48, definition);
    assert_tag_debug_untracked_jul_11_2011(49, definition->name);
    assert_tag_debug_untracked_jul_11_2011(50, definition->maximum_count>0);
    assert_tag_debug_untracked_jul_11_2011(51, definition->initial_count>=0 && definition->initial_count<=definition->maximum_count);
    assert_tag_debug_untracked_jul_11_2011(52, semaphore);

    void * handle = CreateSemaphoreA(NULL, definition->initial_count, definition->maximum_count, NULL);
    dassert_tag_debug_untracked_jul_11_2011(55, VALID_HANDLE(handle), "failed to create semaphore");

    semaphore->initialize(object_id);
    semaphore->set_lock_node_index(lock_node_index);
    semaphore->set_handle(handle);
    semaphore->reset_reference_counts(definition->universal);
};

void c_synchronization_handle::set_handle(void * handle)
{
    mangled_ppc("?set_handle@c_synchronization_handle@@QAAXPAX@Z");

    m_handle = handle;
};

void semaphore_destroy(c_semaphore_instance * semaphore)
{
    mangled_ppc("?semaphore_destroy@@YAXPAVc_semaphore_instance@@@Z");

    assert_tag_debug_untracked_jul_11_2011(69, semaphore);

    void * handle = semaphore->get_handle();
    assert_tag_debug_untracked_jul_11_2011(72, VALID_HANDLE(handle));

    semaphore->set_handle(INVALID_HANDLE_VALUE);
    BOOL result = CloseHandle(handle);
    dassert_tag_debug_untracked_jul_11_2011(76, result, "failed to close semaphore handle");
};

void * c_synchronization_handle::get_handle(void) const
{
    mangled_ppc("?get_handle@c_synchronization_handle@@QBAPAXXZ");

    return m_handle;
};

long semaphore_release_internal(s_semaphore semaphore, bool * out_released)
{
    mangled_ppc("?semaphore_release_internal@@YAJUs_semaphore@@PA_N@Z");

    BOOL success;
    long prev_count;
    c_semaphore_instance * semaphore_object = synchronization_get_semaphore(semaphore.object_id);
    prev_count = 0;
    bool released = false;
    success = ReleaseSemaphore(semaphore_object->get_handle(), 1, &prev_count);
    dassert_tag_debug_untracked_jul_11_2011(89, success || semaphore_object->is_universal(), "failed to release semaphore - possible overflow of maximum count?");

    if (success)
    {
        semaphore_object->remove_reference();
        released = true;
    }

    if (out_released)
    {
        *out_released = released;
    }

    return prev_count;
};

bool c_semaphore_instance::is_universal(void) const
{
    mangled_ppc("?is_universal@c_semaphore_instance@@QBA_NXZ");

    return m_universal_reference_count;
};

// $TODO nonmatching: only the TLS offset of g_synchronization_lock_tracker (li 0x4C0) differs, it is resolved at link time
void semaphore_take_internal(s_semaphore semaphore)
{
    mangled_ppc("?semaphore_take_internal@@YAXUs_semaphore@@@Z");

    c_semaphore_instance * semaphore_instance = synchronization_get_semaphore(semaphore.object_id);
    c_synchronization_block_timer synchronization_block_timer(semaphore.object_id, -1);
    bool result = wait_for_single_object_internal(semaphore_instance->get_handle(), -1);
    dassert_tag_debug_untracked_jul_11_2011(110, result, "failed to take semaphore");

    if (result)
    {
        g_synchronization_lock_tracker->verify_push(semaphore_instance);
        semaphore_instance->add_reference();
    }
};

// $TODO nonmatching: only the TLS offset of g_synchronization_lock_tracker (li 0x4C0) differs, it is resolved at link time
bool semaphore_try_and_take_internal(s_semaphore semaphore)
{
    mangled_ppc("?semaphore_try_and_take_internal@@YA_NUs_semaphore@@@Z");

    c_semaphore_instance * semaphore_instance = synchronization_get_semaphore(semaphore.object_id);
    bool success;
    {
        c_synchronization_block_timer block_timer(semaphore.object_id, -1);
        success = wait_for_single_object_internal(semaphore_instance->get_handle(), 0);

        if (success)
        {
            g_synchronization_lock_tracker->verify_push(semaphore_instance);
            semaphore_instance->add_reference();
        }
    }

    return success;
};

bool semaphore_is_valid(s_semaphore semaphore)
{
    mangled_ppc("?semaphore_is_valid@@YA_NUs_semaphore@@@Z");

    return semaphore.object_id != k_semaphore_invalid.object_id;
};

long semaphore_get_initial_count(s_semaphore semaphore)
{
    mangled_ppc("?semaphore_get_initial_count@@YAJUs_semaphore@@@Z");

    s_semaphore_definition const * definition = synchronization_get_semaphore_definition(semaphore.object_id);
    return definition->initial_count;
};

long semaphore_get_maximum_count(s_semaphore semaphore)
{
    mangled_ppc("?semaphore_get_maximum_count@@YAJUs_semaphore@@@Z");

    s_semaphore_definition const * definition = synchronization_get_semaphore_definition(semaphore.object_id);
    return definition->maximum_count;
};

long semaphore_get_current_thread_reference_count(s_semaphore semaphore)
{
    mangled_ppc("?semaphore_get_current_thread_reference_count@@YAJUs_semaphore@@@Z");

    c_semaphore_instance * semaphore_instance = synchronization_get_semaphore(semaphore.object_id);
    return semaphore_instance->get_reference_count();
};

void c_semaphore_instance::reset_reference_counts(bool universal)
{
    mangled_ppc("?reset_reference_counts@c_semaphore_instance@@QAAX_N@Z");

    m_universal_reference_count = universal;
    m_reference_counts.set_all(0);
};

void c_semaphore_instance::force_release_if_owned_by_thread(long thread_index)
{
    mangled_ppc("?force_release_if_owned_by_thread@c_semaphore_instance@@QAAXJ@Z");

    long reference_count;
    s_semaphore semaphore = { get_object_id() };
    if (!m_universal_reference_count)
    {
        while ((reference_count = get_reference_count()) > 0)
        {
            bool released = false;
            semaphore_release_internal(semaphore, &released);
            dassert_tag_debug_untracked_jul_11_2011(207, released, "unable to force-release semaphore");

            if (!released)
            {
                event(_event_error, "synchronization:semaphore: semaphore '%s' unable to force-release thread %d %s reference-count (%d)",
                    synchronization_object_get_name(get_object_id()),
                    thread_index,
                    m_universal_reference_count ? "universal" : "per-thread",
                    reference_count);
                break;
            }
        }
    }
    else
    {
        bool released = false;
        do
        {
            semaphore_release_internal(semaphore, &released);
        } while (released);
    }
};

unsigned long c_synchronization_object::get_object_id(void) const
{
    mangled_ppc("?get_object_id@c_synchronization_object@@QBAKXZ");

    return m_object_id;
};

long c_semaphore_instance::get_reference_count(void) const
{
    mangled_ppc("?get_reference_count@c_semaphore_instance@@QBAJXZ");

    long thread_index = synchronization_get_current_thread_index();
    assert_tag_debug_untracked_jul_11_2011(236, !m_universal_reference_count);

    return m_reference_counts[thread_index];
};

void c_semaphore_instance::add_reference(void)
{
    mangled_ppc("?add_reference@c_semaphore_instance@@QAAXXZ");

    if (!m_universal_reference_count)
    {
        long thread_index = synchronization_get_current_thread_index();
        m_reference_counts[thread_index]++;
    }
};

void c_semaphore_instance::remove_reference(void)
{
    mangled_ppc("?remove_reference@c_semaphore_instance@@QAAXXZ");

    if (!m_universal_reference_count)
    {
        long thread_index = synchronization_get_current_thread_index();
        m_reference_counts[thread_index] = int_max(m_reference_counts[thread_index] - 1, 0);
    }
};
