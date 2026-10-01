#pragma once
#ifndef __SYNCHRONIZATION_SPASM_H__
#define __SYNCHRONIZATION_SPASM_H__

/* ---------- headers */

#include "foundation\baselib\datatypes\static_array.h"
#include "foundation\baselib\multithreading\synchronization\critical_section_windows.h"
#include "foundation\baselib\multithreading\synchronization\synchronization_event_windows.h"
#include "foundation\baselib\multithreading\synchronization\semaphore_windows.h"

/* ---------- constants */

// Reach has 84 critical sections; only the values below are verified (names follow the H3 pattern)
enum e_critical_sections
{
    k_crit_section_async_xoverlapped_memory = 28, // c_async_xoverlapped_memory_scope_lock
    k_crit_section_game_engine = 29, // c_game_engine_scope_lock
    k_crit_section_audio_region = 36,
    k_crit_section_audio_subsection = 37,
    k_crit_section_shared_region = 38,
    k_crit_section_shared_subsection = 39,
    k_crit_section_shared_subsection_mirror0 = 40,
    k_crit_section_shared_subsection_mirror1 = 41,
    k_crit_section_network_block_detection = 63, // c_block_detection_globals_accessor
    k_crit_section_storage_device_manager = 78, // c_storage_device_manager_globals_accessor, c_storage_device_accessor
    k_crit_section_job_manager_activelist = 79, // job_manager_omaha_initialize
    k_crit_section_job_manager_freelist = 80,
    k_crit_section_job_manager_deps = 81,

    k_total_critical_sections = 84,
    k_invalid_critical_section = -1
};

// Reach has 11 semaphores; names not yet recovered
enum e_synchronization_semaphore
{
    k_semaphore_job_manager0 = 9, // job_manager_omaha_initialize
    k_semaphore_job_manager1 = 10,

    k_total_synchronization_semaphores = 11,
    k_invalid_semaphore = -1
};

// Reach has 8 events; only the values below are verified
enum e_synchronization_events
{
    k_event_network_block_detection = 7, // block_detection_thread_main

    k_total_synchronization_events = 8
};

/* ---------- definitions */

/* ---------- prototypes */

extern void initialize_synchronization_objects(void);
extern void destroy_synchronization_objects(void);

/* ---------- globals */

extern s_static_array<s_critical_section, k_total_critical_sections> g_omaha_critical_sections;
extern s_static_array<s_semaphore, k_total_synchronization_semaphores> g_omaha_semaphores;
extern s_static_array<s_synchronization_event, k_total_synchronization_events> g_omaha_events;

/* ---------- public code */

#endif // __SYNCHRONIZATION_SPASM_H__

