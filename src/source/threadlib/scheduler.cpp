/* ---------- headers */

#include "threadlib\scheduler.h"

#include "foundation\threadlib\jobmanager\scheduler\job_list.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// public: void c_scheduler_fifo::initialize(class c_job_list *);
// public: void c_scheduler_fifo::dispose(void);
// public: unsigned long c_scheduler_fifo::request_jobs(class c_job **, class c_job_handle *, unsigned long);
// public: void c_scheduler_fifo::report_jobs_complete(class c_job **, unsigned long);
// public: void c_scheduler_fifo::kick_semaphore(void);
// public: void c_scheduler_fifo::block_until_work_available(bool);

void c_scheduler_fifo::initialize(c_job_list * job_list)
{
    mangled_ppc("?initialize@c_scheduler_fifo@@QAAXPAVc_job_list@@@Z");

    m_job_list = job_list;
};

void c_scheduler_fifo::dispose()
{
    mangled_ppc("?dispose@c_scheduler_fifo@@QAAXXZ");
};

unsigned long c_scheduler_fifo::request_jobs(c_job ** jobs, c_job_handle * handles, unsigned long max_count)
{
    mangled_ppc("?request_jobs@c_scheduler_fifo@@QAAKPAPAVc_job@@PAVc_job_handle@@K@Z");

    return m_job_list->get_executable_jobs(jobs, handles, max_count);
};

void c_scheduler_fifo::report_jobs_complete(c_job ** jobs, unsigned long count)
{
    mangled_ppc("?report_jobs_complete@c_scheduler_fifo@@QAAXPAPAVc_job@@K@Z");

    m_job_list->return_to_free_list(jobs, count);
};

void c_scheduler_fifo::kick_semaphore()
{
    mangled_ppc("?kick_semaphore@c_scheduler_fifo@@QAAXXZ");

    m_job_list->kick_semaphore();
};

void c_scheduler_fifo::block_until_work_available(bool unused)
{
    mangled_ppc("?block_until_work_available@c_scheduler_fifo@@QAAX_N@Z");

    m_job_list->block_until_work_available(unused);
};
