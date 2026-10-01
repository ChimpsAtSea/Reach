#pragma once
#ifndef __ASSERT_HANDLER_INSTANCE_H__
#define __ASSERT_HANDLER_INSTANCE_H__

/* ---------- headers */

#include "core\corelib\cseries\asserts\assert_handler.h"
#include "core\corelib\cseries\cseries_asserts.h"

/* ---------- constants */

/* ---------- definitions */

// implemented by c_cseries_engine_assert_interface (cseries.obj)
class c_engine_assert_interface
{
public:
    virtual bool thread_manager_handle_assertion_via_exception(void) = 0;
    virtual void thread_manager_post_assertion(char const * expression, char const * file, long line) = 0;
    virtual void call_fatal_error_callbacks(void) = 0;
    virtual void generate_stack_walk(char const * assert_string) = 0;
    virtual void raise_exception_unhandled(char const * expression, char const * file, long line) = 0;
    virtual void raise_exception_handled(char const * expression, char const * file, long line) = 0;
};

class c_assert_handler_instance :
    public c_assert_handler
{
public:
    c_assert_handler_instance(void)
    {
        mangled_ppc("??0c_assert_handler_instance@@QAA@XZ");
    };

private:
    virtual long register_tracked_assert(char const * expression, long line);
    virtual void log_tracked_assert(long tracked_assert_index);
    virtual bool debugger_present(void);
    virtual bool handle_assert(char const * expression, char const * file, long line);
    virtual void halt_execution(void);
    virtual void handle_slim_assert_constant(s_slim_assert_info const * info);
    virtual void handle_slim_assert_dynamic(s_slim_assert_info const * info, c_assert_string const & message);

    void report_assertion(char const * expression, char const * file, long line);
};

/* ---------- prototypes */

extern void assert_handler_initialize(c_engine_assert_interface * engine_assert_interface);
extern void assert_handler_force_crash_report(bool force);
extern void assert_handler_force_debugger_not_present(bool value);
extern void assert_handler_force_debugger_always_present(bool value);
extern bool assert_handler_should_pass_exceptions_to_os(void);
extern void assert_handler_dispose(void);

inline long assert_tracker_register_assert(char const * expression, long line)
{
    mangled_ppc("?assert_tracker_register_assert@@YAJPBDJ@Z");

    return -1;
};

inline void assert_tracker_log_assert(long tracked_assert_index)
{
    mangled_ppc("?assert_tracker_log_assert@@YAXJ@Z");
};

/* ---------- globals */

/* ---------- public code */

#endif // __ASSERT_HANDLER_INSTANCE_H__
