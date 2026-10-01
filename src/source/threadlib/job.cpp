/* ---------- headers */

#include "threadlib\job.h"
#include "foundation\threadlib\multithreading\profiler\mt_profiler_context.h"
#include "foundation\threadlib\multithreading\profiler\mt_profiler_store.h"
#include "threadlib\job_signature.h"
#include "threadlib\work_unit_handle.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// public: void c_job::setup(class c_job_signature &, unsigned long, unsigned long, unsigned long, unsigned long);
// public: void (* c_job_signature::get_entry_point(void))(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, class c_job_handle, class c_jm_work_unit_handle);
// public: class c_job_pre_post const * c_job_signature::get_pre_post(void) const;
// public: void c_job::execute(unsigned long, class c_job_handle, class c_jm_work_unit_handle &);
// public: unsigned long c_job::execute_pre(unsigned long);
// public: unsigned long c_job::execute_post(unsigned long);

void c_job::setup(c_job_signature & signature, unsigned long parameter0, unsigned long parameter1, unsigned long parameter2, unsigned long parameter3)
{
    mangled_ppc("?setup@c_job@@QAAXAAVc_job_signature@@KKKK@Z");

    m_entry_point = signature.get_entry_point();
    if (signature.get_pre_post())
    {
        m_pre_post = *signature.get_pre_post();
    }
    m_parameter0 = parameter0;
    m_parameter1 = parameter1;
    m_parameter2 = parameter2;
    m_parameter3 = parameter3;
};

void c_job::execute(unsigned long thread_index, c_job_handle handle, c_jm_work_unit_handle & work_unit)
{
    mangled_ppc("?execute@c_job@@QAAXKVc_job_handle@@AAVc_jm_work_unit_handle@@@Z");

    static unsigned short profiler_index = profiler_get_index("job", "job2", static_cast<e_mt_color>(6));
    c_mtp_profiler_context profiler_context(profiler_index);

    if (m_entry_point)
    {
        m_entry_point(m_parameter0, m_parameter1, m_parameter2, m_parameter3, thread_index, handle, work_unit);
    }
};

unsigned long c_job::execute_pre(unsigned long thread_index)
{
    mangled_ppc("?execute_pre@c_job@@QAAKK@Z");

    if (m_pre_post.m_hash && thread_index != m_pre_post.m_hash)
    {
        m_pre_post.m_pre_function();
    }

    return m_pre_post.m_hash;
};

unsigned long c_job::execute_post(unsigned long thread_index)
{
    mangled_ppc("?execute_post@c_job@@QAAKK@Z");

    unsigned long result = m_pre_post.m_hash;
    if (m_pre_post.m_hash && m_pre_post.m_hash != thread_index)
    {
        m_pre_post.m_post_function();
        result = 0;
    }

    return result;
};
