#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\cseries\\cseries.cpp"
/* ---------- headers */

#include <xtl.h>

#include "omaha\cseries\cseries.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "baselib\system_os_interface.h"
#include "foundation\baselib\errors\asserts\assert_handler_instance.h"
#include "foundation\baselib\errors\events\event_globals.h"
#include "foundation\baselib\memory\allocation_interface.h"
#include "foundation\baselib\memory\base\base_memory_windows.h"
#include "foundation\baselib\memory\debug_memory\debug_memory_globals.h"
#include "foundation\baselib\multithreading\datatypes\initialization_lock.h"
#include "foundation\baselib\multithreading\synchronization\synchronization_manager.h"
#include "omaha\cache\physical_memory_map.h"
#include "omaha\cseries\cseries_errors.h"
#include "omaha\cseries\cseries_windows_debug.h"
#include "omaha\cseries\stack_walk_windows.h"
#include "omaha\main\main.h"
#include "omaha\math\random_math.h"
#include "omaha\memory\crc.h"
#include "omaha\multithreading\synchronization_spasm.h"
#include "omaha\multithreading\threads.h"
#include "omaha\profiler\profiler.h"
#include "omaha\profiler\profiler_counters.h"
#include "omaha\shell\shell.h"

/* ---------- constants */

/* ---------- definitions */

class c_cseries_engine_assert_interface :
    public c_engine_assert_interface
{
public:
    c_cseries_engine_assert_interface(void)
    {
        mangled_ppc("??0c_cseries_engine_assert_interface@@QAA@XZ");
    };

private:
    virtual bool thread_manager_handle_assertion_via_exception(void);
    virtual void thread_manager_post_assertion(char const * expression, char const * file, long line);
    virtual void call_fatal_error_callbacks(void);
    virtual void generate_stack_walk(char const * assert_string);
    virtual void raise_exception_unhandled(char const * expression, char const * file, long line);
    virtual void raise_exception_handled(char const * expression, char const * file, long line);
};

class c_cseries_base_allocation :
    public c_allocation_interface
{
public:
    c_cseries_base_allocation(void)
    {
        mangled_ppc("??0c_cseries_base_allocation@@QAA@XZ");
    };

    virtual void * allocate(unsigned int size, char const * file, long line, char const * type, char const * subtype, char const * name);
    virtual void deallocate(void * pointer, char const * file, long line);
};

/* ---------- prototypes */

/* ---------- globals */

static c_cseries_engine_assert_interface g_cseries_engine_assert_interface;
static c_cseries_base_allocation g_cseries_base_allocation_instance;

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// char const *const const g_zero_buffer; // "?g_zero_buffer@@3QBDB"
// long const global_real_argb_color_table_size; // "?global_real_argb_color_table_size@@3JB"
// bool g_catch_exceptions; // "?g_catch_exceptions@@3_NA"
// union argb_color const *const global_real_argb_color_table; // "?global_real_argb_color_table@@3PBTargb_color@@B"
// union argb_color const *const global_real_argb_white; // "?global_real_argb_white@@3PBTargb_color@@B"
// union argb_color const *const global_real_argb_grey; // "?global_real_argb_grey@@3PBTargb_color@@B"
// union argb_color const *const global_real_argb_black; // "?global_real_argb_black@@3PBTargb_color@@B"
// union argb_color const *const global_real_argb_red; // "?global_real_argb_red@@3PBTargb_color@@B"
// union argb_color const *const global_real_argb_green; // "?global_real_argb_green@@3PBTargb_color@@B"
// union argb_color const *const global_real_argb_blue; // "?global_real_argb_blue@@3PBTargb_color@@B"
// union argb_color const *const global_real_argb_cyan; // "?global_real_argb_cyan@@3PBTargb_color@@B"
// union argb_color const *const global_real_argb_yellow; // "?global_real_argb_yellow@@3PBTargb_color@@B"
// union argb_color const *const global_real_argb_magenta; // "?global_real_argb_magenta@@3PBTargb_color@@B"
// union argb_color const *const global_real_argb_pink; // "?global_real_argb_pink@@3PBTargb_color@@B"
// union argb_color const *const global_real_argb_lightblue; // "?global_real_argb_lightblue@@3PBTargb_color@@B"
// union argb_color const *const global_real_argb_orange; // "?global_real_argb_orange@@3PBTargb_color@@B"
// union argb_color const *const global_real_argb_purple; // "?global_real_argb_purple@@3PBTargb_color@@B"
// union argb_color const *const global_real_argb_aqua; // "?global_real_argb_aqua@@3PBTargb_color@@B"
// union argb_color const *const global_real_argb_darkgreen; // "?global_real_argb_darkgreen@@3PBTargb_color@@B"
// union argb_color const *const global_real_argb_salmon; // "?global_real_argb_salmon@@3PBTargb_color@@B"
// union argb_color const *const global_real_argb_violet; // "?global_real_argb_violet@@3PBTargb_color@@B"
// union rgb_color const *const global_real_rgb_white; // "?global_real_rgb_white@@3PBTrgb_color@@B"
// union rgb_color const *const global_real_rgb_grey; // "?global_real_rgb_grey@@3PBTrgb_color@@B"
// union rgb_color const *const global_real_rgb_black; // "?global_real_rgb_black@@3PBTrgb_color@@B"
// union rgb_color const *const global_real_rgb_red; // "?global_real_rgb_red@@3PBTrgb_color@@B"
// union rgb_color const *const global_real_rgb_green; // "?global_real_rgb_green@@3PBTrgb_color@@B"
// union rgb_color const *const global_real_rgb_blue; // "?global_real_rgb_blue@@3PBTrgb_color@@B"
// union rgb_color const *const global_real_rgb_cyan; // "?global_real_rgb_cyan@@3PBTrgb_color@@B"
// union rgb_color const *const global_real_rgb_yellow; // "?global_real_rgb_yellow@@3PBTrgb_color@@B"
// union rgb_color const *const global_real_rgb_magenta; // "?global_real_rgb_magenta@@3PBTrgb_color@@B"
// union rgb_color const *const global_real_rgb_pink; // "?global_real_rgb_pink@@3PBTrgb_color@@B"
// union rgb_color const *const global_real_rgb_lightblue; // "?global_real_rgb_lightblue@@3PBTrgb_color@@B"
// union rgb_color const *const global_real_rgb_orange; // "?global_real_rgb_orange@@3PBTrgb_color@@B"
// union rgb_color const *const global_real_rgb_purple; // "?global_real_rgb_purple@@3PBTrgb_color@@B"
// union rgb_color const *const global_real_rgb_aqua; // "?global_real_rgb_aqua@@3PBTrgb_color@@B"
// union rgb_color const *const global_real_rgb_darkgreen; // "?global_real_rgb_darkgreen@@3PBTrgb_color@@B"
// union rgb_color const *const global_real_rgb_salmon; // "?global_real_rgb_salmon@@3PBTrgb_color@@B"
// union rgb_color const *const global_real_rgb_violet; // "?global_real_rgb_violet@@3PBTrgb_color@@B"
// bool g_halt_on_stack_overflow; // "?g_halt_on_stack_overflow@@3_NA"

// void cseries_core_initialize(void);
// void cseries_foundation_initialize(void);
// void cseries_foundation_dispose(void);
// void cseries_core_dispose(void);
// void halt_function_initialize(void);
// void halt_function_dispose(void);
// long assert_stack_walk_exception_filter(unsigned long, struct _EXCEPTION_POINTERS *);
// private: virtual bool c_cseries_engine_assert_interface::thread_manager_handle_assertion_via_exception(void);
// private: virtual void c_cseries_engine_assert_interface::thread_manager_post_assertion(char const *, char const *, long);
// private: virtual void c_cseries_engine_assert_interface::call_fatal_error_callbacks(void);
// private: virtual void c_cseries_engine_assert_interface::generate_stack_walk(char const *);
// private: virtual void c_cseries_engine_assert_interface::raise_exception_unhandled(char const *, char const *, long);
// void raise_managed_dll_exception_immediate(char const *, char const *, long, enum e_crash_type);
// void raise_unmanaged_exception_immediate(char const *, char const *, long);
// private: virtual void c_cseries_engine_assert_interface::raise_exception_handled(char const *, char const *, long);
// unsigned long debug_memory_checksum_buffer(void const *, unsigned int);
// unsigned short debug_memory_local_random(void);
// public: virtual void * c_cseries_base_allocation::allocate(unsigned int, char const *, long, char const *, char const *, char const *);
// public: virtual void c_cseries_base_allocation::deallocate(void *, char const *, long);
// public: c_cseries_engine_assert_interface::c_cseries_engine_assert_interface(void);
// public: c_engine_assert_interface::c_engine_assert_interface(void);
// public: c_cseries_base_allocation::c_cseries_base_allocation(void);

void cseries_core_initialize(void)
{
    mangled_ppc("?cseries_core_initialize@@YAXXZ");

    halt_function_initialize();
    assert_handler_initialize(&g_cseries_engine_assert_interface);
};

void cseries_foundation_initialize(void)
{
    mangled_ppc("?cseries_foundation_initialize@@YAXXZ");

    initialization_lock_startup_begin();
    initialization_lock_thread_begin();
    initialize_performance_counters();
    synchronization_manager_initialize(&g_cseries_base_allocation_instance);
    initialize_thread_management();
    initialize_synchronization_objects();
    debug_memory_manager_initialize(debug_memory_checksum_buffer, debug_memory_local_random);
    physical_memory_register_allocation();
    profiler_initialize_system();
};

void cseries_foundation_dispose(void)
{
    mangled_ppc("?cseries_foundation_dispose@@YAXXZ");

    debug_memory_begin_exit();
    events_dispose();
    destroy_thread_management();
    destroy_synchronization_objects();
};

void cseries_core_dispose(void)
{
    mangled_ppc("?cseries_core_dispose@@YAXXZ");

    assert_handler_dispose();
    halt_function_dispose();
};

void halt_function_initialize(void)
{
    mangled_ppc("?halt_function_initialize@@YAXXZ");

    if (!g_managed_dll)
    {
        system_register_halt_function(main_halt_and_catch_fire);
    }
};

void halt_function_dispose(void)
{
    mangled_ppc("?halt_function_dispose@@YAXXZ");

    if (!g_managed_dll)
    {
        system_register_halt_function(NULL);
    }
};

long assert_stack_walk_exception_filter(unsigned long exception_code, _EXCEPTION_POINTERS * exception_pointers)
{
    mangled_ppc("?assert_stack_walk_exception_filter@@YAJKPAU_EXCEPTION_POINTERS@@@Z");

    long result = EXCEPTION_CONTINUE_SEARCH;
    if (exception_pointers != NULL && exception_pointers->ExceptionRecord != NULL)
    {
        EXCEPTION_POINTERS fake_exception_pointers = *exception_pointers;
        EXCEPTION_RECORD fake_exception_record = *exception_pointers->ExceptionRecord;
        fake_exception_record.ExceptionCode = FAKE_EXCEPTION_CODE;
        fake_exception_pointers.ExceptionRecord = &fake_exception_record;
        generic_exception_filter(FAKE_EXCEPTION_CODE, &fake_exception_pointers);
        result = EXCEPTION_EXECUTE_HANDLER;
    }
    else
    {
        result = generic_exception_filter(exception_code, exception_pointers);
    }

    return result;
};

bool c_cseries_engine_assert_interface::thread_manager_handle_assertion_via_exception(void)
{
    mangled_ppc("?thread_manager_handle_assertion_via_exception@c_cseries_engine_assert_interface@@EAA_NXZ");

    return !is_main_thread();
};

void c_cseries_engine_assert_interface::thread_manager_post_assertion(char const * expression, char const * file, long line)
{
    mangled_ppc("?thread_manager_post_assertion@c_cseries_engine_assert_interface@@EAAXPBD0J@Z");

    s_thread_assert_arguments arguments;
    memset(&arguments, 0, sizeof(arguments));
    arguments.information = reinterpret_cast<unsigned long>(expression);
    arguments.file = reinterpret_cast<unsigned long>(file);
    arguments.line = line;
    arguments.fatal = true;
    post_thread_assert_arguments(&arguments);
};

void c_cseries_engine_assert_interface::call_fatal_error_callbacks(void)
{
    mangled_ppc("?call_fatal_error_callbacks@c_cseries_engine_assert_interface@@EAAXXZ");

    ::call_fatal_error_callbacks();
};

void c_cseries_engine_assert_interface::generate_stack_walk(char const * assert_string)
{
    mangled_ppc("?generate_stack_walk@c_cseries_engine_assert_interface@@EAAXPBD@Z");

    long const levels_to_ignore = 3;
    stack_walk(levels_to_ignore);
    main_write_stack_to_crash_info_status_file(assert_string, NULL);
};

void c_cseries_engine_assert_interface::raise_exception_unhandled(char const * expression, char const * file, long line)
{
    mangled_ppc("?raise_exception_unhandled@c_cseries_engine_assert_interface@@EAAXPBD0J@Z");

    if (g_managed_dll)
    {
        raise_managed_dll_exception_immediate(expression, file, line, _crash_type_assert);
    }
    else
    {
        raise_unmanaged_exception_immediate(expression, file, line);
    }
};

void raise_managed_dll_exception_immediate(char const * expression, char const * file, long line, e_crash_type crash_type)
{
    mangled_ppc("?raise_managed_dll_exception_immediate@@YAXPBD0JW4e_crash_type@@@Z");

    dassert_tag_debug_untracked_jul_11_2011(412, false, "unreachable");
};

void raise_unmanaged_exception_immediate(char const * expression, char const * file, long line)
{
    mangled_ppc("?raise_unmanaged_exception_immediate@@YAXPBD0J@Z");

    *static_cast<char const **>(NULL) = "There once was a man from Bungie...... Nothing rhymes with Bungie.This is the worst possible way we can emulate a stupid !@#$%^& OS exception. And it's not our fault. And that makes it suck even more.I are sad.";
};

void c_cseries_engine_assert_interface::raise_exception_handled(char const * expression, char const * file, long line)
{
    mangled_ppc("?raise_exception_handled@c_cseries_engine_assert_interface@@EAAXPBD0J@Z");

    __try
    {
        raise_exception_unhandled(expression, file, line);
    }
    __except (assert_stack_walk_exception_filter(FAKE_EXCEPTION_CODE, GetExceptionInformation()))
    {
    }
};

unsigned long debug_memory_checksum_buffer(void const * data, unsigned int size)
{
    mangled_ppc("?debug_memory_checksum_buffer@@YAKPBXI@Z");

    unsigned long checksum = crc_new();
    checksum = crc_checksum_buffer(checksum, data, size);

    return checksum;
};

unsigned short debug_memory_local_random(void)
{
    mangled_ppc("?debug_memory_local_random@@YAGXZ");

    return _random(get_local_random_seed_address(), NULL, __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__, 1033);
};

void * c_cseries_base_allocation::allocate(unsigned int size, char const * file, long line, char const * type, char const * subtype, char const * name)
{
    mangled_ppc("?allocate@c_cseries_base_allocation@@UAAPAXIPBDJ000@Z");

    return base_malloc(size);
};

void c_cseries_base_allocation::deallocate(void * pointer, char const * file, long line)
{
    mangled_ppc("?deallocate@c_cseries_base_allocation@@UAAXPAXPBDJ@Z");

    base_free(pointer);
};
