#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\foundation\\threadlib\\multithreading\\test\\thread_wrapper_tests.cpp"
/* ---------- headers */

#include "foundation\threadlib\multithreading\test\thread_wrapper_tests.h"
#include "baselib\synchronized_value_windows.h"
#include "baselib\system_processor_xenon.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "foundation\baselib\datatypes\flags.h"
#include "foundation\baselib\multithreading\threads\thread_manipulation_xenon.h"
#include "foundation\baselib\multithreading\threads\thread_wrappers.h"
#include "omaha\cseries\cseries.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

void thread_wrapper_test_set_affinity(void);
void thread_wrapper_test_affinity_single_thread(void);
unsigned long thread_wrapper_test_affinity_function(void * parameters);
e_thread_xenon_processor thread_wrapper_build_affinity(long thread_index);
void thread_wrapper_validate_affinity(long processor_affinity, e_thread_xenon_processor expected_processor_affinity);
void thread_wrapper_test_affinity_multiple_threads(void);
void thread_wrapper_test_affinity_thread_crew(void);
void thread_wrapper_test_affinity_suspension_thread_crew(void);

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// void thread_wrapper_run_unit_tests(void);
// void thread_wrapper_test_set_affinity(void);
// void thread_wrapper_test_affinity_single_thread(void);
// public: s_thread_platform_parameters::s_thread_platform_parameters(long, enum e_thread_priority, enum e_thread_xenon_processor, class c_flags_zero_init<enum e_thread_platform_flags, unsigned long, 1>);
// unsigned long thread_wrapper_test_affinity_function(void *);
// enum e_thread_xenon_processor thread_wrapper_build_affinity(long);
// void thread_wrapper_validate_affinity(long, enum e_thread_xenon_processor);
// void thread_wrapper_test_affinity_multiple_threads(void);
// void thread_wrapper_test_affinity_thread_crew(void);
// public: s_thread_platform_parameters::s_thread_platform_parameters(void);
// void thread_wrapper_test_affinity_suspension_thread_crew(void);
// public: c_flags_zero_init<enum e_thread_platform_flags, unsigned long, 1>::c_flags_zero_init<enum e_thread_platform_flags, unsigned long, 1>(void);
// public: void s_flags<enum e_thread_platform_flags, unsigned long, 1>::clear(void);
// public: void s_flags<enum e_thread_platform_flags, unsigned long, 1>::set(enum e_thread_platform_flags, bool);
// public: static bool s_flags<enum e_thread_platform_flags, unsigned long, 1>::valid_bit(enum e_thread_platform_flags);
// public: bool s_flags<enum e_thread_platform_flags, unsigned long, 1>::valid(void) const;
// private: static unsigned long s_flags<enum e_thread_platform_flags, unsigned long, 1>::flag_size_type(enum e_thread_platform_flags);
// private: static unsigned long s_flags<enum e_thread_platform_flags, unsigned long, 1>::make_mask_with_all_valid_bits_on_size_type(void);
// private: static unsigned long s_flags<enum e_thread_platform_flags, unsigned long, 1>::make_N_bit_mask_size_type(enum e_thread_platform_flags);

void thread_wrapper_run_unit_tests(void)
{
    mangled_ppc("?thread_wrapper_run_unit_tests@@YAXXZ");

    thread_wrapper_test_set_affinity();
};

void thread_wrapper_test_set_affinity(void)
{
    mangled_ppc("?thread_wrapper_test_set_affinity@@YAXXZ");

    thread_wrapper_test_affinity_single_thread();
    thread_wrapper_test_affinity_multiple_threads();
    thread_wrapper_test_affinity_thread_crew();
    thread_wrapper_test_affinity_suspension_thread_crew();
};

void thread_wrapper_test_affinity_single_thread(void)
{
    mangled_ppc("?thread_wrapper_test_affinity_single_thread@@YAXXZ");

    long thread_count = system_processor_get_logical_count();
    for (long thread_index = 0; thread_index < thread_count; thread_index++)
    {
        c_synchronized_int32 actual_affinity;
        e_thread_xenon_processor expected_processor = thread_wrapper_build_affinity(thread_index);
        c_flags_zero_init<e_thread_platform_flags, unsigned long, k_thread_platform_flags_count> flags;
        s_thread_platform_parameters platform_parameters(0, _thread_priority_normal, expected_processor, flags);
        c_thread_wrapper thread_wrapper;
        thread_wrapper.setup(thread_wrapper_test_affinity_function, &actual_affinity);
        thread_wrapper.set_name("Test");
        thread_wrapper.start_with_parameters(&platform_parameters);
        thread_wrapper.wait();
        thread_wrapper_validate_affinity(actual_affinity.peek(), expected_processor);
    }
};

unsigned long thread_wrapper_test_affinity_function(void * parameters)
{
    mangled_ppc("?thread_wrapper_test_affinity_function@@YAKPAX@Z");

    c_synchronized_int32 * affinity = static_cast<c_synchronized_int32 *>(parameters);
    e_thread_xenon_processor processor_affinity = thread_get_current_thread_xenon_processor();
    affinity->set(processor_affinity);

    return 0;
};

e_thread_xenon_processor thread_wrapper_build_affinity(long thread_index)
{
    mangled_ppc("?thread_wrapper_build_affinity@@YA?AW4e_thread_xenon_processor@@J@Z");

    e_thread_xenon_processor processor = static_cast<e_thread_xenon_processor>(thread_index);

    return processor;
};

void thread_wrapper_validate_affinity(long processor_affinity, e_thread_xenon_processor expected_processor_affinity)
{
    mangled_ppc("?thread_wrapper_validate_affinity@@YAXJW4e_thread_xenon_processor@@@Z");

    assert_tag_debug_untracked_jul_11_2011(90, expected_processor_affinity==static_cast<e_thread_xenon_processor>(processor_affinity));
};

void thread_wrapper_test_affinity_multiple_threads(void)
{
    mangled_ppc("?thread_wrapper_test_affinity_multiple_threads@@YAXXZ");

    long const k_maximum_threads = 64;
    long core_count = system_processor_get_logical_count();
    c_synchronized_int32 actual_affinities[k_maximum_threads];
    c_thread_wrapper threads[k_maximum_threads];
    long thread_indices[k_maximum_threads];
    c_thread_base::allocate_thread_indices(core_count, thread_indices);

    for (long thread_index = 0; thread_index < core_count; thread_index++)
    {
        c_flags_zero_init<e_thread_platform_flags, unsigned long, k_thread_platform_flags_count> flags;
        e_thread_xenon_processor affinity = thread_wrapper_build_affinity(thread_index);
        flags.set(_thread_platform_flag_create_suspended, true);
        s_thread_platform_parameters platform_parameters(0, _thread_priority_normal, affinity, flags);
        threads[thread_index].setup_with_thread_index(thread_wrapper_test_affinity_function, &actual_affinities[thread_index], thread_indices[thread_index]);
        threads[thread_index].set_name("Test");
        threads[thread_index].start_with_parameters(&platform_parameters);
    }

    for (long thread_index = 0; thread_index < core_count; thread_index++)
    {
        threads[thread_index].resume();
    }

    for (long thread_index = 0; thread_index < core_count; thread_index++)
    {
        threads[thread_index].wait();
    }

    for (long thread_index = 0; thread_index < core_count; thread_index++)
    {
        thread_wrapper_validate_affinity(actual_affinities[thread_index].peek(), thread_wrapper_build_affinity(thread_index));
    }
};

void thread_wrapper_test_affinity_thread_crew(void)
{
    mangled_ppc("?thread_wrapper_test_affinity_thread_crew@@YAXXZ");

    long const k_maximum_threads = 64;
    long thread_count = system_processor_get_logical_count();
    s_thread_platform_parameters platform_parameters[k_maximum_threads];
    c_synchronized_int32 affinities[k_maximum_threads];
    c_thread_crew thread_crew;

    for (long thread_index = 0; thread_index < thread_count; thread_index++)
    {
        platform_parameters[thread_index].processor = thread_wrapper_build_affinity(thread_index);
    }

    thread_crew.setup_array("test", thread_count, thread_wrapper_test_affinity_function, affinities, sizeof(c_synchronized_int32));
    thread_crew.start_with_parameters(platform_parameters, thread_count);
    thread_crew.wait();

    for (long affinity_index = 0; affinity_index < thread_count; affinity_index++)
    {
        thread_wrapper_validate_affinity(affinities[affinity_index].peek(), thread_wrapper_build_affinity(affinity_index));
    }
};

void thread_wrapper_test_affinity_suspension_thread_crew(void)
{
    mangled_ppc("?thread_wrapper_test_affinity_suspension_thread_crew@@YAXXZ");

    long const k_maximum_threads = 64;
    long thread_count = system_processor_get_logical_count();
    s_thread_platform_parameters platform_parameters[k_maximum_threads];
    c_synchronized_int32 affinities[k_maximum_threads];
    c_thread_crew thread_crew;

    for (long thread_index = 0; thread_index < thread_count; thread_index++)
    {
        platform_parameters[thread_index].flags.set(_thread_platform_flag_create_suspended, true);
        platform_parameters[thread_index].processor = thread_wrapper_build_affinity(thread_index);
    }

    for (long affinity_index = 0; affinity_index < thread_count; affinity_index++)
    {
        affinities[affinity_index].set(NONE);
    }

    thread_crew.setup_array("test", thread_count, thread_wrapper_test_affinity_function, affinities, sizeof(c_synchronized_int32));
    thread_crew.start_with_parameters(platform_parameters, thread_count);

    for (long affinity_index = 0; affinity_index < thread_count; affinity_index++)
    {
        assert_tag_debug_untracked_jul_11_2011(225, affinities[affinity_index].peek()==NONE);
    }

    thread_crew.resume();
    thread_crew.wait();

    for (long affinity_index = 0; affinity_index < thread_count; affinity_index++)
    {
        thread_wrapper_validate_affinity(affinities[affinity_index].peek(), thread_wrapper_build_affinity(affinity_index));
    }
};
