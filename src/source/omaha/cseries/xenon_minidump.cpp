#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\cseries\\xenon_minidump.cpp"
/* ---------- headers */

#include <xtl.h>

#include "omaha\cseries\xenon_minidump.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_events.h"
#include "core\corelib\cseries\cseries_macros.h"
#include "baselib\system_exception_windows.h"
#include "blamlib\retail_minidump_info_provider.h"
#include "blamlib\xbdm_minidump_info_provider.h"
#include "foundation\baselib\datatypes\static_string.h"
#include "foundation\baselib\system\system_os_interface_xenon.h"
#include "omaha\cache\physical_memory_map.h"
#include "omaha\cseries\cseries_windows_debug.h"
#include "omaha\cseries\minidump_writer.h"
#include "omaha\interface\damaged_media.h"
#include "omaha\main\main.h"
#include "omaha\multithreading\threads.h"
#include "omaha\networking\network_memory.h"
#include "omaha\profiler\profiler_stopwatch.h"
#include "omaha\saved_games\game_state.h"
#include "omaha\text\font_cache.h"

/* ---------- constants */

/* ---------- definitions */

// platform layout behind the opaque s_exception_information storage (see system_build_exception_information)
struct s_exception_information_xenon
{
    unsigned long thread_id; // 0x0
    CONTEXT context; // 0x8
    unsigned long exception_code; // 0xA48
    unsigned long exception_flags; // 0xA4C
    void * exception_address; // 0xA50
    unsigned long number_parameters; // 0xA54
    unsigned long exception_information[4]; // 0xA58
};
static_assert(sizeof(s_exception_information_xenon) == 0xA68, "s_exception_information_xenon");

typedef bool (*memory_descriptor_proc_t)(s_memory_stream_descriptor * descriptor);

/* ---------- prototypes */

/* ---------- globals */

bool g_minidump_use_retail_provider = true;
bool g_minidump_always_force_regular_minidumps_with_ui = true;

static bool g_minidump_allow_debug_output = true;
static unsigned long g_minidump_system_version;

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// private: static long const c_minidump_writer::k_minidump_directory_count; // "?k_minidump_directory_count@c_minidump_writer@@0JB"
// private: static long const c_minidump_writer::k_max_thread_dump_count; // "?k_max_thread_dump_count@c_minidump_writer@@0JB"
// private: static long const c_minidump_writer::k_max_memory_descriptor_count; // "?k_max_memory_descriptor_count@c_minidump_writer@@0JB"
// private: static long const c_minidump_writer::k_total_memory_descriptors_supported; // "?k_total_memory_descriptors_supported@c_minidump_writer@@0JB"
// private: static unsigned long const c_xbdm_minidump_info_provider::k_max_virtual_memory_address; // "?k_max_virtual_memory_address@c_xbdm_minidump_info_provider@@0KB"
// public: static unsigned long const c_retail_minidump_info_provider::k_max_virtual_memory_address; // "?k_max_virtual_memory_address@c_retail_minidump_info_provider@@2KB"
// public: static long const s_static_string<30>::k_index_not_found; // "?k_index_not_found@?$s_static_string@$0BO@@@2JB"
// public: static long const s_static_string<30>::k_element_count; // "?k_element_count@?$s_static_string@$0BO@@@2JB"
// bool g_minidump_use_retail_provider; // "?g_minidump_use_retail_provider@@3_NA"
// bool g_minidump_always_force_regular_minidumps_with_ui; // "?g_minidump_always_force_regular_minidumps_with_ui@@3_NA"

// long minidump_from_exception(long, char const *, unsigned long, struct s_exception_information const *, bool);
// public: s_minidump_configuration::s_minidump_configuration(void);
// public: virtual c_retail_minidump_info_provider::~c_retail_minidump_info_provider(void);
// public: virtual c_xbdm_minidump_info_provider::~c_xbdm_minidump_info_provider(void);
// public: virtual c_minidump_provider_common::~c_minidump_provider_common(void);
// public: virtual c_minidump_provider_interface::~c_minidump_provider_interface(void);
// merged_833486F0;
// void minidump_now(char const *);
// bool get_game_state_memory_descriptor(struct s_memory_stream_descriptor *);
// bool get_network_memory_descriptor(struct s_memory_stream_descriptor *);
// bool get_cache_file_tag_resource_runtime_memory_descriptor(struct s_memory_stream_descriptor *);
// bool get_tag_memory_descriptor(struct s_memory_stream_descriptor *);
// void minidump_progress_report(float, bool);
// long minidump_now_support(char const *, unsigned long, struct s_exception_pointers *);
// public: char const * s_static_string<30>::print(char const *, ...);
// public: char const * s_static_string<30>::get_string(void) const;
// public: c_static_string<30>::c_static_string<30>(void);
// public: void s_static_string<30>::clear(void);

long minidump_from_exception(long flags, char const * out_file, unsigned long exception_code, s_exception_information const * platform_exception_information, bool unknown)
{
    mangled_ppc("?minidump_from_exception@@YAJJPBDKPBUs_exception_information@@_N@Z");

    s_exception_information_xenon const * exception_information = reinterpret_cast<s_exception_information_xenon const *>(platform_exception_information);
    c_minidump_writer writer;
    s_minidump_configuration configuration;
    s_minidump_exception_information minidump_exception_information = { 0 };
    EXCEPTION_POINTERS exception_pointers = { 0 };
    EXCEPTION_RECORD exception_record = { 0 };
    bool damaged_media_only = false;
    memory_descriptor_proc_t memory_descriptor_procs[] =
    {
        get_game_state_memory_descriptor,
        get_network_memory_descriptor,
        get_cache_file_tag_resource_runtime_memory_descriptor,
        get_tag_memory_descriptor,
    };

    assert_tag_debug_untracked_jul_11_2011(97, out_file);
    assert_tag_debug_untracked_jul_11_2011(98, exception_information);

    s_operating_system_version system_version;
    if (system_get_operating_system_version(&system_version))
    {
        g_minidump_system_version = system_version.system_version;
    }

    if (g_minidump_always_force_regular_minidumps_with_ui)
    {
        flags = 0;
        SET_BIT(flags, _minidump_regular_bit, true);
        SET_BIT(flags, _minidump_with_ui_bit, true);
    }

    damaged_media_only = TEST_BIT(flags, _minidump_damaged_media_bit);
    if (damaged_media_only && g_minidump_allow_debug_output)
    {
        g_minidump_allow_debug_output = false;
    }

    configuration.unknown4 = 0;
    bool with_ui = TEST_BIT(flags, _minidump_with_ui_bit);
    configuration.progress_callback = with_ui ? minidump_progress_report : NULL;

    minidump_exception_information.exception_pointers = &exception_pointers;
    exception_pointers.ContextRecord = const_cast<CONTEXT *>(&exception_information->context);
    exception_pointers.ExceptionRecord = &exception_record;
    exception_record.ExceptionAddress = exception_information->exception_address;
    exception_record.ExceptionCode = exception_information->exception_code;
    exception_record.ExceptionFlags = exception_information->exception_flags;
    exception_record.NumberParameters = exception_information->number_parameters;
    if (exception_information->number_parameters > 0 && exception_information->number_parameters * sizeof(unsigned long) <= sizeof(exception_record.ExceptionInformation))
    {
        memcpy(exception_record.ExceptionInformation, exception_information->exception_information, exception_information->number_parameters * sizeof(unsigned long));
    }
    minidump_exception_information.thread_id = exception_information->thread_id;

    configuration.write_full_memory = !damaged_media_only;
    configuration.unknownC = unknown;
    writer.set_minidump_configuration(configuration);

    if (damaged_media_only)
    {
        s_memory_stream_descriptor descriptor = { 0 };
        if (damaged_media_get_global_memory(&descriptor.size, &descriptor.address))
        {
            writer.add_memory_descriptor(descriptor);
        }
    }
    else
    {
        for (unsigned long proc_index = 0; proc_index < NUMBEROF(memory_descriptor_procs); proc_index++)
        {
            s_memory_stream_descriptor descriptor = { 0 };
            if (memory_descriptor_procs[proc_index](&descriptor) && descriptor.address && descriptor.size > 0)
            {
                writer.add_memory_descriptor(descriptor);
            }
        }

        for (long block_index = 0; block_index < physical_memory_get_minidump_count(); block_index++)
        {
            s_memory_stream_descriptor descriptor = { 0 };
            unsigned long block_size = 0;
            descriptor.address = physical_memory_get_minidump_block(block_index, &block_size);
            descriptor.size = block_size;
            writer.add_memory_descriptor(descriptor);
        }
    }

    bool success = false;
    c_stop_watch stop_watch;
    c_wait_for_render_thread wait_for_render_thread(__FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__, 202);
    if (g_minidump_use_retail_provider)
    {
        c_retail_minidump_info_provider retail_provider;
        success = writer.write(&retail_provider, out_file, minidump_exception_information);
    }
    else
    {
        c_xbdm_minidump_info_provider xbdm_provider;
        success = writer.write(&xbdm_provider, out_file, minidump_exception_information);
    }
    stop_watch.hold();

    event_wrapped(_event_message, "system:minidump: total dump time %.2f seconds", stop_watch.total_elapsed_time_in_seconds());
    if (!success)
    {
        event_wrapped(_event_error, "system:minidump: failed to write minidump at %s", out_file);
    }

    return -1;
};

void minidump_now(char const * minidump_file_name)
{
    mangled_ppc("?minidump_now@@YAXPBD@Z");

    assert_tag_debug_untracked_jul_11_2011(237, minidump_file_name);

    __try
    {
        RaiseException(FAKE_EXCEPTION_CODE, 0, 0, NULL);
    }
    __except (minidump_now_support(minidump_file_name, GetExceptionCode(), reinterpret_cast<s_exception_pointers *>(GetExceptionInformation())))
    {
    }
};

bool get_game_state_memory_descriptor(s_memory_stream_descriptor * descriptor)
{
    mangled_ppc("?get_game_state_memory_descriptor@@YA_NPAUs_memory_stream_descriptor@@@Z");

    unsigned long unlock_token;
    __try
    {
        unlock_token = halt_render_thread_and_lock_resources(292);
        descriptor->address = game_state_with_mirrors_get_buffer_address(reinterpret_cast<long *>(&descriptor->size));
    }
    __finally
    {
        unlock_resources_and_resume_render_thread(unlock_token);
    }

    return true;
};

bool get_network_memory_descriptor(s_memory_stream_descriptor * descriptor)
{
    mangled_ppc("?get_network_memory_descriptor@@YA_NPAUs_memory_stream_descriptor@@@Z");

    bool result = false;
    void * low_address = NULL;
    void * high_address = NULL;
    network_memory_get_address_range(&low_address, &high_address);
    if (high_address > low_address)
    {
        unsigned long size = static_cast<char *>(high_address) - static_cast<char *>(low_address);
        descriptor->address = low_address;
        descriptor->size = size;
        result = true;
    }

    return result;
};

bool get_cache_file_tag_resource_runtime_memory_descriptor(s_memory_stream_descriptor * descriptor)
{
    mangled_ppc("?get_cache_file_tag_resource_runtime_memory_descriptor@@YA_NPAUs_memory_stream_descriptor@@@Z");

    return false;
};

bool get_tag_memory_descriptor(s_memory_stream_descriptor * descriptor)
{
    mangled_ppc("?get_tag_memory_descriptor@@YA_NPAUs_memory_stream_descriptor@@@Z");

    return false;
};

void minidump_progress_report(float progress, bool done)
{
    mangled_ppc("?minidump_progress_report@@YAXM_N@Z");

    c_static_string<30> status;
    char progress_string[0x6000];

    status.print("\r\nwriting minidump... %.2f", progress);
    build_error_report_progress_string(progress_string, sizeof(progress_string), status.get_string());
    error_report_think_of_the_kittens(progress_string, sizeof(progress_string));
    crash_uploading_render_pregame_safe(progress_string, static_cast<e_main_pregame_frame>(_main_pregame_frame_crash_uploading + (done != 0)));
};

long minidump_now_support(char const * minidump_file_name, unsigned long exception_code, s_exception_pointers * exception_pointers)
{
    mangled_ppc("?minidump_now_support@@YAJPBDKPAUs_exception_pointers@@@Z");

    long result = -1;
    assert_tag_debug_untracked_jul_11_2011(409, is_main_thread());

    s_exception_information exception_information;
    system_build_exception_information(exception_pointers, &exception_information);

    long flags = 0;
    {
        c_wait_for_render_thread wait_for_render_thread(__FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__, 420);
        c_font_cache_mt_safe font_cache;
        SET_BIT(flags, _minidump_regular_bit, true);
        SET_BIT(flags, _minidump_with_ui_bit, true);
        result = minidump_from_exception(flags, minidump_file_name, exception_code, &exception_information, false);
    }

    return result;
};
