#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\foundation\\threadlib\\jobmanager\\job\\job_groups.cpp"

/* ---------- headers */

#include "foundation\threadlib\jobmanager\job\job_groups.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "threadlib\job.h"
#include "threadlib\work_unit_handle.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// public: c_job_group::c_job_group(class c_jm_work_unit_handle &);
// public: c_job_group::~c_job_group(void);
// public: void c_job_group::activate_jobs(unsigned long, unsigned long);
// public: void c_job_group::allocate_jobs(unsigned long);
// public: class c_job_handle c_job_group::setup(unsigned long, class c_job_signature &, unsigned long, unsigned long, unsigned long, unsigned long);

c_job_group::c_job_group(c_jm_work_unit_handle & work_unit) :
    m_setup(),
    m_work_unit(work_unit)
{
    mangled_ppc("??0c_job_group@@QAA@AAVc_jm_work_unit_handle@@@Z");

    m_num_allocated = 0;
    m_unknown6808 = false;
};

c_job_group::~c_job_group()
{
    mangled_ppc("??1c_job_group@@QAA@XZ");

    for (unsigned long i = 0; i < m_num_allocated; i++)
    {
        if (!(m_setup[i] & 2))
        {
            m_work_unit.free_unused_job(m_jobs[i]);
            m_jobs[i] = NULL;
        }
    }
};

void c_job_group::activate_jobs(unsigned long start, unsigned long end)
{
    mangled_ppc("?activate_jobs@c_job_group@@QAAXKK@Z");

    assert_tag_debug_untracked_jul_11_2011(43, start <= m_num_allocated);
    assert_tag_debug_untracked_jul_11_2011(44, end >= start);
    assert_tag_debug_untracked_jul_11_2011(45, end <= m_num_allocated);

    for (unsigned long i = start; i < end; i++)
    {
        assert_tag_debug_untracked_jul_11_2011(49, m_setup[i] == e_job_group_setup);
        m_setup[i] = e_job_group_activated;
    }

    m_work_unit.add_to_active(static_cast<c_job_handle *>(&m_handles[start]), end - start);
    m_work_unit.activate_array(static_cast<c_job_handle *>(&m_handles[start]), end - start);
};

void c_job_group::allocate_jobs(unsigned long num)
{
    mangled_ppc("?allocate_jobs@c_job_group@@QAAXK@Z");

    bool allocated = m_work_unit.allocate_inactive(num, static_cast<c_job_handle *>(m_handles), m_jobs);
    vassert_tag_debug_untracked_jul_11_2011(71, allocated, "failed to allocate job group");
    m_num_allocated = num;
};

c_job_handle c_job_group::setup(unsigned long index, c_job_signature & signature, unsigned long parameter0, unsigned long parameter1, unsigned long parameter2, unsigned long parameter3)
{
    mangled_ppc("?setup@c_job_group@@QAA?AVc_job_handle@@KAAVc_job_signature@@KKKK@Z");

    assert_tag_debug_untracked_jul_11_2011(82, index < m_num_allocated);
    assert_tag_debug_untracked_jul_11_2011(83, m_setup[index]==e_job_group_unset);

    m_jobs[index]->setup(signature, parameter0, parameter1, parameter2, parameter3);
    m_setup[index] = e_job_group_setup;
    return static_cast<c_job_handle &>(m_handles[index]);
};
