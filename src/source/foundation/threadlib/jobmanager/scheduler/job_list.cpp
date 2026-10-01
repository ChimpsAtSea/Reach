#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\foundation\\threadlib\\jobmanager\\scheduler\\job_list.cpp"
/* ---------- headers */

#include "foundation\threadlib\jobmanager\scheduler\job_list.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_macros.h"
#include "foundation\threadlib\multithreading\profiler\mt_profiler_context.h"
#include "foundation\threadlib\multithreading\profiler\mt_profiler_store.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// public: void c_job_list::initialize(struct s_critical_section, struct s_critical_section, struct s_critical_section, struct s_semaphore, unsigned long);
// public: void c_job_list::dispose(void);
// public: bool c_job_list::active_list_empty(void);
// public: bool c_job_list::free_list_full(void);
// public: bool c_job_list::is_done(class c_job_handle const &);
// protected: unsigned short c_job_handle_unsafe::get_index(void) const;
// protected: long c_job_handle_unsafe::get_usage(void) const;
// public: long c_job_handle_internal::get_usage(void) const;
// public: unsigned short const & c_job_handle_internal::get_index(void) const;
// public: class c_job_handle c_job_list::add(class c_job const &, unsigned long);
// public: void c_job_deps::increment_depcount(void);
// public: class c_job_deps & c_job::dependencies(void);
// public: void c_job_handle_internal::set_state(enum ejob_state);
// public: enum ejob_state c_job_handle_internal::get_state(void) const;
// public: void c_job_handle_internal::increment_usage(void);
// public: void c_job_list::lock_activelist(void);
// public: void c_job_list::unlock_activelist(void);
// public: void c_job_list::lock_freelist(void);
// public: void c_job_list::unlock_freelist(void);
// public: class c_job & c_job::operator=(class c_job const &);
// public: class c_job_deps & c_job_deps::operator=(class c_job_deps const &);
// public: class c_interlocked_int32& c_interlocked_int32::operator=(class c_interlocked_int32const &);
// public: void c_job_list::activate(class c_job_handle const &, bool);
// public: void c_job_deps::decrement_depcount(void);
// public: long c_job_deps::depcount(void) const;
// public: void c_job_list::activate_array(class c_job_handle *, unsigned long);
// public: void c_job_list::add_to_active(class c_job_handle *, unsigned long);
// public: void c_job_list::block_until_work_available(bool);
// public: void c_job_list::kick_semaphore(void);
// public: unsigned long c_job_list::get_executable_jobs(class c_job **, class c_job_handle *, unsigned long);
// public: void c_job_list::free_job_array(class c_job **, unsigned long);
// public: void c_job_list::return_to_free_list(class c_job **, unsigned long);
// public: unsigned short c_job_deps::get_deplist(void);
// public: void c_job_list::lock_deps(void);
// public: void c_job_list::unlock_deps(void);
// public: bool c_job_list::depends(class c_job_handle const &, class c_job_handle const &);
// public: unsigned short c_job_deps::set_dependant(unsigned short);
// public: bool c_job_list::allocate_inactive(unsigned long, class c_job_handle *, class c_job **);
// public: void c_job::clear(void);
// public: void c_job_deps::clear(void);
// public: class c_indexed_list<unsigned short, 4096>::iterator c_indexed_list<unsigned short, 4096>::begin(void);
// public: class c_indexed_list<unsigned short, 4096>::iterator c_indexed_list<unsigned short, 4096>::end(void);
// public: long c_indexed_list<unsigned short, 4096>::count(void) const;
// public: long c_indexed_list<unsigned short, 4096>::max_count(void) const;
// public: bool c_indexed_list<unsigned short, 4096>::empty(void) const;
// public: unsigned short & c_indexed_list<unsigned short, 4096>::iterator::operator*(void);
// public: class c_indexed_list<unsigned short, 4096>::iterator & c_indexed_list<unsigned short, 4096>::iterator::operator++(void);
// public: bool c_indexed_list<unsigned short, 4096>::iterator::operator!=(class c_indexed_list<unsigned short, 4096>::iterator const &) const;
// private: unsigned short c_indexed_list<unsigned short, 4096>::get_next(unsigned short) const;
// private: unsigned short c_indexed_list<unsigned short, 4096>::get_prev(unsigned short) const;
// private: unsigned short c_indexed_list<unsigned short, 4096>::get_head(void) const;
// private: unsigned short c_indexed_list<unsigned short, 4096>::get_tail(void) const;
// private: unsigned short & c_indexed_list<unsigned short, 4096>::get_data(unsigned short);
// public: c_indexed_list<unsigned short, 4096>::iterator::iterator(class c_indexed_list<unsigned short, 4096> *, unsigned short, unsigned short, unsigned short);
// public: bool c_indexed_list<unsigned short, 4096>::iterator::operator==(class c_indexed_list<unsigned short, 4096>::iterator const &) const;
// public: void c_indexed_list<unsigned short, 4096>::initialize(void);
// public: void c_indexed_list<unsigned short, 4096>::dispose(void);
// public: void c_indexed_list<unsigned short, 4096>::clear(void);
// public: bool c_indexed_list<unsigned short, 4096>::push_back(unsigned short const &);
// public: void c_indexed_list<unsigned short, 4096>::remove(class c_indexed_list<unsigned short, 4096>::iterator &);
// public: unsigned short c_indexed_list<unsigned short, 4096>::pop_head(void);
// public: void c_indexed_pool<struct s_il_node, 4096>::initialize(void);
// public: void c_indexed_pool<struct s_il_node, 4096>::dispose(void);
// public: unsigned short c_indexed_pool<struct s_il_node, 4096>::alloc_handle(void);
// public: void c_indexed_pool<struct s_il_node, 4096>::free_handle(unsigned short &);
// public: struct s_il_node * c_indexed_pool<struct s_il_node, 4096>::get_element(unsigned short const &);
// private: unsigned short c_indexed_list<unsigned short, 4096>::pop(void);
// private: void c_indexed_list<unsigned short, 4096>::push(struct s_il_node *);
// private: void c_indexed_list<unsigned short, 4096>::remove_indexed(unsigned short);

void c_job_list::initialize(s_critical_section activelist_critical_section, s_critical_section freelist_critical_section, s_critical_section deps_critical_section, s_semaphore semaphore, unsigned long thread_count)
{
    mangled_ppc("?initialize@c_job_list@@QAAXUs_critical_section@@00Us_semaphore@@K@Z");

    m_activelist_critical_section = activelist_critical_section;
    m_freelist_critical_section = freelist_critical_section;
    m_deps_critical_section = deps_critical_section;
    m_semaphore = semaphore;
    m_thread_count = thread_count;

    m_active_list.initialize();
    m_free_list.initialize();

    for (unsigned long index = 0; index < k_jm_max_num_jobs_per_work_unit; index++)
    {
        m_handles[index].m_index = static_cast<unsigned short>(index);
        m_free_list.push_back(static_cast<unsigned short>(index));
    }

    m_dependency_pool.initialize();
};

void c_job_list::dispose()
{
    mangled_ppc("?dispose@c_job_list@@QAAXXZ");

    assert_tag_debug_untracked_jul_11_2011(55, m_free_list.count() == m_free_list.max_count());

    m_free_list.clear();
    m_free_list.dispose();
    m_active_list.dispose();
    m_dependency_pool.dispose();
};

bool c_job_list::active_list_empty()
{
    mangled_ppc("?active_list_empty@c_job_list@@QAA_NXZ");

    return m_active_list.empty();
};

bool c_job_list::free_list_full()
{
    mangled_ppc("?free_list_full@c_job_list@@QAA_NXZ");

    return m_free_list.count() == k_jm_max_num_jobs_per_work_unit;
};

bool c_job_list::is_done(c_job_handle const & handle)
{
    mangled_ppc("?is_done@c_job_list@@QAA_NABVc_job_handle@@@Z");

    unsigned short index = handle.get_index();
    assert_tag_debug_untracked_jul_11_2011(81, index < k_jm_max_num_jobs_per_work_unit);

    c_job_handle_internal & internal_handle = m_handles[index];
    assert_tag_debug_untracked_jul_11_2011(85, internal_handle.get_index() == index);

    if (internal_handle.get_usage() != handle.get_usage())
    {
        return true;
    }

    return false;
};

c_job_handle c_job_list::add(c_job const & job, unsigned long flags)
{
    mangled_ppc("?add@c_job_list@@QAA?AVc_job_handle@@ABVc_job@@K@Z");

    lock_freelist();
    unsigned short index = m_free_list.pop_head();
    unlock_freelist();
    assert_tag_debug_untracked_jul_11_2011(114, index != k_il_index_null);

    c_job_handle_internal & internal_handle = m_handles[index];
    assert_tag_debug_untracked_jul_11_2011(120, internal_handle.get_state() == _e_job_inactive);

    internal_handle.increment_usage();
    m_job_repository[index] = job;

    if (TEST_BIT(flags, 1))
    {
        m_job_repository[index].dependencies().increment_depcount();
        internal_handle.set_state(_e_job_inactive);
    }
    else
    {
        internal_handle.set_state(_e_job_active);
    }

    c_job_handle handle(internal_handle);

    if (TEST_BIT(flags, 2))
    {
        m_job_repository[index].dependencies().m_flags |= FLAG(2);
    }

    lock_activelist();
    m_active_list.push_back(index);
    unlock_activelist();

    if (!TEST_BIT(flags, 1))
    {
        kick_semaphore();
    }

    return handle;
};

void c_job_list::activate(c_job_handle const & handle, bool kick)
{
    mangled_ppc("?activate@c_job_list@@QAAXABVc_job_handle@@_N@Z");

    unsigned short index = handle.get_index();
    assert_tag_debug_untracked_jul_11_2011(176, m_job_repository[index].dependencies().depcount() > 0);

    c_job_handle_internal & internal_handle = m_handles[index];
    assert_tag_debug_untracked_jul_11_2011(180, internal_handle.get_state() == _e_job_inactive);

    internal_handle.set_state(_e_job_active);
    m_job_repository[index].dependencies().decrement_depcount();

    if (kick)
    {
        kick_semaphore();
    }
};

void c_job_list::activate_array(c_job_handle * handles, unsigned long count)
{
    mangled_ppc("?activate_array@c_job_list@@QAAXPAVc_job_handle@@K@Z");

    for (unsigned long index = 0; index < count; index++)
    {
        activate(handles[index], false);
    }

    kick_semaphore();
};

void c_job_list::add_to_active(c_job_handle * handles, unsigned long count)
{
    mangled_ppc("?add_to_active@c_job_list@@QAAXPAVc_job_handle@@K@Z");

    lock_activelist();

    for (unsigned long index = 0; index < count; index++)
    {
        m_active_list.push_back(handles[index].get_index());
    }

    unlock_activelist();
};

void c_job_list::block_until_work_available(bool unused)
{
    mangled_ppc("?block_until_work_available@c_job_list@@QAAX_N@Z");

    semaphore_take_internal(m_semaphore);
};

void c_job_list::kick_semaphore()
{
    mangled_ppc("?kick_semaphore@c_job_list@@QAAXXZ");

    for (unsigned long index = 0; index < m_thread_count; index++)
    {
        semaphore_release_internal(m_semaphore, NULL);
    }
};

unsigned long c_job_list::get_executable_jobs(c_job ** jobs, c_job_handle * handles, unsigned long max_count)
{
    mangled_ppc("?get_executable_jobs@c_job_list@@QAAKPAPAVc_job@@PAVc_job_handle@@K@Z");

    lock_activelist();

    c_job * job = NULL;
    c_indexed_list<unsigned short, k_jm_max_num_jobs_per_work_unit>::iterator it = m_active_list.begin();
    c_indexed_list<unsigned short, k_jm_max_num_jobs_per_work_unit>::iterator end = m_active_list.end();
    unsigned long num_found = 0;
    bool timed_job = false;

    while (!timed_job && it != end && job == NULL && num_found < max_count)
    {
        unsigned short index = *it;
        if (m_job_repository[index].dependencies().depcount() == 0)
        {
            handles[num_found].m_index = index;
            jobs[num_found] = &m_job_repository[index];
            m_active_list.remove(it);
            m_handles[index].set_state(_e_job_executing);
            timed_job = (jobs[num_found]->dependencies().m_flags & FLAG(2)) > 0;
            num_found++;
        }
        ++it;
    }

    vassert_tag_debug_untracked_jul_11_2011(421, !timed_job || num_found == 1, "only issue 1 timed job per call");

    unlock_activelist();

    return num_found;
};

void c_job_list::free_job_array(c_job ** jobs, unsigned long count)
{
    mangled_ppc("?free_job_array@c_job_list@@QAAXPAPAVc_job@@K@Z");

    lock_freelist();

    for (unsigned long index = 0; index < count; index++)
    {
        m_free_list.push_back(static_cast<unsigned short>(jobs[index] - m_job_repository));
    }

    unlock_freelist();
};

void c_job_list::return_to_free_list(c_job ** jobs, unsigned long count)
{
    mangled_ppc("?return_to_free_list@c_job_list@@QAAXPAPAVc_job@@K@Z");

    static unsigned short profiler_index = profiler_get_index("c_job_list", "return_to_free_list", static_cast<e_mt_color>(10));
    c_mtp_profiler_context profiler_context(profiler_index);

    bool free_jobs = true;
    for (unsigned long job_index = 0; job_index < count; job_index++)
    {
        unsigned short index = static_cast<unsigned short>(jobs[job_index] - m_job_repository);
        m_handles[index].set_state(_e_job_inactive);

        lock_deps();
        m_handles[index].increment_usage();
        unlock_deps();

        unsigned short deplist = jobs[job_index]->dependencies().get_deplist();
        if (deplist != k_il_index_null)
        {
            lock_deps();
            while (deplist != k_il_index_null)
            {
                s_il_node * node = m_dependency_pool.get_element(deplist);
                unsigned short dependant_index = node->prev;
                m_job_repository[dependant_index].dependencies().decrement_depcount();

                unsigned short freed_handle = deplist;
                deplist = node->next;
                m_dependency_pool.free_handle(freed_handle);
            }
            unlock_deps();

            kick_semaphore();
        }
    }

    if (free_jobs)
    {
        free_job_array(jobs, count);
    }
};

bool c_job_list::depends(c_job_handle const & external_handle_a, c_job_handle const & external_handle_b)
{
    mangled_ppc("?depends@c_job_list@@QAA_NABVc_job_handle@@0@Z");

    unsigned short index_b = external_handle_b.get_index();
    c_job_handle_internal & internal_handle_b = m_handles[index_b];
    bool result = false;

    lock_deps();

    if (internal_handle_b.get_usage() == external_handle_b.get_usage())
    {
        result = true;

        unsigned short index_a = external_handle_a.get_index();
        c_job_handle_internal & internal_handle_a = m_handles[index_a];
        assert_tag_debug_untracked_jul_11_2011(584, internal_handle_a.get_state() == _e_job_inactive);
        assert_tag_debug_untracked_jul_11_2011(585, internal_handle_a.get_usage() == external_handle_a.get_usage());

        c_job & job_b = m_job_repository[internal_handle_b.get_index()];
        vassert_tag_debug_untracked_jul_11_2011(593, !TEST_BIT(job_b.dependencies().m_flags, 2), "timed jobs cannot be depended upon");

        unsigned short dep_handle = m_dependency_pool.alloc_handle();
        s_il_node * node = m_dependency_pool.get_element(dep_handle);
        node->prev = internal_handle_a.get_index();
        node->next = job_b.dependencies().set_dependant(dep_handle);

        c_job & job_a = m_job_repository[internal_handle_a.get_index()];
        job_a.dependencies().increment_depcount();
    }

    unlock_deps();

    return result;
};

bool c_job_list::allocate_inactive(unsigned long num, c_job_handle * handles, c_job ** jobs)
{
    mangled_ppc("?allocate_inactive@c_job_list@@QAA_NKPAVc_job_handle@@PAPAVc_job@@@Z");

    assert_tag_debug_untracked_jul_11_2011(620, m_free_list.count() > static_cast<int32>(num));

    lock_freelist();

    for (unsigned long job_index = 0; job_index < num; job_index++)
    {
        unsigned short index = m_free_list.pop_head();
        assert_tag_debug_untracked_jul_11_2011(627, index != k_il_index_null);

        c_job_handle_internal & internal_handle = m_handles[index];
        internal_handle.increment_usage();
        assert_tag_debug_untracked_jul_11_2011(634, internal_handle.get_state() == _e_job_inactive);
        assert_tag_debug_untracked_jul_11_2011(635, index == internal_handle.get_index());

        internal_handle.set_state(_e_job_inactive);
        handles[job_index] = c_job_handle(internal_handle);
        jobs[job_index] = &m_job_repository[index];
        jobs[job_index]->clear();
        jobs[job_index]->dependencies().increment_depcount();
    }

    unlock_freelist();

    return true;
};
