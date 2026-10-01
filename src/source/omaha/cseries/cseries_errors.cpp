#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\cseries\\cseries_errors.cpp"
/* ---------- headers */

#include "omaha\cseries\cseries_errors.h"
#include "omaha\cseries\stack_walk_windows.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_events.h"
#include "core\corelib\cseries\cseries_macros.h"

/* ---------- constants */

long const k_number_of_fatal_error_callbacks = 32;

/* ---------- definitions */

struct s_error_global_data
{
    long callback_count; // 0x0
    void (*callbacks[k_number_of_fatal_error_callbacks])(void); // 0x4
};
static_assert(sizeof(s_error_global_data) == 0x84, "s_error_global_data");

/* ---------- prototypes */

/* ---------- globals */

static s_error_global_data error_globals;

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// void errors_initialize(void);
// void errors_dispose(void);
// bool errors_add_fatal_error_callback(void (*)(void));
// void call_fatal_error_callbacks(void);

void errors_initialize(void)
{
    mangled_ppc("?errors_initialize@@YAXXZ");

    stack_walk_initialize();
};

void errors_dispose(void)
{
    mangled_ppc("?errors_dispose@@YAXXZ");

    stack_walk_dispose();
};

bool errors_add_fatal_error_callback(void (*callback)(void))
{
    mangled_ppc("?errors_add_fatal_error_callback@@YA_NP6AXXZ@Z");

    bool success = false;

    if (VALID_INDEX(error_globals.callback_count, k_number_of_fatal_error_callbacks))
    {
        error_globals.callbacks[error_globals.callback_count] = callback;
        error_globals.callback_count++;
        success = true;
    }
    else
    {
        event(_event_critical, "vwarn: '%s'", NULL);
        if (assert_is_debugger_present())
        {
            __debugbreak();
        }
    }

    return success;
};

void call_fatal_error_callbacks(void)
{
    mangled_ppc("?call_fatal_error_callbacks@@YAXXZ");

    for (long callback_index = 0; callback_index < error_globals.callback_count; callback_index++)
    {
        if (error_globals.callbacks[callback_index] != NULL)
        {
            error_globals.callbacks[callback_index]();
        }
    }
};
