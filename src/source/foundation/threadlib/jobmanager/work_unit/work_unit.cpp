#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\foundation\\threadlib\\jobmanager\\work_unit\\work_unit.cpp"

/* ---------- headers */

#include "foundation\threadlib\jobmanager\work_unit\work_unit.h"

#include "baselib\thread_execution_windows.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "threadlib\work_unit_params.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// public: void c_work_unit::initialize(struct s_work_unit_params const &);
// public: void c_kernel::set_scheduler(class c_scheduler_fifo *);
// public: void c_work_unit::execute(unsigned long);
// public: void c_work_unit::dispose(void);

void c_work_unit::initialize(s_work_unit_params const & params)
{
    mangled_ppc("?initialize@c_work_unit@@QAAXABUs_work_unit_params@@@Z");

    assert_tag_debug_untracked_jul_11_2011(23, params.m_num_workers <= k_jm_max_num_workers);

    m_num_workers = params.m_num_workers;
    m_job_list.initialize(params.m_activelist_critical_section, params.m_freelist_critical_section, params.m_deps_critical_section, params.m_semaphore, m_num_workers);
    m_scheduler.initialize(&m_job_list);

    for (unsigned long kernel_index = 0; kernel_index < m_num_workers; kernel_index++)
    {
        m_kernels[kernel_index].reset();
        m_kernels[kernel_index].set_scheduler(&m_scheduler);
    }
};

void c_work_unit::execute(unsigned long kernel_index)
{
    mangled_ppc("?execute@c_work_unit@@QAAXK@Z");

    assert_tag_debug_untracked_jul_11_2011(41, kernel_index < m_num_workers);

    m_kernels[kernel_index].do_work(kernel_index);
};

void c_work_unit::dispose()
{
    mangled_ppc("?dispose@c_work_unit@@QAAXXZ");

    for (unsigned long kernel_index = 0; kernel_index < m_num_workers; kernel_index++)
    {
        m_kernels[kernel_index].signal_exit();
    }

    for (unsigned long worker_index = 0; worker_index < m_num_workers; worker_index++)
    {
        m_scheduler.kick_semaphore();
    }

    thread_sleep(20);
    m_scheduler.dispose();
    m_job_list.dispose();
};

