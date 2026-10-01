#pragma once
#ifndef __SCHEDULER_H__
#define __SCHEDULER_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"

/* ---------- constants */

/* ---------- definitions */

class c_job;
class c_job_handle;
class c_job_list;

class c_scheduler_fifo
{
public:
    c_scheduler_fifo()
    {
        mangled_ppc("??0c_scheduler_fifo@@QAA@XZ");

        m_job_list = NULL;
    };

    ~c_scheduler_fifo()
    {
        mangled_ppc("??1c_scheduler_fifo@@QAA@XZ");
    };

    void initialize(c_job_list * job_list);
    void dispose();
    unsigned long request_jobs(c_job ** jobs, c_job_handle * handles, unsigned long max_count);
    void report_jobs_complete(c_job ** jobs, unsigned long count);
    void kick_semaphore();
    void block_until_work_available(bool unused);

    c_job_list * m_job_list;
};
static_assert(sizeof(c_scheduler_fifo) == 0x4, "c_scheduler_fifo");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __SCHEDULER_H__

