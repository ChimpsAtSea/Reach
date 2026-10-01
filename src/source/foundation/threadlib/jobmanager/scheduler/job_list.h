#pragma once
#ifndef __JOB_LIST_H__
#define __JOB_LIST_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"
#include "foundation\baselib\datatypes\indexed_list.h"
#include "foundation\baselib\datatypes\indexed_pool.h"
#include "foundation\baselib\multithreading\synchronization\critical_section_windows.h"
#include "foundation\baselib\multithreading\synchronization\semaphore_windows.h"
#include "threadlib\jm_types.h"
#include "threadlib\job.h"

/* ---------- constants */

/* ---------- definitions */

class c_job_list
{
public:
    c_job_list()
    {
        mangled_ppc("??0c_job_list@@QAA@XZ");
    };

    ~c_job_list()
    {
        mangled_ppc("??1c_job_list@@QAA@XZ");
    };

    void initialize(s_critical_section activelist_critical_section, s_critical_section freelist_critical_section, s_critical_section deps_critical_section, s_semaphore semaphore, unsigned long thread_count);
    void dispose();
    bool active_list_empty();
    bool free_list_full();
    bool is_done(c_job_handle const & handle);
    c_job_handle add(c_job const & job, unsigned long flags);
    void activate(c_job_handle const & handle, bool kick);
    void activate_array(c_job_handle * handles, unsigned long count);
    void add_to_active(c_job_handle * handles, unsigned long count);
    void block_until_work_available(bool unused);
    void kick_semaphore();
    unsigned long get_executable_jobs(c_job ** jobs, c_job_handle * handles, unsigned long max_count);
    void free_job_array(c_job ** jobs, unsigned long count);
    void return_to_free_list(c_job ** jobs, unsigned long count);
    bool depends(c_job_handle const & handle_a, c_job_handle const & handle_b);
    bool allocate_inactive(unsigned long num, c_job_handle * handles, c_job ** jobs);

    void lock_activelist()
    {
        mangled_ppc("?lock_activelist@c_job_list@@QAAXXZ");

        critical_section_enter_internal(m_activelist_critical_section, _critical_section_non_recursive);
    };

    void unlock_activelist()
    {
        mangled_ppc("?unlock_activelist@c_job_list@@QAAXXZ");

        critical_section_leave_internal(m_activelist_critical_section, _critical_section_non_recursive);
    };

    void lock_freelist()
    {
        mangled_ppc("?lock_freelist@c_job_list@@QAAXXZ");

        critical_section_enter_internal(m_freelist_critical_section, _critical_section_non_recursive);
    };

    void unlock_freelist()
    {
        mangled_ppc("?unlock_freelist@c_job_list@@QAAXXZ");

        critical_section_leave_internal(m_freelist_critical_section, _critical_section_non_recursive);
    };

    void lock_deps()
    {
        mangled_ppc("?lock_deps@c_job_list@@QAAXXZ");

        critical_section_enter_internal(m_deps_critical_section, _critical_section_non_recursive);
    };

    void unlock_deps()
    {
        mangled_ppc("?unlock_deps@c_job_list@@QAAXXZ");

        critical_section_leave_internal(m_deps_critical_section, _critical_section_non_recursive);
    };

private:
    c_job_handle_internal m_handles[k_jm_max_num_jobs_per_work_unit];
    c_job m_job_repository[k_jm_max_num_jobs_per_work_unit];
    c_indexed_pool<s_il_node, k_jm_max_num_jobs_per_work_unit> m_dependency_pool;
    s_critical_section m_activelist_critical_section;
    s_critical_section m_freelist_critical_section;
    s_critical_section m_deps_critical_section;
    s_semaphore m_semaphore;
    c_indexed_list<unsigned short, k_jm_max_num_jobs_per_work_unit> m_active_list;
    c_indexed_list<unsigned short, k_jm_max_num_jobs_per_work_unit> m_free_list;
    unsigned long m_thread_count;
};
static_assert(sizeof(c_job_list) == 0x50048, "c_job_list");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __JOB_LIST_H__

