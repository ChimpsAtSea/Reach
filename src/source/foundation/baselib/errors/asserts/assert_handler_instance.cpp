#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\foundation\\baselib\\errors\\asserts\\assert_handler_instance.cpp"
/* ---------- headers */

#include "foundation\baselib\errors\asserts\assert_handler_instance.h"
#include "baselib\synchronized_value_windows.h"
#include "baselib\system_debugger_xenon.h"
#include "baselib\system_os_interface.h"
#include "baselib\thread_execution_windows.h"
#include "core\corelib\config\version.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_events.h"
#include "foundation\baselib\datatypes\static_string.h"
#include "foundation\baselib\errors\output\output_globals.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

static c_engine_assert_interface * g_engine_assert_interface;
static bool g_assert_handler_force_debugger_always_present;
static bool g_assert_handler_force_debugger_not_present;
static bool g_assert_handler_pass_exceptions_to_os;
static bool g_assert_handler_force_crash_report;
static c_assert_handler_instance g_assert_handler_instance;
static c_interlocked_int32 g_assert_handler_global_entry_gate(0);
static long g_assert_handler_halt_without_exit;
static __declspec(thread) bool g_assert_handler_thread_handling_assert;

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// void assert_handler_initialize(class c_engine_assert_interface *);
// void assert_handler_force_crash_report(bool);
// void assert_handler_force_debugger_not_present(bool);
// void assert_handler_force_debugger_always_present(bool);
// bool assert_handler_should_pass_exceptions_to_os(void);
// void assert_handler_dispose(void);
// private: virtual long c_assert_handler_instance::register_tracked_assert(char const *, long);
// long assert_tracker_register_assert(char const *, long);
// private: virtual void c_assert_handler_instance::log_tracked_assert(long);
// void assert_tracker_log_assert(long);
// private: virtual bool c_assert_handler_instance::debugger_present(void);
// private: virtual bool c_assert_handler_instance::handle_assert(char const *, char const *, long);
// private: virtual void c_assert_handler_instance::halt_execution(void);
// private: virtual void c_assert_handler_instance::handle_slim_assert_constant(struct s_slim_assert_info const *);
// private: virtual void c_assert_handler_instance::handle_slim_assert_dynamic(struct s_slim_assert_info const *, class c_assert_string const &);
// private: void c_assert_handler_instance::report_assertion(char const *, char const *, long);
// public: char const * s_static_string<1156>::get_string(void) const;
// public: c_assert_handler_instance::c_assert_handler_instance(void);
// public: c_assert_handler::c_assert_handler(void);
// void g_assert_handler_global_entry_gate::`dynamic atexit destructor'(void);

void assert_handler_initialize(c_engine_assert_interface * engine_assert_interface)
{
    mangled_ppc("?assert_handler_initialize@@YAXPAVc_engine_assert_interface@@@Z");

    g_assert_handler_pass_exceptions_to_os |= !version_is_tracked_build() && true;
    g_engine_assert_interface = engine_assert_interface;
    c_assert_handler_hook::attach_handler(&g_assert_handler_instance);
};

void assert_handler_force_crash_report(bool force)
{
    mangled_ppc("?assert_handler_force_crash_report@@YAX_N@Z");

    g_assert_handler_force_crash_report = force;
};

void assert_handler_force_debugger_not_present(bool value)
{
    mangled_ppc("?assert_handler_force_debugger_not_present@@YAX_N@Z");

    g_assert_handler_force_debugger_not_present = value;
    if (value)
    {
        g_assert_handler_force_debugger_always_present = false;
    }
};

void assert_handler_force_debugger_always_present(bool value)
{
    mangled_ppc("?assert_handler_force_debugger_always_present@@YAX_N@Z");

    g_assert_handler_force_debugger_always_present = value;
    if (value)
    {
        g_assert_handler_force_debugger_not_present = false;
    }
};

bool assert_handler_should_pass_exceptions_to_os(void)
{
    mangled_ppc("?assert_handler_should_pass_exceptions_to_os@@YA_NXZ");

    return g_assert_handler_pass_exceptions_to_os && !assert_is_debugger_present();
};

void assert_handler_dispose(void)
{
    mangled_ppc("?assert_handler_dispose@@YAXXZ");

    c_assert_handler_hook::detach_handler(&g_assert_handler_instance);
};

long c_assert_handler_instance::register_tracked_assert(char const * expression, long line)
{
    mangled_ppc("?register_tracked_assert@c_assert_handler_instance@@EAAJPBDJ@Z");

    return assert_tracker_register_assert(expression, line);
};

void c_assert_handler_instance::log_tracked_assert(long tracked_assert_index)
{
    mangled_ppc("?log_tracked_assert@c_assert_handler_instance@@EAAXJ@Z");

    assert_tracker_log_assert(tracked_assert_index);
};

bool c_assert_handler_instance::debugger_present(void)
{
    mangled_ppc("?debugger_present@c_assert_handler_instance@@EAA_NXZ");

    bool debugger_present = false;
    if (!g_assert_handler_force_debugger_not_present)
    {
        debugger_present = g_assert_handler_force_debugger_always_present || system_is_debugger_present();
    }

    return debugger_present;
};

// $TODO nonmatching: only diff is the TLS offset of g_assert_handler_thread_handling_assert (target li 0x4b4 is an already-resolved image TLS offset, ours is a SECREL reloc of 0)
bool c_assert_handler_instance::handle_assert(char const * expression, char const * file, long line)
{
    mangled_ppc("?handle_assert@c_assert_handler_instance@@EAA_NPBD0J@Z");

    bool handled = false;

    if (g_assert_handler_thread_handling_assert)
    {
        output_debug("FATAL ERROR: assert fired during assert handling! %s at %s, %d", expression, file, line);
        halt_execution();
    }
    else
    {
        g_assert_handler_thread_handling_assert = true;
    }

    {
        long gate_value = g_assert_handler_global_entry_gate.set_if_equal(1, 0);
        while (gate_value != 0)
        {
            thread_switch();
            gate_value = g_assert_handler_global_entry_gate.set_if_equal(1, 0);
        }
    }

    if (assert_is_debugger_present())
    {
    }
    else
    {
        if (g_assert_handler_pass_exceptions_to_os)
        {
            __debugbreak();
        }

        if (g_engine_assert_interface && g_engine_assert_interface->thread_manager_handle_assertion_via_exception())
        {
            g_engine_assert_interface->thread_manager_post_assertion(expression, file, line);
            g_assert_handler_global_entry_gate.set(0);
            g_engine_assert_interface->raise_exception_unhandled(expression, file, line);
            dassert_tag_debug_untracked_jul_11_2011(226, false, "unreachable");
        }
    }

    if (!handled)
    {
        bool raise_exception = (g_assert_handler_force_crash_report || version_is_tracked_build() && !assert_is_debugger_present()) ? true : false;

        report_assertion(expression, file, line);

        if (g_engine_assert_interface)
        {
            g_engine_assert_interface->call_fatal_error_callbacks();
        }

        if (raise_exception && g_engine_assert_interface)
        {
            g_engine_assert_interface->raise_exception_handled(expression, file, line);
        }
    }

    g_assert_handler_thread_handling_assert = false;
    g_assert_handler_global_entry_gate.set(0);

    return handled;
};

void c_assert_handler_instance::halt_execution(void)
{
    mangled_ppc("?halt_execution@c_assert_handler_instance@@EAAXXZ");

    if (assert_is_debugger_present())
    {
        __debugbreak();
    }

    if (!g_assert_handler_halt_without_exit)
    {
        system_exit_application(_application_exit_code_failure);
    }
};

void c_assert_handler_instance::handle_slim_assert_constant(s_slim_assert_info const * info)
{
    mangled_ppc("?handle_slim_assert_constant@c_assert_handler_instance@@EAAXPBUs_slim_assert_info@@@Z");

    if (!handle_assert(info->expression, info->file, info->line))
    {
        halt_execution();
    }
};

void c_assert_handler_instance::handle_slim_assert_dynamic(s_slim_assert_info const * info, c_assert_string const & message)
{
    mangled_ppc("?handle_slim_assert_dynamic@c_assert_handler_instance@@EAAXPBUs_slim_assert_info@@ABVc_assert_string@@@Z");

    s_slim_assert_info dynamic_info = *info;
    dynamic_info.expression = message;
    handle_slim_assert_constant(&dynamic_info);
};

void c_assert_handler_instance::report_assertion(char const * expression, char const * file, long line)
{
    mangled_ppc("?report_assertion@c_assert_handler_instance@@AAAXPBD0J@Z");

    s_static_string<1156> assert_string;

    if (!assert_is_debugger_present())
    {
        char const * full_string = version_get_full_string();
        event(_event_critical, "%s", full_string);
        assert_string.print("version:\r\n%s\r\n", full_string);

        event(_event_critical, "### ASSERTION FAILED: at %s,#%d", file, line);
        assert_string.append_print("halt:\r\n### ASSERTION FAILED:  at %s,#%d\r\n", file, line);

        if (expression)
        {
            event(_event_critical, "  %s", expression);
            assert_string.append_print(" %s\r\n", expression);
        }
    }
    else
    {
        event(_event_critical, "%s(%d): ASSERT: %s", file, line, expression ? expression : "");
        assert_string.print("halt:\r\n%s(%d): ASSERT: %s\r\n", file, line, expression ? expression : "");
    }

    if (g_engine_assert_interface)
    {
        g_engine_assert_interface->generate_stack_walk(assert_string.get_string());
    }
};

