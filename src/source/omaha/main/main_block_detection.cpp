#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\main\\main_block_detection.cpp"
/* ---------- headers */

#include "omaha\main\main_block_detection.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "omaha\multithreading\synchronization_spasm.h"
#include "omaha\multithreading\threads.h"
#include "omaha\networking\network_time.h"
#include "omaha\profiler\profiler_stopwatch.h"

#include <xtl.h>
#include <xbdm.h>

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

c_block_detection_globals_container block_detection_globals;

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// public: static long const s_static_array<struct s_block_detection_type_data, 2>::k_element_count; // "?k_element_count@?$s_static_array@Us_block_detection_type_data@@$01@@2JB"
// class c_block_detection_globals_container block_detection_globals; // "?block_detection_globals@@3Vc_block_detection_globals_container@@A"

// unsigned long block_detection_thread_main(void *);
// long network_time_since(unsigned long);
// unsigned long network_time_get(void);
// unsigned long network_time_get_exact(void);
// long network_time_difference_msec(unsigned long, unsigned long);
// void block_detection_initialize(void);
// void block_detection_dispose(void);
// void block_detection_configure(enum e_block_detection_type, bool, bool, long);
// long block_detection_notify_unblocked(enum e_block_detection_type);
// void block_detection_suspend(enum e_block_detection_type);
// void block_detection_resume(enum e_block_detection_type);
// public: c_block_detection_globals_accessor::c_block_detection_globals_accessor(void);
// public: c_block_detection_globals_accessor::~c_block_detection_globals_accessor(void);
// public: struct s_block_detection_globals const * c_block_detection_globals_accessor::operator->(void) const;
// public: struct s_block_detection_globals * c_block_detection_globals_accessor::operator->(void);
// bool block_detection_is_debugger_present_internal(void);
// public: struct s_block_detection_type_data & s_static_array<struct s_block_detection_type_data, 2>::operator[]<long>(long);
// public: struct s_block_detection_type_data & s_static_array<struct s_block_detection_type_data, 2>::operator[]<enum e_block_detection_type>(enum e_block_detection_type);
// public: static bool s_static_array<struct s_block_detection_type_data, 2>::valid<long>(long);
// public: static bool s_static_array<struct s_block_detection_type_data, 2>::valid<enum e_block_detection_type>(enum e_block_detection_type);
// public: c_block_detection_globals_container::c_block_detection_globals_container(void);
// public: s_block_detection_globals::s_block_detection_globals(void);

unsigned long block_detection_thread_main(void * thread_parameter)
{
    mangled_ppc("?block_detection_thread_main@@YAKPAX@Z");

    while (!current_thread_should_exit())
    {
        bool block_detection_active = true;
        synchronization_event_wait_internal(g_omaha_events[k_event_network_block_detection]);

        while (block_detection_active && !current_thread_should_exit())
        {
            unsigned long sleep_time = 5;
            sleep(sleep_time);

            {
                c_block_detection_globals_accessor globals;
                block_detection_active = false;
                if (globals->exit_requested)
                {
                    block_detection_active = true;
                }

                for (long type_index = 0; type_index < k_block_detection_type_count; type_index++)
                {
                    s_block_detection_type_data & block_detection_type_data = globals->types[type_index];
                    block_detection_active |= block_detection_type_data.enabled;
                    if (block_detection_type_data.enabled && block_detection_type_data.block_detection_threshold > 0 && block_detection_type_data.suspend_block_detection_stack == 0)
                    {
                        long threshold = block_detection_type_data.block_detection_threshold + block_detection_type_data.suspended_time;
                        if (network_time_since(block_detection_type_data.last_unblocked_time) >= threshold && !block_detection_type_data.block_detected)
                        {
                            bool should_break = true;
                            if (block_detection_type_data.only_break_when_debugger_present)
                            {
                                should_break = block_detection_is_debugger_present_internal();
                            }

                            if (should_break)
                            {
                                c_stop_watch stop_watch;
                                DebugBreak();
                                block_detection_type_data.block_detected = true;
                            }
                        }
                    }
                }
            }

            current_thread_update_test_functions();
        }
    }

    return 0;
};

void block_detection_initialize(void)
{
    mangled_ppc("?block_detection_initialize@@YAXXZ");

    start_thread(k_thread_network_block_detection);

    c_block_detection_globals_accessor globals;
    for (long type_index = 0; type_index < k_block_detection_type_count; type_index++)
    {
        s_block_detection_type_data & block_detection_type_data = globals->types[type_index];
        block_detection_type_data.last_unblocked_time = network_time_get();
    }
};

void block_detection_dispose(void)
{
    mangled_ppc("?block_detection_dispose@@YAXXZ");

    {
        c_block_detection_globals_accessor globals;
        globals->exit_requested = true;
    }

    synchronization_event_set_internal(g_omaha_events[k_event_network_block_detection]);
    stop_thread(k_thread_network_block_detection);
};

void block_detection_configure(e_block_detection_type type, bool enabled, bool only_break_when_debugger_present, long block_detection_threshold)
{
    mangled_ppc("?block_detection_configure@@YAXW4e_block_detection_type@@_N1J@Z");

    c_block_detection_globals_accessor globals;
    s_block_detection_type_data * block_detection_type_data = &globals->types[type];
    block_detection_type_data->enabled = enabled;
    block_detection_type_data->only_break_when_debugger_present = only_break_when_debugger_present;
    block_detection_type_data->block_detection_threshold = block_detection_threshold;
    if (enabled)
    {
        synchronization_event_set_internal(g_omaha_events[k_event_network_block_detection]);
    }

    block_detection_notify_unblocked(type);
};

long block_detection_notify_unblocked(e_block_detection_type type)
{
    mangled_ppc("?block_detection_notify_unblocked@@YAJW4e_block_detection_type@@@Z");

    c_block_detection_globals_accessor globals;
    s_block_detection_type_data & block_detection_type_data = globals->types[type];
    long time_since_unblocked = network_time_since(block_detection_type_data.last_unblocked_time);
    block_detection_type_data.last_unblocked_time = network_time_get();
    block_detection_type_data.suspended_time = 0;
    block_detection_type_data.block_detected = false;
    if (globals->signal_on_unblock)
    {
        synchronization_event_set_internal(g_omaha_events[k_event_network_block_detection]);
        globals->signal_on_unblock = false;
    }

    return time_since_unblocked;
};

void block_detection_suspend(e_block_detection_type type)
{
    mangled_ppc("?block_detection_suspend@@YAXW4e_block_detection_type@@@Z");

    c_block_detection_globals_accessor globals;
    s_block_detection_type_data * block_detection_type_data = &globals->types[type];
    assert_tag_debug_untracked_jul_11_2011(289, block_detection_type_data->suspend_block_detection_stack>=0);

    if (block_detection_type_data->suspend_block_detection_stack == 0)
    {
        block_detection_type_data->suspend_start_time = network_time_get();
    }
    block_detection_type_data->suspend_block_detection_stack++;
};

void block_detection_resume(e_block_detection_type type)
{
    mangled_ppc("?block_detection_resume@@YAXW4e_block_detection_type@@@Z");

    c_block_detection_globals_accessor globals;
    s_block_detection_type_data * block_detection_type_data = &globals->types[type];
    assert_tag_debug_untracked_jul_11_2011(305, block_detection_type_data->suspend_block_detection_stack>0);

    block_detection_type_data->suspend_block_detection_stack--;
    if (block_detection_type_data->suspend_block_detection_stack == 0)
    {
        block_detection_type_data->suspended_time += network_time_since(block_detection_type_data->suspend_start_time);
    }
};

c_block_detection_globals_accessor::c_block_detection_globals_accessor(void)
{
    mangled_ppc("??0c_block_detection_globals_accessor@@QAA@XZ");

    critical_section_enter_internal(g_omaha_critical_sections[k_crit_section_network_block_detection], _critical_section_non_recursive);
};

c_block_detection_globals_accessor::~c_block_detection_globals_accessor(void)
{
    mangled_ppc("??1c_block_detection_globals_accessor@@QAA@XZ");

    critical_section_leave_internal(g_omaha_critical_sections[k_crit_section_network_block_detection], _critical_section_non_recursive);
};

s_block_detection_globals const * c_block_detection_globals_accessor::operator->(void) const
{
    mangled_ppc("??Cc_block_detection_globals_accessor@@QBAPBUs_block_detection_globals@@XZ");

    return &block_detection_globals.m_globals;
};

s_block_detection_globals * c_block_detection_globals_accessor::operator->(void)
{
    mangled_ppc("??Cc_block_detection_globals_accessor@@QAAPAUs_block_detection_globals@@XZ");

    return &block_detection_globals.m_globals;
};

bool block_detection_is_debugger_present_internal(void)
{
    mangled_ppc("?block_detection_is_debugger_present_internal@@YA_NXZ");

    bool debugger_present = false;
    if (DmIsDebuggerPresent())
    {
        debugger_present = true;
    }

    return debugger_present;
};
