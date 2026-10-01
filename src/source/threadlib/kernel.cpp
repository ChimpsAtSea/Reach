/* ---------- headers */

#include "threadlib\kernel.h"
#include "core\corelib\cseries\cseries_macros.h"
#include "foundation\threadlib\jobmanager\job_manager.h"
#include "threadlib\jm_types.h"
#include "threadlib\job.h"
#include "threadlib\scheduler.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// bool execute_jobs(class c_scheduler_fifo *, unsigned long, unsigned long, class c_job_pre_post *);
// public: class c_job_pre_post const & c_job::get_pre_post(void);
// bool execute_one_job(class c_scheduler_fifo *, unsigned long);
// public: c_kernel::c_kernel(void);
// public: unsigned long c_kernel::do_work(unsigned long);
// public: bool c_kernel::should_exit(void);
// public: void c_kernel::signal_exit(void);
// public: void c_kernel::reset(void);

bool execute_jobs(c_scheduler_fifo * scheduler, unsigned long thread_index, unsigned long max_jobs, c_job_pre_post * pre_post)
{
    mangled_ppc("?execute_jobs@@YA_NPAVc_scheduler_fifo@@KKPAVc_job_pre_post@@@Z");

    unsigned long count;
    c_job_handle handles[8];
    c_job * job_list[8];

    count = scheduler->request_jobs(job_list, handles, max_jobs);
    if (count != 0)
    {
        if (pre_post->m_hash != 0 && pre_post->m_hash != job_list[0]->get_pre_post().m_hash)
        {
            pre_post->m_post_function();
        }

        unsigned long i;
        for (i = 0; i < count - 1; i++)
        {
            pre_post->m_hash = job_list[i]->execute_pre(pre_post->m_hash);
            job_list[i]->execute(thread_index, handles[i], job_manager_get_default_work_unit());
            pre_post->m_hash = job_list[i]->execute_post(job_list[i + 1]->get_pre_post().m_hash);
        }

        unsigned long last_job_index = count - 1;
        job_list[last_job_index]->execute_pre(pre_post->m_hash);
        job_list[last_job_index]->execute(thread_index, handles[last_job_index], job_manager_get_default_work_unit());
        pre_post->m_hash = job_list[last_job_index]->get_pre_post().m_hash;
        pre_post->m_post_function = job_list[last_job_index]->get_pre_post().m_post_function;

        scheduler->report_jobs_complete(job_list, count);

        return true;
    }
    else
    {
        if (pre_post->m_hash != 0)
        {
            pre_post->m_post_function();
        }

        return false;
    }
};

bool execute_one_job(c_scheduler_fifo * scheduler, unsigned long thread_index)
{
    mangled_ppc("?execute_one_job@@YA_NPAVc_scheduler_fifo@@K@Z");

    c_job_pre_post pre_post;
    return execute_jobs(scheduler, thread_index, 1, &pre_post);
};

c_kernel::c_kernel()
{
    mangled_ppc("??0c_kernel@@QAA@XZ");

    m_flags = 0;
    m_scheduler = NULL;
};

unsigned long c_kernel::do_work(unsigned long thread_index)
{
    mangled_ppc("?do_work@c_kernel@@QAAKK@Z");

    while (!should_exit())
    {
        m_scheduler->block_until_work_available(thread_index == 0);

        c_job_pre_post pre_post;
        c_job_pre_post * pre_post_pointer = &pre_post;
        while (execute_jobs(m_scheduler, thread_index, 4, pre_post_pointer))
        {
        }
    }

    return 1;
};

bool c_kernel::should_exit()
{
    mangled_ppc("?should_exit@c_kernel@@QAA_NXZ");

    return 0 != (m_flags & FLAG(0));
};

void c_kernel::signal_exit()
{
    mangled_ppc("?signal_exit@c_kernel@@QAAXXZ");

    m_flags |= FLAG(0);
};

void c_kernel::reset()
{
    mangled_ppc("?reset@c_kernel@@QAAXXZ");

    m_flags = 0;
};
