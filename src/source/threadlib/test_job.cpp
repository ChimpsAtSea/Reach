/* ---------- headers */

#include "threadlib\test_job.h"
#include "baselib\synchronized_value_windows.h"
#include "baselib\system_time_windows.h"
#include "foundation\baselib\errors\output\output_globals.h"
#include "foundation\threadlib\multithreading\profiler\mt_profiler_context.h"
#include "foundation\threadlib\multithreading\profiler\mt_profiler_store.h"
#include "threadlib\jm_types.h"
#include "threadlib\job.h"
#include "threadlib\job_signature.h"
#include "threadlib\work_unit_handle.h"
#include "core\corelib\cseries\cseries_macros.h"

/* ---------- constants */

/* ---------- definitions */

// $TODO: also defined (identically) in job_manager_test.cpp; move to a shared header
struct s_job_timing
{
    __int64 start;
    __int64 end;
    unsigned long thread;
};
static_assert(sizeof(s_job_timing) == 0x18, "s_job_timing");

/* ---------- prototypes */

void delay(unsigned long delay_time);
void test_entry_point(unsigned long parameter0, unsigned long parameter1, unsigned long parameter2, unsigned long parameter3, unsigned long thread_index, c_job_handle job_handle, c_jm_work_unit_handle work_unit);
void test_entry_point2(unsigned long parameter0, unsigned long parameter1, unsigned long parameter2, unsigned long parameter3, unsigned long thread_index, c_job_handle job_handle, c_jm_work_unit_handle work_unit);
void test_entry_point3(unsigned long parameter0, unsigned long parameter1, unsigned long parameter2, unsigned long parameter3, unsigned long thread_index, c_job_handle job_handle, c_jm_work_unit_handle work_unit);
void example_entry_point(unsigned long parameter0, unsigned long parameter1, unsigned long parameter2, unsigned long parameter3, unsigned long thread_index, c_job_handle job_handle, c_jm_work_unit_handle work_unit);
void test_entry_point4(unsigned long parameter0, unsigned long parameter1, unsigned long parameter2, unsigned long parameter3, unsigned long thread_index, c_job_handle job_handle, c_jm_work_unit_handle work_unit);

/* ---------- globals */

c_job_signature test_signature(test_entry_point);
c_job_signature test_signature2(test_entry_point2);
c_job_signature test_signature3(test_entry_point3);
c_job_signature example_signature(example_entry_point);
c_job_signature test_signature4(test_entry_point4);

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// class c_job_signature test_signature; // "?test_signature@@3Vc_job_signature@@A"
// class c_job_signature test_signature2; // "?test_signature2@@3Vc_job_signature@@A"
// class c_job_signature test_signature3; // "?test_signature3@@3Vc_job_signature@@A"
// class c_job_signature example_signature; // "?example_signature@@3Vc_job_signature@@A"
// class c_job_signature test_signature4; // "?test_signature4@@3Vc_job_signature@@A"

// void delay(unsigned long);
// void test_entry_point(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, class c_job_handle, class c_jm_work_unit_handle);
// void test_entry_point2(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, class c_job_handle, class c_jm_work_unit_handle);
// void test_entry_point3(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, class c_job_handle, class c_jm_work_unit_handle);
// void example_entry_point(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, class c_job_handle, class c_jm_work_unit_handle);
// void test_entry_point4(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, class c_job_handle, class c_jm_work_unit_handle);
// void test_signature::`dynamic atexit destructor'(void);
// void test_signature2::`dynamic atexit destructor'(void);
// void test_signature3::`dynamic atexit destructor'(void);
// void example_signature::`dynamic atexit destructor'(void);
// void test_signature4::`dynamic atexit destructor'(void);

void delay(unsigned long delay_time)
{
    mangled_ppc("?delay@@YAXK@Z");

    double current_time = static_cast<double>(system_performance_timer_get()) / static_cast<double>(system_performance_timer_frequency() / 1000 / 1000);
    double end_time = delay_time + current_time;
    while (end_time > current_time)
    {
        current_time = static_cast<double>(system_performance_timer_get()) / static_cast<double>(system_performance_timer_frequency() / 1000 / 1000);
    }
};

void test_entry_point(unsigned long parameter0, unsigned long parameter1, unsigned long parameter2, unsigned long parameter3, unsigned long thread_index, c_job_handle job_handle, c_jm_work_unit_handle work_unit)
{
    mangled_ppc("?test_entry_point@@YAXKKKKKVc_job_handle@@Vc_jm_work_unit_handle@@@Z");

    static unsigned short profiler_index = profiler_get_index("job", "test1", static_cast<e_mt_color>(0));
    c_mtp_profiler_context profiler_context(profiler_index);

    delay((parameter1 + 20) * 1000);

    if (parameter2 == 0)
    {
        output_debug("test entry point (%d) (%d) (0x%08x)", parameter0, parameter1, thread_index);
    }
    else if (parameter2 < 3)
    {
        unsigned long * value = reinterpret_cast<unsigned long *>(parameter3);
        if (parameter2 == 1)
        {
            output_debug("mul entry point (%d) * (%d) = (%d)", *value, parameter0, *value * parameter0);
            *value *= parameter0;
        }
        if (parameter2 == 2)
        {
            output_debug("add entry point (%d) * (%d) = (%d)", *value, parameter0, *value + parameter0);
            *value += parameter0;
        }
    }
    else
    {
        c_synchronized_int32 * index = reinterpret_cast<c_synchronized_int32 *>(parameter2);
        unsigned long * results = reinterpret_cast<unsigned long *>(index->add(8));
        results[0] = thread_index;
        results[1] = parameter0;
    }
};

void test_entry_point2(unsigned long parameter0, unsigned long parameter1, unsigned long parameter2, unsigned long parameter3, unsigned long thread_index, c_job_handle job_handle, c_jm_work_unit_handle work_unit)
{
    mangled_ppc("?test_entry_point2@@YAXKKKKKVc_job_handle@@Vc_jm_work_unit_handle@@@Z");

    static unsigned short profiler_index = profiler_get_index("job", "test2", static_cast<e_mt_color>(0));
    c_mtp_profiler_context profiler_context(profiler_index);

    s_job_timing * job_time = reinterpret_cast<s_job_timing *>(parameter3);
    job_time->start = system_performance_timer_get();

    if (parameter0 < 16)
    {
        c_synchronized_int32 * index = reinterpret_cast<c_synchronized_int32 *>(parameter2);
        unsigned long * results = reinterpret_cast<unsigned long *>(index->add(4));
        *results = parameter0;
    }

    delay(parameter1);

    job_time->end = system_performance_timer_get();
    job_time->thread = thread_index;
};

void test_entry_point3(unsigned long parameter0, unsigned long parameter1, unsigned long parameter2, unsigned long parameter3, unsigned long thread_index, c_job_handle job_handle, c_jm_work_unit_handle work_unit)
{
    mangled_ppc("?test_entry_point3@@YAXKKKKKVc_job_handle@@Vc_jm_work_unit_handle@@@Z");

    static unsigned short profiler_index = profiler_get_index("job", "test3", static_cast<e_mt_color>(0));
    c_mtp_profiler_context profiler_context(profiler_index);

    delay(parameter0);
    output_debug("%d, %d, %d, %d", parameter0, parameter1, parameter2, parameter3);

    if (parameter1 < parameter3)
    {
        c_job job;
        c_job_handle handles[128];
        for (unsigned long job_index = 0; job_index < parameter2; job_index++)
        {
            job.setup(test_signature3, parameter0 + job_index, parameter1 + 1, parameter2 * 2, parameter3);
            c_job_handle handle = work_unit.add_job(job, 2);
            work_unit.a_depends_on_b(handle, job_handle);
            work_unit.activate(handle);
        }
    }
};

void example_entry_point(unsigned long parameter0, unsigned long parameter1, unsigned long parameter2, unsigned long parameter3, unsigned long thread_index, c_job_handle job_handle, c_jm_work_unit_handle work_unit)
{
    mangled_ppc("?example_entry_point@@YAXKKKKKVc_job_handle@@Vc_jm_work_unit_handle@@@Z");
};

void test_entry_point4(unsigned long parameter0, unsigned long parameter1, unsigned long parameter2, unsigned long parameter3, unsigned long thread_index, c_job_handle job_handle, c_jm_work_unit_handle work_unit)
{
    mangled_ppc("?test_entry_point4@@YAXKKKKKVc_job_handle@@Vc_jm_work_unit_handle@@@Z");

    if (parameter1 == 0)
    {
        static unsigned short profiler_index = profiler_get_index("job", "test3", static_cast<e_mt_color>(18));
        c_mtp_profiler_context profiler_context(profiler_index);

        delay(3000);
    }
    else
    {
        static unsigned short profiler_index = profiler_get_index("job", "test3", static_cast<e_mt_color>(12));
        c_mtp_profiler_context profiler_context(profiler_index);

        delay(1500);
    }
};
