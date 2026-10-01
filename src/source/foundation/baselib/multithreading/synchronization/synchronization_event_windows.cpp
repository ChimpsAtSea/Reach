#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\foundation\\baselib\\multithreading\\synchronization\\synchronization_event_windows.cpp"
/* ---------- headers */

#include "foundation\baselib\multithreading\synchronization\synchronization_event_windows.h"
#include "core\corelib\cseries\cseries_asserts.h"
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

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// struct s_synchronization_event synchronization_event_declare(long, struct s_synchronization_event_definition const *);
// void synchronization_event_create(class c_synchronization_handle *, unsigned long, struct s_synchronization_event_definition const *);
// void synchronization_event_destroy(class c_synchronization_handle *);
// void synchronization_event_wait_internal(struct s_synchronization_event);
// bool synchronization_event_wait_timeout_internal(struct s_synchronization_event, long);
// void synchronization_event_set_internal(struct s_synchronization_event);
// void synchronization_event_reset_internal(struct s_synchronization_event);
// bool synchronization_event_has_automatic_reset(struct s_synchronization_event);

s_synchronization_event synchronization_event_declare(long synchronization_group_index, s_synchronization_event_definition const * definition)
{
    mangled_ppc("?synchronization_event_declare@@YA?AUs_synchronization_event@@JPBUs_synchronization_event_definition@@@Z");

    assert_tag_debug_untracked_jul_11_2011(24, definition);
    assert_tag_debug_untracked_jul_11_2011(25, definition->name);

    s_synchronization_event event;
    event.object_id = synchronization_declare_synchronization_event(synchronization_group_index, definition);
    dassert_tag_debug_untracked_jul_11_2011(28, event.object_id != NONE, "too many events, increase k_maximum_events");

    return event;
};

void synchronization_event_create(c_synchronization_handle * event, unsigned long object_id, s_synchronization_event_definition const * definition)
{
    mangled_ppc("?synchronization_event_create@@YAXPAVc_synchronization_handle@@KPBUs_synchronization_event_definition@@@Z");

    assert_tag_debug_untracked_jul_11_2011(40, definition);
    assert_tag_debug_untracked_jul_11_2011(41, definition->name);
    assert_tag_debug_untracked_jul_11_2011(42, event);

    void * handle = CreateEventA(NULL, definition->manual_reset, definition->initial_state, NULL);
    dassert_tag_debug_untracked_jul_11_2011(45, VALID_HANDLE(handle), "failed to create event");

    event->initialize(object_id);
    event->set_handle(handle);
};

void synchronization_event_destroy(c_synchronization_handle * event)
{
    mangled_ppc("?synchronization_event_destroy@@YAXPAVc_synchronization_handle@@@Z");

    assert_tag_debug_untracked_jul_11_2011(57, event);

    void * handle = event->get_handle();
    assert_tag_debug_untracked_jul_11_2011(60, VALID_HANDLE(handle));

    event->set_handle(INVALID_HANDLE_VALUE);
    BOOL result = CloseHandle(handle);
    dassert_tag_debug_untracked_jul_11_2011(64, result, "failed to close event handle");
};

// $TODO nonmatching: only the g_synchronization_lock_tracker TLS offset (li 0x4c0 vs 0x0) differs, a link-time value
void synchronization_event_wait_internal(s_synchronization_event event)
{
    mangled_ppc("?synchronization_event_wait_internal@@YAXUs_synchronization_event@@@Z");

    c_synchronization_handle * event_handle = synchronization_get_synchronization_event(event.object_id);
    s_synchronization_event_definition const * definition = synchronization_get_synchronization_event_definition(event.object_id);
    if (definition->allow_wait_with_locks_held)
    {
        // waiting while holding locks is allowed for this event
    }
    else
    {
        g_synchronization_lock_tracker->check_empty();
    }

    c_synchronization_block_timer block_timer(event.object_id, -1);
    {
        bool success = wait_for_single_object_internal(event_handle->get_handle(), -1);
        dassert_tag_debug_untracked_jul_11_2011(89, success, "failed to wait on event");
    }
};

// $TODO nonmatching: only the g_synchronization_lock_tracker TLS offset (li 0x4c0 vs 0x0) differs, a link-time value
bool synchronization_event_wait_timeout_internal(s_synchronization_event event, long timeout_milliseconds)
{
    mangled_ppc("?synchronization_event_wait_timeout_internal@@YA_NUs_synchronization_event@@J@Z");

    c_synchronization_handle * event_handle = synchronization_get_synchronization_event(event.object_id);
    s_synchronization_event_definition const * definition = synchronization_get_synchronization_event_definition(event.object_id);
    bool success = false;
    if (timeout_milliseconds == 0)
    {
        // polling never blocks
    }
    else if (definition->allow_wait_with_locks_held)
    {
    }
    else
    {
        g_synchronization_lock_tracker->check_empty();
    }

    {
        c_synchronization_block_timer block_timer(event.object_id, -1);
        success = wait_for_single_object_internal(event_handle->get_handle(), timeout_milliseconds);
    }

    return success;
};

void synchronization_event_set_internal(s_synchronization_event event)
{
    mangled_ppc("?synchronization_event_set_internal@@YAXUs_synchronization_event@@@Z");

    BOOL success;
    c_synchronization_handle * event_instance = synchronization_get_synchronization_event(event.object_id);
    success = SetEvent(event_instance->get_handle());
    assert_tag_debug_untracked_jul_11_2011(132, success!=0);
};

void synchronization_event_reset_internal(s_synchronization_event event)
{
    mangled_ppc("?synchronization_event_reset_internal@@YAXUs_synchronization_event@@@Z");

    BOOL success;
    c_synchronization_handle * event_instance = synchronization_get_synchronization_event(event.object_id);
    success = ResetEvent(event_instance->get_handle());
    assert_tag_debug_untracked_jul_11_2011(142, success!=0);
};

bool synchronization_event_has_automatic_reset(s_synchronization_event event)
{
    mangled_ppc("?synchronization_event_has_automatic_reset@@YA_NUs_synchronization_event@@@Z");

    s_synchronization_event_definition const * definition = synchronization_get_synchronization_event_definition(event.object_id);
    return !definition->manual_reset;
};
