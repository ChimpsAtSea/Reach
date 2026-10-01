#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\foundation\\baselib\\multithreading\\threads\\thread_wrappers.cpp"
/* ---------- headers */

#include <excpt.h>

#include "foundation\baselib\multithreading\threads\thread_wrappers.h"
#include "baselib\system_exception_windows.h"
#include "baselib\thread_execution_windows.h"
#include "baselib\thread_manipulation.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_memory.h"
#include "foundation\baselib\multithreading\synchronization\synchronization_manager.h"
#include "omaha\cseries\cseries.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// public: c_thread_base::c_thread_base(void);
// merged_84C3A3E8;
// public: virtual c_thread_base::~c_thread_base(void);
// public: void c_thread_base::start_with_parameters(struct s_thread_platform_parameters const *);
// public: void c_thread_base::start(void);
// public: void c_thread_base::resume(void);
// public: void c_thread_base::wait(void);
// public: bool c_thread_base::wait_timeout(long);
// public: void c_thread_base::stop(void);
// public: char const * c_thread_base::get_name(void) const;
// public: void c_thread_base::set_name(char const *);
// public: void c_thread_base::set_name_by_group(char const *, long, long);
// public: long c_thread_base::get_thread_index(void) const;
// public: void c_thread_base::set_thread_index(long);
// public: static void c_thread_base::allocate_thread_indices(long, long *);
// public: struct s_thread_id c_thread_base::get_thread_id(void) const;
// public: unsigned long c_thread_base::do_work_wrapper(void);
// public: unsigned long c_thread_base::get_exit_code(void) const;
// public: bool c_thread_base::has_been_started(void) const;
// public: bool c_thread_base::has_crashed(void) const;
// protected: void c_thread_base::validate_graceful_exit(void) const;
// public: void c_thread_base::on_crash(void);
// public: static unsigned long c_thread_base::entry_point(void *);
// public: c_thread_wrapper::c_thread_wrapper(void);
// merged_84C3AED0;
// ??0c_thread_wrapper@@QAA@Q6AKPAX@Z0@Z;
// ?setup@c_thread_wrapper@@QAAXQ6AKPAX@Z0@Z;
// ?setup_with_thread_index@c_thread_wrapper@@QAAXQ6AKPAX@Z0J@Z;
// protected: virtual unsigned long c_thread_wrapper::do_work(void);
// public: c_thread_crew::c_thread_crew(void);
// public: s_static_array<class c_thread_wrapper, 16>::s_static_array<class c_thread_wrapper, 16>(void);
// ?setup@c_thread_crew@@QAAXPBDJQ6AKPAX@ZPAPAX@Z;
// ?setup_array@c_thread_crew@@QAAXPBDJQ6AKPAX@Z1I@Z;
// public: void c_thread_crew::start(void);
// public: void c_thread_crew::start_with_parameters(struct s_thread_platform_parameters const *, long);
// public: void c_thread_crew::resume(void);
// public: void c_thread_crew::wait(void);
// public: class c_thread_wrapper * c_thread_crew::get_thread(long);
// unsigned long thread_exception_handler(class c_thread_base *, struct s_exception_pointers *, struct s_exception_information *);
// public: static long s_static_array<class c_thread_wrapper, 16>::get_count(void);
// public: void ** s_static_array<void *, 16>::get_elements(void);
// public: bool s_flags<enum e_thread_platform_flags, unsigned long, 1>::test(enum e_thread_platform_flags) const;
// public: class c_thread_wrapper & s_static_array<class c_thread_wrapper, 16>::operator[]<long>(long);
// public: static bool s_static_array<class c_thread_wrapper, 16>::valid<long>(long);

c_thread_base::c_thread_base(void) :
    m_thread_index(NONE),
    m_exit_code(NONE),
    m_has_crashed(0)
{
    mangled_ppc("??0c_thread_base@@QAA@XZ");

    m_name.set("unnamed thread");
    m_thread_handle = k_thread_handle_invalid;
    m_thread_id = k_thread_id_invalid;
    csmemset(&m_exception_information, 0, sizeof(m_exception_information));
};

//merged_84C3A3E8
//{
//    mangled_ppc("merged_84C3A3E8");
//};

c_thread_base::~c_thread_base(void)
{
    mangled_ppc("??1c_thread_base@@UAA@XZ");

    stop();
};

void c_thread_base::start_with_parameters(s_thread_platform_parameters const * platform_parameters)
{
    mangled_ppc("?start_with_parameters@c_thread_base@@QAAXPBUs_thread_platform_parameters@@@Z");

    bool resume_thread = true;
    unsigned int stack_size = 0;
    if (platform_parameters)
    {
        stack_size = platform_parameters->stack_size;
    }

    assert_tag_debug_untracked_jul_11_2011(64, m_thread_index!=NONE);

    m_thread_handle = thread_create(entry_point, this, _thread_creation_state_suspended, _thread_creation_inheritance_none, stack_size, &m_thread_id);
    assert_tag_debug_untracked_jul_11_2011(74, thread_handle_valid(m_thread_handle));
    assert_tag_debug_untracked_jul_11_2011(75, thread_id_valid(m_thread_id));

    if (platform_parameters)
    {
        thread_set_priority(m_thread_handle, platform_parameters->priority);
        thread_set_xenon_processor(m_thread_handle, platform_parameters->processor);
        resume_thread = !platform_parameters->flags.test(_thread_platform_flag_create_suspended);
    }

    if (resume_thread)
    {
        resume();
    }
};

void c_thread_base::start(void)
{
    mangled_ppc("?start@c_thread_base@@QAAXXZ");

    start_with_parameters(NULL);
};

void c_thread_base::resume(void)
{
    mangled_ppc("?resume@c_thread_base@@QAAXXZ");

    assert_tag_debug_untracked_jul_11_2011(108, thread_handle_valid(m_thread_handle));
    thread_resume(m_thread_handle);
};

void c_thread_base::wait(void)
{
    mangled_ppc("?wait@c_thread_base@@QAAXXZ");

    bool finished = false;
    long const wait_time = 5000;
    while (!finished)
    {
        finished = thread_wait_timeout(m_thread_handle, wait_time);
        assert_tag_debug_untracked_jul_11_2011(127, !m_has_crashed);
    }

    validate_graceful_exit();
};

bool c_thread_base::wait_timeout(long timeout)
{
    mangled_ppc("?wait_timeout@c_thread_base@@QAA_NJ@Z");

    bool finished = thread_wait_timeout(m_thread_handle, timeout);
    if (finished)
    {
        validate_graceful_exit();
    }

    return finished;
};

void c_thread_base::stop(void)
{
    mangled_ppc("?stop@c_thread_base@@QAAXXZ");

    if (thread_handle_valid(m_thread_handle))
    {
        thread_destroy(m_thread_handle);
        m_thread_handle = k_thread_handle_invalid;
    }
};

char const * c_thread_base::get_name(void) const
{
    mangled_ppc("?get_name@c_thread_base@@QBAPBDXZ");

    char const * name = "";
    name = m_name.get_string();

    return name;
};

void c_thread_base::set_name(char const * name)
{
    mangled_ppc("?set_name@c_thread_base@@QAAXPBD@Z");

    m_name.set(name);
};

void c_thread_base::set_name_by_group(char const * name, long index, long count)
{
    mangled_ppc("?set_name_by_group@c_thread_base@@QAAXPBDJJ@Z");

    m_name.print("%s #%d/%d", name, index, count);
};

long c_thread_base::get_thread_index(void) const
{
    mangled_ppc("?get_thread_index@c_thread_base@@QBAJXZ");

    return m_thread_index;
};

void c_thread_base::set_thread_index(long thread_index)
{
    mangled_ppc("?set_thread_index@c_thread_base@@QAAXJ@Z");

    assert_tag_debug_untracked_jul_11_2011(197, thread_index!=NONE);
    m_thread_index = thread_index;
};

void c_thread_base::allocate_thread_indices(long thread_count, long * out_thread_indices)
{
    mangled_ppc("?allocate_thread_indices@c_thread_base@@SAXJPAJ@Z");

    synchronization_declare_threads(thread_count, out_thread_indices);
};

s_thread_id c_thread_base::get_thread_id(void) const
{
    mangled_ppc("?get_thread_id@c_thread_base@@QBA?AUs_thread_id@@XZ");

    assert_tag_debug_untracked_jul_11_2011(211, thread_id_valid(m_thread_id));

    return m_thread_id;
};

unsigned long c_thread_base::do_work_wrapper(void)
{
    mangled_ppc("?do_work_wrapper@c_thread_base@@QAAKXZ");

    __try
    {
        m_exit_code.set(do_work());
    }
    __except (thread_exception_handler(this, reinterpret_cast<s_exception_pointers *>(GetExceptionInformation()), &m_exception_information))
    {
    }

    return m_exit_code;
};

unsigned long c_thread_base::get_exit_code(void) const
{
    mangled_ppc("?get_exit_code@c_thread_base@@QBAKXZ");

    return m_exit_code;
};

bool c_thread_base::has_been_started(void) const
{
    mangled_ppc("?has_been_started@c_thread_base@@QBA_NXZ");

    return thread_handle_valid(m_thread_handle);
};

bool c_thread_base::has_crashed(void) const
{
    mangled_ppc("?has_crashed@c_thread_base@@QBA_NXZ");

    return m_has_crashed != 0;
};

void c_thread_base::validate_graceful_exit(void) const
{
    mangled_ppc("?validate_graceful_exit@c_thread_base@@IBAXXZ");

    dassert_tag_debug_untracked_jul_11_2011(258, has_been_started(), "you never started this thread");
    vassert_tag_debug_untracked_jul_11_2011(259, !m_has_crashed, "thread id %d handle %p has crashed, see m_exception_information for information", m_thread_id, m_thread_handle);
    dassert_tag_debug_untracked_jul_11_2011(260, static_cast<unsigned long>(m_exit_code) == 0, "thread returned error on exit");
};

void c_thread_base::on_crash(void)
{
    mangled_ppc("?on_crash@c_thread_base@@QAAXXZ");

    m_exit_code.set(NONE);
    m_has_crashed.set(1);
};

unsigned long c_thread_base::entry_point(void * parameters)
{
    mangled_ppc("?entry_point@c_thread_base@@SAKPAX@Z");

    unsigned long exit_code = NONE;
    c_thread_base * thread_base = static_cast<c_thread_base *>(parameters);
    if (thread_base)
    {
        long thread_index = thread_base->get_thread_index();
        dassert_tag_debug_untracked_jul_11_2011(282, thread_index != NONE, "must set index before starting thread, use c_thread_base::allocate_thread_indices");

        synchronization_register_thread(thread_index);
        thread_set_current_thread_name(thread_base->get_name());
        exit_code = thread_base->do_work_wrapper();
        synchronization_unregister_thread(thread_index);
    }

    return exit_code;
};

c_thread_wrapper::c_thread_wrapper(void) :
    m_thread_function(NULL),
    m_thread_parameters(NULL)
{
    mangled_ppc("??0c_thread_wrapper@@QAA@XZ");
};

//merged_84C3AED0
//{
//    mangled_ppc("merged_84C3AED0");
//};

c_thread_wrapper::c_thread_wrapper(unsigned long (* const thread_function)(void *), void * thread_parameters)
{
    mangled_ppc("??0c_thread_wrapper@@QAA@Q6AKPAX@Z0@Z");

    setup(thread_function, thread_parameters);
};

void c_thread_wrapper::setup(unsigned long (* const thread_function)(void *), void * thread_parameters)
{
    mangled_ppc("?setup@c_thread_wrapper@@QAAXQ6AKPAX@Z0@Z");

    long thread_index = NONE;
    allocate_thread_indices(1, &thread_index);
    setup_with_thread_index(thread_function, thread_parameters, thread_index);
};

void c_thread_wrapper::setup_with_thread_index(unsigned long (* const thread_function)(void *), void * thread_parameters, long thread_index)
{
    mangled_ppc("?setup_with_thread_index@c_thread_wrapper@@QAAXQ6AKPAX@Z0J@Z");

    assert_tag_debug_untracked_jul_11_2011(332, thread_function!=NULL);

    m_thread_function = thread_function;
    m_thread_parameters = thread_parameters;
    set_thread_index(thread_index);
};

unsigned long c_thread_wrapper::do_work(void)
{
    mangled_ppc("?do_work@c_thread_wrapper@@MAAKXZ");

    unsigned long result = NONE;
    assert_tag_debug_untracked_jul_11_2011(344, m_thread_function);

    if (m_thread_function)
    {
        result = m_thread_function(m_thread_parameters);
    }

    return result;
};

c_thread_crew::c_thread_crew(void) :
    m_count(0)
{
    mangled_ppc("??0c_thread_crew@@QAA@XZ");
};

void c_thread_crew::setup(char const * name, long count, unsigned long (* const thread_function)(void *), void ** thread_parameters)
{
    mangled_ppc("?setup@c_thread_crew@@QAAXPBDJQ6AKPAX@ZPAPAX@Z");

    assert_tag_debug_untracked_jul_11_2011(369, count>0 && count<=m_threads.get_count());
    m_count = count;

    s_static_array<long, k_maximum_crew_size> thread_indices;
    c_thread_base::allocate_thread_indices(count, thread_indices.get_elements());

    for (long thread_index = 0; thread_index < count; thread_index++)
    {
        m_threads[thread_index].setup_with_thread_index(thread_function, thread_parameters[thread_index], thread_indices[thread_index]);
        m_threads[thread_index].set_name_by_group(name, thread_index, count);
    }
};

void c_thread_crew::setup_array(char const * name, long count, unsigned long (* const thread_function)(void *), void * thread_parameters_array, unsigned int thread_parameters_size)
{
    mangled_ppc("?setup_array@c_thread_crew@@QAAXPBDJQ6AKPAX@Z1I@Z");

    s_static_array<void *, k_maximum_crew_size> thread_parameters;
    for (long thread_index = 0; thread_index < count; thread_index++)
    {
        thread_parameters[thread_index] = offset_pointer(thread_parameters_array, thread_index * thread_parameters_size);
    }

    setup(name, count, thread_function, thread_parameters.get_elements());
};

void c_thread_crew::start(void)
{
    mangled_ppc("?start@c_thread_crew@@QAAXXZ");

    start_with_parameters(NULL, 0);
};

void c_thread_crew::start_with_parameters(s_thread_platform_parameters const * platform_parameters, long count)
{
    mangled_ppc("?start_with_parameters@c_thread_crew@@QAAXPBUs_thread_platform_parameters@@J@Z");

    assert_tag_debug_untracked_jul_11_2011(412, m_count==count || (platform_parameters==NULL && count==0));

    for (long thread_index = 0; thread_index < m_count; thread_index++)
    {
        s_thread_platform_parameters const * thread_platform_parameters = platform_parameters ? &platform_parameters[thread_index] : NULL;
        m_threads[thread_index].start_with_parameters(thread_platform_parameters);
    }
};

void c_thread_crew::resume(void)
{
    mangled_ppc("?resume@c_thread_crew@@QAAXXZ");

    for (long thread_index = 0; thread_index < m_count; thread_index++)
    {
        m_threads[thread_index].resume();
    }
};

void c_thread_crew::wait(void)
{
    mangled_ppc("?wait@c_thread_crew@@QAAXXZ");

    for (long thread_index = 0; thread_index < m_count; thread_index++)
    {
        m_threads[thread_index].wait();
    }
};

c_thread_wrapper * c_thread_crew::get_thread(long thread_index)
{
    mangled_ppc("?get_thread@c_thread_crew@@QAAPAVc_thread_wrapper@@J@Z");

    return &m_threads[thread_index];
};

unsigned long thread_exception_handler(c_thread_base * thread, s_exception_pointers * exception_pointers, s_exception_information * exception_information)
{
    mangled_ppc("?thread_exception_handler@@YAKPAVc_thread_base@@PAUs_exception_pointers@@PAUs_exception_information@@@Z");

    system_build_exception_information(exception_pointers, exception_information);
    if (thread)
    {
        thread->on_crash();
        for (;;)
        {
            thread_sleep(1000);
        }
    }

    return 1;
};
