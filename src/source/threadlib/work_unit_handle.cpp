/* ---------- headers */

#include "threadlib\work_unit_handle.h"

#include "baselib\thread_execution_windows.h"
#include "foundation\threadlib\jobmanager\job_manager.h"
#include "foundation\threadlib\jobmanager\work_unit\work_unit.h"
#include "threadlib\kernel.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// public: static unsigned long const c_thread_base::k_exit_code_success; // "?k_exit_code_success@c_thread_base@@2KB"
// public: static unsigned long const c_thread_base::k_exit_code_failure; // "?k_exit_code_failure@c_thread_base@@2KB"
// private: static long const c_thread_crew::k_maximum_crew_size; // "?k_maximum_crew_size@c_thread_crew@@0JB"
// public: static long const s_static_array<class c_thread_wrapper, 16>::k_element_count; // "?k_element_count@?$s_static_array@Vc_thread_wrapper@@$0BA@@@2JB"

// public: bool c_jm_work_unit_handle::allocate_inactive(unsigned long, class c_job_handle *, class c_job **);
// public: void c_jm_work_unit_handle::free_unused_job(class c_job *);
// public: class c_job_handle c_jm_work_unit_handle::add_job(class c_job const &, unsigned long);
// public: void c_jm_work_unit_handle::activate(class c_job_handle &);
// public: void c_jm_work_unit_handle::activate_array(class c_job_handle *, unsigned long);
// public: void c_jm_work_unit_handle::add_to_active(class c_job_handle *, unsigned long);
// public: void c_jm_work_unit_handle::do_not_use_wait_until_all_work_done(void);
// public: void c_jm_work_unit_handle::block_wait_until_done(class c_job_handle const &);
// public: bool c_work_unit::is_done(class c_job_handle const &);
// public: bool c_jm_work_unit_handle::job_is_done(class c_job_handle const &);
// public: void c_jm_work_unit_handle::relinquish_until_done(class c_job_handle const &);
// public: bool c_jm_work_unit_handle::a_depends_on_b(class c_job_handle const &, class c_job_handle const &);
// public: void c_jm_work_unit_handle::thread_entry_point(unsigned long);

bool c_jm_work_unit_handle::allocate_inactive(unsigned long count, c_job_handle * handles, c_job ** jobs)
{
    mangled_ppc("?allocate_inactive@c_jm_work_unit_handle@@QAA_NKPAVc_job_handle@@PAPAVc_job@@@Z");

    return m_work_unit->m_job_list.allocate_inactive(count, handles, jobs);
};

void c_jm_work_unit_handle::free_unused_job(c_job * job)
{
    mangled_ppc("?free_unused_job@c_jm_work_unit_handle@@QAAXPAVc_job@@@Z");

    c_job * jobs = job;
    m_work_unit->m_job_list.return_to_free_list(&jobs, 1);
};

c_job_handle c_jm_work_unit_handle::add_job(c_job const & job, unsigned long flags)
{
    mangled_ppc("?add_job@c_jm_work_unit_handle@@QAA?AVc_job_handle@@ABVc_job@@K@Z");

    return m_work_unit->m_job_list.add(job, flags);
};

void c_jm_work_unit_handle::activate(c_job_handle & handle)
{
    mangled_ppc("?activate@c_jm_work_unit_handle@@QAAXAAVc_job_handle@@@Z");

    m_work_unit->m_job_list.activate(handle, true);
};

void c_jm_work_unit_handle::activate_array(c_job_handle * handles, unsigned long count)
{
    mangled_ppc("?activate_array@c_jm_work_unit_handle@@QAAXPAVc_job_handle@@K@Z");

    m_work_unit->m_job_list.activate_array(handles, count);
};

void c_jm_work_unit_handle::add_to_active(c_job_handle * handles, unsigned long count)
{
    mangled_ppc("?add_to_active@c_jm_work_unit_handle@@QAAXPAVc_job_handle@@K@Z");

    m_work_unit->m_job_list.add_to_active(handles, count);
};

void c_jm_work_unit_handle::do_not_use_wait_until_all_work_done()
{
    mangled_ppc("?do_not_use_wait_until_all_work_done@c_jm_work_unit_handle@@QAAXXZ");

    while (!m_work_unit->m_job_list.free_list_full())
    {
        thread_sleep(1);
        get_job_manager().invoke_block_callback();
    }
};

void c_jm_work_unit_handle::block_wait_until_done(c_job_handle const & handle)
{
    mangled_ppc("?block_wait_until_done@c_jm_work_unit_handle@@QAAXABVc_job_handle@@@Z");

    while (!m_work_unit->is_done(handle))
    {
        thread_sleep(0);
        get_job_manager().invoke_block_callback();
    }
};

bool c_work_unit::is_done(c_job_handle const & handle)
{
    mangled_ppc("?is_done@c_work_unit@@QAA_NABVc_job_handle@@@Z");

    return m_job_list.is_done(handle);
};

bool c_jm_work_unit_handle::job_is_done(c_job_handle const & handle)
{
    mangled_ppc("?job_is_done@c_jm_work_unit_handle@@QAA_NABVc_job_handle@@@Z");

    return m_work_unit->is_done(handle);
};

void c_jm_work_unit_handle::relinquish_until_done(c_job_handle const & handle)
{
    mangled_ppc("?relinquish_until_done@c_jm_work_unit_handle@@QAAXABVc_job_handle@@@Z");

    unsigned long thread_index = 0;

    while (!m_work_unit->is_done(handle))
    {
        execute_one_job(&m_work_unit->m_scheduler, thread_index);
        get_job_manager().invoke_block_callback();
    }
};

bool c_jm_work_unit_handle::a_depends_on_b(c_job_handle const & a, c_job_handle const & b)
{
    mangled_ppc("?a_depends_on_b@c_jm_work_unit_handle@@QAA_NABVc_job_handle@@0@Z");

    return m_work_unit->m_job_list.depends(a, b);
};

void c_jm_work_unit_handle::thread_entry_point(unsigned long thread_index)
{
    mangled_ppc("?thread_entry_point@c_jm_work_unit_handle@@QAAXK@Z");

    m_work_unit->execute(thread_index);
};

