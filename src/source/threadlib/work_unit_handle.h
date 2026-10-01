#pragma once
#ifndef __WORK_UNIT_HANDLE_H__
#define __WORK_UNIT_HANDLE_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"
#include "threadlib\jm_types.h"

/* ---------- constants */

/* ---------- definitions */

class c_job;
class c_work_unit;

class c_jm_work_unit_handle
{
public:
    c_jm_work_unit_handle()
    {
        mangled_ppc("??0c_jm_work_unit_handle@@QAA@XZ");

        m_handle = 0xFFFFFFFF;
        m_work_unit = NULL;
    };

    // inline in the target (bodies owned by other translation units)
    ~c_jm_work_unit_handle();
    bool valid();

    bool allocate_inactive(unsigned long count, c_job_handle * handles, c_job ** jobs);
    void free_unused_job(c_job * job);
    c_job_handle add_job(c_job const & job, unsigned long flags);
    void activate(c_job_handle & handle);
    void activate_array(c_job_handle * handles, unsigned long count);
    void add_to_active(c_job_handle * handles, unsigned long count);
    void do_not_use_wait_until_all_work_done();
    void block_wait_until_done(c_job_handle const & handle);
    bool job_is_done(c_job_handle const & handle);
    void relinquish_until_done(c_job_handle const & handle);
    bool a_depends_on_b(c_job_handle const & a, c_job_handle const & b);
    void thread_entry_point(unsigned long thread_index);

    unsigned long m_handle;
    c_work_unit * m_work_unit;
};
static_assert(sizeof(c_jm_work_unit_handle) == 0x8, "c_jm_work_unit_handle");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __WORK_UNIT_HANDLE_H__

