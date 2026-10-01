#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\job_manager\\job_manager_spasm.cpp"
/* ---------- headers */

#include "omaha\job_manager\job_manager_spasm.h"
#include "baselib\system_processor_xenon.h"
#include "baselib\thread_execution_windows.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_macros.h"
#include "core\corelib\cseries\cseries_memory.h"
#include "foundation\threadlib\jobmanager\job_manager.h"
#include "foundation\threadlib\multithreading\profiler\mt_profiler_store.h"
#include "omaha\cseries\cseries_windows_debug.h"
#include "omaha\multithreading\synchronization_spasm.h"
#include "omaha\multithreading\threads.h"
#include "threadlib\work_unit_handle.h"
#include "threadlib\work_unit_params.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

bool volatile g_signal_active_job_threads;
static c_jm_work_unit_handle g_work_unit_handle;

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// bool volatile g_signal_active_job_threads; // "?g_signal_active_job_threads@@3_NC"

// unsigned long job_main_thread(void *);
// void job_manager_omaha_initialize(void);
// public: struct s_critical_section const & c_job_manager::get_cs(unsigned long) const;
// public: struct s_semaphore const & c_job_manager::get_semaphore(unsigned long) const;
// enum e_registered_threads operator++(enum e_registered_threads &, int);
// void job_manager_omaha_dispose(void);
// public: c_jm_work_unit_handle::c_jm_work_unit_handle(void);
// void job_manager_block_callback(void);
// bool job_manager_has_any_job_thread_crashed(void);
// public: struct s_semaphore & s_static_array<struct s_semaphore, 11>::operator[]<enum e_synchronization_semaphore>(enum e_synchronization_semaphore);
// public: static bool s_static_array<struct s_semaphore, 11>::valid<enum e_synchronization_semaphore>(enum e_synchronization_semaphore);
// void g_work_unit_handle::`dynamic atexit destructor'(void);

unsigned long job_main_thread(void * thread_parameter)
{
    mangled_ppc("?job_main_thread@@YAKPAX@Z");

    unsigned long thread_index = address_from_pointer(thread_parameter);
    while (!g_signal_active_job_threads)
    {
        thread_sleep(100);
    }
    g_work_unit_handle.thread_entry_point(thread_index);

    return 0;
};

void job_manager_omaha_initialize(void)
{
    mangled_ppc("?job_manager_omaha_initialize@@YAXXZ");

    long thread_count = 2;
    mt_profiler_initialize();
    assert_tag_debug_untracked_jul_11_2011(64, !g_work_unit_handle.valid());

    job_manager_initialize(
        g_omaha_critical_sections[k_crit_section_job_manager_activelist],
        g_omaha_critical_sections[k_crit_section_job_manager_freelist],
        g_omaha_critical_sections[k_crit_section_job_manager_deps],
        g_omaha_semaphores[k_semaphore_job_manager0],
        g_omaha_semaphores[k_semaphore_job_manager1]);

    thread_count = MIN(MAX(thread_count, 1), system_processor_get_logical_count());

    c_job_manager & job_manager = get_job_manager();
    job_manager.register_block_callback(job_manager_block_callback);

    // local names affect /Od stack slot assignment (wu_params must sit below thread_count)
    s_work_unit_params wu_params(thread_count, job_manager.get_cs(0), job_manager.get_cs(1), job_manager.get_cs(2), job_manager.get_semaphore(1));
    g_work_unit_handle = c_job_manager::create_work_unit(wu_params);
    job_manager_set_default_work_unit(g_work_unit_handle);
    assert_tag_debug_untracked_jul_11_2011(93, g_work_unit_handle.valid());

    for (e_registered_threads thread_index = k_thread_job_first; thread_index < thread_count + k_thread_job_first; thread_index++)
    {
        start_thread(thread_index);
    }

    g_signal_active_job_threads = true;
};

void job_manager_omaha_dispose(void)
{
    mangled_ppc("?job_manager_omaha_dispose@@YAXXZ");

    assert_tag_debug_untracked_jul_11_2011(113, g_work_unit_handle.valid());

    c_job_manager::destroy_work_unit(g_work_unit_handle);
    job_manager_set_default_work_unit(c_jm_work_unit_handle());
    job_manager_dispose();
};

void job_manager_block_callback(void)
{
    mangled_ppc("?job_manager_block_callback@@YAXXZ");

    if (is_main_thread())
    {
        exceptions_update();
    }
    else if (job_manager_has_any_job_thread_crashed())
    {
        *reinterpret_cast<char const **>(NULL) = "Job Manager crashed, propagate please!";
    }
};

bool job_manager_has_any_job_thread_crashed(void)
{
    mangled_ppc("?job_manager_has_any_job_thread_crashed@@YA_NXZ");

    bool crashed = false;
    for (e_registered_threads thread_index = k_thread_job_first; !crashed && thread_index <= k_thread_job_last; ++thread_index)
    {
        crashed = crashed || thread_has_crashed(thread_index);
    }

    return crashed;
};
