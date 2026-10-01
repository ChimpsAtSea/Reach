#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\foundation\\threadlib\\async\\async_profile.cpp"
/* ---------- headers */

#include "foundation\threadlib\async\async_profile.h"
#include "foundation\threadlib\async\async_setup.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_macros.h"
#include "core\corelib\cseries\cseries_memory.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

static char const * g_async_profile_block_names[k_async_profile_block_count] =
{
    "async_thread_tick",
    "async_task_add_sized_task_data_unsafe",
};

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// void async_profile_get_statistics_for_thread(long, struct s_async_thread_statistics *);
// long async_profile_get_total_tasks_added(void);
// char const * async_profile_get_block_name(enum e_async_profile_blocks);
// void async_profile_record_task_timings(struct s_async_thread_context *, long, unsigned long);
// public: c_async_profile_block::c_async_profile_block(char const *);
// public: c_async_profile_block::~c_async_profile_block(void);
// public: struct s_async_task_priority_timings & s_static_array<struct s_async_task_priority_timings, 32>::operator[]<long>(long);
// public: static bool s_static_array<struct s_async_task_priority_timings, 32>::valid<long>(long);
// unsigned long int_max<unsigned long>(unsigned long const &, unsigned long const &);

void async_profile_get_statistics_for_thread(long thread_index, s_async_thread_statistics * statistics)
{
    mangled_ppc("?async_profile_get_statistics_for_thread@@YAXJPAUs_async_thread_statistics@@@Z");

    s_async_thread_context * thread_context = NULL;

    assert_tag_debug_untracked_jul_11_2011(32, statistics);

    csmemset(statistics, 0, sizeof(s_async_thread_statistics));
    thread_context = async_setup_get_context_for_thread(thread_index);
    statistics->work_list_size = thread_context->work_list.size();
    statistics->unknown4 = thread_context->statistics.unknown0;
    statistics->unknown8 = thread_context->statistics.unknown4.peek();
    csmemcpy(&statistics->unknownC, &thread_context->statistics.unknown8, sizeof(statistics->unknownC));
    csmemcpy(&statistics->unknown8C, &thread_context->statistics.unknown88, sizeof(statistics->unknown8C));
    csmemcpy(&statistics->priority_timings, &thread_context->statistics.priority_timings, sizeof(statistics->priority_timings));
};

long async_profile_get_total_tasks_added(void)
{
    mangled_ppc("?async_profile_get_total_tasks_added@@YAJXZ");

    return async_setup_get_total_tasks_added();
};

char const * async_profile_get_block_name(e_async_profile_blocks block_index)
{
    mangled_ppc("?async_profile_get_block_name@@YAPBDW4e_async_profile_blocks@@@Z");

    assert_tag_debug_untracked_jul_11_2011(65, VALID_INDEX(block_index, k_async_profile_block_count));

    return g_async_profile_block_names[block_index];
};

void async_profile_record_task_timings(s_async_thread_context * thread_context, long priority, unsigned long elapsed_time)
{
    mangled_ppc("?async_profile_record_task_timings@@YAXPAUs_async_thread_context@@JK@Z");

    s_async_task_priority_timings * timings = NULL;

    assert_tag_debug_untracked_jul_11_2011(78, thread_context!=NULL);

    timings = &thread_context->statistics.priority_timings[priority];
    timings->total_time += elapsed_time;
    timings->maximum_time = int_max(timings->maximum_time, elapsed_time);
    timings->count++;
};

c_async_profile_block::c_async_profile_block(char const * block_name)
{
    mangled_ppc("??0c_async_profile_block@@QAA@PBD@Z");

    c_async_profile_interface * profiler = async_setup_get_registered_profiler();
    if (profiler != NULL)
    {
        profiler->start_profile_block(block_name, m_block_data);
    }
};

c_async_profile_block::~c_async_profile_block(void)
{
    mangled_ppc("??1c_async_profile_block@@QAA@XZ");

    c_async_profile_interface * profiler = async_setup_get_registered_profiler();
    if (profiler != NULL)
    {
        profiler->end_profile_block(m_block_data);
    }
};
