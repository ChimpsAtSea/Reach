#pragma once
#ifndef __JOB_MANAGER_TEST_H__
#define __JOB_MANAGER_TEST_H__

/* ---------- headers */

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

namespace JMTest
{
    void simple_runonce(void);
    void simple_run_many(void);
    void check_timed(void);
    void check_dependency(void);
    void check_dependency_already_executing(void);
    unsigned long find_in_list(unsigned long value, unsigned long * list, unsigned long start_index, unsigned long count);
    void check_thrash(void);
    void check_add_from_job(void);

    template<long k_mode, long k_depth>
    void check_dependency_largescale(void);

    template<long k_mode>
    void check_wait_single(void);
};

namespace IndexedTest
{
    void test_pool(void);
    void test_linked_list(void);
};

extern void job_manager_test_hook(void);

/* ---------- globals */

/* ---------- public code */

#endif // __JOB_MANAGER_TEST_H__

