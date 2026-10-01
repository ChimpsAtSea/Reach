#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\foundation\\threadlib\\jobmanager\\test\\job_manager_test.cpp"
/* ---------- headers */

#include "foundation\threadlib\jobmanager\test\job_manager_test.h"
#include "baselib\system_time_windows.h"
#include "baselib\system_time_xenon.h"
#include "baselib\thread_execution_windows.h"
#include "foundation\baselib\datatypes\indexed_list.h"
#include "foundation\baselib\datatypes\indexed_pool.h"
#include "foundation\baselib\errors\output\output_globals.h"
#include "foundation\threadlib\jobmanager\job_manager.h"
#include "foundation\threadlib\multithreading\profiler\mt_profiler_context.h"
#include "threadlib\jm_types.h"
#include "threadlib\job.h"
#include "threadlib\test_job.h"
#include "threadlib\work_unit_handle.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_macros.h"
#include "core\corelib\cseries\cseries_memory.h"

/* ---------- constants */

/* ---------- definitions */

struct s_job_timing
{
    __int64 start;
    __int64 end;
    unsigned long thread;
};
static_assert(sizeof(s_job_timing) == 0x18, "s_job_timing");

/* ---------- prototypes */

/* ---------- globals */

static float k_check_timed_duration1 = 16.6666f;
static float k_check_timed_duration0 = 4.13f;

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// void JMTest::simple_runonce(void);
// void JMTest::simple_run_many(void);
// void JMTest::check_timed(void);
// void JMTest::check_dependency(void);
// void JMTest::check_dependency_already_executing(void);
// unsigned long JMTest::find_in_list(unsigned long, unsigned long *, unsigned long, unsigned long);
// void JMTest::check_thrash(void);
// void JMTest::check_add_from_job(void);
// void IndexedTest::test_pool(void);
// void IndexedTest::test_linked_list(void);
// void job_manager_test_hook(void);
// public: class c_indexed_list<unsigned short, 32>::iterator c_indexed_list<unsigned short, 32>::begin(void);
// public: class c_indexed_list<unsigned short, 32>::iterator c_indexed_list<unsigned short, 32>::end(void);
// public: c_indexed_list<unsigned short, 32>::const_iterator::const_iterator(class c_indexed_list<unsigned short, 32>::iterator const &);
// public: unsigned short const & c_indexed_list<unsigned short, 32>::const_iterator::operator*(void) const;
// public: class c_indexed_list<unsigned short, 32>::const_iterator & c_indexed_list<unsigned short, 32>::const_iterator::operator++(void);
// public: bool c_indexed_list<unsigned short, 32>::const_iterator::operator!=(class c_indexed_list<unsigned short, 32>::const_iterator const &) const;
// public: unsigned short & c_indexed_list<unsigned short, 32>::iterator::operator*(void);
// public: class c_indexed_list<unsigned short, 32>::iterator & c_indexed_list<unsigned short, 32>::iterator::operator++(void);
// public: bool c_indexed_list<unsigned short, 32>::iterator::operator!=(class c_indexed_list<unsigned short, 32>::iterator const &) const;
// private: unsigned short c_indexed_list<unsigned short, 32>::get_next(unsigned short) const;
// private: unsigned short c_indexed_list<unsigned short, 32>::get_prev(unsigned short) const;
// private: unsigned short c_indexed_list<unsigned short, 32>::get_head(void) const;
// private: unsigned short c_indexed_list<unsigned short, 32>::get_tail(void) const;
// private: unsigned short & c_indexed_list<unsigned short, 32>::get_data(unsigned short);
// private: unsigned short const & c_indexed_list<unsigned short, 32>::get_data(unsigned short) const;
// public: bool c_indexed_list<unsigned short, 32>::const_iterator::operator==(class c_indexed_list<unsigned short, 32>::const_iterator const &) const;
// public: c_indexed_list<unsigned short, 32>::iterator::iterator(class c_indexed_list<unsigned short, 32> *, unsigned short, unsigned short, unsigned short);
// public: bool c_indexed_list<unsigned short, 32>::iterator::operator==(class c_indexed_list<unsigned short, 32>::iterator const &) const;
// void JMTest::check_dependency_largescale<0, 2>(void);
// void JMTest::check_dependency_largescale<1, 2>(void);
// void JMTest::check_dependency_largescale<1, 0>(void);
// public: c_indexed_pool<int, 256>::c_indexed_pool<int, 256>(void);
// public: c_indexed_pool<int, 256>::~c_indexed_pool<int, 256>(void);
// public: void c_indexed_pool<int, 256>::initialize(void);
// public: void c_indexed_pool<int, 256>::dispose(void);
// public: unsigned short c_indexed_pool<int, 256>::alloc_handle(void);
// public: void c_indexed_pool<int, 256>::free_handle(unsigned short &);
// public: int * c_indexed_pool<int, 256>::get_element(unsigned short const &);
// public: void c_indexed_list<unsigned short, 32>::initialize(void);
// public: void c_indexed_list<unsigned short, 32>::dispose(void);
// public: void c_indexed_list<unsigned short, 32>::clear(void);
// public: bool c_indexed_list<unsigned short, 32>::push_back(unsigned short const &);
// public: bool c_indexed_list<unsigned short, 32>::push_front(unsigned short const &);
// public: void c_indexed_list<unsigned short, 32>::remove(class c_indexed_list<unsigned short, 32>::iterator &);
// public: unsigned short c_indexed_list<unsigned short, 32>::pop_head(void);
// void JMTest::check_wait_single<0>(void);
// void JMTest::check_wait_single<1>(void);
// private: unsigned short c_indexed_list<unsigned short, 32>::pop(void);
// private: void c_indexed_list<unsigned short, 32>::push(struct s_il_node *);
// private: void c_indexed_list<unsigned short, 32>::remove_indexed(unsigned short);

void JMTest::simple_runonce(void)
{
    mangled_ppc("?simple_runonce@JMTest@@YAXXZ");

    c_jm_work_unit_handle & work_unit_handle = job_manager_get_default_work_unit();
    assert_tag_debug_untracked_jul_11_2011(37, work_unit_handle.valid());

    c_job job(test_signature, 1122, 0, 0, 0);
    job.execute(0, c_job_handle(), job_manager_get_default_work_unit());
};

void JMTest::simple_run_many(void)
{
    mangled_ppc("?simple_run_many@JMTest@@YAXXZ");

    c_jm_work_unit_handle & work_unit_handle = job_manager_get_default_work_unit();
    assert_tag_debug_untracked_jul_11_2011(55, work_unit_handle.valid());

    unsigned long results[100][2];
    c_synchronized_int32 index;
    c_job jobs[100];
    c_job_handle handles[100];

    index.set(reinterpret_cast<long>(results));

    for (unsigned long job_index = 0; job_index < 100; job_index++)
    {
        jobs[job_index].setup(test_signature, job_index, (reinterpret_cast<unsigned long>(&jobs[job_index]) & 0xF) * 5, reinterpret_cast<unsigned long>(&index), 0);
        handles[job_index] = work_unit_handle.add_job(jobs[job_index], 2);
    }

    for (unsigned long job_index = 0; job_index < 100; job_index++)
    {
        work_unit_handle.activate(handles[job_index]);
    }

    work_unit_handle.do_not_use_wait_until_all_work_done();

    unsigned long * result_ptr = results[0];
    for (unsigned long job_index = 0; job_index < 100; job_index++)
    {
        output_debug("%3d test entry point (0x%08x)  (0x%08x) (%d)", job_index, result_ptr[0], result_ptr[1], result_ptr[1]);
        result_ptr += 2;
    }
};

void JMTest::check_timed(void)
{
    mangled_ppc("?check_timed@JMTest@@YAXXZ");

    c_jm_work_unit_handle & work_unit_handle = job_manager_get_default_work_unit();
    assert_tag_debug_untracked_jul_11_2011(156, work_unit_handle.valid());

    {
        c_job timed_job;
        timed_job.setup(test_signature4, *reinterpret_cast<unsigned long const *>(&k_check_timed_duration0), 0, 0, 0);
        c_job_handle job_handle = work_unit_handle.add_job(timed_job, 4);
    }

    {
        c_job timed_job;
        timed_job.setup(test_signature4, *reinterpret_cast<unsigned long const *>(&k_check_timed_duration1), 1, 0, 0);
        c_job_handle job_handle = work_unit_handle.add_job(timed_job, 4);
    }
};

void JMTest::check_dependency(void)
{
    mangled_ppc("?check_dependency@JMTest@@YAXXZ");

    c_jm_work_unit_handle & work_unit_handle = job_manager_get_default_work_unit();
    assert_tag_debug_untracked_jul_11_2011(187, work_unit_handle.valid());

    long testval = 1;
    c_job jobs[5];
    c_job_handle handles_local[5];
    unsigned long job_ops[5] = { 1, 0, 2, 0, 1 };

    for (unsigned long job_index = 0; job_index < 5; job_index++)
    {
        jobs[job_index].setup(test_signature, job_index + 2, 100, job_ops[job_index], reinterpret_cast<unsigned long>(&testval));
        handles_local[job_index] = work_unit_handle.add_job(jobs[job_index], 2);
    }

    work_unit_handle.a_depends_on_b(handles_local[4], handles_local[2]);
    work_unit_handle.a_depends_on_b(handles_local[2], handles_local[0]);

    for (unsigned long job_index = 0; job_index < 5; job_index++)
    {
        work_unit_handle.activate(handles_local[job_index]);
    }

    work_unit_handle.do_not_use_wait_until_all_work_done();

    long testvalcmp = 36;
    assert_tag_debug_untracked_jul_11_2011(225, testval == testvalcmp);
};

void JMTest::check_dependency_already_executing(void)
{
    mangled_ppc("?check_dependency_already_executing@JMTest@@YAXXZ");

    c_jm_work_unit_handle & work_unit_handle = job_manager_get_default_work_unit();
    assert_tag_debug_untracked_jul_11_2011(237, work_unit_handle.valid());

    long testval = 1;
    c_job jobs[5];
    c_job_handle handles_local[5];
    unsigned long job_ops[5] = { 1, 0, 2, 0, 1 };

    for (unsigned long job_index = 0; job_index < 5; job_index++)
    {
        jobs[job_index].setup(test_signature, job_index + 2, job_index != 0 ? 100 : 0, job_ops[job_index], reinterpret_cast<unsigned long>(&testval));
        handles_local[job_index] = work_unit_handle.add_job(jobs[job_index], job_index != 0 ? 2 : 0);
    }

    work_unit_handle.a_depends_on_b(handles_local[4], handles_local[2]);
    work_unit_handle.a_depends_on_b(*(handles_local + 2), *handles_local);

    for (unsigned long job_index = 1; job_index < 5; job_index++)
    {
        work_unit_handle.activate(handles_local[job_index]);
    }

    work_unit_handle.do_not_use_wait_until_all_work_done();

    long testvalcmp = 36;
    assert_tag_debug_untracked_jul_11_2011(275, testval == testvalcmp);
};

unsigned long JMTest::find_in_list(unsigned long value, unsigned long * list, unsigned long start_index, unsigned long count)
{
    mangled_ppc("?find_in_list@JMTest@@YAKKPAKKK@Z");

    unsigned long result = 0xFFFFFFFF;
    for (unsigned long pos = start_index; pos < start_index + count; pos++)
    {
        if (list[pos] == value)
        {
            result = pos;
        }
    }

    return result;
};

void JMTest::check_thrash(void)
{
    mangled_ppc("?check_thrash@JMTest@@YAXXZ");

    for (unsigned long iteration = 0; iteration < 100; iteration++)
    {
        check_dependency_largescale<0, 2>();
        check_dependency_largescale<1, 2>();
    }

    mt_profiler_internal::start_frame();
    for (unsigned long iteration = 0; iteration < 100; iteration++)
    {
        mt_profiler_internal::start_frame();
        check_dependency_largescale<1, 0>();
    }
};

void JMTest::check_add_from_job(void)
{
    mangled_ppc("?check_add_from_job@JMTest@@YAXXZ");

    c_jm_work_unit_handle & work_unit_handle = job_manager_get_default_work_unit();
    assert_tag_debug_untracked_jul_11_2011(576, work_unit_handle.valid());

    c_job job(test_signature3, 1, 1, 1, 6);
    c_job_handle job_handle = work_unit_handle.add_job(job, 1);
    work_unit_handle.relinquish_until_done(job_handle);
};

void IndexedTest::test_pool(void)
{
    mangled_ppc("?test_pool@IndexedTest@@YAXXZ");

    c_indexed_pool<int, 256> int_pool;
    int_pool.initialize();

    unsigned short handle = int_pool.alloc_handle();
    int * element = int_pool.get_element(handle);
    *element = 10;
    int_pool.free_handle(handle);

    int_pool.dispose();
};

void IndexedTest::test_linked_list(void)
{
    mangled_ppc("?test_linked_list@IndexedTest@@YAXXZ");

    unsigned short checkdata[8] = { 0x1234, 0x1233, 0x1232, 0x1231, 0x1235, 0x1236, 0x1237, 0x1238 };

    {
        c_indexed_list<unsigned short, 32> list;
        list.initialize();
        list.push_front(0x1231);
        list.push_front(0x1232);
        list.push_front(0x1233);
        list.push_front(0x1234);
        list.push_back(0x1235);
        list.push_back(0x1236);
        list.push_back(0x1237);
        list.push_back(0x1238);

        for (unsigned short i = 0; i < 8; i++)
        {
            unsigned short data = list.pop_head();
            assert_tag_debug_untracked_jul_11_2011(657, data == checkdata[i]);
        }

        list.dispose();
    }

    {
        c_indexed_list<unsigned short, 32> list;
        list.initialize();
        list.push_front(0x1231);
        list.push_front(0x1232);
        list.push_front(0x1233);
        list.push_front(0x1234);
        list.push_back(0x1235);
        list.push_back(0x1236);
        list.push_back(0x1237);
        list.push_back(0x1238);

        c_indexed_list<unsigned short, 32>::const_iterator it = list.begin();
        c_indexed_list<unsigned short, 32>::const_iterator end_it = list.end();
        unsigned long i = 0;
        while (it != end_it)
        {
            unsigned short data = *it;
            assert_tag_debug_untracked_jul_11_2011(690, data == checkdata[i]);
            ++it;
            i++;
        }

        list.clear();
        list.dispose();
    }

    {
        c_indexed_list<unsigned short, 32> list;
        list.initialize();
        list.push_front(0x1231);
        list.push_front(0x1232);
        list.push_front(0x1233);
        list.push_front(0x1234);
        list.push_back(0x1235);
        list.push_back(0x1236);
        list.push_back(0x1237);
        list.push_back(0x1238);

        {
            c_indexed_list<unsigned short, 32>::iterator it = list.begin();
            c_indexed_list<unsigned short, 32>::iterator end_it = list.end();
            unsigned long i = 0;
            while (it != end_it)
            {
                if (i == 3)
                {
                    list.remove(it);
                }
                ++it;
                i++;
            }
        }

        {
            c_indexed_list<unsigned short, 32>::iterator it = list.begin();
            c_indexed_list<unsigned short, 32>::iterator end_it = list.end();
            unsigned long i = 0;
            while (it != end_it)
            {
                unsigned short data = *it;
                if (i >= 3)
                {
                    assert_tag_debug_untracked_jul_11_2011(749, data == checkdata[i+1]);
                }
                ++it;
                i++;
            }
        }

        list.clear();
        list.dispose();
    }
};

void job_manager_test_hook(void)
{
    mangled_ppc("?job_manager_test_hook@@YAXXZ");

    IndexedTest::test_pool();
    IndexedTest::test_linked_list();
    JMTest::simple_runonce();
    JMTest::simple_run_many();
    JMTest::check_wait_single<0>();
    JMTest::check_wait_single<1>();
    JMTest::check_dependency();
    mt_profiler_internal::start_frame();
    JMTest::check_dependency_largescale<0, 2>();
    mt_profiler_internal::start_frame();
    JMTest::check_dependency_largescale<1, 2>();
    mt_profiler_internal::start_frame();
    JMTest::check_dependency_already_executing();
    mt_profiler_internal::start_frame();
    JMTest::check_thrash();
    mt_profiler_internal::start_frame();
    JMTest::check_add_from_job();
    mt_profiler_internal::start_frame();
    JMTest::check_timed();
    output_message("job manager test hook\n");
};

template<long k_mode, long k_depth>
void JMTest::check_dependency_largescale(void)
{
    mangled_ppc("??$check_dependency_largescale@$0A@$01@JMTest@@YAXXZ");

    c_jm_work_unit_handle & work_unit_handle = job_manager_get_default_work_unit();
    assert_tag_debug_untracked_jul_11_2011(332, work_unit_handle.valid());

    c_job test_jobs_array[26];
    c_job_handle job_handles_array[26];
    s_job_timing job_times[26];
    unsigned long exec_order[26];
    c_synchronized_int32 idx_counter;
    unsigned long delays_array[4] = { 500, 1000, 1500, 2000 };

    idx_counter.set(reinterpret_cast<long>(exec_order));

    for (unsigned long i = 0; i < 26; i++)
    {
        test_jobs_array[i].setup(test_signature2, i, delays_array[i & 3], reinterpret_cast<unsigned long>(&idx_counter), reinterpret_cast<unsigned long>(&job_times[i]));
        job_handles_array[i] = work_unit_handle.add_job(test_jobs_array[i], 2);
    }

    work_unit_handle.a_depends_on_b(job_handles_array[3], job_handles_array[0]);
    work_unit_handle.a_depends_on_b(job_handles_array[3], job_handles_array[1]);
    work_unit_handle.a_depends_on_b(job_handles_array[3], job_handles_array[2]);
    work_unit_handle.a_depends_on_b(job_handles_array[4], job_handles_array[3]);
    work_unit_handle.a_depends_on_b(job_handles_array[5], job_handles_array[4]);
    work_unit_handle.a_depends_on_b(job_handles_array[6], job_handles_array[4]);
    work_unit_handle.a_depends_on_b(job_handles_array[7], job_handles_array[4]);
    work_unit_handle.a_depends_on_b(job_handles_array[8], job_handles_array[5]);
    work_unit_handle.a_depends_on_b(job_handles_array[9], job_handles_array[6]);
    work_unit_handle.a_depends_on_b(job_handles_array[10], job_handles_array[7]);
    work_unit_handle.a_depends_on_b(job_handles_array[11], job_handles_array[8]);
    work_unit_handle.a_depends_on_b(job_handles_array[11], job_handles_array[9]);
    work_unit_handle.a_depends_on_b(job_handles_array[11], job_handles_array[10]);
    work_unit_handle.a_depends_on_b(job_handles_array[12], job_handles_array[11]);
    work_unit_handle.a_depends_on_b(job_handles_array[13], job_handles_array[11]);
    work_unit_handle.a_depends_on_b(job_handles_array[14], job_handles_array[11]);
    work_unit_handle.a_depends_on_b(job_handles_array[15], job_handles_array[12]);
    work_unit_handle.a_depends_on_b(job_handles_array[15], job_handles_array[13]);
    work_unit_handle.a_depends_on_b(job_handles_array[15], job_handles_array[14]);

    work_unit_handle.activate_array(job_handles_array, 26);

    __int64 base_ticks = system_performance_timer_get();
    if (k_mode)
    {
        work_unit_handle.relinquish_until_done(job_handles_array[15]);
    }
    else
    {
        work_unit_handle.do_not_use_wait_until_all_work_done();
    }

    unsigned long res0 = find_in_list(0, exec_order, 0, 3);
    unsigned long res1 = find_in_list(1, exec_order, 0, 3);
    unsigned long res2 = find_in_list(2, exec_order, 0, 3);
    unsigned long res3 = find_in_list(3, exec_order, 3, 1);
    unsigned long res4 = find_in_list(4, exec_order, 4, 1);
    unsigned long res5 = find_in_list(5, exec_order, 5, 3);
    unsigned long res6 = find_in_list(6, exec_order, 5, 3);
    unsigned long res7 = find_in_list(7, exec_order, 5, 3);
    unsigned long res8 = find_in_list(7, exec_order, res5 + 1, 10 - res5);
    unsigned long res9 = find_in_list(8, exec_order, res6 + 1, 10 - res6);
    unsigned long resa = find_in_list(10, exec_order, res7 + 1, 10 - res7);
    unsigned long resb = find_in_list(11, exec_order, 11, 1);
    unsigned long resc = find_in_list(12, exec_order, 12, 3);
    unsigned long resd = find_in_list(13, exec_order, 12, 3);
    unsigned long rese = find_in_list(14, exec_order, 12, 3);
    unsigned long resf = find_in_list(15, exec_order, 15, 1);

    assert_tag_debug_untracked_jul_11_2011(435, res0 != 0xffffffff);
    assert_tag_debug_untracked_jul_11_2011(436, res1 != 0xffffffff);
    assert_tag_debug_untracked_jul_11_2011(437, res2 != 0xffffffff);
    assert_tag_debug_untracked_jul_11_2011(438, res3 != 0xffffffff);
    assert_tag_debug_untracked_jul_11_2011(440, res4 != 0xffffffff);
    assert_tag_debug_untracked_jul_11_2011(441, res5 != 0xffffffff);
    assert_tag_debug_untracked_jul_11_2011(442, res6 != 0xffffffff);
    assert_tag_debug_untracked_jul_11_2011(443, res7 != 0xffffffff);
    assert_tag_debug_untracked_jul_11_2011(445, res8 != 0xffffffff);
    assert_tag_debug_untracked_jul_11_2011(446, res9 != 0xffffffff);
    assert_tag_debug_untracked_jul_11_2011(447, resa != 0xffffffff);
    assert_tag_debug_untracked_jul_11_2011(448, resb != 0xffffffff);
    assert_tag_debug_untracked_jul_11_2011(450, resc != 0xffffffff);
    assert_tag_debug_untracked_jul_11_2011(451, resd != 0xffffffff);
    assert_tag_debug_untracked_jul_11_2011(452, rese != 0xffffffff);
    assert_tag_debug_untracked_jul_11_2011(453, resf != 0xffffffff);

    const unsigned long k_width = 256;
    char space_string[] = "                                                                                                                                                                                                                                                                ";
    char numbers[] = "0     1     2     3     4     5     6     7     8     9     0     1     2     3     4     5     6     7     8     9     0     1     2     3     4     5     6     7     8     9     0     1     2     3     4     5     6     7     8     9     0     1     2   ";
    char bar_string[] = "----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------";

    if (k_depth > 2)
    {
        output_debug("0x%08x[%c](%4d) %s", 0, ' ', 0, numbers);
    }

    for (unsigned long j = 0; j < 26; j++)
    {
        __int64 start_time = job_times[j].start;
        __int64 end_time = job_times[j].end;
        double start_milliseconds = static_cast<double>(start_time - base_ticks) / (system_performance_timer_frequency() / 1000);
        double end_msecs = static_cast<double>(end_time - base_ticks) / (system_performance_timer_frequency() / 1000);
        long s = static_cast<long>(start_milliseconds * 6.0);
        long chars = static_cast<long>((end_msecs - start_milliseconds) * 6.0);
        if (chars > k_width)
        {
            chars = k_width;
        }
        if (s > k_width)
        {
            s = 0;
        }

        char bar[512];
        csmemcpy(bar, bar_string + s, chars);
        bar[chars] = 0;

        if (k_depth > 2)
        {
            output_debug("0x%08x[%c](%4d) %s%s", job_times[j].thread, 'a' + static_cast<char>(j), delays_array[j & 3], space_string + k_width - s, bar);
        }

        job_times[j].start = s;
        job_times[j].end = chars;
    }

    unsigned long threadid = job_times[0].thread;
    while (threadid != -1)
    {
        char line[256];
        csmemset(line, ' ', sizeof(line));
        line[255] = 0;

        for (unsigned long k = 0; k < 26; k++)
        {
            if (job_times[k].thread == threadid)
            {
                job_times[k].thread = -1;
                __int64 start = job_times[k].start;
                __int64 length = job_times[k].end;

                line[start] = '<';
                for (unsigned long m = 1; m < length - 1; m++)
                {
                    line[start + m] = '-';
                }
                line[start + length - 1] = '>';
                line[start + (length >> 1)] = 'a' + static_cast<char>(k);
            }
        }

        if (k_depth > 0)
        {
            output_debug("0x%08x[%c](%4d) %s", threadid, ' ', 0, line);
        }

        threadid = -1;
        for (unsigned long n = 0; threadid == -1 && n < 26; n++)
        {
            if (job_times[n].thread != -1)
            {
                threadid = job_times[n].thread;
            }
        }
    }
};



template<long k_mode>
void JMTest::check_wait_single(void)
{
    mangled_ppc("??$check_wait_single@$0A@@JMTest@@YAXXZ");

    c_jm_work_unit_handle & work_unit_handle = job_manager_get_default_work_unit();
    assert_tag_debug_untracked_jul_11_2011(102, work_unit_handle.valid());

    c_job job;
    c_job_handle job_handle;
    unsigned long delay = 100;
    job.setup(test_signature, 0, delay, 0, 0);
    job_handle = work_unit_handle.add_job(job, 2);
    work_unit_handle.activate(job_handle);

    unsigned long start_time = system_milliseconds();
    if (k_mode)
    {
        work_unit_handle.block_wait_until_done(job_handle);
    }
    else
    {
        bool waiting = true;
        unsigned long count = 0;
        while (waiting)
        {
            waiting = !work_unit_handle.job_is_done(job_handle);
            if (waiting)
            {
                output_debug("(%3d): waiting for job to be done manually while doing my own thing", count);
                count++;
                thread_sleep(10);
            }
        }
    }

    unsigned long end_milliseconds = system_milliseconds();
    unsigned long t = end_milliseconds - start_time;
    assert_tag_debug_untracked_jul_11_2011(146, t > 50);
};

