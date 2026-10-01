#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\SD\Reach\Publishing\Main\shared\engine\source\foundation\baselib\errors\events\event_log_interface.cpp"
/* ---------- headers */

#include "foundation\baselib\errors\events\event_log_interface.h"
#include "baselib\system_time_xenon.h"
#include "baselib\thread_execution_windows.h"
#include "baselib\thread_manipulation.h"
#include "core\corelib\config\version.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_events.h"
#include "core\corelib\cseries\cseries_macros.h"
#include "foundation\baselib\datatypes\static_string.h"
#include "foundation\baselib\errors\events\event_globals.h"
#include "foundation\baselib\errors\events\event_log_cache.h"
#include "foundation\baselib\errors\events\event_log_folder_manager.h"
#include "foundation\baselib\errors\events\event_log_manager.h"
#include "foundation\baselib\errors\events\event_manager.h"
#include "foundation\baselib\files\file_errors.h"
#include "foundation\baselib\files\file_location_manager.h"
#include "foundation\baselib\multithreading\datatypes\initialization_lock.h"
#include "foundation\baselib\multithreading\synchronization\critical_section_windows.h"
#include "foundation\baselib\multithreading\synchronization\synchronization_event_windows.h"
#include "foundation\baselib\multithreading\synchronization\synchronization_manager.h"
#include "foundation\baselib\system\system_os_interface_xenon.h"

/* ---------- constants */

/* ---------- definitions */

struct s_event_log_globals
{
    bool initialized; // 0x0
    s_critical_section critical_section; // 0x4
    s_synchronization_event flush_event; // 0x8
    c_event_log_thread_interface * thread_interface; // 0xC
    s_static_string<128> subfolder; // 0x10
    c_event_log_folder_manager folder_manager; // 0x90
    c_event_log_manager manager; // 0x110
    c_event_log_cache cache; // 0x9659C
};
static_assert(sizeof(s_event_log_globals) == 0xA05B4, "s_event_log_globals");

/* ---------- prototypes */

static void event_logs_dispose_atexit(void);
static unsigned long event_logs_worker_thread_function(void * parameter);
static bool events_should_force_flush(unsigned long last_flush_time);

/* ---------- globals */

static s_critical_section_definition const k_event_logs_critical_section_definition = { "CS:SpasmEventLogs", 0, true, false, 0 };
static s_synchronization_event_definition const k_event_logs_flush_event_definition = { "EV:SpasmEventLogs", true, false };

static s_event_log_globals g_event_log_globals;

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// private: static long const c_event_log_cache::k_maximum_cache_entries; // "?k_maximum_cache_entries@c_event_log_cache@@0JB"
// private: static long const c_event_log_cache::k_string_buffer_size; // "?k_string_buffer_size@c_event_log_cache@@0JB"
// private: static long const c_event_log_cache::k_string_buffer_flush_threshold; // "?k_string_buffer_flush_threshold@c_event_log_cache@@0JB"
// public: static long const s_static_array<char, 32768>::k_element_count; // "?k_element_count@?$s_static_array@D$0IAAA@@@2JB"
// private: static long const c_file_output_buffer::k_buffer_size; // "?k_buffer_size@c_file_output_buffer@@0JB"
// private: static long const c_event_log_manager::k_maximum_event_log_filename_length; // "?k_maximum_event_log_filename_length@c_event_log_manager@@0JB"
// private: static long const c_event_log_manager::k_file_buffer_size; // "?k_file_buffer_size@c_event_log_manager@@0JB"
// public: static long const s_static_array<unsigned char, 65536>::k_element_count; // "?k_element_count@?$s_static_array@E$0BAAAA@@@2JB"
// private: static long const c_event_log_folder_manager::k_directory_lock_invalid; // "?k_directory_lock_invalid@c_event_log_folder_manager@@0JB"

// void event_logs_initialize(void);
// public: void c_event_log_cache::set_enabled(bool);
// public: void c_event_log_manager::set_retain_open_files(bool);
// void event_logs_dispose(void);
// void event_logs_set_thread_interface(class c_event_log_thread_interface *);
// void event_logs_set_subfolder(char const *);
// bool event_logs_get_subfolder(long, char *);
// enum e_event_log_index event_logs_create_log(char const *, class s_flags<enum e_event_log_flags, unsigned long, 5>);
// void event_logs_write(long, enum e_event_log_index const *, char const *);
// public: bool c_event_log_cache::get_enabled(void) const;
// void event_logs_flush(void);
// long event_logs_build_snapshot_files(long, class c_file_path *);
// bool event_logs_build_report_file_path(char const *, enum e_report_file_location, class c_file_path *);
// void event_logs_get_synchronization_objects(struct s_critical_section *);
// public: c_event_logs_critical_section::c_event_logs_critical_section(void);
// public: c_event_logs_critical_section::~c_event_logs_critical_section(void);
// bool event_logs_usable(void);
// void event_logs_flush_cache(void);
// void event_logs_dispose_atexit(void);
// unsigned long event_logs_worker_thread_function(void *);
// bool events_should_force_flush(unsigned long);
// public: s_event_log_globals::s_event_log_globals(void);
// public: c_event_log_manager::c_event_log_manager(void);
// public: c_event_log_cache::c_event_log_cache(void);
// public: c_static_stack<struct c_event_log_cache::s_cache_entry, 1024>::c_static_stack<struct c_event_log_cache::s_cache_entry, 1024>(void);
// public: c_static_stack<struct c_event_log_manager::s_event_log, 32>::c_static_stack<struct c_event_log_manager::s_event_log, 32>(void);
// public: c_event_log_manager::s_event_log::s_event_log(void);
// public: s_event_log_globals::~s_event_log_globals(void);
// public: c_event_log_manager::~c_event_log_manager(void);
// public: c_static_stack<struct c_event_log_manager::s_event_log, 32>::~c_static_stack<struct c_event_log_manager::s_event_log, 32>(void);
// public: c_event_log_manager::s_event_log::~s_event_log(void);
// void g_event_log_globals::`dynamic atexit destructor'(void);

void event_logs_initialize(void)
{
    mangled_ppc("?event_logs_initialize@@YAXXZ");

    assert_tag_debug_untracked_jul_11_2011(98, !g_event_log_globals.initialized);

    g_event_log_globals.critical_section = critical_section_declare(k_synchronization_group_base, &k_event_logs_critical_section_definition);
    g_event_log_globals.flush_event = synchronization_event_declare(k_synchronization_group_base, &k_event_logs_flush_event_definition);
    g_event_log_globals.thread_interface = NULL;

    file_locations_initialize();

    g_event_log_globals.folder_manager.initialize();
    g_event_log_globals.folder_manager.set_subfolder(g_event_log_globals.subfolder.get_string());
    g_event_log_globals.folder_manager.obtain_report_directory_lock();

    g_event_log_globals.manager.initialize(&g_event_log_globals.folder_manager);
    g_event_log_globals.manager.set_retain_open_files(true);

    g_event_log_globals.cache.initialize(&g_event_log_globals.manager);
    g_event_log_globals.cache.set_enabled(true);

    system_register_exit_function(event_logs_dispose_atexit);

    g_event_log_globals.initialized = true;
};

void event_logs_dispose(void)
{
    mangled_ppc("?event_logs_dispose@@YAXXZ");

    assert_tag_debug_untracked_jul_11_2011(148, g_event_log_globals.initialized);

    event_logs_flush();

    if (g_event_log_globals.thread_interface)
    {
        g_event_log_globals.thread_interface->stop_thread();
    }

    {
        c_event_logs_critical_section critical_section;

        g_event_log_globals.cache.dispose();
        g_event_log_globals.manager.dispose();
        g_event_log_globals.folder_manager.dispose();
    }

    g_event_log_globals.initialized = false;
};

void event_logs_set_thread_interface(c_event_log_thread_interface * thread_interface)
{
    mangled_ppc("?event_logs_set_thread_interface@@YAXPAVc_event_log_thread_interface@@@Z");

    assert_tag_debug_untracked_jul_11_2011(173, thread_interface);
    assert_tag_debug_untracked_jul_11_2011(174, g_event_log_globals.initialized);
    assert_tag_debug_untracked_jul_11_2011(175, g_event_log_globals.thread_interface==NULL);

    g_event_log_globals.thread_interface = thread_interface;
    thread_interface->start_thread(event_logs_worker_thread_function);
};

void event_logs_set_subfolder(char const * subfolder)
{
    mangled_ppc("?event_logs_set_subfolder@@YAXPBD@Z");

    if (g_event_log_globals.initialized)
    {
        if (subfolder == NULL)
        {
            event(_event_message, "events: removing subfolder and returning to main event log folder");
        }
        else
        {
            event(_event_message, "events: setting subfolder to '%s'", subfolder);
        }

        {
            c_event_logs_critical_section critical_section;

            event_logs_flush_cache();
            g_event_log_globals.manager.reset_all_logs_for_redirect();
            g_event_log_globals.folder_manager.release_report_directory_lock();
            g_event_log_globals.folder_manager.set_subfolder(subfolder);
            g_event_log_globals.folder_manager.obtain_report_directory_lock();
        }
    }
    else if (subfolder)
    {
        g_event_log_globals.subfolder.set(subfolder);
    }
    else
    {
        g_event_log_globals.subfolder.clear();
    }
};

bool event_logs_get_subfolder(long subfolder_length, char * out_subfolder)
{
    mangled_ppc("?event_logs_get_subfolder@@YA_NJPAD@Z");

    bool result = false;

    if (g_event_log_globals.initialized)
    {
        c_event_logs_critical_section critical_section;

        result = g_event_log_globals.folder_manager.get_subfolder(subfolder_length, out_subfolder);
    }
    else
    {
        g_event_log_globals.subfolder.copy_to(out_subfolder, subfolder_length);
        result = !g_event_log_globals.subfolder.is_empty();
    }

    return result;
};

e_event_log_index event_logs_create_log(char const * filename, s_flags<e_event_log_flags, unsigned long, k_event_log_flag_count> flags)
{
    mangled_ppc("?event_logs_create_log@@YA?AW4e_event_log_index@@PBDV?$s_flags@W4e_event_log_flags@@K$04@@@Z");

    e_event_log_index event_log_index = k_event_log_invalid;

    if (event_logs_usable())
    {
        c_event_logs_critical_section critical_section;

        event_log_index = g_event_log_globals.manager.create_log(filename, flags);
    }

    return event_log_index;
};

void event_logs_write(long event_log_count, e_event_log_index const * event_log_indices, char const * string)
{
    mangled_ppc("?event_logs_write@@YAXJPBW4e_event_log_index@@PBD@Z");

    if (event_logs_usable())
    {
        c_event_logs_critical_section critical_section;
        bool request_flush = false;

        assert_tag_debug_untracked_jul_11_2011(272, event_log_count>0 && event_log_count<=k_maximum_event_logs);
        assert_tag_debug_untracked_jul_11_2011(273, event_log_indices);
        assert_tag_debug_untracked_jul_11_2011(274, string);

        if (g_event_log_globals.cache.get_enabled() && g_event_log_globals.cache.add_to_cache(event_log_count, event_log_indices, string, &request_flush))
        {
            request_flush = request_flush || events_should_force_flush(g_event_log_globals.cache.get_last_flush_time());
            if (request_flush)
            {
                if (g_event_log_globals.thread_interface)
                {
                    synchronization_event_set_internal(g_event_log_globals.flush_event);
                }
                else
                {
                    event_logs_flush_cache();
                }
            }
        }
        else
        {
            event_logs_flush_cache();

            assert_tag_debug_untracked_jul_11_2011(300, g_event_log_globals.cache.is_empty());

            for (long log_index = 0; log_index < event_log_count; log_index++)
            {
                e_event_log_index event_log_index = event_log_indices[log_index];
                g_event_log_globals.manager.write_to_log(event_log_index, c_event_log_manager::_write_buffer_mode_flush, string);
            }
        }
    }
};

void event_logs_flush(void)
{
    mangled_ppc("?event_logs_flush@@YAXXZ");

    if (event_logs_usable())
    {
        c_event_logs_critical_section critical_section;

        event_logs_flush_cache();
    }
};

long event_logs_build_snapshot_files(long maximum_file_count, c_file_path * out_file_paths)
{
    mangled_ppc("?event_logs_build_snapshot_files@@YAJJPAVc_file_path@@@Z");

    long file_count = 0;

    assert_tag_debug_untracked_jul_11_2011(332, maximum_file_count>=k_maximum_event_logs);
    assert_tag_debug_untracked_jul_11_2011(333, out_file_paths);

    if (event_logs_usable())
    {
        c_event_logs_critical_section critical_section;

        event_logs_flush_cache();
        g_event_log_globals.manager.touch_all_logs();
        g_event_log_globals.manager.close_all_logs();
        file_count = g_event_log_globals.manager.get_log_paths(maximum_file_count, out_file_paths);
    }

    return file_count;
};

bool event_logs_build_report_file_path(char const * filename, e_report_file_location location, c_file_path * out_file_path)
{
    mangled_ppc("?event_logs_build_report_file_path@@YA_NPBDW4e_report_file_location@@PAVc_file_path@@@Z");

    bool result = false;

    if (g_event_log_globals.initialized)
    {
        c_event_logs_critical_section critical_section;

        g_event_log_globals.folder_manager.build_report_file_path(filename, location, out_file_path);
        result = true;
    }

    return result;
};

void event_logs_get_synchronization_objects(s_critical_section * out_critical_section)
{
    mangled_ppc("?event_logs_get_synchronization_objects@@YAXPAUs_critical_section@@@Z");

    assert_tag_debug_untracked_jul_11_2011(375, g_event_log_globals.initialized);
    assert_tag_debug_untracked_jul_11_2011(376, out_critical_section);

    *out_critical_section = g_event_log_globals.critical_section;
};

c_event_logs_critical_section::c_event_logs_critical_section(void) :
    m_locked(false)
{
    mangled_ppc("??0c_event_logs_critical_section@@QAA@XZ");

    assert_tag_debug_untracked_jul_11_2011(386, g_event_log_globals.initialized);

    if (synchronization_object_group_created(k_synchronization_group_base))
    {
        events_blocking_begin();
        critical_section_enter_internal(g_event_log_globals.critical_section, _critical_section_non_recursive);
        events_blocking_end();

        m_locked = true;
        file_errors_suppress_push();
    }
    else
    {
        assert_tag_debug_untracked_jul_11_2011(400, g_event_log_globals.thread_interface==NULL);
        initialization_lock_assert_thread_write_valid();
    }
};

c_event_logs_critical_section::~c_event_logs_critical_section(void)
{
    mangled_ppc("??1c_event_logs_critical_section@@QAA@XZ");

    if (m_locked)
    {
        file_errors_suppress_pop();
        critical_section_leave_internal(g_event_log_globals.critical_section, _critical_section_non_recursive);
        m_locked = false;
    }
};

bool event_logs_usable(void)
{
    mangled_ppc("?event_logs_usable@@YA_NXZ");

    bool usable = g_event_log_globals.initialized;

    if (g_event_log_globals.thread_interface)
    {
        usable = usable && !g_event_log_globals.thread_interface->is_crashed();
    }

    return usable;
};

void event_logs_flush_cache(void)
{
    mangled_ppc("?event_logs_flush_cache@@YAXXZ");

    unsigned long flush_start_time = system_milliseconds();

    g_event_log_globals.cache.flush();

    if (g_event_log_globals.thread_interface)
    {
        synchronization_event_reset_internal(g_event_log_globals.flush_event);
    }

    unsigned long flush_time = system_milliseconds() - flush_start_time;
    if (flush_time > 100)
    {
        events_internal_error("events: flush_event_log_cache took %d msecs to flush", flush_time);
    }
};

static void event_logs_dispose_atexit(void)
{
    mangled_ppc("?event_logs_dispose_atexit@@YAXXZ");

    if (g_event_log_globals.initialized)
    {
        event_logs_flush_cache();
    }
};

static unsigned long event_logs_worker_thread_function(void * parameter)
{
    mangled_ppc("?event_logs_worker_thread_function@@YAKPAX@Z");

    events_force_emergency_redirection_thread_push();
    thread_set_current_thread_name("EVENT_LOGS");

    assert_tag_debug_untracked_jul_11_2011(474, g_event_log_globals.thread_interface);

    while (!g_event_log_globals.thread_interface->thread_should_exit())
    {
        long const flush_timeout_milliseconds = 1000;
        if (synchronization_event_wait_timeout_internal(g_event_log_globals.flush_event, flush_timeout_milliseconds))
        {
            c_event_logs_critical_section critical_section;

            event_logs_flush_cache();
        }

        g_event_log_globals.thread_interface->thread_idle();
        thread_switch();
    }

    events_force_emergency_redirection_thread_pop();

    return 0;
};

static bool events_should_force_flush(unsigned long last_flush_time)
{
    mangled_ppc("?events_should_force_flush@@YA_NK@Z");

    bool force_flush = false;

    if (!version_is_tracked_build())
    {
        unsigned long current_time = system_milliseconds();
        unsigned long time_since_flush = current_time - last_flush_time;
        force_flush = time_since_flush > 5000;
    }

    return force_flush;
};
