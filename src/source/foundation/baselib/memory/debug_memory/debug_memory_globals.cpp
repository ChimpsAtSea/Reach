#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\foundation\\baselib\\memory\\debug_memory\\debug_memory_globals.cpp"
/* ---------- headers */

#include "foundation\baselib\memory\debug_memory\debug_memory_globals.h"
#include "foundation\baselib\memory\debug_memory\debug_memory_allocators.h"
#include "foundation\baselib\memory\debug_memory\debug_memory_reporting.h"
#include "foundation\baselib\memory\allocation_interface.h"
#include "foundation\baselib\memory\base\base_memory_windows.h"
#include "foundation\baselib\datatypes\constant_pool.h"
#include "foundation\baselib\datatypes\hash_table.h"
#include "foundation\baselib\datatypes\static_hash_table.h"
#include "foundation\baselib\datatypes\static_hash_table_data.h"
#include "foundation\baselib\system\system_os_interface_xenon.h"
#include "baselib\platform_tracking_xenon.h"
#include "baselib\system_executable_windows.h"
#include "baselib\system_time_windows.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_events.h"
#include "core\corelib\cseries\cseries_macros.h"
#include "core\corelib\cseries\cseries_memory.h"
#include "core\corelib\cseries\cseries_string.h"
#include "omaha\cseries\cseries.h"

// $TODO the debug string routines replace the crt ones in debug builds, move this to a shared header
#define strcmp strcmp_debug
#define strlen strlen_debug

/* ---------- constants */

unsigned long const k_debug_memory_globals_signature = 'SAFT';
unsigned int const k_debug_memory_emergency_reserve_size = 0x20000;
long const k_nonheap_hash_table_bucket_count = 0x18000;
long const k_nonheap_hash_table_maximum_elements = 0xC000;
long const k_maximum_constant_strings = 0x4000;
long const k_maximum_constant_string_size = 0x40000;
unsigned long const k_default_header_checksum = 0x5A5A5A5A;
void const * const k_unspecified_nonheap_resource = reinterpret_cast<void const *>(NONE);
long const k_maximum_tracking_infos = 0x2000;

/* ---------- definitions */

typedef unsigned long debug_memory_checksum_function(void const * data, unsigned int size);
typedef unsigned short debug_memory_random_function(void);

struct s_physical_memory_monitor
{
    unsigned int minimum_free;
    unsigned int maximum_free;
};

struct s_debug_memory_globals
{
    unsigned long header_signature;
    long identifier;
    unsigned int current_heap_size;
    unsigned int current_nonheap_size;
    unsigned int largest_heap_size;
    unsigned int largest_nonheap_size;
    unsigned int pretracked_nonheap_size;
    long unknown1C;
    s_pointer_header * header_queue;
    s_pointer_header * freed_header_queue;
    s_pointer_header * valid_header_range_bottom;
    s_pointer_header * valid_header_range_top;
    long break_on_alloc_identifier;
    long break_on_free_identifier;
    void * emergency_reserve;
    bool initialized;
    bool initialized_for_exit;
    bool disposed;
    bool checkpoint_valid;
    s_base_memory_information checkpoint_information;
    __int64 checkpoint_time;
    debug_memory_checksum_function * checksum_function;
    debug_memory_random_function * local_random_function;
    long unknown60;
    unsigned long trailer_signature;
};
static_assert(sizeof(s_debug_memory_globals) == 0x68, "s_debug_memory_globals");

typedef c_static_hash_table_data<s_header_tracking_info *, k_maximum_tracking_infos> c_tracking_info_hash_data;
typedef c_static_hash_table<c_tracking_info_hash_data, 3001, 7187, 9973> c_tracking_info_hash_table;

class c_debug_memory_initializer
{
public:
    c_debug_memory_initializer(void);
};

class c_debug_memory_internal_allocation :
    public c_allocation_interface
{
public:
    virtual void * allocate(unsigned int size, char const * file, long line, char const * type, char const * subtype, char const * name);
    virtual void deallocate(void * pointer, char const * file, long line);
};

/* ---------- prototypes */

void debug_memory_manager_dispose(void);
void debug_memory_initialize_static(void);
void debug_dump_memory_at_exit(void);
void debug_notify_out_of_memory(char const * file, long line);
void debug_checkpoint_memory(char const * name, char const * file, long line);
void debug_physical_memory_monitor(s_physical_memory_monitor * monitor, char const * name);
void queue_header(s_pointer_header * header);
bool query_possible_header(s_pointer_header const * header);
unsigned long checksum_header(s_pointer_header const * header);
bool debug_pointer_valid(void * pointer);
unsigned int debug_get_used_memory_size(void * pointer, char const * file, long line);
unsigned int debug_get_actual_memory_size(void * pointer, char const * file, long line);
unsigned long nonheap_hash_function(void const * key);
bool nonheap_compare_function(void const * key1, void const * key2);
s_header_tracking_info * find_or_allocate_tracking_info(char const * file, long line, char const * type, char const * subtype, char const * name);
long get_constant_string_key(char const * string);
void dispose_tracking_info(void);
void set_checksum_function(debug_memory_checksum_function * const checksum_function);
void set_local_random_function(debug_memory_random_function * const local_random_function);

/* ---------- globals */

char const * const k_source_directory_string = "source\\";

static s_debug_memory_globals g_debug_memory_globals =
{
    k_debug_memory_globals_signature,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    NULL,
    NULL,
    NULL,
    NULL,
    NONE,
    NONE,
    NULL,
    false,
    false,
    false,
    false,
    { 0, 0, 0, 0 },
    0,
    NULL,
    NULL,
    0,
    k_debug_memory_globals_signature
};

static bool g_debug_memory_manager_initialized;
static c_tracking_info_hash_data g_tracking_info_hash_data;
static __declspec(thread) bool g_thread_can_use_debug_memory;
static s_constant_pool * g_debug_memory_constant_string_pool;
static bool g_tracking_info_hash_data_initialized;
static c_debug_memory_initializer g_debug_memory_initializer;
c_hash_table<s_pointer_header *, void> g_nonheap_hash_table;
static c_debug_memory_internal_allocation g_debug_memory_internal_allocation;

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// public: static short const c_static_hash_table_data<struct s_header_tracking_info *, 8192>::k_hash_entry_invalid; // "?k_hash_entry_invalid@?$c_static_hash_table_data@PAUs_header_tracking_info@@$0CAAA@@@2FB"
// public: static long const s_static_array<struct c_static_hash_table_data<struct s_header_tracking_info *, 8192>::s_data, 8192>::k_element_count; // "?k_element_count@?$s_static_array@Us_data@?$c_static_hash_table_data@PAUs_header_tracking_info@@$0CAAA@@@$0CAAA@@@2JB"
// public: static long const c_static_hash_table<class c_static_hash_table_data<struct s_header_tracking_info *, 8192>, 3001, 7187, 9973>::k_hash_invalid; // "?k_hash_invalid@?$c_static_hash_table@V?$c_static_hash_table_data@PAUs_header_tracking_info@@$0CAAA@@@$0LLJ@$0BMBD@$0CGPF@@@2JB"
// char const *const k_source_directory_string; // "?k_source_directory_string@@3PBDB"
// long volatile `public: static long __cdecl c_static_hash_table<class c_static_hash_table_data<struct s_header_tracking_info *, 8192>, 3001, 7187, 9973>::find_entry(class c_static_hash_table_data<struct s_header_tracking_info *, 8192> const *, long, long, long)'::`32'::x_event_category_index; // "?x_event_category_index@?CA@??find_entry@?$c_static_hash_table@V?$c_static_hash_table_data@PAUs_header_tracking_info@@$0CAAA@@@$0LLJ@$0BMBD@$0CGPF@@@SAJPBV?$c_static_hash_table_data@PAUs_header_tracking_info@@$0CAAA@@@JJJ@Z@4JC"
// class c_hash_table<struct s_pointer_header *, void> g_nonheap_hash_table; // "?g_nonheap_hash_table@@3V?$c_hash_table@PAUs_pointer_header@@X@@A"

// ?debug_memory_manager_initialize@@YAXQ6AKPBXI@ZQ6AGXZ@Z;
// void debug_memory_manager_dispose(void);
// void debug_memory_initialize_static(void);
// void debug_dump_memory_at_exit(void);
// void debug_memory_begin_exit(void);
// void debug_verify_memory(char const *, long);
// void * get_user_pointer_from_header(struct s_pointer_header *);
// void debug_notify_out_of_memory(char const *, long);
// void debug_checkpoint_memory(char const *, char const *, long);
// void debug_physical_memory_monitor(struct s_physical_memory_monitor *, char const *);
// void debug_memory_get_memory_information(struct s_debug_memory_information *);
// void check_debug_memory_manager(char const *, long);
// void check_header(struct s_pointer_header const *, char const *, long);
// void const * get_user_pointer_from_header_const(struct s_pointer_header const *);
// void check_pointer(void const *, char const *, long);
// struct s_pointer_header const * get_header_from_user_pointer_const(void const *);
// struct s_pointer_header * get_header_from_user_pointer(void *);
// struct s_pointer_trailer const * get_trailer_from_header_const(struct s_pointer_header const *);
// struct s_pointer_trailer * get_trailer_from_header(struct s_pointer_header *);
// void check_nonheap_resource(struct s_pointer_header const *, char const *, long);
// void build_header_and_trailer(void *, unsigned int, long, long, enum e_debug_memory_flags, char const *, long, long, unsigned int, char const *, char const *, char const *, void const *, bool);
// struct s_pointer_header const * get_heap_queue(void);
// struct s_pointer_header const * get_free_queue(void);
// void queue_header(struct s_pointer_header *);
// void dequeue_header(struct s_pointer_header *, char const *, long);
// bool query_possible_header(struct s_pointer_header const *);
// struct s_pointer_header * query_nonheap_header(void const *);
// unsigned long checksum_header(struct s_pointer_header const *);
// void force_release_header(struct s_pointer_header *, char const *, long);
// void track_heap_allocation_size(unsigned int, unsigned int);
// void track_nonheap_allocation_size(unsigned int, unsigned int);
// void pretrack_nonheap_allocation_size(unsigned int, unsigned int);
// char const * make_constant_string(char const *);
// char const * safe_printable_string(char const *);
// char const * strip_source_directory(char const *);
// void debug_memory_free_emergency_reserve(void);
// bool thread_can_use_debug_memory(void);
// bool debug_pointer_valid(void *);
// unsigned int debug_get_used_memory_size(void *, char const *, long);
// void * get_base_pointer_from_header(struct s_pointer_header *);
// unsigned int debug_get_actual_memory_size(void *, char const *, long);
// unsigned int header_get_actual_size(struct s_pointer_header const *);
// public: virtual void * c_debug_memory_internal_allocation::allocate(unsigned int, char const *, long, char const *, char const *, char const *);
// public: virtual void c_debug_memory_internal_allocation::deallocate(void *, char const *, long);
// unsigned long nonheap_hash_function(void const *);
// bool nonheap_compare_function(void const *, void const *);
// struct s_header_tracking_info * find_or_allocate_tracking_info(char const *, long, char const *, char const *, char const *);
// long get_constant_string_key(char const *);
// void dispose_tracking_info(void);
// ?set_checksum_function@@YAXQ6AKPBXI@Z@Z;
// ?set_local_random_function@@YAXQ6AGXZ@Z;
// public: struct s_header_tracking_info ** c_static_hash_table_data<struct s_header_tracking_info *, 8192>::get_element(long);
// public: bool c_hash_table<struct s_pointer_header *, void>::is_created(void) const;
// ?create@?$c_hash_table@PAUs_pointer_header@@X@@QAA_NPBDJJQ6AKPBX@ZQ6A_N11@Z0JPAVc_allocation_interface@@@Z;
// public: void c_hash_table<struct s_pointer_header *, void>::dispose(char const *, long);
// public: bool c_hash_table<struct s_pointer_header *, void>::remove(void const *);
// public: void const * c_hash_table<struct s_pointer_header *, void>::find(void const *, struct s_pointer_header **) const;
// public: void c_static_hash_table_data<struct s_header_tracking_info *, 8192>::clear_all(void);
// unsigned int int_max<unsigned int>(unsigned int const &, unsigned int const &);
// public: static long c_static_hash_table<class c_static_hash_table_data<struct s_header_tracking_info *, 8192>, 3001, 7187, 9973>::iterator_begin(class c_static_hash_table_data<struct s_header_tracking_info *, 8192> const *);
// public: static long c_static_hash_table<class c_static_hash_table_data<struct s_header_tracking_info *, 8192>, 3001, 7187, 9973>::iterator_next(class c_static_hash_table_data<struct s_header_tracking_info *, 8192> const *, long);
// public: static long c_static_hash_table<class c_static_hash_table_data<struct s_header_tracking_info *, 8192>, 3001, 7187, 9973>::add_entry(class c_static_hash_table_data<struct s_header_tracking_info *, 8192> *, long, long, long);
// public: static long c_static_hash_table<class c_static_hash_table_data<struct s_header_tracking_info *, 8192>, 3001, 7187, 9973>::find_entry(class c_static_hash_table_data<struct s_header_tracking_info *, 8192> const *, long, long, long);
// public: struct c_static_hash_table_data<struct s_header_tracking_info *, 8192>::s_data & s_static_array<struct c_static_hash_table_data<struct s_header_tracking_info *, 8192>::s_data, 8192>::operator[]<long>(long);
// public: struct c_static_hash_table_data<struct s_header_tracking_info *, 8192>::s_data * c_static_hash_table_data<struct s_header_tracking_info *, 8192>::get_data(long);
// public: struct c_static_hash_table_data<struct s_header_tracking_info *, 8192>::s_data const * c_static_hash_table_data<struct s_header_tracking_info *, 8192>::get_data(long) const;
// public: long c_static_hash_table_data<struct s_header_tracking_info *, 8192>::get_total_count(void) const;
// public: long c_static_hash_table_data<struct s_header_tracking_info *, 8192>::get_maximum_count(void) const;
// public: void c_static_hash_table_data<struct s_header_tracking_info *, 8192>::increment_total_count(void);
// public: short * c_static_hash_table_data<struct s_header_tracking_info *, 8192>::get_hash_entry_count(void);
// public: short const * c_static_hash_table_data<struct s_header_tracking_info *, 8192>::get_hash_entry_count(void) const;
// public: short * c_static_hash_table_data<struct s_header_tracking_info *, 8192>::get_original_hash_entry(void);
// public: short const * c_static_hash_table_data<struct s_header_tracking_info *, 8192>::get_original_hash_entry(void) const;
// private: static long c_static_hash_table<class c_static_hash_table_data<struct s_header_tracking_info *, 8192>, 3001, 7187, 9973>::calculate_hash(class c_static_hash_table_data<struct s_header_tracking_info *, 8192> const *, long, long, long);
// private: static long c_static_hash_table<class c_static_hash_table_data<struct s_header_tracking_info *, 8192>, 3001, 7187, 9973>::find_new_hash_entry(class c_static_hash_table_data<struct s_header_tracking_info *, 8192> *, long);
// public: static bool s_static_array<struct c_static_hash_table_data<struct s_header_tracking_info *, 8192>::s_data, 8192>::valid<long>(long);
// public: struct c_static_hash_table_data<struct s_header_tracking_info *, 8192>::s_data const & s_static_array<struct c_static_hash_table_data<struct s_header_tracking_info *, 8192>::s_data, 8192>::operator[]<long>(long) const;
// public: c_debug_memory_initializer::c_debug_memory_initializer(void);
// public: c_hash_table<struct s_pointer_header *, void>::c_hash_table<struct s_pointer_header *, void>(void);
// public: c_debug_memory_internal_allocation::c_debug_memory_internal_allocation(void);
// public: c_hash_table<struct s_pointer_header *, void>::~c_hash_table<struct s_pointer_header *, void>(void);
// void g_nonheap_hash_table::`dynamic atexit destructor'(void);

// $TODO nonmatching: target tls offset for g_thread_can_use_debug_memory is 0x4A0 (only diff)
void debug_memory_manager_initialize(debug_memory_checksum_function * const checksum_function, debug_memory_random_function * const local_random_function)
{
    mangled_ppc("?debug_memory_manager_initialize@@YAXQ6AKPBXI@ZQ6AGXZ@Z");

    debug_memory_initialize_static();
    check_debug_memory_manager(__FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__, 230);
    set_checksum_function(checksum_function);
    set_local_random_function(local_random_function);

    assert_tag_debug_untracked_jul_11_2011(235, g_debug_memory_globals.emergency_reserve==NULL);
    g_debug_memory_globals.emergency_reserve = base_malloc(k_debug_memory_emergency_reserve_size);
    dassert_tag_debug_untracked_jul_11_2011(237, g_debug_memory_globals.emergency_reserve != NULL, "failed to allocate debug memory emergency reserve");

    g_nonheap_hash_table.create("nonheap table", k_nonheap_hash_table_bucket_count, k_nonheap_hash_table_maximum_elements, nonheap_hash_function, nonheap_compare_function, __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__, 246, &g_debug_memory_internal_allocation);

    g_debug_memory_constant_string_pool = constant_pool_new("debug memory strings", k_maximum_constant_strings, k_maximum_constant_string_size, constant_pool_string_size_function, string_hash_table_hash_function, NULL, string_hash_table_compare_function, NULL, &g_debug_memory_internal_allocation, __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__, 258);
    dassert_tag_debug_untracked_jul_11_2011(259, g_debug_memory_constant_string_pool != NULL, "failed to create debug memory constant string pool");

    g_debug_memory_manager_initialized = true;
    g_thread_can_use_debug_memory = true;
    debug_platform_memory_tracking_thread_enable(true);
};

void debug_memory_manager_dispose(void)
{
    mangled_ppc("?debug_memory_manager_dispose@@YAXXZ");

    check_debug_memory_manager(__FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__, 273);

    s_pointer_header * header = g_debug_memory_globals.freed_header_queue;
    while (header != NULL)
    {
        s_pointer_header * next_header = header->next;
        base_free(header);
        header = next_header;
    }

    dispose_tracking_info();

    if (g_debug_memory_constant_string_pool != NULL)
    {
        constant_pool_dispose(g_debug_memory_constant_string_pool, __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__, 289);
        g_debug_memory_constant_string_pool = NULL;
    }

    if (g_nonheap_hash_table.is_created())
    {
        g_nonheap_hash_table.dispose(__FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__, 297);
    }

    debug_memory_free_emergency_reserve();
    g_debug_memory_globals.disposed = true;
};

void debug_memory_initialize_static(void)
{
    mangled_ppc("?debug_memory_initialize_static@@YAXXZ");

    if (!g_debug_memory_globals.initialized)
    {
        g_debug_memory_globals.initialized = true;
        system_register_exit_function(debug_memory_manager_dispose);
        system_register_exit_function(debug_dump_memory_at_exit);
    }
};

void debug_dump_memory_at_exit(void)
{
    mangled_ppc("?debug_dump_memory_at_exit@@YAXXZ");

    debug_dump_memory();
};

void debug_memory_begin_exit(void)
{
    mangled_ppc("?debug_memory_begin_exit@@YAXXZ");

    s_pointer_header * header = g_debug_memory_globals.header_queue;
    while (header != NULL)
    {
        s_pointer_header * next_header = header->next;
        if (header->freed_externally_on_exit)
        {
            assert_tag_debug_untracked_jul_11_2011(344, header->nonheap_resource!=NULL);
            force_release_header(header, __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__, 345);
        }
        header = next_header;
    }

    g_debug_memory_globals.initialized_for_exit = true;
};

void debug_verify_memory(char const * file, long line)
{
    mangled_ppc("?debug_verify_memory@@YAXPBDJ@Z");

    check_debug_memory_manager(file, line);

    for (s_pointer_header * header = g_debug_memory_globals.header_queue; header != NULL; header = header->next)
    {
        check_header(header, file, line);
        check_pointer(get_user_pointer_from_header(header), file, line);
        check_nonheap_resource(header, file, line);
    }
};

void debug_notify_out_of_memory(char const * file, long line)
{
    mangled_ppc("?debug_notify_out_of_memory@@YAXPBDJ@Z");

    debug_dump_out_of_memory(file, line);
};

void debug_checkpoint_memory(char const * name, char const * file, long line)
{
    mangled_ppc("?debug_checkpoint_memory@@YAXPBD0J@Z");

    if (!thread_can_use_debug_memory())
    {
        event(_event_error, "memory:debug_memory: discarding memory checkpoint that wasn't from main thread ('%s' from %s,%d)", name, file, line);
    }
    else
    {
        s_base_memory_information information;
        base_memory_information_get(&information);
        __int64 time = system_performance_timer_get();

        if (!g_debug_memory_globals.checkpoint_valid)
        {
            g_debug_memory_globals.checkpoint_information = information;
            g_debug_memory_globals.checkpoint_time = time;
            g_debug_memory_globals.checkpoint_valid = true;
        }

        debug_report_memory_checkpoint(name, file, line, g_debug_memory_globals.checkpoint_time, &g_debug_memory_globals.checkpoint_information, time, &information);
        debug_end_tracking_nonheap_allocation(&g_debug_memory_globals.checkpoint_information, &information, name, file, line, NONE, "memory checkpoint", name, NULL);

        g_debug_memory_globals.checkpoint_information = information;
        g_debug_memory_globals.checkpoint_time = time;
    }
};

void debug_physical_memory_monitor(s_physical_memory_monitor * monitor, char const * name)
{
    mangled_ppc("?debug_physical_memory_monitor@@YAXPAUs_physical_memory_monitor@@PBD@Z");

    s_base_memory_information information;
    base_memory_information_get(&information);

    assert_tag_debug_untracked_jul_11_2011(439, monitor);

    monitor->minimum_free = int_min(*reinterpret_cast<unsigned int *>(&information.free), monitor->minimum_free);
    monitor->maximum_free = int_max(*reinterpret_cast<unsigned int *>(&information.free), monitor->maximum_free);

    if (monitor->maximum_free - monitor->minimum_free > 0x4000)
    {
        event(_event_warning, "memory:debug_memory: physical memory monitor failed at %s, difference between min and max memory free is %d", name, monitor->maximum_free - monitor->minimum_free);
    }
};

void debug_memory_get_memory_information(s_debug_memory_information * out_information)
{
    mangled_ppc("?debug_memory_get_memory_information@@YAXPAUs_debug_memory_information@@@Z");

    assert_tag_debug_untracked_jul_11_2011(454, out_information);

    csmemset(out_information, 0, sizeof(s_debug_memory_information));
    out_information->current_heap_size = g_debug_memory_globals.current_heap_size;
    out_information->current_nonheap_size = g_debug_memory_globals.current_nonheap_size;
    out_information->largest_heap_size = g_debug_memory_globals.largest_heap_size;
    out_information->largest_nonheap_size = g_debug_memory_globals.largest_nonheap_size;
    out_information->pretracked_nonheap_size = g_debug_memory_globals.pretracked_nonheap_size;
};

void check_debug_memory_manager(char const * file, long line)
{
    mangled_ppc("?check_debug_memory_manager@@YAXPBDJ@Z");

    vassert_tag_debug_untracked_jul_11_2011(472, g_debug_memory_globals.header_signature == k_debug_memory_globals_signature && g_debug_memory_globals.trailer_signature == k_debug_memory_globals_signature, "Debug memory manager is uninitialized or corrupted. (%s:%d)", file, line);
};

void check_header(s_pointer_header const * header, char const * file, long line)
{
    mangled_ppc("?check_header@@YAXPBUs_pointer_header@@PBDJ@Z");

    char const * error = NULL;

    vassert_tag_debug_untracked_jul_11_2011(485, g_debug_memory_globals.header_queue != NULL, "Attempted an operation with pointer at 0x%x when no pointers have been allocated. (%s:%d)", get_user_pointer_from_header_const(header), file, line);
    vassert_tag_debug_untracked_jul_11_2011(490, header >= g_debug_memory_globals.valid_header_range_bottom && header <= g_debug_memory_globals.valid_header_range_top, "Attempted an operation with pointer at 0x%x, outside of the valid pointer range. (%s:%d)", get_user_pointer_from_header_const(header), file, line);
    vassert_tag_debug_untracked_jul_11_2011(494, header->tracking != NULL, "Header tracking information not allocated for pointer at 0x%x. (%s:%d)", get_user_pointer_from_header_const(header), file, line);

    if (header->signature == k_pointer_header_signature_disposed)
    {
        error = "Pointer has been disposed.";
    }
    else if (header->signature != k_pointer_header_signature)
    {
        error = "Signature is incorrect.";
    }
    else if (checksum_header(header) != header->checksum)
    {
        error = "Checksum is incorrect.";
    }

    vassert_tag_debug_untracked_jul_11_2011(511, error == NULL, "Invalid pointer: %s header: 0x%x signature: 0x%x size: 0x%x (accessed by %s:%d)", error, header, header->signature, header->size, file, line);
};

void check_pointer(void const * pointer, char const * file, long line)
{
    mangled_ppc("?check_pointer@@YAXPBXPBDJ@Z");

    s_pointer_header const * header = get_header_from_user_pointer_const(pointer);
    s_pointer_trailer const * trailer = get_trailer_from_header_const(header);

    assert_tag_debug_untracked_jul_11_2011(523, header->tracking!=NULL);
    vassert_tag_debug_untracked_jul_11_2011(527, trailer->signature == k_pointer_trailer_signature, "Pointer allocated at %s, %d has overrun the end of its buffer. (Size: %d) (%s:%d)", header->tracking->file, header->tracking->line, header->size, file, line);
};

void check_nonheap_resource(s_pointer_header const * header, char const * file, long line)
{
    mangled_ppc("?check_nonheap_resource@@YAXPBUs_pointer_header@@PBDJ@Z");

    if (header->nonheap_resource != NULL)
    {
        if (g_nonheap_hash_table.is_created() && header->nonheap_resource != k_unspecified_nonheap_resource)
        {
            s_pointer_header * found_header = NULL;
            void const * found_nonheap_resource = g_nonheap_hash_table.find(header->nonheap_resource, &found_header);
            if (found_nonheap_resource != NULL)
            {
                assert_tag_debug_untracked_jul_11_2011(550, found_nonheap_resource==header->nonheap_resource);
            }
            else
            {
                dassert_tag_debug_untracked_jul_11_2011(558, header->freed_externally_on_exit, "nonheap resources not in the hash table must be implicitly-free-on-exit");
            }
        }
        else
        {
            dassert_tag_debug_untracked_jul_11_2011(564, header->freed_externally_on_exit, "nonheap resources not in the hash table must be implicitly-free-on-exit");
        }
    }
};

void build_header_and_trailer(void * user_pointer, unsigned int size, long alignment_bits, long offset, e_debug_memory_flags flags, char const * file, long line, long type_identifier, unsigned int actual_size, char const * type, char const * subtype, char const * name, void const * nonheap_resource, bool freed_externally_on_exit)
{
    mangled_ppc("?build_header_and_trailer@@YAXPAXIJJW4e_debug_memory_flags@@PBDJJI222PBX_N@Z");

    assert_tag_debug_untracked_jul_11_2011(585, IN_RANGE_INCLUSIVE(alignment_bits, 0, k_maximum_alignment_bits));
    assert_tag_debug_untracked_jul_11_2011(586, IN_RANGE_INCLUSIVE(size, 0, k_maximum_pointer_size));
    dassert_tag_debug_untracked_jul_11_2011(588, thread_can_use_debug_memory(), "guess what? the debug memory manager isn't thread safe!!");

    s_header_tracking_info * tracking = find_or_allocate_tracking_info(file, line, type, subtype, name);
    assert_tag_debug_untracked_jul_11_2011(594, tracking);

    s_pointer_header * header = get_header_from_user_pointer(user_pointer);
    header->signature = k_pointer_header_signature;
    header->size = size;
    header->alignment_bits = alignment_bits;
    header->offset = offset;
    header->identifier = g_debug_memory_globals.identifier++;
    header->tracking = tracking;
    header->tracking->file = file;
    header->tracking->line = line;
    header->tracking->type = type;
    header->tracking->subtype = subtype;
    header->tracking->name = name;
    header->nonheap_resource = nonheap_resource;
    header->type_identifier = type_identifier;
    header->actual_size_offset = actual_size - size;
    assert_tag_debug_untracked_jul_11_2011(612, static_cast<size_t>(header->actual_size_offset)==(actual_size-size));
    header->exclude_from_minidump = TEST_BIT(flags, _debug_memory_exclude_from_minidump_bit);
    header->freed_externally_on_exit = freed_externally_on_exit;

    {
        s_base_memory_information information;
        base_memory_information_get(&information);
        header->total_free_at_allocation = information.free;
    }

    s_pointer_trailer * trailer = get_trailer_from_header(header);
    trailer->signature = k_pointer_trailer_signature;

    queue_header(header);
};

// $TODO nonmatching: target leaf uses an unrelocated absolute address for g_debug_memory_globals (only diff)
s_pointer_header const * get_heap_queue(void)
{
    mangled_ppc("?get_heap_queue@@YAPBUs_pointer_header@@XZ");

    return g_debug_memory_globals.header_queue;
};

// $TODO nonmatching: target leaf uses an unrelocated absolute address for g_debug_memory_globals (only diff)
s_pointer_header const * get_free_queue(void)
{
    mangled_ppc("?get_free_queue@@YAPBUs_pointer_header@@XZ");

    return g_debug_memory_globals.freed_header_queue;
};

void queue_header(s_pointer_header * header)
{
    mangled_ppc("?queue_header@@YAXPAUs_pointer_header@@@Z");

    debug_memory_initialize_static();

    if (header->identifier == g_debug_memory_globals.break_on_alloc_identifier && assert_is_debugger_present())
    {
        __debugbreak();
    }

    if (g_debug_memory_globals.header_queue == NULL || header < g_debug_memory_globals.valid_header_range_bottom)
    {
        g_debug_memory_globals.valid_header_range_bottom = header;
    }

    if (g_debug_memory_globals.header_queue == NULL || header > g_debug_memory_globals.valid_header_range_top)
    {
        g_debug_memory_globals.valid_header_range_top = header;
    }

    header->next = g_debug_memory_globals.header_queue;
    if (header->next != NULL)
    {
        header->next->previous = header;
        header->next->checksum = checksum_header(header->next);
    }

    header->previous = NULL;
    g_debug_memory_globals.header_queue = header;
    header->checksum = checksum_header(header);
};

void dequeue_header(s_pointer_header * header, char const * file, long line)
{
    mangled_ppc("?dequeue_header@@YAXPAUs_pointer_header@@PBDJ@Z");

    if (header->identifier == g_debug_memory_globals.break_on_free_identifier && assert_is_debugger_present())
    {
        __debugbreak();
    }

    dassert_tag_debug_untracked_jul_11_2011(706, !g_debug_memory_globals.disposed, "memory is being freed after the manager was disposed");

    if (header->nonheap_resource != NULL)
    {
        if (header->freed_externally_on_exit)
        {
        }
        else
        {
            bool success = g_nonheap_hash_table.remove(header->nonheap_resource);
            assert_tag_debug_untracked_jul_11_2011(742, success);
        }
    }

    if (header == g_debug_memory_globals.header_queue)
    {
        g_debug_memory_globals.header_queue = header->next;
        if (g_debug_memory_globals.header_queue != NULL)
        {
            g_debug_memory_globals.header_queue->previous = NULL;
            g_debug_memory_globals.header_queue->checksum = checksum_header(g_debug_memory_globals.header_queue);
        }
    }
    else
    {
        s_pointer_header * previous = header->previous;
        assert_tag_debug_untracked_jul_11_2011(760, previous!=NULL);

        previous->next = header->next;
        previous->checksum = checksum_header(previous);
        if (previous->next != NULL)
        {
            previous->next->previous = previous;
            previous->next->checksum = checksum_header(previous->next);
        }
    }

    header->signature = k_pointer_header_signature_disposed;
};

bool query_possible_header(s_pointer_header const * header)
{
    mangled_ppc("?query_possible_header@@YA_NPBUs_pointer_header@@@Z");

    return header->signature == k_pointer_header_signature && checksum_header(header) == header->checksum;
};

s_pointer_header * query_nonheap_header(void const * nonheap_resource)
{
    mangled_ppc("?query_nonheap_header@@YAPAUs_pointer_header@@PBX@Z");

    s_pointer_header * result = NULL;

    assert_tag_debug_untracked_jul_11_2011(791, nonheap_resource!=NULL);
    assert_tag_debug_untracked_jul_11_2011(792, nonheap_resource!=k_unspecified_nonheap_resource);

    for (s_pointer_header * header = g_debug_memory_globals.header_queue; header != NULL; header = header->next)
    {
        if (header->nonheap_resource == nonheap_resource)
        {
            result = header;
            break;
        }
    }

    return result;
};

unsigned long checksum_header(s_pointer_header const * header)
{
    mangled_ppc("?checksum_header@@YAKPBUs_pointer_header@@@Z");

    unsigned long checksum = k_default_header_checksum;
    if (g_debug_memory_globals.checksum_function != NULL)
    {
        checksum = g_debug_memory_globals.checksum_function(header, OFFSETOF(s_pointer_header, checksum));
    }

    return checksum;
};

void force_release_header(s_pointer_header * header, char const * file, long line)
{
    mangled_ppc("?force_release_header@@YAXPAUs_pointer_header@@PBDJ@Z");

    assert_tag_debug_untracked_jul_11_2011(829, header);

    check_header(header, file, line);
    check_pointer(get_user_pointer_from_header(header), file, line);
    check_nonheap_resource(header, file, line);

    if (header->nonheap_resource != NULL)
    {
        if (g_debug_memory_globals.current_nonheap_size >= header->size)
        {
            g_debug_memory_globals.current_nonheap_size -= header->size;
        }
        else
        {
            g_debug_memory_globals.current_nonheap_size = 0;
            event(_event_error, "system:debug_memory: nonheap size underflow in force_release_header, someone probably tracked a nonheap resource address twice");
        }
    }
    else
    {
        if (g_debug_memory_globals.current_heap_size >= header->size)
        {
            g_debug_memory_globals.current_heap_size -= header->size;
        }
        else
        {
            g_debug_memory_globals.current_heap_size = 0;
            event(_event_error, "system:debug_memory: heap size underflow in force_release_header, something is badly wrong");
        }
    }

    dequeue_header(header, file, line);
    base_free(header);
};

void track_heap_allocation_size(unsigned int old_size, unsigned int new_size)
{
    mangled_ppc("?track_heap_allocation_size@@YAXII@Z");

    g_debug_memory_globals.current_heap_size += new_size - old_size;
    g_debug_memory_globals.largest_heap_size = int_max(g_debug_memory_globals.largest_heap_size, g_debug_memory_globals.current_heap_size);
};

void track_nonheap_allocation_size(unsigned int old_size, unsigned int new_size)
{
    mangled_ppc("?track_nonheap_allocation_size@@YAXII@Z");

    g_debug_memory_globals.current_nonheap_size += new_size - old_size;
    g_debug_memory_globals.largest_nonheap_size = int_max(g_debug_memory_globals.largest_nonheap_size, g_debug_memory_globals.current_nonheap_size);
};

void pretrack_nonheap_allocation_size(unsigned int old_size, unsigned int new_size)
{
    mangled_ppc("?pretrack_nonheap_allocation_size@@YAXII@Z");

    track_nonheap_allocation_size(old_size, new_size);
    g_debug_memory_globals.pretracked_nonheap_size += new_size - old_size;
};

char const * make_constant_string(char const * string)
{
    mangled_ppc("?make_constant_string@@YAPBDPBD@Z");

    char const * result = NULL;

    if (string == NULL || system_executable_is_address_constant_and_static(string))
    {
        result = string;
    }
    else
    {
        if (g_debug_memory_constant_string_pool != NULL)
        {
            result = static_cast<char const *>(constant_pool_add(g_debug_memory_constant_string_pool, string));
            if (result != NULL)
            {
                assert_tag_debug_untracked_jul_11_2011(918, strcmp(string, result)==0);
            }
            else
            {
                dassert_tag_debug_untracked_jul_11_2011(922, false, "debug constant string pool is out of memory! (increase k_maximum_constant_string_size)");
            }
        }

        if (result == NULL)
        {
            result = "???";
        }
    }

    return result;
};

char const * safe_printable_string(char const * string)
{
    mangled_ppc("?safe_printable_string@@YAPBDPBD@Z");

    char const * result = "(unknown)";

    if (string == NULL)
    {
        result = "(null)";
    }
    else if (system_executable_is_address_constant_and_static(string))
    {
        result = string;
    }
    else if (g_debug_memory_constant_string_pool != NULL && constant_pool_contains(g_debug_memory_constant_string_pool, string))
    {
        result = string;
    }

    return result;
};

char const * strip_source_directory(char const * file)
{
    mangled_ppc("?strip_source_directory@@YAPBDPBD@Z");

    char const * result = file;

    if (file != NULL)
    {
        char const * source_directory = csstristr(file, k_source_directory_string);
        if (source_directory != NULL)
        {
            result = source_directory + strlen(k_source_directory_string);
        }
    }

    return result;
};

void debug_memory_free_emergency_reserve(void)
{
    mangled_ppc("?debug_memory_free_emergency_reserve@@YAXXZ");

    if (g_debug_memory_globals.emergency_reserve != NULL)
    {
        base_free(g_debug_memory_globals.emergency_reserve);
        g_debug_memory_globals.emergency_reserve = NULL;
    }
};

// $TODO nonmatching: target leaf uses unrelocated absolute addresses and tls offset 0x4A0 (only diffs)
bool thread_can_use_debug_memory(void)
{
    mangled_ppc("?thread_can_use_debug_memory@@YA_NXZ");

    bool can_use = true;

    if (g_debug_memory_globals.initialized_for_exit)
    {
    }
    else if (!g_debug_memory_manager_initialized)
    {
    }
    else
    {
        can_use = g_thread_can_use_debug_memory;
    }

    return can_use;
};

bool debug_pointer_valid(void * pointer)
{
    mangled_ppc("?debug_pointer_valid@@YA_NPAX@Z");

    s_pointer_header * header = get_header_from_user_pointer(pointer);
    bool valid = false;

    if (g_debug_memory_globals.header_queue != NULL && header >= g_debug_memory_globals.valid_header_range_bottom && header <= g_debug_memory_globals.valid_header_range_top && header->signature == k_pointer_header_signature)
    {
        valid = true;
    }

    return valid;
};

unsigned int debug_get_used_memory_size(void * pointer, char const * file, long line)
{
    mangled_ppc("?debug_get_used_memory_size@@YAIPAXPBDJ@Z");

    s_pointer_header * header = get_header_from_user_pointer(pointer);

    file = strip_source_directory(file);
    check_debug_memory_manager(file, line);
    check_header(header, file, line);
    check_pointer(pointer, file, line);
    check_nonheap_resource(header, file, line);

    assert_tag_debug_untracked_jul_11_2011(1048, base_memory_get_used_memory_size(get_base_pointer_from_header(header))>=header->offset+sizeof(s_pointer_header)+header->size+sizeof(s_pointer_trailer));

    return header->size;
};

unsigned int debug_get_actual_memory_size(void * pointer, char const * file, long line)
{
    mangled_ppc("?debug_get_actual_memory_size@@YAIPAXPBDJ@Z");

    s_pointer_header * header = get_header_from_user_pointer(pointer);

    file = strip_source_directory(file);
    check_debug_memory_manager(file, line);
    check_header(header, file, line);
    check_pointer(pointer, file, line);
    check_nonheap_resource(header, file, line);

    assert_tag_debug_untracked_jul_11_2011(1067, base_memory_get_used_memory_size(get_base_pointer_from_header(header))>=header->offset+sizeof(s_pointer_header)+header->size+sizeof(s_pointer_trailer));

    return header_get_actual_size(header);
};

void * c_debug_memory_internal_allocation::allocate(unsigned int size, char const * file, long line, char const * type, char const * subtype, char const * name)
{
    mangled_ppc("?allocate@c_debug_memory_internal_allocation@@UAAPAXIPBDJ000@Z");

    void * pointer = base_malloc(size);
    if (pointer != NULL)
    {
        debug_track_nonheap_alloc(pointer, size, static_cast<e_debug_memory_flags>(FLAG(_debug_memory_free_implicitly_on_exit_bit)), file, line, NONE, type, subtype, name);
    }

    return pointer;
};

void c_debug_memory_internal_allocation::deallocate(void * pointer, char const * file, long line)
{
    mangled_ppc("?deallocate@c_debug_memory_internal_allocation@@UAAXPAXPBDJ@Z");

    base_free(pointer);
};

unsigned long nonheap_hash_function(void const * key)
{
    mangled_ppc("?nonheap_hash_function@@YAKPBX@Z");

    return address_from_pointer(key);
};

bool nonheap_compare_function(void const * key1, void const * key2)
{
    mangled_ppc("?nonheap_compare_function@@YA_NPBX0@Z");

    bool equal = key1 == key2;

    return equal;
};

s_header_tracking_info * find_or_allocate_tracking_info(char const * file, long line, char const * type, char const * subtype, char const * name)
{
    mangled_ppc("?find_or_allocate_tracking_info@@YAPAUs_header_tracking_info@@PBDJ000@Z");

    s_header_tracking_info * info = NULL;

    if (!g_tracking_info_hash_data_initialized)
    {
        g_tracking_info_hash_data.clear_all();
        g_tracking_info_hash_data_initialized = true;
    }

    long key_a = (file == NULL ? 0 : get_constant_string_key(file) * line) + (type == NULL ? 0 : get_constant_string_key(type));
    long key_b = subtype == NULL ? 0 : get_constant_string_key(subtype);
    long key_c = name == NULL ? 0 : get_constant_string_key(name);

    long hash_index = c_tracking_info_hash_table::find_entry(&g_tracking_info_hash_data, key_a, key_b, key_c);
    if (hash_index != c_tracking_info_hash_table::k_hash_invalid)
    {
        s_header_tracking_info ** info_pointer = g_tracking_info_hash_data.get_element(hash_index);
        assert_tag_debug_untracked_jul_11_2011(1163, info_pointer);

        info = *info_pointer;
    }
    else
    {
        hash_index = c_tracking_info_hash_table::add_entry(&g_tracking_info_hash_data, key_a, key_b, key_c);
        dassert_tag_debug_untracked_jul_11_2011(1172, hash_index != c_tracking_info_hash_table::k_hash_invalid, "ran out of hash tracking infos - increase k_maximum_tracking_infos");

        s_header_tracking_info ** info_pointer = g_tracking_info_hash_data.get_element(hash_index);
        assert_tag_debug_untracked_jul_11_2011(1175, info_pointer);

        info = static_cast<s_header_tracking_info *>(base_malloc(sizeof(s_header_tracking_info)));
        assert_tag_debug_untracked_jul_11_2011(1178, info);

        *info_pointer = info;
        info->file = file;
        info->line = line;
        info->type = type;
        info->subtype = subtype;
        info->name = name;
    }

    assert_tag_debug_untracked_jul_11_2011(1188, info);

    return info;
};

long get_constant_string_key(char const * string)
{
    mangled_ppc("?get_constant_string_key@@YAJPBD@Z");

    return address_from_pointer(string);
};

void dispose_tracking_info(void)
{
    mangled_ppc("?dispose_tracking_info@@YAXXZ");

    if (g_tracking_info_hash_data_initialized)
    {
        for (long index = c_tracking_info_hash_table::iterator_begin(&g_tracking_info_hash_data); index != c_tracking_info_hash_table::k_hash_invalid; index = c_tracking_info_hash_table::iterator_next(&g_tracking_info_hash_data, index))
        {
            s_header_tracking_info ** info_pointer = g_tracking_info_hash_data.get_element(index);
            assert_tag_debug_untracked_jul_11_2011(1204, info_pointer);
            assert_tag_debug_untracked_jul_11_2011(1205, *info_pointer);

            base_free(*info_pointer);
        }

        g_tracking_info_hash_data.clear_all();
    }
};

void set_checksum_function(debug_memory_checksum_function * const checksum_function)
{
    mangled_ppc("?set_checksum_function@@YAXQ6AKPBXI@Z@Z");

    if (g_debug_memory_globals.checksum_function != checksum_function)
    {
        g_debug_memory_globals.checksum_function = checksum_function;

        for (s_pointer_header * header = g_debug_memory_globals.header_queue; header != NULL; header = header->next)
        {
            header->checksum = checksum_header(header);
        }
    }
};

// $TODO nonmatching: target leaf uses an unrelocated absolute address for g_debug_memory_globals (only diff)
void set_local_random_function(debug_memory_random_function * const local_random_function)
{
    mangled_ppc("?set_local_random_function@@YAXQ6AGXZ@Z");

    g_debug_memory_globals.local_random_function = local_random_function;
};

c_debug_memory_initializer::c_debug_memory_initializer(void)
{
    mangled_ppc("??0c_debug_memory_initializer@@QAA@XZ");

    debug_memory_initialize_static();
};

