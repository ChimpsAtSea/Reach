#pragma once
#ifndef __THREADS_H__
#define __THREADS_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"
#include "baselib\thread_execution_windows.h"

/* ---------- constants */

// Reach has 17 registered threads; only the values below are verified (start_thread asserts 1 < index < 17)
enum e_registered_threads
{
    k_thread_unknown = 0,
    k_thread_main = 1,

    k_thread_network_block_detection = 11,

    k_thread_job_first = 12,
    k_thread_job_last = 15,

    k_registered_thread_count = 17
};

inline e_registered_threads & operator++(e_registered_threads & thread_index)
{
    thread_index = static_cast<e_registered_threads>(thread_index + 1);

    return thread_index;
};

inline e_registered_threads operator++(e_registered_threads & thread_index, int)
{
    e_registered_threads result = thread_index;
    thread_index = static_cast<e_registered_threads>(thread_index + 1);

    return result;
};

/* ---------- definitions */

struct s_thread_assert_arguments
{
    unsigned long information;
    unsigned long file;
    unsigned long line;
    unsigned long fatal;
};
static_assert(sizeof(s_thread_assert_arguments) == 0x10, "s_thread_assert_arguments");

/* ---------- prototypes */

extern void initialize_thread_management(void);
extern void destroy_thread_management(void);
extern void post_thread_assert_arguments(s_thread_assert_arguments const * arguments);
extern long get_current_thread_index(void);
extern bool is_main_thread(void);
extern void start_thread(e_registered_threads thread_index);
extern bool thread_has_crashed(e_registered_threads thread_index);
extern void stop_thread(e_registered_threads thread_index);
extern bool current_thread_should_exit(void);
extern void current_thread_update_test_functions(void);

/* ---------- globals */

/* ---------- public code */

inline void sleep(unsigned long sleep_time_in_milliseconds)
{
    mangled_ppc("?sleep@@YAXK@Z");

    thread_sleep(sleep_time_in_milliseconds);
};

#endif // __THREADS_H__

