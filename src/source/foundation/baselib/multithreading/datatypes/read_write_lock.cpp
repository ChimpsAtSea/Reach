#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\foundation\\baselib\\multithreading\\datatypes\\read_write_lock.cpp"
/* ---------- headers */

#include "foundation\baselib\multithreading\datatypes\read_write_lock.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_macros.h"
#include "core\corelib\cseries\cseries_memory.h"
#include "foundation\baselib\multithreading\synchronization\synchronization_dependencies.h"
#include "foundation\baselib\multithreading\synchronization\synchronization_manager.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// public: void c_read_write_lock::initialize_automatic(char const *, char const *);
// public: void c_read_write_lock::initialize_manual(struct s_critical_section, struct s_semaphore);
// public: void c_read_write_lock::dispose(void);
// public: bool c_read_write_lock::ready_for_use(void) const;
// public: void c_read_write_lock::get_synchronization_objects(struct s_critical_section *, struct s_semaphore *) const;
// public: void c_read_write_lock::read_lock(void);
// public: bool c_read_write_lock::read_try_and_lock(void);
// public: void c_read_write_lock::read_unlock(void);
// public: void c_read_write_lock::write_lock(void);
// public: bool c_read_write_lock::write_try_and_lock(void);
// public: void c_read_write_lock::write_unlock(void);
// public: static void c_read_write_lock::declare_synchronization_objects(long, long, char const *, char const *, struct s_critical_section *, struct s_semaphore *);

void c_read_write_lock::initialize_automatic(char const * critical_section_name, char const * semaphore_name)
{
    mangled_ppc("?initialize_automatic@c_read_write_lock@@QAAXPBD0@Z");

    assert_tag_debug_untracked_jul_11_2011(30, !m_initialized);

    s_critical_section write_lock;
    s_semaphore read_lock;
    declare_synchronization_objects(k_synchronization_group_base, 0, critical_section_name, semaphore_name, &write_lock, &read_lock);
    initialize_manual(write_lock, read_lock);
};

void c_read_write_lock::initialize_manual(s_critical_section write_lock, s_semaphore read_lock)
{
    mangled_ppc("?initialize_manual@c_read_write_lock@@QAAXUs_critical_section@@Us_semaphore@@@Z");

    assert_tag_debug_untracked_jul_11_2011(39, !m_initialized);

    m_write_lock = write_lock;
    m_read_lock = read_lock;
    m_max_readers = semaphore_get_maximum_count(read_lock);
    dassert_tag_debug_untracked_jul_11_2011(43, semaphore_get_initial_count(read_lock) == m_max_readers, "the read-write lock semaphore must be set up to be initially available");

    m_initialized = true;
};

void c_read_write_lock::dispose(void)
{
    mangled_ppc("?dispose@c_read_write_lock@@QAAXXZ");

    m_initialized = false;
};

bool c_read_write_lock::ready_for_use(void) const
{
    mangled_ppc("?ready_for_use@c_read_write_lock@@QBA_NXZ");

    bool result = false;
    if (m_initialized)
    {
        long synchronization_group_index = SYNCHRONIZATION_OBJECT_GROUP(m_read_lock.object_id);
        result = synchronization_object_group_created(synchronization_group_index);
    }

    return result;
};

void c_read_write_lock::get_synchronization_objects(s_critical_section * out_write_lock, s_semaphore * out_read_lock) const
{
    mangled_ppc("?get_synchronization_objects@c_read_write_lock@@QBAXPAUs_critical_section@@PAUs_semaphore@@@Z");

    assert_tag_debug_untracked_jul_11_2011(73, m_initialized);
    assert_tag_debug_untracked_jul_11_2011(74, out_write_lock);
    assert_tag_debug_untracked_jul_11_2011(75, out_read_lock);

    *out_write_lock = m_write_lock;
    *out_read_lock = m_read_lock;
};

void c_read_write_lock::read_lock(void)
{
    mangled_ppc("?read_lock@c_read_write_lock@@QAAXXZ");

    assert_tag_debug_untracked_jul_11_2011(83, ready_for_use());
    dassert_tag_debug_untracked_jul_11_2011(85, semaphore_get_current_thread_reference_count(m_read_lock) < m_max_readers, "can't take read lock while holding the write lock (this may also be reentrancy of greater than max-readers which is not supported)");

    semaphore_take_internal(m_read_lock);
};

bool c_read_write_lock::read_try_and_lock(void)
{
    mangled_ppc("?read_try_and_lock@c_read_write_lock@@QAA_NXZ");

    assert_tag_debug_untracked_jul_11_2011(93, ready_for_use());
    dassert_tag_debug_untracked_jul_11_2011(95, semaphore_get_current_thread_reference_count(m_read_lock) < m_max_readers, "can't take read lock while holding the write lock (this may also be reentrancy of greater than max-readers which is not supported)");

    return semaphore_try_and_take_internal(m_read_lock);
};

void c_read_write_lock::read_unlock(void)
{
    mangled_ppc("?read_unlock@c_read_write_lock@@QAAXXZ");

    assert_tag_debug_untracked_jul_11_2011(103, ready_for_use());

    semaphore_release_internal(m_read_lock, NULL);
};

void c_read_write_lock::write_lock(void)
{
    mangled_ppc("?write_lock@c_read_write_lock@@QAAXXZ");

    assert_tag_debug_untracked_jul_11_2011(110, ready_for_use());
    dassert_tag_debug_untracked_jul_11_2011(112, semaphore_get_current_thread_reference_count(m_read_lock) == 0, "can't take write lock while holding the read lock (this may also be a reentry to the write lock which is not supported)");

    c_critical_section_scope critical_section_scope(m_write_lock);
    for (long reader_index = 0; reader_index < m_max_readers; reader_index++)
    {
        semaphore_take_internal(m_read_lock);
    }
};

bool c_read_write_lock::write_try_and_lock(void)
{
    mangled_ppc("?write_try_and_lock@c_read_write_lock@@QAA_NXZ");

    assert_tag_debug_untracked_jul_11_2011(132, ready_for_use());
    dassert_tag_debug_untracked_jul_11_2011(134, semaphore_get_current_thread_reference_count(m_read_lock) == 0, "can't take write lock while holding the read lock (this may also be a reentry to the write lock which is not supported)");

    bool result = false;
    if (critical_section_try_and_enter_internal(m_write_lock))
    {
        long reader_index;
        for (reader_index = 0; reader_index < m_max_readers && semaphore_try_and_take_internal(m_read_lock); reader_index++)
        {
        }

        if (reader_index == m_max_readers)
        {
            result = true;
        }
        else
        {
            for (; reader_index > 0; reader_index--)
            {
                semaphore_release_internal(m_read_lock, NULL);
            }
        }

        critical_section_leave_internal(m_write_lock, _critical_section_non_recursive);
    }

    return result;
};

void c_read_write_lock::write_unlock(void)
{
    mangled_ppc("?write_unlock@c_read_write_lock@@QAAXXZ");

    assert_tag_debug_untracked_jul_11_2011(167, ready_for_use());

    for (long reader_index = 0; reader_index < m_max_readers; reader_index++)
    {
        semaphore_release_internal(m_read_lock, NULL);
    }
};

void c_read_write_lock::declare_synchronization_objects(long synchronization_group_index, long maximum_readers, char const * critical_section_name, char const * semaphore_name, s_critical_section * out_write_lock, s_semaphore * out_read_lock)
{
    mangled_ppc("?declare_synchronization_objects@c_read_write_lock@@SAXJJPBD0PAUs_critical_section@@PAUs_semaphore@@@Z");

    assert_tag_debug_untracked_jul_11_2011(188, out_write_lock);
    assert_tag_debug_untracked_jul_11_2011(189, out_read_lock);

    s_critical_section write_lock;
    s_semaphore read_lock;

    {
        s_critical_section_definition critical_section_definition;
        csmemset(&critical_section_definition, 0, sizeof(critical_section_definition));
        critical_section_definition.name = critical_section_name;
        write_lock = critical_section_declare(synchronization_group_index, &critical_section_definition);
    }

    {
        long semaphore_maximum_count = maximum_readers;
        if (semaphore_maximum_count > 0)
        {
            assert_tag_debug_untracked_jul_11_2011(205, semaphore_maximum_count<=k_synchronization_maximum_registered_threads);
        }
        else
        {
            semaphore_maximum_count = k_synchronization_maximum_registered_threads;
        }

        s_semaphore_definition semaphore_definition;
        csmemset(&semaphore_definition, 0, sizeof(semaphore_definition));
        semaphore_definition.name = semaphore_name;
        semaphore_definition.initial_count = semaphore_maximum_count;
        semaphore_definition.maximum_count = semaphore_maximum_count;
        read_lock = semaphore_declare(synchronization_group_index, &semaphore_definition);
    }

    critical_section_semaphore_dependency(write_lock, read_lock);

    *out_write_lock = write_lock;
    *out_read_lock = read_lock;
};
