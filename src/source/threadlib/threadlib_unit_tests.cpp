#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\threadlib\\threadlib_unit_tests.cpp"
/* ---------- headers */

#include "threadlib\threadlib_unit_tests.h"
#include "foundation\baselib\errors\output\output_globals.h"
#include "foundation\threadlib\jobmanager\test\job_manager_test.h"
#include "foundation\threadlib\multithreading\test\lockfree_event_fifo_tests.h"
#include "foundation\threadlib\multithreading\test\lockfree_event_queue_tests.h"
#include "foundation\threadlib\multithreading\test\thread_safe_linked_list_tests.h"
#include "foundation\threadlib\multithreading\test\thread_wrapper_tests.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

s_unit_test_function g_threadlib_unit_test_functions[] =
{
    { "job_manager_test_hook", job_manager_test_hook },
    { "lockfree_event_fifo_run_unit_test", lockfree_event_fifo_run_unit_test },
    { "lockfree_event_queue_run_unit_test", lockfree_event_queue_run_unit_test },
    { "thread_wrapper_run_unit_tests", thread_wrapper_run_unit_tests },
    { "thread_safe_linked_list_run_unit_test", thread_safe_linked_list_run_unit_test },
};

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// struct s_unit_test_function *g_threadlib_unit_test_functions; // "?g_threadlib_unit_test_functions@@3PAUs_unit_test_function@@A"

// void threadlib_run_unit_tests(void);

void threadlib_run_unit_tests(void)
{
    mangled_ppc("?threadlib_run_unit_tests@@YAXXZ");

    long const test_count = NUMBEROF(g_threadlib_unit_test_functions);
    output_message("threadlib_run_unit_tests started\r\n");
    for (long test_index = 0; test_index < test_count; test_index++)
    {
        s_unit_test_function * test = &g_threadlib_unit_test_functions[test_index];
        output_message("running %s...\r\n", test->name);
        test->function();
    }
    output_message("threadlib_run_unit_tests completed\r\n");
};

