#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\SD\Reach\Publishing\Main\shared\engine\source\foundation\baselib\multithreading\datatypes\initialization_lock.cpp"
/* ---------- headers */

#include "foundation\baselib\multithreading\datatypes\initialization_lock.h"
#include "baselib\synchronized_value_windows.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_macros.h"
#include "foundation\baselib\multithreading\threads\thread_manipulation_windows.h"

/* ---------- constants */

/* ---------- definitions */

struct s_initialization_lock_globals
{
    c_synchronized_int32 initialization_started;
    c_synchronized_int32 initialization_complete;
    c_synchronized_int32 thread_initializing;
    s_thread_id initializing_thread_id;
};
static_assert(sizeof(s_initialization_lock_globals) == 0x10, "s_initialization_lock_globals");

/* ---------- prototypes */

/* ---------- globals */

static s_initialization_lock_globals g_initialization_lock_globals;

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// void initialization_lock_startup_begin(void);
// void initialization_lock_thread_begin(void);
// void initialization_lock_thread_end(void);
// void initialization_lock_startup_complete(void);
// void initialization_lock_assert_thread_read_valid(void);
// void initialization_lock_assert_thread_write_valid(void);
// public: s_initialization_lock_globals::s_initialization_lock_globals(void);
// public: s_initialization_lock_globals::~s_initialization_lock_globals(void);
// void g_initialization_lock_globals::`dynamic atexit destructor'(void);

void initialization_lock_startup_begin(void)
{
    mangled_ppc("?initialization_lock_startup_begin@@YAXXZ");

    assert_tag_debug_untracked_jul_11_2011(34, g_initialization_lock_globals.initialization_started.peek()==0);
    assert_tag_debug_untracked_jul_11_2011(35, g_initialization_lock_globals.initialization_complete.peek()==0);

    g_initialization_lock_globals.initialization_started.set(1);
};

void initialization_lock_thread_begin(void)
{
    mangled_ppc("?initialization_lock_thread_begin@@YAXXZ");

    assert_tag_debug_untracked_jul_11_2011(43, g_initialization_lock_globals.initialization_started.peek());
    assert_tag_debug_untracked_jul_11_2011(44, g_initialization_lock_globals.initialization_complete.peek()==0);
    assert_tag_debug_untracked_jul_11_2011(45, g_initialization_lock_globals.thread_initializing.peek()==0);

    long previous_value = g_initialization_lock_globals.thread_initializing.set_if_equal(1, 0);
    assert_tag_debug_untracked_jul_11_2011(48, previous_value==0);

    g_initialization_lock_globals.initializing_thread_id = thread_get_current_id();
};

void initialization_lock_thread_end(void)
{
    mangled_ppc("?initialization_lock_thread_end@@YAXXZ");

    s_thread_id current_thread = thread_get_current_id();

    assert_tag_debug_untracked_jul_11_2011(59, g_initialization_lock_globals.thread_initializing.peek());
    assert_tag_debug_untracked_jul_11_2011(60, g_initialization_lock_globals.initializing_thread_id.id==current_thread.id);

    g_initialization_lock_globals.initializing_thread_id = k_thread_id_invalid;
    g_initialization_lock_globals.thread_initializing.set(0);
};

void initialization_lock_startup_complete(void)
{
    mangled_ppc("?initialization_lock_startup_complete@@YAXXZ");

    assert_tag_debug_untracked_jul_11_2011(70, g_initialization_lock_globals.initialization_started.peek());
    assert_tag_debug_untracked_jul_11_2011(71, g_initialization_lock_globals.thread_initializing.peek()==0);

    g_initialization_lock_globals.initialization_complete.set(1);
};

void initialization_lock_assert_thread_read_valid(void)
{
    mangled_ppc("?initialization_lock_assert_thread_read_valid@@YAXXZ");

    if (!g_initialization_lock_globals.initialization_started.peek())
    {
        // not using the lock
    }
    else if (g_initialization_lock_globals.initialization_complete.peek())
    {
        // startup is complete, anyone can read
    }
    else if (g_initialization_lock_globals.thread_initializing.peek())
    {
        s_thread_id current_thread = thread_get_current_id();
        dassert_tag_debug_untracked_jul_11_2011(90, g_initialization_lock_globals.initializing_thread_id.id==current_thread.id, "can't read a protected structure from a thread other than the one that is initializing");
    }
    else
    {
        dassert_tag_debug_untracked_jul_11_2011(94, false, "can't read protected structure - calling before startup begins?");
    }
};

void initialization_lock_assert_thread_write_valid(void)
{
    mangled_ppc("?initialization_lock_assert_thread_write_valid@@YAXXZ");

    if (!g_initialization_lock_globals.initialization_started.peek())
    {
        // not using the lock
    }
    else if (g_initialization_lock_globals.initialization_complete.peek())
    {
        dassert_tag_debug_untracked_jul_11_2011(107, false, "can't write to protected structure after startup completes");
    }
    else if (g_initialization_lock_globals.thread_initializing.peek())
    {
        s_thread_id current_thread = thread_get_current_id();
        dassert_tag_debug_untracked_jul_11_2011(113, g_initialization_lock_globals.initializing_thread_id.id==current_thread.id, "can't write to a protected structure from a thread other than the one that is initializing");
    }
    else
    {
        dassert_tag_debug_untracked_jul_11_2011(117, false, "can't write to protected structure - calling before startup begins?");
    }
};

// s_initialization_lock_globals::s_initialization_lock_globals, ::~s_initialization_lock_globals and
// g_initialization_lock_globals' dynamic initializer / atexit destructor are compiler-generated
