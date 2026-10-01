#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\foundation\\threadlib\\async\\async_thread.cpp"
/* ---------- headers */

#include "foundation\threadlib\async\async_thread.h"
#include "baselib\system_time_xenon.h"
#include "baselib\thread_execution_windows.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_macros.h"
#include "core\corelib\cseries\cseries_memory.h"
#include "foundation\baselib\multithreading\synchronization\semaphore_windows.h"
#include "foundation\baselib\multithreading\synchronization\virtual_guard_block.h"
#include "foundation\threadlib\async\async.h"
#include "foundation\threadlib\async\async_profile.h"
#include "foundation\threadlib\async\async_setup.h"
#include "foundation\threadlib\multithreading\profiler\mt_profiler_context.h"
#include "foundation\threadlib\multithreading\profiler\mt_profiler_store.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

extern s_async_task_id async_add_task_to_work_list_ordered(s_async_thread_context * thread_context, t_thread_safe_list<s_async_task_element>::s_list_element * task_element);

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// unsigned short & get_profile_index(unsigned long);
// bool async_thread_tick(void *);
// public: c_virtual_guard_block_scope::c_virtual_guard_block_scope(struct s_virtual_guard_block);
// public: c_virtual_guard_block_scope::~c_virtual_guard_block_scope(void);

unsigned short & get_profile_index(unsigned long category)
{
    mangled_ppc("?get_profile_index@@YAAAGK@Z");

    static unsigned short none_index = profiler_get_index("0", "none", static_cast<e_mt_color>(12));
    static unsigned short bckgrnd_copy_index = profiler_get_index("0", "bckgrnd_copy", static_cast<e_mt_color>(12));
    static unsigned short cache_misc_index = profiler_get_index("0", "cache_misc", static_cast<e_mt_color>(12));
    static unsigned short text_index = profiler_get_index("0", "text", static_cast<e_mt_color>(12));
    static unsigned short saved_games_index = profiler_get_index("0", "saved_games", static_cast<e_mt_color>(12));
    static unsigned short online_files_index = profiler_get_index("0", "online_files", static_cast<e_mt_color>(12));
    static unsigned short datamine_index = profiler_get_index("0", "datamine", static_cast<e_mt_color>(12));
    static unsigned short pref_index = profiler_get_index("0", "pref", static_cast<e_mt_color>(12));
    static unsigned short sound_index = profiler_get_index("0", "sound", static_cast<e_mt_color>(12));
    static unsigned short levels_dvd_index = profiler_get_index("0", "levels_dvd", static_cast<e_mt_color>(12));
    static unsigned short content_index = profiler_get_index("0", "content", static_cast<e_mt_color>(12));
    static unsigned short cmd_bf_index = profiler_get_index("0", "cmd bf", static_cast<e_mt_color>(12));
    static unsigned short stmch_index = profiler_get_index("0", "stmch", static_cast<e_mt_color>(12));
    static unsigned short film_index = profiler_get_index("0", "film", static_cast<e_mt_color>(12));
    static unsigned short debug_index = profiler_get_index("0", "debug", static_cast<e_mt_color>(12));
    static unsigned short decomp_index = profiler_get_index("0", "decomp", static_cast<e_mt_color>(12));

    unsigned short * profile_indices[] =
    {
        &none_index,
        &bckgrnd_copy_index,
        &cache_misc_index,
        &text_index,
        &saved_games_index,
        &online_files_index,
        &datamine_index,
        &pref_index,
        &sound_index,
        &levels_dvd_index,
        &content_index,
        &cmd_bf_index,
        &stmch_index,
        &text_index,
        &saved_games_index,
        &decomp_index,
    };

    if (category < NUMBEROF(profile_indices))
    {
        return *profile_indices[category];
    }

    return *profile_indices[0];
};

bool async_thread_tick(void * thread_parameter)
{
    mangled_ppc("?async_thread_tick@@YA_NPAX@Z");

    bool running = true;
    t_thread_safe_list<s_async_task_element>::s_list_element * work_element = NULL;
    long thread_index = address_from_pointer(thread_parameter);
    s_async_thread_context * thread_context = async_setup_get_context_for_thread(thread_index);

    semaphore_take_internal(thread_context->work_available_semaphore);
    work_element = thread_context->work_list.get_and_remove_head_element();
    if (work_element != NULL)
    {
        long work_delay;
        {
            unsigned long start_time = system_milliseconds();
            c_async_profile_block profile_block(async_profile_get_block_name(_async_profile_block_thread_tick));
            c_mtp_profiler_context profiler_index_context(get_profile_index(work_element->data.category));
            work_delay = async_setup_get_thread_work_delay(thread_index);
            long priority = work_element->data.priority;
            e_async_completion completion_status;
            {
                c_virtual_guard_block_scope guard_block_scope(thread_context->guard_block);
                completion_status = work_element->data.callback(work_element->data.task_data);
                assert_tag_debug_untracked_jul_11_2011(109, VALID_INDEX(completion_status, k_async_completion_count));
            }
            if (completion_status != _async_completion_retry)
            {
                assert_tag_debug_untracked_jul_11_2011(116, completion_status==_async_completion_done || completion_status==_async_completion_thread_exit);
                if (work_element->data.completion_flag != NULL)
                {
                    work_element->data.completion_flag->set(1);
                }
                thread_context->statistics.unknown0++;
                thread_context->statistics.unknown8[work_element->data.category]++;
                thread_context->statistics.unknown88[priority]++;
                work_element->data.task_id = k_invalid_async_task_id;
                thread_context->free_list.add_element_to_front(work_element);
                running = completion_status != _async_completion_thread_exit;
            }
            else
            {
                async_add_task_to_work_list_ordered(thread_context, work_element);
            }
            unsigned long elapsed_time = system_milliseconds() - start_time;
            async_profile_record_task_timings(thread_context, priority, elapsed_time);
        }
        thread_sleep(work_delay);
    }

    return running;
};
