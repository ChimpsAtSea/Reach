#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\foundation\\baselib\\errors\\events\\event_globals.cpp"
/* ---------- headers */

#include "foundation\baselib\errors\events\event_globals.h"
#include "baselib\event_constants.h"
#include "baselib\synchronized_value_windows.h"
#include "baselib\thread_manipulation.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_events.h"
#include "core\corelib\cseries\cseries_macros.h"
#include "core\corelib\cseries\cseries_string.h"
#include "core\corelib\config\version.h"
#include "core\corelib\cseries\events\event_handler.h"
#include "foundation\baselib\errors\events\event_buffer.h"
#include "foundation\baselib\errors\events\event_context.h"
#include "foundation\baselib\errors\events\event_log_interface.h"
#include "foundation\baselib\errors\events\event_manager.h"
#include "foundation\baselib\errors\output\output_globals.h"
#include "foundation\baselib\files\debug_paths.h"
#include "foundation\baselib\files\file_path.h"
#include "foundation\baselib\files\file_synchronous_utilities.h"
#include "foundation\baselib\files\file_synchronous_utilities_windows.h"
#include "foundation\baselib\files\simple_file.h"
#include "foundation\baselib\multithreading\datatypes\read_write_lock.h"
#include "foundation\baselib\multithreading\primitives\thread_local_storage.h"
#include "foundation\baselib\multithreading\synchronization\synchronization_manager.h"
#include "foundation\baselib\multithreading\threads\thread_manipulation_windows.h"
#include "foundation\baselib\system\system_time.h"


/* ---------- constants */

long const k_event_category_index_unknown = -1;

/* ---------- definitions */

struct s_event_globals
{
    bool initialized; // 0x0
    bool initializing; // 0x1
    bool disposed; // 0x2
    event_datamine_handler_t datamine_handler; // 0x4
    event_time_format_function_t time_format_function; // 0x8
    event_blocking_function_t blocking_begin_function; // 0xC
    event_blocking_function_t blocking_end_function; // 0x10
    event_guard_function_t guard_begin_function; // 0x14
    event_guard_function_t guard_end_function; // 0x18
    c_interlocked_int32 events_disabled; // 0x1C
    c_interlocked_int32 global_minimum_level; // 0x20
    c_read_write_lock manager_lock; // 0x24
    c_event_manager manager; // 0x34
    c_read_write_lock buffer_lock; // 0x83298
    c_event_buffer buffer; // 0x832A8
};

struct s_event_thread_globals
{
    bool generating_event; // 0x0
    bool holding_manager_write_lock; // 0x1
    long events_disabled_count; // 0x4
    long events_force_emergency_redirection_count; // 0x8
    c_event_thread_context thread_context; // 0xC
};
static_assert(sizeof(s_event_thread_globals) == 0x190, "s_event_thread_globals");

class c_category_output_dump_visitor :
    public c_event_category_visitor
{
public:
    virtual void visit_category(c_event_manager const * manager, e_event_category category_index, s_event_category const * category);
};

class c_category_category_set_level_visitor :
    public c_event_category_visitor
{
public:
    c_category_category_set_level_visitor(char const * category_name, char const * level_description);
    virtual void visit_category(c_event_manager const * manager, e_event_category category_index, s_event_category const * category);
    void print_summary(void);

private:
    char const * m_category_name; // 0x4
    s_static_string<256> m_level_description; // 0x8
    long m_categories_set; // 0x108
};

class c_event_handler_instance :
    public c_event_handler
{
public:
    c_event_handler_instance(void);
    ~c_event_handler_instance(void);

    virtual bool event_level_query(e_event_level level);
    virtual bool event_query(s_event_properties const * properties);
    virtual long event_process(s_event_properties const * properties, char const * format, char * arglist);
    virtual void store_category(long generated_category_index, long volatile * category_storage);
    virtual void context_push(char const * type, unsigned long flags, char const * description);
    virtual void context_pop(void);
};

/* ---------- prototypes */

e_event_log_index event_manager_log_creator_function(char const * log_name);
void events_set_category_level_by_name_internal(char const * category_name, e_event_level level, e_event_manager_category_set_level set_level, char const * level_description);
void event_cache_global_settings(c_event_manager const * manager);
e_event_category event_generate_internal(e_event_level level, e_event_category category_index, c_event_generation_flags flags, char const * format, char * arglist);
void event_dispatch_output(e_event_level level, s_static_string<2048> const * message, s_event_response const * response);
void event_dispatch_log(e_event_level level, s_static_string<2048> const * message, s_event_response const * response);
void event_dispatch_debug(e_event_level level, s_static_string<2048> const * message, s_event_response const * response);
void event_dispatch_datamine(e_event_level level, char const * format, char * arglist);
void event_dispatch_debugger_break(s_static_string<2048> const * message);
void event_dispatch_halt(s_static_string<2048> const * message);
void event_dispatch_listeners(e_event_level level, s_static_string<2048> const * message, s_event_response const * response);
void event_format_for_log(e_event_level level, s_static_string<2048> const * message, s_event_response const * response, s_static_string<2048> const * prefix, s_static_string<256> const * context, s_static_string<2048> * out_string);
void event_generate_handle_recursion(e_event_level level, e_event_category category, c_event_generation_flags flags, char const * format, char * arglist);
void event_build_lost_events_file_name_for_current_thread(s_static_string<256> * out_file_name);
bool events_copy_file_to_snapshot(c_file_path const * snapshot_directory, c_file_path const * source_file, c_file_path * out_destination_file);

/* ---------- globals */

char const * const k_primary_event_log_filename = "debug.txt";
char const * const k_primary_full_event_log_filename = "debug_full.txt";
char const * const k_error_snapshot_directory = "error_snapshot\\";
char const * const k_thrown_away_events_log_file_name_format_string_with_id = "debug_lost_%x.txt";
char const * const k_thrown_away_events_log_file_name_format_string_with_name = "debug_lost_%s.txt";
char const * const k_thrown_away_events_log_file_name_search_spec = "debug_lost_*.txt";
char const * k_event_level_severity_strings[k_event_level_count] =
{
    "verbose",
    "status ",
    "message",
    "WARNING",
    "-ERROR-",
    "-FATAL-"
};

static c_event_handler_instance g_event_handler;
static s_event_globals g_event_globals;
static __declspec(thread) s_event_thread_globals g_event_thread_globals;

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// private: static long const c_event_buffer::k_event_buffer_max_entries; // "?k_event_buffer_max_entries@c_event_buffer@@0JB"
// private: static long const c_event_buffer::k_event_buffer_size; // "?k_event_buffer_size@c_event_buffer@@0JB"
// public: static long const s_static_array<struct s_event_buffer_entry, 128>::k_element_count; // "?k_element_count@?$s_static_array@Us_event_buffer_entry@@$0IA@@@2JB"
// public: static long const s_static_array<char, 65536>::k_element_count; // "?k_element_count@?$s_static_array@D$0BAAAA@@@2JB"
// private: static long const c_event_thread_context::k_stack_maximum_depth; // "?k_stack_maximum_depth@c_event_thread_context@@0JB"
// public: static long const s_static_array<struct c_event_thread_context::s_stack_entry, 32>::k_element_count; // "?k_element_count@?$s_static_array@Us_stack_entry@c_event_thread_context@@$0CA@@@2JB"
// public: static long const s_static_array<class c_file_path, 32>::k_element_count; // "?k_element_count@?$s_static_array@Vc_file_path@@$0CA@@@2JB"
// char const *const k_primary_event_log_filename; // "?k_primary_event_log_filename@@3PBDB"
// char const *const k_primary_full_event_log_filename; // "?k_primary_full_event_log_filename@@3PBDB"
// char const *const k_error_snapshot_directory; // "?k_error_snapshot_directory@@3PBDB"
// char const *const k_thrown_away_events_log_file_name_format_string_with_id; // "?k_thrown_away_events_log_file_name_format_string_with_id@@3PBDB"
// char const *const k_thrown_away_events_log_file_name_format_string_with_name; // "?k_thrown_away_events_log_file_name_format_string_with_name@@3PBDB"
// char const *const k_thrown_away_events_log_file_name_search_spec; // "?k_thrown_away_events_log_file_name_search_spec@@3PBDB"
// char const **k_event_level_severity_strings; // "?k_event_level_severity_strings@@3PAPBDA"

// void events_initialize(long, struct s_event_category_default_configuration const *);
// void events_start_threads(class c_event_log_thread_interface *);
// void events_dispose(void);
// void events_dump_categories(char const *);
// public: c_category_output_dump_visitor::c_category_output_dump_visitor(void);
// public: c_event_category_visitor::c_event_category_visitor(void);
// void events_build_correct_category_name(char const *, char *, long);
// void events_set_output_level_global(enum e_event_level);
// void events_set_log_level_global(enum e_event_level);
// void events_set_debug_level_global(enum e_event_level);
// void events_set_datamine_level_global(enum e_event_level);
// void events_set_output_level_by_name(char const *, enum e_event_level);
// void events_set_log_level_by_name(char const *, enum e_event_level);
// void events_set_debug_level_by_name(char const *, enum e_event_level);
// void events_set_debugger_break_level_by_name(char const *, enum e_event_level);
// void events_set_halt_level_by_name(char const *, enum e_event_level);
// void events_set_datamine_level_by_name(char const *, enum e_event_level);
// void events_set_force_output_level_by_name(char const *, enum e_event_level);
// bool events_register_listener(class c_event_listener *);
// void events_unregister_listener(class c_event_listener *);
// ?events_attach_datamine_handler@@YAXQ6AXW4e_event_level@@PBD1PAD@Z@Z;
// ?events_detach_datamine_handler@@YAXQ6AXW4e_event_level@@PBD1PAD@Z@Z;
// ?events_attach_time_format_function@@YAXQ6AXJPAD@Z@Z;
// ?events_detach_time_format_function@@YAXQ6AXJPAD@Z@Z;
// ?events_attach_blocking_functions@@YAXQ6AXXZ0@Z;
// ?events_detach_blocking_functions@@YAXQ6AXXZ0@Z;
// ?events_attach_guard_functions@@YAXQ6AXXZ0@Z;
// ?events_detach_guard_functions@@YAXQ6AXXZ0@Z;
// void events_enable(bool);
// public: void c_event_manager::set_events_enabled(bool);
// void events_suppression_enable(bool);
// public: void c_event_manager::set_event_suppression_enabled(bool);
// void events_spam_suppression_enable(bool);
// public: void c_event_manager::set_spam_suppression_enabled(bool);
// void events_suppress_output(bool);
// public: void c_event_manager::set_output_suppression_enabled(bool);
// long events_get_recent(long, long, char *);
// void events_internal_error(char const *, ...);
// void events_disable_thread_push(void);
// void events_disable_thread_pop(void);
// bool events_disabled_thread(void);
// void events_blocking_begin(void);
// void events_blocking_end(void);
// class c_event_thread_context * events_thread_context_get(void);
// void events_clear(void);
// void events_flush(void);
// void events_snapshot(void);
// long events_build_snapshot_files(long, class c_file_path *);
// long events_get_spamming(long, char const **);
// bool events_get_output_suppressed(void);
// public: bool c_event_manager::get_output_suppression_enabled(void) const;
// bool events_get_current_desired_output(void);
// void events_get_synchronization_objects(struct s_event_synchronization_objects *);
// void events_set_subfolder(char const *);
// bool events_get_subfolder(long, char *);
// bool events_build_report_file_path(char const *, enum e_report_file_location, class c_file_path *);
// void events_force_emergency_redirection_thread_push(void);
// void events_force_emergency_redirection_thread_pop(void);
// bool events_should_use_emergency_redirection_for_thread(void);
// public: c_event_manager_read_lock::c_event_manager_read_lock(void);
// public: c_event_manager_read_lock::~c_event_manager_read_lock(void);
// public: class c_event_manager const * c_event_manager_read_lock::manager(void);
// public: c_event_manager_write_lock::c_event_manager_write_lock(void);
// public: c_event_manager_write_lock::~c_event_manager_write_lock(void);
// public: class c_event_manager * c_event_manager_write_lock::manager(void);
// public: c_event_buffer_read_lock::c_event_buffer_read_lock(void);
// public: c_event_buffer_read_lock::~c_event_buffer_read_lock(void);
// public: class c_event_buffer const * c_event_buffer_read_lock::buffer(void);
// public: c_event_buffer_write_lock::c_event_buffer_write_lock(void);
// public: c_event_buffer_write_lock::~c_event_buffer_write_lock(void);
// public: class c_event_buffer * c_event_buffer_write_lock::buffer(void);
// public: virtual void c_category_output_dump_visitor::visit_category(class c_event_manager const *, enum e_event_category, struct s_event_category const *);
// public: c_category_category_set_level_visitor::c_category_category_set_level_visitor(char const *, char const *);
// public: virtual void c_category_category_set_level_visitor::visit_category(class c_event_manager const *, enum e_event_category, struct s_event_category const *);
// public: void c_category_category_set_level_visitor::print_summary(void);
// public: c_event_handler_instance::c_event_handler_instance(void);
// public: c_event_handler::c_event_handler(void);
// public: c_event_handler_instance::~c_event_handler_instance(void);
// public: virtual bool c_event_handler_instance::event_level_query(enum e_event_level);
// public: virtual bool c_event_handler_instance::event_query(struct s_event_properties const *);
// public: virtual long c_event_handler_instance::event_process(struct s_event_properties const *, char const *, char *);
// public: virtual void c_event_handler_instance::store_category(long, long volatile *);
// public: virtual void c_event_handler_instance::context_push(char const *, unsigned long, char const *);
// public: virtual void c_event_handler_instance::context_pop(void);
// bool events_try_to_initialize(void);
// public: bool c_event_manager::get_log_trimming_enabled(void) const;
// public: void c_event_manager::set_log_trimming_enabled(bool);
// public: void c_event_manager::set_logs_enabled(bool);
// enum e_event_log_index event_manager_log_creator_function(char const *);
// void events_set_category_level_by_name_internal(char const *, enum e_event_level, enum e_event_manager_category_set_level, char const *);
// enum e_event_category event_generate_internal(enum e_event_level, enum e_event_category, class c_flags_zero_init<enum e_event_generation_flags, unsigned long, 1>, char const *, char *);
// void event_dispatch_output(enum e_event_level, class s_static_string<2048> const *, struct s_event_response const *);
// void event_dispatch_log(enum e_event_level, class s_static_string<2048> const *, struct s_event_response const *);
// void event_dispatch_debug(enum e_event_level, class s_static_string<2048> const *, struct s_event_response const *);
// void event_dispatch_datamine(enum e_event_level, char const *, char *);
// void event_dispatch_debugger_break(class s_static_string<2048> const *);
// void event_dispatch_halt(class s_static_string<2048> const *);
// void event_dispatch_listeners(enum e_event_level, class s_static_string<2048> const *, struct s_event_response const *);
// void event_generate_handle_recursion(enum e_event_level, enum e_event_category, class c_flags_zero_init<enum e_event_generation_flags, unsigned long, 1>, char const *, char *);
// void event_cache_global_settings(class c_event_manager const *);
// void event_format_for_log(enum e_event_level, class s_static_string<2048> const *, struct s_event_response const *, class s_static_string<2048> const *, class s_static_string<256> const *, class s_static_string<2048> *);
// bool events_copy_file_to_snapshot(class c_file_path const *, class c_file_path const *, class c_file_path *);
// void event_build_lost_events_file_name_for_current_thread(class s_static_string<256> *);
// public: void s_static_array<enum e_event_log_index, 5>::set_all(enum e_event_log_index const &);
// public: static long s_static_array<class c_event_listener *, 8>::get_count(void);
// public: c_flags_zero_init<enum e_event_generation_flags, unsigned long, 1>::c_flags_zero_init<enum e_event_generation_flags, unsigned long, 1>(void);
// public: bool c_static_stack<class c_file_path, 66>::full(void) const;
// public: long c_static_stack<class c_file_path, 66>::count(void) const;
// public: static unsigned int c_static_stack<class c_file_path, 66>::element_size(void);
// public: long c_static_stack<class c_file_path, 66>::push(void);
// public: class c_file_path * c_static_stack<class c_file_path, 66>::get_elements(void);
// public: class c_file_path * c_static_stack<class c_file_path, 66>::get_next(void);
// public: c_static_stack<class c_file_path, 66>::c_static_stack<class c_file_path, 66>(void);
// public: class c_file_path * s_static_array<class c_file_path, 32>::get_elements(void);
// public: static long s_static_array<class c_file_path, 32>::get_count(void);
// public: long c_static_stack<enum e_event_log_index, 6>::count(void) const;
// public: void c_static_stack<enum e_event_log_index, 6>::push_back(enum e_event_log_index const &);
// public: enum e_event_log_index * c_static_stack<enum e_event_log_index, 6>::get_elements(void);
// public: c_static_stack<enum e_event_log_index, 6>::c_static_stack<enum e_event_log_index, 6>(void);
// public: bool c_static_stack<class c_file_path, 66>::valid(void) const;
// public: long c_static_stack<class c_file_path, 66>::next(void) const;
// public: long c_static_stack<enum e_event_log_index, 6>::push(void);
// public: enum e_event_log_index * c_static_stack<enum e_event_log_index, 6>::get(long);
// public: bool c_static_stack<enum e_event_log_index, 6>::valid(long) const;
// public: bool c_static_stack<enum e_event_log_index, 6>::full(void) const;
// public: bool c_static_stack<enum e_event_log_index, 6>::valid(void) const;
// public: void s_static_string<2048>::clear(void);
// public: char const * s_static_string<2048>::append(char const *);
// public: char const * s_static_string<2048>::print(char const *, ...);
// public: void s_static_string<2048>::print_va(char const *, char *);
// public: char const * s_static_string<2048>::operator char const *(void) const;
// public: bool s_flags<enum e_event_response_flags, unsigned long, 8>::test(enum e_event_response_flags) const;
// public: bool s_flags<enum e_event_response_flags, unsigned long, 8>::is_empty(void) const;
// public: void s_flags<enum e_event_generation_flags, unsigned long, 1>::clear(void);
// public: void s_flags<enum e_event_generation_flags, unsigned long, 1>::set_unsafe(unsigned long);
// public: class c_file_path & s_static_array<class c_file_path, 32>::operator[]<long>(long);
// public: void s_flags<enum e_find_files_flags, unsigned long, 3>::clear(void);
// public: struct s_critical_section & s_static_array<struct s_critical_section, 2>::operator[]<int>(int);
// public: struct s_semaphore & s_static_array<struct s_semaphore, 2>::operator[]<int>(int);
// public: void s_flags<enum e_event_log_flags, unsigned long, 5>::clear(void);
// public: void s_flags<enum e_event_log_flags, unsigned long, 5>::set(enum e_event_log_flags, bool);
// public: enum e_event_log_index const & s_static_array<enum e_event_log_index, 5>::operator[]<enum e_event_manager_tracked_log>(enum e_event_manager_tracked_log) const;
// public: class c_event_listener *const & s_static_array<class c_event_listener *, 8>::operator[]<long>(long) const;
// public: char * c_file_path::get_filename<256>(class s_static_string<256> *) const;
// public: char * c_file_path::get_filename(char *, long) const;
// public: static bool s_flags<enum e_event_response_flags, unsigned long, 8>::valid_bit(enum e_event_response_flags);
// private: static unsigned long s_flags<enum e_event_response_flags, unsigned long, 8>::flag_size_type(enum e_event_response_flags);
// private: static unsigned long s_flags<enum e_event_response_flags, unsigned long, 8>::make_mask_with_all_valid_bits_on_size_type(void);
// public: bool s_flags<enum e_event_generation_flags, unsigned long, 1>::valid(void) const;
// public: static bool s_static_array<class c_file_path, 32>::valid<long>(long);
// public: static bool s_static_array<struct s_critical_section, 2>::valid<int>(int);
// public: static bool s_static_array<struct s_semaphore, 2>::valid<int>(int);
// public: static bool s_flags<enum e_event_log_flags, unsigned long, 5>::valid_bit(enum e_event_log_flags);
// public: bool s_flags<enum e_event_log_flags, unsigned long, 5>::valid(void) const;
// private: static unsigned long s_flags<enum e_event_log_flags, unsigned long, 5>::flag_size_type(enum e_event_log_flags);
// public: static bool s_static_array<enum e_event_log_index, 5>::valid<enum e_event_manager_tracked_log>(enum e_event_manager_tracked_log);
// public: static bool s_static_array<class c_event_listener *, 8>::valid<long>(long);
// private: static unsigned long s_flags<enum e_event_response_flags, unsigned long, 8>::make_N_bit_mask_size_type(enum e_event_response_flags);
// private: static unsigned long s_flags<enum e_event_generation_flags, unsigned long, 1>::make_mask_with_all_valid_bits_on_size_type(void);
// private: static unsigned long s_flags<enum e_event_log_flags, unsigned long, 5>::make_mask_with_all_valid_bits_on_size_type(void);
// private: static unsigned long s_flags<enum e_event_generation_flags, unsigned long, 1>::make_N_bit_mask_size_type(enum e_event_generation_flags);
// private: static unsigned long s_flags<enum e_event_log_flags, unsigned long, 5>::make_N_bit_mask_size_type(enum e_event_log_flags);
// public: s_event_globals::s_event_globals(void);
// public: c_event_manager::c_event_manager(void);
// public: c_static_stack<struct s_event_category, 1024>::c_static_stack<struct s_event_category, 1024>(void);
// public: s_event_globals::~s_event_globals(void);
// void g_event_handler::`dynamic atexit destructor'(void);
// void g_event_globals::`dynamic atexit destructor'(void);

void events_initialize(long default_category_count, s_event_category_default_configuration const * default_categories)
{
    mangled_ppc("?events_initialize@@YAXJPBUs_event_category_default_configuration@@@Z");

    g_event_globals.disposed = false;
    events_try_to_initialize();
    assert_tag_debug_untracked_jul_11_2011(259, g_event_globals.initialized);

    {
        c_event_manager_write_lock lock;
        lock.manager()->set_default_categories(default_category_count, default_categories);
        event_cache_global_settings(lock.manager());
    }

    event(_event_message, "lifecycle: events initalize");
};

void events_start_threads(c_event_log_thread_interface * thread_interface)
{
    mangled_ppc("?events_start_threads@@YAXPAVc_event_log_thread_interface@@@Z");

    event(_event_message, "lifecycle: events start threads");

    if (thread_interface)
    {
        event_logs_set_thread_interface(thread_interface);
    }
};

void events_dispose(void)
{
    mangled_ppc("?events_dispose@@YAXXZ");

    if (g_event_globals.initialized)
    {
        event_logs_dispose();
        g_event_globals.manager.dispose();
        g_event_globals.initializing = false;
        g_event_globals.initialized = false;
        g_event_globals.disposed = true;
    }
};

void events_dump_categories(char const * category_name)
{
    mangled_ppc("?events_dump_categories@@YAXPBD@Z");

    c_event_manager_read_lock lock;
    c_event_manager const * event_manager = lock.manager();
    e_event_category category = event_manager->find_category_from_name(category_name);
    if (category != _event_category_none)
    {
        c_category_output_dump_visitor visitor;
        output_message("dumping categories under '%s':", category_name);
        event_manager->visit_categories_recursive(category, &visitor);
    }
    else
    {
        output_message("category '%s' not found", category_name);
    }
};



void events_build_correct_category_name(char const * category_name, char * out_category_name, long out_category_name_length)
{
    mangled_ppc("?events_build_correct_category_name@@YAXPBDPADJ@Z");

    c_event_manager::build_correct_category_name(category_name, out_category_name, out_category_name_length);
};

void events_set_output_level_global(e_event_level level)
{
    mangled_ppc("?events_set_output_level_global@@YAXW4e_event_level@@@Z");

    if (VALID_INDEX(level, k_event_level_count))
    {
        c_event_manager_write_lock lock;
        lock.manager()->set_output_level(level);
        event_cache_global_settings(lock.manager());
        output_message("events output level set to %s", k_event_level_names[level]);
    }
    else
    {
        output_error("unknown events output level (%d)", level);
    }
};

void events_set_log_level_global(e_event_level level)
{
    mangled_ppc("?events_set_log_level_global@@YAXW4e_event_level@@@Z");

    if (VALID_INDEX(level, k_event_level_count))
    {
        c_event_manager_write_lock lock;
        lock.manager()->set_log_level(level);
        event_cache_global_settings(lock.manager());
        output_message("events log level set to %s", k_event_level_names[level]);
    }
    else
    {
        output_error("unknown events log level (%d)", level);
    }
};

void events_set_debug_level_global(e_event_level level)
{
    mangled_ppc("?events_set_debug_level_global@@YAXW4e_event_level@@@Z");

    if (VALID_INDEX(level, k_event_level_count))
    {
        c_event_manager_write_lock lock;
        lock.manager()->set_debug_level(level);
        event_cache_global_settings(lock.manager());
        output_message("events debug channel level set to %s", k_event_level_names[level]);
    }
    else
    {
        output_error("unknown events debug channel level (%d)", level);
    }
};

void events_set_datamine_level_global(e_event_level level)
{
    mangled_ppc("?events_set_datamine_level_global@@YAXW4e_event_level@@@Z");

    if (VALID_INDEX(level, k_event_level_count))
    {
        c_event_manager_write_lock lock;
        lock.manager()->set_datamine_level(level);
        event_cache_global_settings(lock.manager());
        output_message("events datamine level set to %s", k_event_level_names[level]);
    }
    else
    {
        output_error("unknown events datamine level (%d)", level);
    }
};

void events_set_output_level_by_name(char const * category_name, e_event_level level)
{
    mangled_ppc("?events_set_output_level_by_name@@YAXPBDW4e_event_level@@@Z");

    events_set_category_level_by_name_internal(category_name, level, _event_manager_category_set_output_level, "output level");
};

void events_set_log_level_by_name(char const * category_name, e_event_level level)
{
    mangled_ppc("?events_set_log_level_by_name@@YAXPBDW4e_event_level@@@Z");

    events_set_category_level_by_name_internal(category_name, level, _event_manager_category_set_log_level, "log level");
};

void events_set_debug_level_by_name(char const * category_name, e_event_level level)
{
    mangled_ppc("?events_set_debug_level_by_name@@YAXPBDW4e_event_level@@@Z");

    events_set_category_level_by_name_internal(category_name, level, _event_manager_category_set_debug_level, "debug level");
};

void events_set_debugger_break_level_by_name(char const * category_name, e_event_level level)
{
    mangled_ppc("?events_set_debugger_break_level_by_name@@YAXPBDW4e_event_level@@@Z");

    events_set_category_level_by_name_internal(category_name, level, _event_manager_category_set_debugger_break_level, "debugger-break level");
};

void events_set_halt_level_by_name(char const * category_name, e_event_level level)
{
    mangled_ppc("?events_set_halt_level_by_name@@YAXPBDW4e_event_level@@@Z");

    events_set_category_level_by_name_internal(category_name, level, _event_manager_category_set_halt_level, "halt level");
};

void events_set_datamine_level_by_name(char const * category_name, e_event_level level)
{
    mangled_ppc("?events_set_datamine_level_by_name@@YAXPBDW4e_event_level@@@Z");

    events_set_category_level_by_name_internal(category_name, level, _event_manager_category_set_datamine_level, "datamine level");
};

void events_set_force_output_level_by_name(char const * category_name, e_event_level level)
{
    mangled_ppc("?events_set_force_output_level_by_name@@YAXPBDW4e_event_level@@@Z");

    events_set_category_level_by_name_internal(category_name, level, _event_manager_category_set_force_output_level, "force-output level");
};

bool events_register_listener(c_event_listener * event_listener)
{
    mangled_ppc("?events_register_listener@@YA_NPAVc_event_listener@@@Z");

    bool result = false;
    assert_tag_debug_untracked_jul_11_2011(452, event_listener);

    if (g_event_globals.initialized)
    {
        c_event_manager_write_lock lock;
        result = lock.manager()->register_listener(event_listener);
    }

    return result;
};

void events_unregister_listener(c_event_listener * listener)
{
    mangled_ppc("?events_unregister_listener@@YAXPAVc_event_listener@@@Z");

    assert_tag_debug_untracked_jul_11_2011(467, listener);

    if (g_event_globals.initialized)
    {
        c_event_manager_write_lock lock;
        lock.manager()->unregister_listener(listener);
    }
};

void events_attach_datamine_handler(event_datamine_handler_t const datamine_handler)
{
    mangled_ppc("?events_attach_datamine_handler@@YAXQ6AXW4e_event_level@@PBD1PAD@Z@Z");

    assert_tag_debug_untracked_jul_11_2011(480, g_event_globals.initialized);
    assert_tag_debug_untracked_jul_11_2011(481, g_event_globals.datamine_handler==NULL);

    g_event_globals.datamine_handler = datamine_handler;
};

void events_detach_datamine_handler(event_datamine_handler_t const datamine_handler)
{
    mangled_ppc("?events_detach_datamine_handler@@YAXQ6AXW4e_event_level@@PBD1PAD@Z@Z");

    if (g_event_globals.initialized && g_event_globals.datamine_handler == datamine_handler)
    {
        g_event_globals.datamine_handler = NULL;
    }
};

void events_attach_time_format_function(event_time_format_function_t const time_format_function)
{
    mangled_ppc("?events_attach_time_format_function@@YAXQ6AXJPAD@Z@Z");

    assert_tag_debug_untracked_jul_11_2011(498, g_event_globals.initialized);
    assert_tag_debug_untracked_jul_11_2011(499, g_event_globals.time_format_function==NULL);

    g_event_globals.time_format_function = time_format_function;
};

void events_detach_time_format_function(event_time_format_function_t const time_format_function)
{
    mangled_ppc("?events_detach_time_format_function@@YAXQ6AXJPAD@Z@Z");

    if (g_event_globals.initialized && g_event_globals.time_format_function == time_format_function)
    {
        g_event_globals.time_format_function = NULL;
    }
};

void events_attach_blocking_functions(event_blocking_function_t const blocking_begin_function, event_blocking_function_t const blocking_end_function)
{
    mangled_ppc("?events_attach_blocking_functions@@YAXQ6AXXZ0@Z");

    assert_tag_debug_untracked_jul_11_2011(517, g_event_globals.initialized);
    assert_tag_debug_untracked_jul_11_2011(518, g_event_globals.blocking_begin_function==NULL);
    assert_tag_debug_untracked_jul_11_2011(519, g_event_globals.blocking_end_function==NULL);

    g_event_globals.blocking_begin_function = blocking_begin_function;
    g_event_globals.blocking_end_function = blocking_end_function;
};

void events_detach_blocking_functions(event_blocking_function_t const blocking_begin_function, event_blocking_function_t const blocking_end_function)
{
    mangled_ppc("?events_detach_blocking_functions@@YAXQ6AXXZ0@Z");

    if (g_event_globals.initialized && g_event_globals.blocking_begin_function == blocking_begin_function && g_event_globals.blocking_end_function == blocking_end_function)
    {
        g_event_globals.blocking_begin_function = NULL;
        g_event_globals.blocking_end_function = NULL;
    }
};

void events_attach_guard_functions(event_guard_function_t const guard_begin_function, event_guard_function_t const guard_end_function)
{
    mangled_ppc("?events_attach_guard_functions@@YAXQ6AXXZ0@Z");

    assert_tag_debug_untracked_jul_11_2011(541, g_event_globals.initialized);
    assert_tag_debug_untracked_jul_11_2011(542, g_event_globals.guard_begin_function==NULL);
    assert_tag_debug_untracked_jul_11_2011(543, g_event_globals.guard_end_function==NULL);

    g_event_globals.guard_begin_function = guard_begin_function;
    g_event_globals.guard_end_function = guard_end_function;
};

void events_detach_guard_functions(event_guard_function_t const guard_begin_function, event_guard_function_t const guard_end_function)
{
    mangled_ppc("?events_detach_guard_functions@@YAXQ6AXXZ0@Z");

    if (g_event_globals.initialized && g_event_globals.guard_begin_function == guard_begin_function && g_event_globals.guard_end_function == guard_end_function)
    {
        g_event_globals.guard_begin_function = NULL;
        g_event_globals.guard_end_function = NULL;
    }
};

void events_enable(bool enable)
{
    mangled_ppc("?events_enable@@YAX_N@Z");

    c_event_manager_write_lock lock;
    lock.manager()->set_events_enabled(enable);
    g_event_globals.events_disabled.set(!enable);
    output_message("events now %s", enable ? "enabled" : "disabled");
};


void events_suppression_enable(bool enable)
{
    mangled_ppc("?events_suppression_enable@@YAX_N@Z");

    c_event_manager_write_lock lock;
    lock.manager()->set_event_suppression_enabled(enable);
    output_message("event suppression now %s", enable ? "enabled" : "disabled");
};


void events_spam_suppression_enable(bool enable)
{
    mangled_ppc("?events_spam_suppression_enable@@YAX_N@Z");

    c_event_manager_write_lock lock;
    lock.manager()->set_spam_suppression_enabled(enable);
    output_message("event spam-suppression now %s", enable ? "enabled" : "disabled");
};


void events_suppress_output(bool suppress)
{
    mangled_ppc("?events_suppress_output@@YAX_N@Z");

    c_event_manager_write_lock lock;
    lock.manager()->set_output_suppression_enabled(suppress);
    output_message("event output now %s", suppress ? "suppressed" : "enabled");
};


long events_get_recent(long maximum_event_count, long string_length, char * out_string)
{
    mangled_ppc("?events_get_recent@@YAJJJPAD@Z");

    c_event_buffer_read_lock lock;
    s_event_buffer_entry const * events = NULL;
    long events_count = lock.buffer()->get_event_history(&events);
    long separator_length = strlen_debug("\r\n");
    long size_used = 0;
    long events_copied = 0;
    long event_index;

    assert_tag_debug_untracked_jul_11_2011(612, out_string);
    assert_tag_debug_untracked_jul_11_2011(613, string_length>0);

    for (event_index = events_count - 1; event_index >= 0; event_index--)
    {
        size_used += events[event_index].text_size - 1 + separator_length;
        if (size_used >= string_length)
        {
            break;
        }
        else if (maximum_event_count > 0 && events_count - event_index > maximum_event_count)
        {
            break;
        }
    }
    event_index++;

    csstrnzcpy(out_string, "", string_length);
    size_used = 0;
    for (; event_index < events_count; event_index++)
    {
        csstrnzcpy(out_string + size_used, events[event_index].string, string_length - size_used);
        size_used += events[event_index].text_size - 1;
        assert_tag_debug_untracked_jul_11_2011(641, size_used<string_length);
        csstrnzcpy(out_string + size_used, "\r\n", string_length - size_used);
        size_used += separator_length;
        assert_tag_debug_untracked_jul_11_2011(645, size_used<string_length);
        events_copied++;
    }

    return events_copied;
};

void events_internal_error(char const * format, ...)
{
    mangled_ppc("?events_internal_error@@YAXPBDZZ");

    if (events_try_to_initialize() && g_event_globals.events_disabled.peek() == 0 && !events_disabled_thread())
    {
        e_event_level const level = _event_error;
        va_list args;
        e_event_category const category = _event_category_none;
        c_event_generation_flags generation_flags;
        generation_flags.clear();

        va_start(args, format);
        event_generate_handle_recursion(level, category, generation_flags, format, args);
        va_end(args);
    }
};

void events_disable_thread_push(void)
{
    mangled_ppc("?events_disable_thread_push@@YAXXZ");

    TLS_DATA_GET_VALUE_REFERENCE(g_event_thread_globals).events_disabled_count++;
};

void events_disable_thread_pop(void)
{
    mangled_ppc("?events_disable_thread_pop@@YAXXZ");

    assert_tag_debug_untracked_jul_11_2011(687, TLS_DATA_GET_VALUE_REFERENCE(g_event_thread_globals).events_disabled_count>0);

    if (TLS_DATA_GET_VALUE_REFERENCE(g_event_thread_globals).events_disabled_count > 0)
    {
        TLS_DATA_GET_VALUE_REFERENCE(g_event_thread_globals).events_disabled_count--;
    }
};

bool events_disabled_thread(void)
{
    mangled_ppc("?events_disabled_thread@@YA_NXZ");

    return TLS_DATA_GET_VALUE_REFERENCE(g_event_thread_globals).events_disabled_count > 0;
};

void events_blocking_begin(void)
{
    mangled_ppc("?events_blocking_begin@@YAXXZ");

    if (g_event_globals.blocking_begin_function)
    {
        g_event_globals.blocking_begin_function();
    }
};

void events_blocking_end(void)
{
    mangled_ppc("?events_blocking_end@@YAXXZ");

    if (g_event_globals.blocking_end_function)
    {
        g_event_globals.blocking_end_function();
    }
};

c_event_thread_context * events_thread_context_get(void)
{
    mangled_ppc("?events_thread_context_get@@YAPAVc_event_thread_context@@XZ");

    return &TLS_DATA_GET_VALUE_REFERENCE(g_event_thread_globals).thread_context;
};

void events_clear(void)
{
    mangled_ppc("?events_clear@@YAXXZ");

    event_logs_flush();

    c_event_buffer_write_lock lock;
    lock.buffer()->reset();
};

void events_flush(void)
{
    mangled_ppc("?events_flush@@YAXXZ");

    event_logs_flush();
};

void events_snapshot(void)
{
    mangled_ppc("?events_snapshot@@YAXXZ");

    events_build_snapshot_files(0, NULL);
};

long events_build_snapshot_files(long maximum_file_count, c_file_path * out_file_list)
{
    mangled_ppc("?events_build_snapshot_files@@YAJJPAVc_file_path@@@Z");

    long const k_max_additional_files = 2;
    long const k_max_event_logs = 32;
    long const k_max_copied_files = 66;
    c_static_stack<c_file_path, k_max_copied_files> copied_files;
    c_debug_path debug_location;
    c_file_path snapshot_directory;
    s_find_files_data find_files_state;
    s_flags<e_find_files_flags, unsigned long, k_find_files_flags_count> find_file_flags;
    c_file_path current_file;
    c_file_path lost_files_directory;
    long log_index;
    s_static_array<c_file_path, k_max_event_logs> log_file_list;
    long log_count;

    assert_tag_debug_untracked_jul_11_2011(766, (maximum_file_count==0 && out_file_list==NULL) || (maximum_file_count>=k_max_copied_files && out_file_list!=NULL));

    debug_location.get_directory_path(k_error_snapshot_directory, &snapshot_directory);
    directory_create_and_delete_contents(&snapshot_directory);

    log_count = event_logs_build_snapshot_files(log_file_list.get_count(), log_file_list.get_elements());
    for (log_index = 0; log_index < log_count; log_index++)
    {
        if (copied_files.full())
        {
            break;
        }

        if (events_copy_file_to_snapshot(&snapshot_directory, &log_file_list[log_index], copied_files.get_next()))
        {
            copied_files.push();
        }
    }

    find_file_flags.clear();
    debug_location.get_directory_path("", &lost_files_directory);
    find_files_start(find_file_flags, &lost_files_directory, k_thrown_away_events_log_file_name_search_spec, &find_files_state);
    while (!copied_files.full() && find_files_next(&find_files_state, &current_file, NULL))
    {
        if (events_copy_file_to_snapshot(&snapshot_directory, &current_file, copied_files.get_next()))
        {
            copied_files.push();
        }
    }
    find_files_end(&find_files_state);

    if (maximum_file_count > 0)
    {
        long file_count = 0;
        char unused_buffer[64]; // $TODO unknown 0x40 bytes of stack in the target
        file_count = int_min(maximum_file_count, copied_files.count());
        assert_tag_debug_untracked_jul_11_2011(828, out_file_list);
        csmemcpy(out_file_list, copied_files.get_elements(), file_count * copied_files.element_size());
    }

    return copied_files.count();
};

long events_get_spamming(long line_count, char const ** out_lines)
{
    mangled_ppc("?events_get_spamming@@YAJJPAPBD@Z");

    c_event_manager_read_lock lock;
    long result = lock.manager()->update_spam_lines(line_count, out_lines);

    return result;
};

bool events_get_output_suppressed(void)
{
    mangled_ppc("?events_get_output_suppressed@@YA_NXZ");

    bool result = false;
    c_event_manager_read_lock lock;
    result = lock.manager()->get_output_suppression_enabled();
    return result;
};

bool events_get_current_desired_output(void)
{
    mangled_ppc("?events_get_current_desired_output@@YA_NXZ");

    bool result = false;
    c_event_manager_read_lock lock;
    result = lock.manager()->get_current_desired_output();
    return result;
};

void events_get_synchronization_objects(s_event_synchronization_objects * out_objects)
{
    mangled_ppc("?events_get_synchronization_objects@@YAXPAUs_event_synchronization_objects@@@Z");

    assert_tag_debug_untracked_jul_11_2011(873, g_event_globals.initialized);
    assert_tag_debug_untracked_jul_11_2011(874, out_objects);

    g_event_globals.manager_lock.get_synchronization_objects(&out_objects->critical_sections[0], &out_objects->semaphores[0]);
    g_event_globals.buffer_lock.get_synchronization_objects(&out_objects->critical_sections[1], &out_objects->semaphores[1]);
    event_logs_get_synchronization_objects(&out_objects->event_log_critical_section);
};

void events_set_subfolder(char const * subfolder)
{
    mangled_ppc("?events_set_subfolder@@YAXPBD@Z");

    event_logs_set_subfolder(subfolder);
};

bool events_get_subfolder(long subfolder_length, char * out_subfolder)
{
    mangled_ppc("?events_get_subfolder@@YA_NJPAD@Z");

    return event_logs_get_subfolder(subfolder_length, out_subfolder);
};

bool events_build_report_file_path(char const * filename, e_report_file_location location, c_file_path * out_file_path)
{
    mangled_ppc("?events_build_report_file_path@@YA_NPBDW4e_report_file_location@@PAVc_file_path@@@Z");

    return event_logs_build_report_file_path(filename, location, out_file_path);
};

void events_force_emergency_redirection_thread_push(void)
{
    mangled_ppc("?events_force_emergency_redirection_thread_push@@YAXXZ");

    TLS_DATA_GET_VALUE_REFERENCE(g_event_thread_globals).events_force_emergency_redirection_count++;
};

void events_force_emergency_redirection_thread_pop(void)
{
    mangled_ppc("?events_force_emergency_redirection_thread_pop@@YAXXZ");

    assert_tag_debug_untracked_jul_11_2011(915, TLS_DATA_GET_VALUE_REFERENCE(g_event_thread_globals).events_force_emergency_redirection_count>0);

    if (TLS_DATA_GET_VALUE_REFERENCE(g_event_thread_globals).events_force_emergency_redirection_count > 0)
    {
        TLS_DATA_GET_VALUE_REFERENCE(g_event_thread_globals).events_force_emergency_redirection_count--;
    }
};

bool events_should_use_emergency_redirection_for_thread(void)
{
    mangled_ppc("?events_should_use_emergency_redirection_for_thread@@YA_NXZ");

    bool generating_event = TLS_DATA_GET_VALUE_REFERENCE(g_event_thread_globals).generating_event;
    bool forced = TLS_DATA_GET_VALUE_REFERENCE(g_event_thread_globals).events_force_emergency_redirection_count > 0;
    return generating_event || forced;
};

c_event_manager_read_lock::c_event_manager_read_lock(void)
{
    mangled_ppc("??0c_event_manager_read_lock@@QAA@XZ");

    m_locked = false;
    assert_tag_debug_untracked_jul_11_2011(936, g_event_globals.initialized);

    if (g_event_globals.manager_lock.ready_for_use())
    {
        if (TLS_DATA_GET_VALUE_REFERENCE(g_event_thread_globals).holding_manager_write_lock)
        {
            // this thread already holds the write lock
        }
        else
        {
            events_blocking_begin();
            g_event_globals.manager_lock.read_lock();
            events_blocking_end();
            m_locked = true;
        }
    }
};

c_event_manager_read_lock::~c_event_manager_read_lock(void)
{
    mangled_ppc("??1c_event_manager_read_lock@@QAA@XZ");

    if (m_locked)
    {
        g_event_globals.manager_lock.read_unlock();
    }
};

c_event_manager const * c_event_manager_read_lock::manager(void)
{
    mangled_ppc("?manager@c_event_manager_read_lock@@QAAPBVc_event_manager@@XZ");

    return &g_event_globals.manager;
};

c_event_manager_write_lock::c_event_manager_write_lock(void)
{
    mangled_ppc("??0c_event_manager_write_lock@@QAA@XZ");

    m_locked = false;
    assert_tag_debug_untracked_jul_11_2011(979, g_event_globals.initialized);

    events_force_emergency_redirection_thread_push();
    if (g_event_globals.manager_lock.ready_for_use())
    {
        events_blocking_begin();
        g_event_globals.manager_lock.write_lock();
        events_blocking_end();
        m_locked = true;

        assert_tag_debug_untracked_jul_11_2011(993, !TLS_DATA_GET_VALUE_REFERENCE(g_event_thread_globals).holding_manager_write_lock);
        TLS_DATA_GET_VALUE_REFERENCE(g_event_thread_globals).holding_manager_write_lock = true;
    }
};

c_event_manager_write_lock::~c_event_manager_write_lock(void)
{
    mangled_ppc("??1c_event_manager_write_lock@@QAA@XZ");

    if (m_locked)
    {
        g_event_globals.manager_lock.write_unlock();
        TLS_DATA_GET_VALUE_REFERENCE(g_event_thread_globals).holding_manager_write_lock = false;
    }
    events_force_emergency_redirection_thread_pop();
};

c_event_manager * c_event_manager_write_lock::manager(void)
{
    mangled_ppc("?manager@c_event_manager_write_lock@@QAAPAVc_event_manager@@XZ");

    return &g_event_globals.manager;
};

c_event_buffer_read_lock::c_event_buffer_read_lock(void)
{
    mangled_ppc("??0c_event_buffer_read_lock@@QAA@XZ");

    m_locked = false;
    assert_tag_debug_untracked_jul_11_2011(1027, g_event_globals.initialized);

    if (g_event_globals.buffer_lock.ready_for_use())
    {
        events_blocking_begin();
        g_event_globals.buffer_lock.read_lock();
        events_blocking_end();
        m_locked = true;
    }
};

c_event_buffer_read_lock::~c_event_buffer_read_lock(void)
{
    mangled_ppc("??1c_event_buffer_read_lock@@QAA@XZ");

    if (m_locked)
    {
        g_event_globals.buffer_lock.read_unlock();
    }
};

c_event_buffer const * c_event_buffer_read_lock::buffer(void)
{
    mangled_ppc("?buffer@c_event_buffer_read_lock@@QAAPBVc_event_buffer@@XZ");

    return &g_event_globals.buffer;
};

c_event_buffer_write_lock::c_event_buffer_write_lock(void)
{
    mangled_ppc("??0c_event_buffer_write_lock@@QAA@XZ");

    m_locked = false;
    assert_tag_debug_untracked_jul_11_2011(1062, g_event_globals.initialized);

    if (g_event_globals.buffer_lock.ready_for_use())
    {
        events_blocking_begin();
        g_event_globals.buffer_lock.write_lock();
        events_blocking_end();
        m_locked = true;
    }
};

c_event_buffer_write_lock::~c_event_buffer_write_lock(void)
{
    mangled_ppc("??1c_event_buffer_write_lock@@QAA@XZ");

    if (m_locked)
    {
        g_event_globals.buffer_lock.write_unlock();
    }
};

c_event_buffer * c_event_buffer_write_lock::buffer(void)
{
    mangled_ppc("?buffer@c_event_buffer_write_lock@@QAAPAVc_event_buffer@@XZ");

    return &g_event_globals.buffer;
};

void c_category_output_dump_visitor::visit_category(c_event_manager const * manager, e_event_category category_index, s_event_category const * category)
{
    mangled_ppc("?visit_category@c_category_output_dump_visitor@@UAAXPBVc_event_manager@@W4e_event_category@@PBUs_event_category@@@Z");

    s_static_string<256> description;
    manager->describe_category(category_index, description.get_buffer(), description.max_length());
    output_message("  '%s'", description.get_string());
};

c_category_category_set_level_visitor::c_category_category_set_level_visitor(char const * category_name, char const * level_description) :
    m_category_name(category_name),
    m_categories_set(0)
{
    mangled_ppc("??0c_category_category_set_level_visitor@@QAA@PBD0@Z");

    m_level_description.set(level_description);
};

void c_category_category_set_level_visitor::visit_category(c_event_manager const * manager, e_event_category category_index, s_event_category const * category)
{
    mangled_ppc("?visit_category@c_category_category_set_level_visitor@@UAAXPBVc_event_manager@@W4e_event_category@@PBUs_event_category@@@Z");

    s_static_string<256> description;
    manager->describe_category(category_index, description.get_buffer(), description.max_length());
    output_message("  set '%s'", description.get_string());
    m_categories_set++;
};

void c_category_category_set_level_visitor::print_summary(void)
{
    mangled_ppc("?print_summary@c_category_category_set_level_visitor@@QAAXXZ");

    if (m_categories_set == 0)
    {
        output_message("couldn't find any category called '%s'", m_category_name);
    }
    else
    {
        output_message("set %s for %d %s", m_level_description.get_string(), m_categories_set, m_categories_set > 1 ? "categories" : "category");
    }
};

c_event_handler_instance::c_event_handler_instance(void)
{
    mangled_ppc("??0c_event_handler_instance@@QAA@XZ");

    c_event_handler_hook::attach_handler(this);
};


c_event_handler_instance::~c_event_handler_instance(void)
{
    mangled_ppc("??1c_event_handler_instance@@QAA@XZ");

    c_event_handler_hook::detach_handler(this);
};

bool c_event_handler_instance::event_level_query(e_event_level level)
{
    mangled_ppc("?event_level_query@c_event_handler_instance@@UAA_NW4e_event_level@@@Z");

    bool result = true;
    result = result && g_event_globals.initialized;
    result = result && g_event_globals.events_disabled.peek() == 0;
    result = result && !events_disabled_thread();
    if (result)
    {
        result = result && level >= g_event_globals.global_minimum_level.peek();
        assert_tag_debug_untracked_jul_11_2011(1176, g_event_globals.global_minimum_level.peek()==g_event_globals.manager.get_minimum_level());
    }

    return result;
};

bool c_event_handler_instance::event_query(s_event_properties const * properties)
{
    mangled_ppc("?event_query@c_event_handler_instance@@UAA_NPBUs_event_properties@@@Z");

    return event_level_query(properties->level);
};

// $TODO nonmatching: only the TLS offset (li 0x310 vs li 0) differs, as for every g_event_thread_globals access
long c_event_handler_instance::event_process(s_event_properties const * properties, char const * format, char * arglist)
{
    mangled_ppc("?event_process@c_event_handler_instance@@UAAJPBUs_event_properties@@PBDPAD@Z");

    e_event_level level = properties->level;
    e_event_category category_index = static_cast<e_event_category>(properties->category_index);
    c_event_generation_flags generation_flags;
    generation_flags.set_unsafe(properties->flags);

    if (!events_should_use_emergency_redirection_for_thread())
    {
        TLS_DATA_GET_VALUE_REFERENCE(g_event_thread_globals).generating_event = true;
        if (g_event_globals.guard_begin_function)
        {
            g_event_globals.guard_begin_function();
        }

        if (events_try_to_initialize() && g_event_globals.events_disabled.peek() == 0 && !events_disabled_thread())
        {
            category_index = event_generate_internal(level, category_index, generation_flags, format, arglist);
        }

        if (g_event_globals.guard_end_function)
        {
            g_event_globals.guard_end_function();
        }
        TLS_DATA_GET_VALUE_REFERENCE(g_event_thread_globals).generating_event = false;
    }
    else
    {
        if (events_try_to_initialize() && g_event_globals.events_disabled.peek() == 0 && !events_disabled_thread())
        {
            event_generate_handle_recursion(level, category_index, generation_flags, format, arglist);
        }
    }

    return category_index;
};

void c_event_handler_instance::store_category(long generated_category_index, long volatile * category_storage)
{
    mangled_ppc("?store_category@c_event_handler_instance@@UAAXJPCJ@Z");

    long result = c_synchronized_int32::set_if_equal_external(category_storage, generated_category_index, k_event_category_index_unknown);
    assert_tag_debug_untracked_jul_11_2011(1251, result==k_event_category_index_unknown || result==generated_category_index);
};

void c_event_handler_instance::context_push(char const * type, unsigned long flags, char const * description)
{
    mangled_ppc("?context_push@c_event_handler_instance@@UAAXPBDK0@Z");

    c_event_thread_context * context = events_thread_context_get();
    context->push(type, description, (flags & FLAG(0)) == 0);
};

void c_event_handler_instance::context_pop(void)
{
    mangled_ppc("?context_pop@c_event_handler_instance@@UAAXXZ");

    c_event_thread_context * context = events_thread_context_get();
    context->pop();
};

bool events_try_to_initialize(void)
{
    mangled_ppc("?events_try_to_initialize@@YA_NXZ");

    if (!g_event_globals.initialized && !g_event_globals.initializing && !g_event_globals.disposed && synchronization_manager_initialized())
    {
        g_event_globals.initializing = true;
        g_event_globals.events_disabled.set(0);
        g_event_globals.global_minimum_level.set(_event_warning);
        g_event_globals.manager_lock.initialize_automatic("CS: Event Manager RW Lock", "S4: Event Manager RW Lock");
        g_event_globals.buffer_lock.initialize_automatic("CS: Event Buffer RW Lock", "S4: Event Buffer RW Lock");
        g_event_globals.datamine_handler = NULL;
        g_event_globals.time_format_function = NULL;
        g_event_globals.blocking_begin_function = NULL;
        g_event_globals.blocking_end_function = NULL;

        g_event_globals.manager.initialize(event_manager_log_creator_function);
        g_event_globals.manager.set_logs_enabled(true);
        g_event_globals.manager.set_log_trimming_enabled(true);
        g_event_globals.manager.set_output_level(_event_warning);
        g_event_globals.manager.set_log_level(_event_warning);
        g_event_globals.manager.set_debug_level(_event_warning);
        g_event_globals.manager.set_datamine_level(_event_warning);
        if (output_has_console_window())
        {
            g_event_globals.manager.set_spam_suppression_enabled(false);
            g_event_globals.manager.set_output_suppression_enabled(false);
        }
        if (!version_is_tracked_build())
        {
            g_event_globals.manager.set_output_suppression_enabled(false);
        }
        event_cache_global_settings(&g_event_globals.manager);
        g_event_globals.buffer.reset();

        event_logs_initialize();

        {
            s_flags<e_event_log_flags, unsigned long, k_event_log_flag_count> flags;
            flags.clear();
            flags.set(_event_log_place_in_root_bit, true);
            flags.set(_event_log_trim_file_bit, g_event_globals.manager.get_log_trimming_enabled());
            e_event_log_index log_index = event_logs_create_log(k_primary_event_log_filename, flags);
            g_event_globals.manager.register_event_log(static_cast<e_event_manager_tracked_log>(0), log_index);
        }

        {
            s_flags<e_event_log_flags, unsigned long, k_event_log_flag_count> flags;
            flags.clear();
            flags.set(_event_log_append_to_file_bit, true);
            flags.set(_event_log_disable_file_trimming, true);
            flags.set(_event_log_trim_file_bit, g_event_globals.manager.get_log_trimming_enabled());
            e_event_log_index log_index = event_logs_create_log(k_primary_event_log_filename, flags);
            g_event_globals.manager.register_event_log(static_cast<e_event_manager_tracked_log>(1), log_index);
            log_index = event_logs_create_log(k_primary_full_event_log_filename, flags);
            g_event_globals.manager.register_event_log(static_cast<e_event_manager_tracked_log>(2), log_index);
        }

        {
            s_flags<e_event_log_flags, unsigned long, k_event_log_flag_count> flags;
            flags.clear();
            flags.set(_event_log_only_for_custom_subfolder, true);
            flags.set(_event_log_trim_file_bit, g_event_globals.manager.get_log_trimming_enabled());
            e_event_log_index log_index = event_logs_create_log(k_primary_event_log_filename, flags);
            g_event_globals.manager.register_event_log(static_cast<e_event_manager_tracked_log>(3), log_index);
            log_index = event_logs_create_log(k_primary_full_event_log_filename, flags);
            g_event_globals.manager.register_event_log(static_cast<e_event_manager_tracked_log>(4), log_index);
        }

        g_event_globals.initialized = true;
    }

    return g_event_globals.initialized;
};

e_event_log_index event_manager_log_creator_function(char const * log_name)
{
    mangled_ppc("?event_manager_log_creator_function@@YA?AW4e_event_log_index@@PBD@Z");

    s_flags<e_event_log_flags, unsigned long, k_event_log_flag_count> flags;
    flags.clear();
    flags.set(_event_log_trim_file_bit, g_event_globals.manager.get_log_trimming_enabled());

    return event_logs_create_log(log_name, flags);
};

void events_set_category_level_by_name_internal(char const * category_name, e_event_level level, e_event_manager_category_set_level set_level, char const * level_description)
{
    mangled_ppc("?events_set_category_level_by_name_internal@@YAXPBDW4e_event_level@@W4e_event_manager_category_set_level@@0@Z");

    assert_tag_debug_untracked_jul_11_2011(1412, category_name);

    if (VALID_INDEX(level, k_event_level_count))
    {
        c_event_manager_write_lock lock;
        c_category_category_set_level_visitor visitor(category_name, level_description);
        lock.manager()->set_category_level_by_name(category_name, set_level, level, &visitor);
        event_cache_global_settings(lock.manager());
        visitor.print_summary();
    }
    else
    {
        output_error("unknown events %s (%d)", level_description, level);
    }
};

e_event_category event_generate_internal(e_event_level level, e_event_category category, c_event_generation_flags generation_flags, char const * format, char * arglist)
{
    mangled_ppc("?event_generate_internal@@YA?AW4e_event_category@@W4e_event_level@@W41@V?$c_flags_zero_init@W4e_event_generation_flags@@K$00@@PBDPAD@Z");

    e_event_category category_index = category;
    c_event_response_flags flags;

    assert_tag_debug_untracked_jul_11_2011(1441, g_event_globals.initialized);

    if (category_index == _event_category_none)
    {
        c_event_manager_write_lock lock;
        category_index = lock.manager()->create_category_from_name(format);
    }

    {
        c_event_manager_read_lock lock;
        flags = lock.manager()->query_event(level, category_index, generation_flags);
    }

    if (!flags.is_empty())
    {
        s_static_string<2048> message;
        s_event_response response;

        message.print_va(format, arglist);
        {
            c_event_manager_write_lock lock;
            lock.manager()->finalize_event(level, category_index, flags, &message, &response);
        }

        if (!response.response_flags.is_empty())
        {
            if (response.response_flags.test(_event_response_output))
            {
                event_dispatch_output(level, &message, &response);
            }
            if (response.response_flags.test(_event_response_log))
            {
                event_dispatch_log(level, &message, &response);
            }
            if (response.response_flags.test(_event_response_debug))
            {
                event_dispatch_debug(level, &message, &response);
            }
            if (response.response_flags.test(_event_response_datamine))
            {
                event_dispatch_datamine(level, format, arglist);
            }
            if (response.response_flags.test(_event_response_debugger_break))
            {
                event_dispatch_debugger_break(&message);
            }
            if (response.response_flags.test(_event_response_halt))
            {
                event_dispatch_halt(&message);
            }
            event_dispatch_listeners(level, &message, &response);
        }
    }

    return category_index;
};

void event_dispatch_output(e_event_level level, s_static_string<2048> const * message, s_event_response const * response)
{
    mangled_ppc("?event_dispatch_output@@YAXW4e_event_level@@PBV?$s_static_string@$0IAA@@@PBUs_event_response@@@Z");

    e_event_level output_level = level;
    c_event_thread_context * context = events_thread_context_get();
    bool has_context = false;
    s_static_string<256> context_description;
    has_context = context->describe(_event_context_query_destination_console, &context_description);

    if (response->response_flags.test(_event_response_force_output))
    {
        output_level = _event_critical;
    }

    output_event(output_level, has_context ? context_description.get_string() : NULL, message->get_string(), &response->output_color);
};

void event_dispatch_log(e_event_level level, s_static_string<2048> const * message, s_event_response const * response)
{
    mangled_ppc("?event_dispatch_log@@YAXW4e_event_level@@PBV?$s_static_string@$0IAA@@@PBUs_event_response@@@Z");

    s_static_string<2048> log_text;
    s_static_string<2048> log_prefix;
    s_static_string<2048> custom_log_string;
    long const k_maximum_logs = 6;
    c_static_stack<e_event_log_index, k_maximum_logs> logs_to_write;
    c_event_thread_context * event_context = events_thread_context_get();
    s_static_string<256> const * thread_context_string = NULL;
    s_static_string<256> event_context_description;

    if (event_context->describe(_event_context_query_destination_log, &event_context_description))
    {
        thread_context_string = &event_context_description;
    }

    if (response->event_log_index != k_event_log_invalid)
    {
        if (response->log_format_function)
        {
            log_prefix.clear();
            response->log_format_function(log_prefix.get_buffer(), log_prefix.max_length());
            event_format_for_log(level, message, response, &log_prefix, thread_context_string, &custom_log_string);
            event_logs_write(1, &response->event_log_index, custom_log_string.get_string());
        }
        else
        {
            logs_to_write.push_back(response->event_log_index);
        }
    }

    if (response->response_flags.test(_event_response_log_primary))
    {
        if (response->event_log_indices[static_cast<e_event_manager_tracked_log>(0)] != k_event_log_invalid)
        {
            logs_to_write.push_back(response->event_log_indices[static_cast<e_event_manager_tracked_log>(0)]);
        }
        logs_to_write.push_back(response->event_log_indices[static_cast<e_event_manager_tracked_log>(1)]);
        logs_to_write.push_back(response->event_log_indices[static_cast<e_event_manager_tracked_log>(3)]);
        logs_to_write.push_back(response->event_log_indices[static_cast<e_event_manager_tracked_log>(4)]);
    }
    logs_to_write.push_back(response->event_log_indices[static_cast<e_event_manager_tracked_log>(2)]);

    event_format_for_log(level, message, response, NULL, thread_context_string, &log_text);
    event_logs_write(logs_to_write.count(), logs_to_write.get_elements(), log_text.get_string());
};

void event_dispatch_debug(e_event_level event_level, s_static_string<2048> const * message, s_event_response const * response)
{
    mangled_ppc("?event_dispatch_debug@@YAXW4e_event_level@@PBV?$s_static_string@$0IAA@@@PBUs_event_response@@@Z");

    c_event_thread_context * thread_context = events_thread_context_get();
    assert_tag_debug_untracked_jul_11_2011(1614, VALID_INDEX(event_level, NUMBEROF(k_event_level_severity_strings)));
    char const * event_level_string = k_event_level_severity_strings[event_level];
    s_static_string<256> context_desc;
    s_static_string<2048> debug_string;

    if (thread_context->describe(_event_context_query_destination_remote_log, &context_desc))
    {
        debug_string.print("%s (%s) %s", event_level_string, context_desc.get_string(), message->get_string());
    }
    else
    {
        debug_string.print("%s %s", event_level_string, message->get_string());
    }

    {
        c_event_buffer_write_lock lock;
        lock.buffer()->add_event(debug_string.get_string());
    }

    debug_string.append("\r\n");
    output_debug_string(debug_string.get_string());
};

void event_dispatch_datamine(e_event_level level, char const * format, char * arglist)
{
    mangled_ppc("?event_dispatch_datamine@@YAXW4e_event_level@@PBDPAD@Z");

    if (g_event_globals.datamine_handler)
    {
        c_event_thread_context * context = events_thread_context_get();
        s_static_string<256> context_string;
        context->describe(_event_context_query_destination_unknown3, &context_string);
        g_event_globals.datamine_handler(level, context_string.get_string(), format, arglist);
    }
};

void event_dispatch_debugger_break(s_static_string<2048> const * message)
{
    mangled_ppc("?event_dispatch_debugger_break@@YAXPBV?$s_static_string@$0IAA@@@@Z");

    static bool x_disable_debugger = false;

    if (!x_disable_debugger)
    {
        s_static_string<2048> debug_string;
        debug_string.print("critical event encountered: %s", message->get_string());
        __debugbreak();
    }
};

void event_dispatch_halt(s_static_string<2048> const * message)
{
    mangled_ppc("?event_dispatch_halt@@YAXPBV?$s_static_string@$0IAA@@@@Z");

    static bool x_disable_halt = false;

    if (!x_disable_halt)
    {
        s_static_string<2048> debug_string;
        debug_string.print("critical event encountered: %s", message->get_string());
        dassert_tag_debug_untracked_jul_11_2011(1677, false, debug_string);
    }
};

void event_dispatch_listeners(e_event_level level, s_static_string<2048> const * message, s_event_response const * response)
{
    mangled_ppc("?event_dispatch_listeners@@YAXW4e_event_level@@PBV?$s_static_string@$0IAA@@@PBUs_event_response@@@Z");

    for (long listener_index = 0; listener_index < response->listeners.get_count(); listener_index++)
    {
        if (TEST_BIT(response->event_listeners, listener_index))
        {
            c_event_listener * listener = response->listeners[listener_index];
            assert_tag_debug_untracked_jul_11_2011(1692, listener!=NULL);
            listener->handle_event(level, message->get_string());
        }
    }
};

void event_generate_handle_recursion(e_event_level level, e_event_category category, c_event_generation_flags generation_flags, char const * format, char * arglist)
{
    mangled_ppc("?event_generate_handle_recursion@@YAXW4e_event_level@@W4e_event_category@@V?$c_flags_zero_init@W4e_event_generation_flags@@K$00@@PBDPAD@Z");

    events_disable_thread_push();

    s_event_response response;
    csmemset(&response, 0, sizeof(response));
    response.event_log_index = k_event_log_invalid;
    response.event_log_indices.set_all(k_event_log_invalid);
    response.response_flags = g_event_globals.manager.query_event(level, category, generation_flags);

    if (!response.response_flags.is_empty())
    {
        s_static_string<2048> event_text;
        event_text.print_va(format, arglist);

        if (response.response_flags.test(_event_response_datamine))
        {
            event_text.append("(!datamined)");
        }
        if (response.response_flags.test(_event_response_log))
        {
            event_text.append("(!logged)");
        }

        {
            c_simple_file emergency_file;
            s_static_string<256> lost_events_file_name;
            event_build_lost_events_file_name_for_current_thread(&lost_events_file_name);
            emergency_file.set_debug_filename(lost_events_file_name.get_string());

            if (emergency_file.open(FLAG(_simple_file_open_write_bit) | FLAG(_simple_file_open_write_append_bit)))
            {
                s_static_string<256> const * thread_context_string = NULL;
                c_event_thread_context * context = events_thread_context_get();
                s_static_string<2048> formatted_string;
                s_static_string<256> event_context_description;

                if (context->describe(_event_context_query_destination_unknown3, &event_context_description))
                {
                    thread_context_string = &event_context_description;
                }

                event_format_for_log(level, &event_text, &response, NULL, thread_context_string, &formatted_string);
                emergency_file.print(formatted_string.get_string());
            }
            else
            {
                event_text.append("(!emergency-logged)");
            }
        }

        output_debug_string(event_text.get_string());
        output_debug_string("\r\n");
    }

    events_disable_thread_pop();
};

void event_cache_global_settings(c_event_manager const * manager)
{
    mangled_ppc("?event_cache_global_settings@@YAXPBVc_event_manager@@@Z");

    assert_tag_debug_untracked_jul_11_2011(1801, manager);

    g_event_globals.global_minimum_level.set(manager->get_minimum_level());
};

void event_format_for_log(e_event_level event_level, s_static_string<2048> const * event_text, s_event_response const * response, s_static_string<2048> const * prefix, s_static_string<256> const * context, s_static_string<2048> * out_log_text)
{
    mangled_ppc("?event_format_for_log@@YAXW4e_event_level@@PBV?$s_static_string@$0IAA@@@PBUs_event_response@@1PBV?$s_static_string@$0BAA@@@PAV2@@Z");

    s_static_string<256> date_and_time_string;
    s_static_string<256> custom_time;

    assert_tag_debug_untracked_jul_11_2011(1817, VALID_INDEX(event_level, NUMBEROF(k_event_level_severity_strings)));
    assert_tag_debug_untracked_jul_11_2011(1818, event_text);
    assert_tag_debug_untracked_jul_11_2011(1819, response);

    custom_time.clear();
    if (g_event_globals.time_format_function)
    {
        g_event_globals.time_format_function(custom_time.max_length(), custom_time.get_buffer());
    }
    system_print_date_and_time(_date_and_time_print_format_default, date_and_time_string.get_buffer(), date_and_time_string.max_length());

    assert_tag_debug_untracked_jul_11_2011(1829, out_log_text);

    out_log_text->print("%s %07d %s %s %s %s %s\r\n",
        date_and_time_string.get_string(),
        response->event_index,
        custom_time.get_string(),
        prefix ? prefix->get_string() : "",
        k_event_level_severity_strings[event_level],
        event_text->get_string(),
        context ? context->get_string() : "");
};

bool events_copy_file_to_snapshot(c_file_path const * snapshot_directory, c_file_path const * source_file, c_file_path * out_destination_file)
{
    mangled_ppc("?events_copy_file_to_snapshot@@YA_NPBVc_file_path@@0PAV1@@Z");

    bool result = false;
    s_static_string<256> filename;

    source_file->get_filename(&filename);
    out_destination_file->copy(snapshot_directory);
    out_destination_file->set_filename(filename.get_string());
    file_create_parent_directories(out_destination_file);
    result = file_copy(source_file, out_destination_file, _file_overwrite_mode_overwrite);

    return result;
};

void event_build_lost_events_file_name_for_current_thread(s_static_string<256> * debug_lost_file_name)
{
    mangled_ppc("?event_build_lost_events_file_name_for_current_thread@@YAXPAV?$s_static_string@$0BAA@@@@Z");

    char const * thread_name = NULL;

    assert_tag_debug_untracked_jul_11_2011(1869, debug_lost_file_name);

    thread_name = thread_get_current_thread_name();
    if (thread_name)
    {
        debug_lost_file_name->print(k_thrown_away_events_log_file_name_format_string_with_name, thread_name);
    }
    else
    {
        s_thread_id thread_id = thread_get_current_id();
        debug_lost_file_name->print(k_thrown_away_events_log_file_name_format_string_with_id, thread_id);
    }
};
