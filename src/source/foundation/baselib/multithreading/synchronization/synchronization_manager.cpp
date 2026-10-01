#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\foundation\\baselib\\multithreading\\synchronization\\synchronization_manager.cpp"
/* ---------- headers */

#include "foundation\baselib\multithreading\synchronization\synchronization_manager.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_macros.h"
#include "foundation\baselib\datatypes\static_array.h"
#include "foundation\baselib\datatypes\static_stack.h"
#include "foundation\baselib\files\simple_file.h"
#include "foundation\baselib\multithreading\primitives\synchronized_array.h"
#include "foundation\baselib\multithreading\synchronization\busy_wait.h"
#include "foundation\baselib\multithreading\synchronization\critical_section_windows.h"
#include "foundation\baselib\multithreading\synchronization\lock_hierarchy.h"
#include "foundation\baselib\multithreading\synchronization\lock_tracker.h"
#include "foundation\baselib\multithreading\synchronization\mutex_windows.h"
#include "foundation\baselib\multithreading\synchronization\semaphore_windows.h"
#include "foundation\baselib\multithreading\synchronization\synchronization_event_windows.h"
#include "foundation\baselib\multithreading\synchronization\synchronization_object.h"
#include "foundation\baselib\multithreading\synchronization\virtual_guard_block.h"
#include "omaha\cseries\cseries.h"

#include <xtl.h>

/* ---------- constants */

#define VALID_HANDLE(handle) ((handle) != NULL && (handle) != INVALID_HANDLE_VALUE)

long const k_maximum_critical_sections = 100;
long const k_maximum_mutexes = 4;
long const k_maximum_synchronization_events = 10;
long const k_maximum_semaphores = 13;
long const k_maximum_busy_waits = 10;
long const k_maximum_virtual_guard_blocks = 3;

/* ---------- definitions */

struct s_critical_section_declaration
{
    long synchronization_group_index; // 0x0
    long lock_node_index; // 0x4
    s_critical_section_definition definition; // 0x8
};
static_assert(sizeof(s_critical_section_declaration) == 0x14, "s_critical_section_declaration");

struct s_mutex_declaration
{
    long synchronization_group_index; // 0x0
    long lock_node_index; // 0x4
    s_mutex_definition definition; // 0x8
};
static_assert(sizeof(s_mutex_declaration) == 0x10, "s_mutex_declaration");

struct s_event_declaration
{
    long synchronization_group_index; // 0x0
    s_synchronization_event_definition definition; // 0x4
};
static_assert(sizeof(s_event_declaration) == 0xC, "s_event_declaration");

struct s_semaphore_declaration
{
    long synchronization_group_index; // 0x0
    long lock_node_index; // 0x4
    s_semaphore_definition definition; // 0x8
};
static_assert(sizeof(s_semaphore_declaration) == 0x18, "s_semaphore_declaration");

struct s_busy_wait_declaration
{
    long synchronization_group_index; // 0x0
    s_busy_wait_definition definition; // 0x4
};
static_assert(sizeof(s_busy_wait_declaration) == 0x8, "s_busy_wait_declaration");

struct s_virtual_guard_block_declaration
{
    long synchronization_group_index; // 0x0
    long lock_node_index; // 0x4
    s_virtual_guard_block_definition definition; // 0x8
};
static_assert(sizeof(s_virtual_guard_block_declaration) == 0xC, "s_virtual_guard_block_declaration");

struct s_synchronization_globals
{
    bool initialized; // 0x0
    long group_count; // 0x4
    unsigned long group_created_mask; // 0x8
    c_lock_hierarchy lock_hierarchy; // 0xC
    c_allocation_interface * allocator; // 0x18
    c_static_stack<s_critical_section_declaration, k_maximum_critical_sections> critical_sections; // 0x1C
    c_static_stack<s_mutex_declaration, k_maximum_mutexes> mutexes; // 0x7F0
    c_static_stack<s_event_declaration, k_maximum_synchronization_events> events; // 0x834
    c_static_stack<s_semaphore_declaration, k_maximum_semaphores> semaphores; // 0x8B0
    c_static_stack<s_busy_wait_declaration, k_maximum_busy_waits> busy_waits; // 0x9EC
    c_static_stack<s_virtual_guard_block_declaration, k_maximum_virtual_guard_blocks> virtual_guard_blocks; // 0xA40
    s_static_array<c_critical_section_instance, k_maximum_critical_sections> critical_section_instances; // 0xA68
    s_static_array<c_synchronization_handle, k_maximum_mutexes> mutex_instances; // 0x1D28
    s_static_array<c_synchronization_handle, k_maximum_synchronization_events> event_instances; // 0x1D88
    s_static_array<c_semaphore_instance, k_maximum_semaphores> semaphore_instances; // 0x1E78
    s_static_array<c_synchronization_object, k_maximum_virtual_guard_blocks> virtual_guard_block_instances; // 0x2490
    c_synchronized_bitvector<k_synchronization_maximum_registered_threads> declared_thread_vector; // 0x24CC
    c_synchronized_bitvector<k_synchronization_maximum_registered_threads> registered_thread_vector; // 0x24D0
    s_static_array<c_lock_tracker, k_synchronization_maximum_registered_threads> lock_trackers; // 0x24D4
};
static_assert(sizeof(s_synchronization_globals) == 0x53E8, "s_synchronization_globals");

/* ---------- prototypes */

long create_lock_node_index(long synchronization_group_index, unsigned long object_id, char const * name);

/* ---------- globals */

extern char const * const k_hierarchy_dump_text_filename = "lock_hierarchy.txt";
extern char const * const k_hierarchy_dump_graphviz_filename = "lock_hierarchy.dot";
s_synchronization_globals g_synchronization_globals;
static __declspec(thread) bool g_synchronization_thread_registered;
static __declspec(thread) long g_synchronization_thread_index;
__declspec(thread) c_lock_tracker * g_synchronization_lock_tracker;

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// public: static long const s_static_array<class c_critical_section_instance, 100>::k_element_count; // "?k_element_count@?$s_static_array@Vc_critical_section_instance@@$0GE@@@2JB"
// public: static long const s_static_array<class c_synchronization_handle, 4>::k_element_count; // "?k_element_count@?$s_static_array@Vc_synchronization_handle@@$03@@2JB"
// public: static long const s_static_array<class c_synchronization_handle, 10>::k_element_count; // "?k_element_count@?$s_static_array@Vc_synchronization_handle@@$09@@2JB"
// public: static long const s_static_array<class c_semaphore_instance, 13>::k_element_count; // "?k_element_count@?$s_static_array@Vc_semaphore_instance@@$0N@@@2JB"
// public: static long const s_static_array<class c_synchronization_object, 3>::k_element_count; // "?k_element_count@?$s_static_array@Vc_synchronization_object@@$02@@2JB"
// public: static long const s_static_array<class c_lock_tracker, 23>::k_element_count; // "?k_element_count@?$s_static_array@Vc_lock_tracker@@$0BH@@@2JB"
// char const *const k_hierarchy_dump_text_filename; // "?k_hierarchy_dump_text_filename@@3PBDB"
// char const *const k_hierarchy_dump_graphviz_filename; // "?k_hierarchy_dump_graphviz_filename@@3PBDB"
// struct s_synchronization_globals g_synchronization_globals; // "?g_synchronization_globals@@3Us_synchronization_globals@@A"
// class c_lock_tracker *g_synchronization_lock_tracker; // "?g_synchronization_lock_tracker@@3PAVc_lock_tracker@@A"

// void synchronization_manager_initialize(class c_allocation_interface *);
// void synchronization_manager_dispose(void);
// bool synchronization_manager_initialized(void);
// long synchronization_declare_object_group(void);
// void synchronization_create_object_group(long);
// void synchronization_destroy_object_group(long);
// bool synchronization_object_group_created(long);
// void synchronization_declare_threads_explicit(long const *, long);
// void synchronization_declare_threads(long, long *);
// void synchronization_register_thread(long);
// void synchronization_unregister_thread(long);
// bool synchronization_is_thread_registered(void);
// long synchronization_get_maximum_declared_threads(void);
// long synchronization_get_declared_threads(void);
// long synchronization_get_available_thread_declarations(void);
// void synchronization_release_objects_owned_by_thread(void);
// void synchronization_release_crash_required_objects_owned_by_thread(void);
// void synchronization_enable_lock_enforcement(bool);
// long synchronization_get_current_thread_index(void);
// class c_lock_hierarchy * synchronization_get_lock_hierarchy(void);
// public: bool c_lock_hierarchy::is_finalized(void) const;
// class c_lock_hierarchy const * synchronization_get_lock_hierarchy_const(void);
// unsigned long synchronization_declare_critical_section(long, struct s_critical_section_definition const *);
// unsigned long synchronization_declare_mutex(long, struct s_mutex_definition const *);
// unsigned long synchronization_declare_synchronization_event(long, struct s_synchronization_event_definition const *);
// unsigned long synchronization_declare_semaphore(long, struct s_semaphore_definition const *);
// unsigned long synchronization_declare_busy_wait(long, struct s_busy_wait_definition const *);
// unsigned long synchronization_declare_virtual_guard_block(long, struct s_virtual_guard_block_definition const *);
// char const * synchronization_object_get_name(unsigned long);
// long synchronization_object_get_lock_node_index(unsigned long);
// class c_synchronization_object * synchronization_get_object(unsigned long);
// class c_critical_section_instance * synchronization_get_critical_section(unsigned long);
// class c_synchronization_handle * synchronization_get_mutex(unsigned long);
// class c_synchronization_handle * synchronization_get_synchronization_event(unsigned long);
// class c_semaphore_instance * synchronization_get_semaphore(unsigned long);
// class c_synchronization_object * synchronization_get_virtual_guard_block(unsigned long);
// struct s_synchronization_event_definition const * synchronization_get_synchronization_event_definition(unsigned long);
// struct s_semaphore_definition const * synchronization_get_semaphore_definition(unsigned long);
// bool wait_for_single_object_internal(void *, long);
// public: c_synchronization_block_timer::c_synchronization_block_timer(unsigned long, long);
// public: c_synchronization_block_timer::~c_synchronization_block_timer(void);
// long create_lock_node_index(long, unsigned long, char const *);
// public: bool c_static_stack<struct s_critical_section_declaration, 100>::valid(long) const;
// public: bool c_static_stack<struct s_critical_section_declaration, 100>::full(void) const;
// public: long c_static_stack<struct s_critical_section_declaration, 100>::count(void) const;
// public: void c_static_stack<struct s_critical_section_declaration, 100>::clear(void);
// public: void c_static_stack<struct s_critical_section_declaration, 100>::resize(long);
// public: long c_static_stack<struct s_critical_section_declaration, 100>::push(void);
// public: struct s_critical_section_declaration & c_static_stack<struct s_critical_section_declaration, 100>::operator[](long);
// public: bool c_static_stack<struct s_mutex_declaration, 4>::valid(long) const;
// public: bool c_static_stack<struct s_mutex_declaration, 4>::full(void) const;
// public: long c_static_stack<struct s_mutex_declaration, 4>::count(void) const;
// public: void c_static_stack<struct s_mutex_declaration, 4>::clear(void);
// public: void c_static_stack<struct s_mutex_declaration, 4>::resize(long);
// public: long c_static_stack<struct s_mutex_declaration, 4>::push(void);
// public: struct s_mutex_declaration & c_static_stack<struct s_mutex_declaration, 4>::operator[](long);
// public: bool c_static_stack<struct s_event_declaration, 10>::valid(long) const;
// public: bool c_static_stack<struct s_event_declaration, 10>::full(void) const;
// public: long c_static_stack<struct s_event_declaration, 10>::count(void) const;
// public: void c_static_stack<struct s_event_declaration, 10>::clear(void);
// public: void c_static_stack<struct s_event_declaration, 10>::resize(long);
// public: long c_static_stack<struct s_event_declaration, 10>::push(void);
// public: struct s_event_declaration & c_static_stack<struct s_event_declaration, 10>::operator[](long);
// public: bool c_static_stack<struct s_semaphore_declaration, 13>::valid(long) const;
// public: bool c_static_stack<struct s_semaphore_declaration, 13>::full(void) const;
// public: long c_static_stack<struct s_semaphore_declaration, 13>::count(void) const;
// public: void c_static_stack<struct s_semaphore_declaration, 13>::clear(void);
// public: void c_static_stack<struct s_semaphore_declaration, 13>::resize(long);
// public: long c_static_stack<struct s_semaphore_declaration, 13>::push(void);
// public: struct s_semaphore_declaration & c_static_stack<struct s_semaphore_declaration, 13>::operator[](long);
// public: bool c_static_stack<struct s_busy_wait_declaration, 10>::valid(long) const;
// public: bool c_static_stack<struct s_busy_wait_declaration, 10>::full(void) const;
// public: long c_static_stack<struct s_busy_wait_declaration, 10>::count(void) const;
// public: void c_static_stack<struct s_busy_wait_declaration, 10>::clear(void);
// public: void c_static_stack<struct s_busy_wait_declaration, 10>::resize(long);
// public: long c_static_stack<struct s_busy_wait_declaration, 10>::push(void);
// public: struct s_busy_wait_declaration & c_static_stack<struct s_busy_wait_declaration, 10>::operator[](long);
// public: bool c_static_stack<struct s_virtual_guard_block_declaration, 3>::valid(long) const;
// public: bool c_static_stack<struct s_virtual_guard_block_declaration, 3>::full(void) const;
// public: long c_static_stack<struct s_virtual_guard_block_declaration, 3>::count(void) const;
// public: void c_static_stack<struct s_virtual_guard_block_declaration, 3>::clear(void);
// public: void c_static_stack<struct s_virtual_guard_block_declaration, 3>::resize(long);
// public: long c_static_stack<struct s_virtual_guard_block_declaration, 3>::push(void);
// public: struct s_virtual_guard_block_declaration & c_static_stack<struct s_virtual_guard_block_declaration, 3>::operator[](long);
// public: void c_synchronized_bitvector<23>::clear(void);
// public: bool c_synchronized_bitvector<23>::test_bit(long) const;
// public: void c_synchronized_bitvector<23>::set_bit(long, bool);
// public: bool c_static_stack<struct s_critical_section_declaration, 100>::valid(void) const;
// public: bool c_static_stack<struct s_mutex_declaration, 4>::valid(void) const;
// public: bool c_static_stack<struct s_event_declaration, 10>::valid(void) const;
// public: bool c_static_stack<struct s_semaphore_declaration, 13>::valid(void) const;
// public: bool c_static_stack<struct s_busy_wait_declaration, 10>::valid(void) const;
// public: bool c_static_stack<struct s_virtual_guard_block_declaration, 3>::valid(void) const;
// public: class c_synchronized_int32& c_synchronized_int32_array<1>::get_member(long);
// public: class c_synchronized_int32const & c_synchronized_int32_array<1>::get_member_const(long) const;
// public: void c_synchronized_int32_array<1>::set_array(long);
// public: class c_critical_section_instance & s_static_array<class c_critical_section_instance, 100>::operator[]<long>(long);
// public: class c_synchronization_handle & s_static_array<class c_synchronization_handle, 4>::operator[]<long>(long);
// public: class c_synchronization_handle & s_static_array<class c_synchronization_handle, 10>::operator[]<long>(long);
// public: class c_semaphore_instance & s_static_array<class c_semaphore_instance, 13>::operator[]<long>(long);
// public: class c_synchronization_object & s_static_array<class c_synchronization_object, 3>::operator[]<long>(long);
// public: class c_lock_tracker & s_static_array<class c_lock_tracker, 23>::operator[]<long>(long);
// public: static bool s_static_array<class c_critical_section_instance, 100>::valid<long>(long);
// public: static bool s_static_array<class c_synchronization_handle, 4>::valid<long>(long);
// public: static bool s_static_array<class c_synchronization_handle, 10>::valid<long>(long);
// public: static bool s_static_array<class c_semaphore_instance, 13>::valid<long>(long);
// public: static bool s_static_array<class c_synchronization_object, 3>::valid<long>(long);
// public: static bool s_static_array<class c_lock_tracker, 23>::valid<long>(long);
// public: s_synchronization_globals::s_synchronization_globals(void);
// public: c_lock_hierarchy::c_lock_hierarchy(void);
// public: s_static_array<class c_critical_section_instance, 100>::s_static_array<class c_critical_section_instance, 100>(void);
// public: c_critical_section_instance::c_critical_section_instance(void);
// public: c_synchronization_object::c_synchronization_object(void);
// public: s_static_array<class c_synchronization_handle, 4>::s_static_array<class c_synchronization_handle, 4>(void);
// public: c_synchronization_handle::c_synchronization_handle(void);
// public: s_static_array<class c_synchronization_handle, 10>::s_static_array<class c_synchronization_handle, 10>(void);
// public: s_static_array<class c_semaphore_instance, 13>::s_static_array<class c_semaphore_instance, 13>(void);
// public: c_semaphore_instance::c_semaphore_instance(void);
// public: s_static_array<class c_synchronization_object, 3>::s_static_array<class c_synchronization_object, 3>(void);
// public: s_static_array<class c_lock_tracker, 23>::s_static_array<class c_lock_tracker, 23>(void);
// public: c_lock_tracker::c_lock_tracker(void);
// public: c_static_stack<struct s_lock_tracker_entry, 32>::c_static_stack<struct s_lock_tracker_entry, 32>(void);
// public: c_static_stack<struct s_critical_section_declaration, 100>::c_static_stack<struct s_critical_section_declaration, 100>(void);
// public: c_static_stack<struct s_mutex_declaration, 4>::c_static_stack<struct s_mutex_declaration, 4>(void);
// public: c_static_stack<struct s_event_declaration, 10>::c_static_stack<struct s_event_declaration, 10>(void);
// public: c_static_stack<struct s_semaphore_declaration, 13>::c_static_stack<struct s_semaphore_declaration, 13>(void);
// public: c_static_stack<struct s_busy_wait_declaration, 10>::c_static_stack<struct s_busy_wait_declaration, 10>(void);
// public: c_static_stack<struct s_virtual_guard_block_declaration, 3>::c_static_stack<struct s_virtual_guard_block_declaration, 3>(void);
// public: c_synchronized_bitvector<23>::c_synchronized_bitvector<23>(void);
// public: c_synchronized_int32_array<1>::c_synchronized_int32_array<1>(void);
// public: s_synchronization_globals::~s_synchronization_globals(void);
// public: c_lock_hierarchy::~c_lock_hierarchy(void);
// public: s_static_array<class c_critical_section_instance, 100>::~s_static_array<class c_critical_section_instance, 100>(void);
// public: c_critical_section_instance::~c_critical_section_instance(void);
// public: c_synchronization_object::~c_synchronization_object(void);
// public: s_static_array<class c_synchronization_handle, 4>::~s_static_array<class c_synchronization_handle, 4>(void);
// public: c_synchronization_handle::~c_synchronization_handle(void);
// public: s_static_array<class c_synchronization_handle, 10>::~s_static_array<class c_synchronization_handle, 10>(void);
// public: s_static_array<class c_semaphore_instance, 13>::~s_static_array<class c_semaphore_instance, 13>(void);
// public: c_semaphore_instance::~c_semaphore_instance(void);
// public: s_static_array<class c_synchronization_object, 3>::~s_static_array<class c_synchronization_object, 3>(void);
// public: s_static_array<class c_lock_tracker, 23>::~s_static_array<class c_lock_tracker, 23>(void);
// public: c_lock_tracker::~c_lock_tracker(void);
// public: c_synchronized_bitvector<23>::~c_synchronized_bitvector<23>(void);
// public: c_synchronized_int32_array<1>::~c_synchronized_int32_array<1>(void);
// void g_synchronization_globals::`dynamic atexit destructor'(void);

void synchronization_manager_initialize(c_allocation_interface * allocator)
{
    mangled_ppc("?synchronization_manager_initialize@@YAXPAVc_allocation_interface@@@Z");

    assert_tag_debug_untracked_jul_11_2011(151, !g_synchronization_globals.initialized);
    assert_tag_debug_untracked_jul_11_2011(152, allocator);

    g_synchronization_globals.allocator = allocator;
    g_synchronization_globals.lock_hierarchy.initialize(allocator);
    g_synchronization_globals.initialized = true;
};

void synchronization_manager_dispose(void)
{
    mangled_ppc("?synchronization_manager_dispose@@YAXXZ");

    if (g_synchronization_globals.initialized)
    {
        for (long group_index = 0; group_index < g_synchronization_globals.group_count; group_index++)
        {
            synchronization_destroy_object_group(group_index);
        }

        assert_tag_debug_untracked_jul_11_2011(171, g_synchronization_globals.group_created_mask==0);

        g_synchronization_globals.critical_sections.clear();
        g_synchronization_globals.mutexes.clear();
        g_synchronization_globals.events.clear();
        g_synchronization_globals.semaphores.clear();
        g_synchronization_globals.busy_waits.clear();
        g_synchronization_globals.virtual_guard_blocks.clear();
        g_synchronization_globals.group_count = 0;
        g_synchronization_globals.declared_thread_vector.clear();
        g_synchronization_globals.registered_thread_vector.clear();
        g_synchronization_globals.lock_hierarchy.dispose();
        g_synchronization_globals.allocator = NULL;
        g_synchronization_globals.initialized = false;
    }
};

bool synchronization_manager_initialized(void)
{
    mangled_ppc("?synchronization_manager_initialized@@YA_NXZ");

    return g_synchronization_globals.initialized;
};

long synchronization_declare_object_group(void)
{
    mangled_ppc("?synchronization_declare_object_group@@YAJXZ");

    long group_index = g_synchronization_globals.group_count;
    assert_tag_debug_untracked_jul_11_2011(208, VALID_INDEX(group_index, k_synchronization_group_count));
    g_synchronization_globals.group_count++;

    return group_index;
};

void synchronization_create_object_group(long group_index)
{
    mangled_ppc("?synchronization_create_object_group@@YAXJ@Z");

    assert_tag_debug_untracked_jul_11_2011(218, g_synchronization_globals.initialized);
    assert_tag_debug_untracked_jul_11_2011(219, VALID_INDEX(group_index, g_synchronization_globals.group_count));
    assert_tag_debug_untracked_jul_11_2011(220, !TEST_BIT(g_synchronization_globals.group_created_mask, group_index));

    for (long critical_section_index = 0; critical_section_index < g_synchronization_globals.critical_sections.count(); critical_section_index++)
    {
        s_critical_section_declaration & declaration = g_synchronization_globals.critical_sections[critical_section_index];
        if (declaration.synchronization_group_index == group_index)
        {
            unsigned long object_id = SYNCHRONIZATION_OBJECT_ID(group_index, _synchronization_object_critical_section, critical_section_index);
            critical_section_create(&g_synchronization_globals.critical_section_instances[critical_section_index], object_id, declaration.lock_node_index, &declaration.definition);
        }
    }

    for (long mutex_index = 0; mutex_index < g_synchronization_globals.mutexes.count(); mutex_index++)
    {
        s_mutex_declaration & declaration = g_synchronization_globals.mutexes[mutex_index];
        if (declaration.synchronization_group_index == group_index)
        {
            unsigned long object_id = SYNCHRONIZATION_OBJECT_ID(group_index, _synchronization_object_mutex, mutex_index);
            mutex_create(&g_synchronization_globals.mutex_instances[mutex_index], object_id, declaration.lock_node_index, &declaration.definition);
        }
    }

    for (long event_index = 0; event_index < g_synchronization_globals.events.count(); event_index++)
    {
        s_event_declaration & declaration = g_synchronization_globals.events[event_index];
        if (declaration.synchronization_group_index == group_index)
        {
            unsigned long object_id = SYNCHRONIZATION_OBJECT_ID(group_index, _synchronization_object_event, event_index);
            synchronization_event_create(&g_synchronization_globals.event_instances[event_index], object_id, &declaration.definition);
        }
    }

    for (long semaphore_index = 0; semaphore_index < g_synchronization_globals.semaphores.count(); semaphore_index++)
    {
        s_semaphore_declaration & declaration = g_synchronization_globals.semaphores[semaphore_index];
        if (declaration.synchronization_group_index == group_index)
        {
            unsigned long object_id = SYNCHRONIZATION_OBJECT_ID(group_index, _synchronization_object_semaphore, semaphore_index);
            semaphore_create(&g_synchronization_globals.semaphore_instances[semaphore_index], object_id, declaration.lock_node_index, &declaration.definition);
        }
    }

    for (long virtual_guard_block_index = 0; virtual_guard_block_index < g_synchronization_globals.virtual_guard_blocks.count(); virtual_guard_block_index++)
    {
        s_virtual_guard_block_declaration & declaration = g_synchronization_globals.virtual_guard_blocks[virtual_guard_block_index];
        if (declaration.synchronization_group_index == group_index)
        {
            unsigned long object_id = SYNCHRONIZATION_OBJECT_ID(group_index, _synchronization_object_virtual_guard_block, virtual_guard_block_index);
            virtual_guard_block_create(&g_synchronization_globals.virtual_guard_block_instances[virtual_guard_block_index], object_id, declaration.lock_node_index, &declaration.definition);
        }
    }

    SET_BIT(g_synchronization_globals.group_created_mask, group_index, true);

    if (group_index == k_synchronization_group_base)
    {
        g_synchronization_globals.lock_hierarchy.finalize();

        {
            c_simple_file file(k_hierarchy_dump_text_filename);
            if (file.open(4))
            {
                g_synchronization_globals.lock_hierarchy.dump_as_text(&file);
            }
        }

        {
            c_simple_file file(k_hierarchy_dump_graphviz_filename);
            if (file.open(4))
            {
                g_synchronization_globals.lock_hierarchy.dump_as_graphviz(&file);
            }
        }
    }
};

void synchronization_destroy_object_group(long group_index)
{
    mangled_ppc("?synchronization_destroy_object_group@@YAXJ@Z");

    bool const group_created = TEST_BIT(g_synchronization_globals.group_created_mask, group_index);
    assert_tag_debug_untracked_jul_11_2011(326, g_synchronization_globals.initialized);

    if (group_created)
    {
        SET_BIT(g_synchronization_globals.group_created_mask, group_index, false);
    }

    {
        long last_used_index = NONE;
        for (long index = 0; index < g_synchronization_globals.critical_sections.count(); index++)
        {
            if (g_synchronization_globals.critical_sections[index].synchronization_group_index == group_index)
            {
                if (group_created)
                {
                    critical_section_destroy(&g_synchronization_globals.critical_section_instances[index]);
                }
                g_synchronization_globals.critical_sections[index].synchronization_group_index = NONE;
            }
            else
            {
                last_used_index = index;
            }
        }
        g_synchronization_globals.critical_sections.resize(last_used_index + 1);
    }

    {
        long last_used_index = NONE;
        for (long index = 0; index < g_synchronization_globals.mutexes.count(); index++)
        {
            if (g_synchronization_globals.mutexes[index].synchronization_group_index == group_index)
            {
                if (group_created)
                {
                    mutex_destroy(&g_synchronization_globals.mutex_instances[index]);
                }
                g_synchronization_globals.mutexes[index].synchronization_group_index = NONE;
            }
            else
            {
                last_used_index = index;
            }
        }
        g_synchronization_globals.mutexes.resize(last_used_index + 1);
    }

    {
        long last_used_index = NONE;
        for (long index = 0; index < g_synchronization_globals.events.count(); index++)
        {
            if (g_synchronization_globals.events[index].synchronization_group_index == group_index)
            {
                if (group_created)
                {
                    synchronization_event_destroy(&g_synchronization_globals.event_instances[index]);
                }
                g_synchronization_globals.events[index].synchronization_group_index = NONE;
            }
            else
            {
                last_used_index = index;
            }
        }
        g_synchronization_globals.events.resize(last_used_index + 1);
    }

    {
        long last_used_index = NONE;
        for (long index = 0; index < g_synchronization_globals.semaphores.count(); index++)
        {
            if (g_synchronization_globals.semaphores[index].synchronization_group_index == group_index)
            {
                if (group_created)
                {
                    semaphore_destroy(&g_synchronization_globals.semaphore_instances[index]);
                }
                g_synchronization_globals.semaphores[index].synchronization_group_index = NONE;
            }
            else
            {
                last_used_index = index;
            }
        }
        g_synchronization_globals.semaphores.resize(last_used_index + 1);
    }

    {
        long last_used_index = NONE;
        for (long index = 0; index < g_synchronization_globals.busy_waits.count(); index++)
        {
            if (g_synchronization_globals.busy_waits[index].synchronization_group_index == group_index)
            {
                g_synchronization_globals.busy_waits[index].synchronization_group_index = NONE;
            }
            else
            {
                last_used_index = index;
            }
        }
        g_synchronization_globals.busy_waits.resize(last_used_index + 1);
    }

    {
        long last_used_index = NONE;
        for (long index = 0; index < g_synchronization_globals.virtual_guard_blocks.count(); index++)
        {
            if (g_synchronization_globals.virtual_guard_blocks[index].synchronization_group_index == group_index)
            {
                if (group_created)
                {
                    virtual_guard_block_destroy(&g_synchronization_globals.virtual_guard_block_instances[index]);
                }
                g_synchronization_globals.virtual_guard_blocks[index].synchronization_group_index = NONE;
            }
            else
            {
                last_used_index = index;
            }
        }
        g_synchronization_globals.virtual_guard_blocks.resize(last_used_index + 1);
    }

    if (group_index == g_synchronization_globals.group_count - 1)
    {
        g_synchronization_globals.group_count = group_index;
    }
};

bool synchronization_object_group_created(long group_index)
{
    mangled_ppc("?synchronization_object_group_created@@YA_NJ@Z");

    bool created = false;
    if (g_synchronization_globals.initialized)
    {
        assert_tag_debug_untracked_jul_11_2011(485, group_index==k_synchronization_group_base || VALID_INDEX(group_index, g_synchronization_globals.group_count));
        created = TEST_BIT(g_synchronization_globals.group_created_mask, group_index);
    }

    return created;
};

void synchronization_declare_threads_explicit(long const * thread_indices, long thread_count)
{
    mangled_ppc("?synchronization_declare_threads_explicit@@YAXPBJJ@Z");

    assert_tag_debug_untracked_jul_11_2011(498, g_synchronization_globals.initialized);

    for (long index = 0; index < thread_count; index++)
    {
        long thread_index = thread_indices[index];
        assert_tag_debug_untracked_jul_11_2011(504, VALID_INDEX(thread_index, k_synchronization_maximum_registered_threads));
        assert_tag_debug_untracked_jul_11_2011(505, !g_synchronization_globals.declared_thread_vector.test_bit(thread_index));
        g_synchronization_globals.declared_thread_vector.set_bit(thread_index, true);
    }
};

void synchronization_declare_threads(long thread_count, long * out_thread_indices)
{
    mangled_ppc("?synchronization_declare_threads@@YAXJPAJ@Z");

    long declared_count = 0;
    assert_tag_debug_untracked_jul_11_2011(519, g_synchronization_globals.initialized);
    assert_tag_debug_untracked_jul_11_2011(522, thread_count>=1 && thread_count<=k_synchronization_maximum_registered_threads);
    assert_tag_debug_untracked_jul_11_2011(523, out_thread_indices);

    csmemset(out_thread_indices, NONE, sizeof(long) * thread_count);

    for (long thread_index = 0; thread_index < k_synchronization_maximum_registered_threads && declared_count < thread_count; thread_index++)
    {
        if (!g_synchronization_globals.registered_thread_vector.test_bit(thread_index) && !g_synchronization_globals.declared_thread_vector.test_bit(thread_index))
        {
            g_synchronization_globals.declared_thread_vector.set_bit(thread_index, true);
            out_thread_indices[declared_count] = thread_index;
            declared_count++;
        }
    }

    dassert_tag_debug_untracked_jul_11_2011(536, declared_count == thread_count, "overflowed k_synchronization_maximum_registered_threads");
};

void synchronization_register_thread(long thread_index)
{
    mangled_ppc("?synchronization_register_thread@@YAXJ@Z");

    assert_tag_debug_untracked_jul_11_2011(542, g_synchronization_globals.initialized);
    assert_tag_debug_untracked_jul_11_2011(545, VALID_INDEX(thread_index, k_synchronization_maximum_registered_threads));
    dassert_tag_debug_untracked_jul_11_2011(546, !g_synchronization_thread_registered, "tried to register a thread twice with the synchronization manager");
    dassert_tag_debug_untracked_jul_11_2011(547, !g_synchronization_globals.registered_thread_vector.test_bit(thread_index), "this thread index is already registered");

    g_synchronization_thread_index = thread_index;
    g_synchronization_thread_registered = true;
    g_synchronization_globals.registered_thread_vector.set_bit(thread_index, true);
    g_synchronization_globals.lock_trackers[thread_index].initialize(&g_synchronization_globals.lock_hierarchy);
    g_synchronization_lock_tracker = &g_synchronization_globals.lock_trackers[thread_index];
};

void synchronization_unregister_thread(long thread_index)
{
    mangled_ppc("?synchronization_unregister_thread@@YAXJ@Z");

    assert_tag_debug_untracked_jul_11_2011(564, g_synchronization_globals.initialized);
    assert_tag_debug_untracked_jul_11_2011(567, VALID_INDEX(thread_index, k_synchronization_maximum_registered_threads));
    dassert_tag_debug_untracked_jul_11_2011(568, g_synchronization_thread_registered, "unregistering a thread that is not currently registered");
    dassert_tag_debug_untracked_jul_11_2011(569, g_synchronization_thread_index == thread_index, "unregistering the wrong thread index");
    assert_tag_debug_untracked_jul_11_2011(570, g_synchronization_globals.registered_thread_vector.test_bit(thread_index));

    g_synchronization_globals.lock_trackers[thread_index].dispose();
    g_synchronization_lock_tracker = NULL;
    g_synchronization_thread_index = NONE;
    g_synchronization_thread_registered = false;
    g_synchronization_globals.registered_thread_vector.set_bit(thread_index, false);
    g_synchronization_globals.declared_thread_vector.set_bit(thread_index, false);
};

bool synchronization_is_thread_registered(void)
{
    mangled_ppc("?synchronization_is_thread_registered@@YA_NXZ");

    return g_synchronization_thread_registered;
};

long synchronization_get_maximum_declared_threads(void)
{
    mangled_ppc("?synchronization_get_maximum_declared_threads@@YAJXZ");

    return k_synchronization_maximum_registered_threads;
};

long synchronization_get_declared_threads(void)
{
    mangled_ppc("?synchronization_get_declared_threads@@YAJXZ");

    long declared_count = 0;
    assert_tag_debug_untracked_jul_11_2011(602, g_synchronization_globals.initialized);

    for (long thread_index = 0; thread_index < k_synchronization_maximum_registered_threads; thread_index++)
    {
        if (g_synchronization_globals.declared_thread_vector.test_bit(thread_index))
        {
            declared_count++;
        }
    }

    return declared_count;
};

long synchronization_get_available_thread_declarations(void)
{
    mangled_ppc("?synchronization_get_available_thread_declarations@@YAJXZ");

    return synchronization_get_maximum_declared_threads() - synchronization_get_declared_threads();
};

void synchronization_release_objects_owned_by_thread(void)
{
    mangled_ppc("?synchronization_release_objects_owned_by_thread@@YAXXZ");

    if (g_synchronization_globals.group_created_mask != 0)
    {
        long thread_index = synchronization_get_current_thread_index();

        for (long index = 0; index < g_synchronization_globals.critical_sections.count(); index++)
        {
            if (TEST_BIT(g_synchronization_globals.group_created_mask, g_synchronization_globals.critical_sections[index].synchronization_group_index))
            {
                critical_section_force_release_if_owned_by_thread(&g_synchronization_globals.critical_section_instances[index], thread_index);
            }
        }

        for (long index = 0; index < g_synchronization_globals.mutexes.count(); index++)
        {
            if (TEST_BIT(g_synchronization_globals.group_created_mask, g_synchronization_globals.mutexes[index].synchronization_group_index))
            {
                mutex_force_release_if_owned_by_thread(&g_synchronization_globals.mutex_instances[index], thread_index);
            }
        }

        for (long index = 0; index < g_synchronization_globals.semaphores.count(); index++)
        {
            if (TEST_BIT(g_synchronization_globals.group_created_mask, g_synchronization_globals.semaphores[index].synchronization_group_index))
            {
                g_synchronization_globals.semaphore_instances[index].force_release_if_owned_by_thread(thread_index);
            }
        }
    }
};

void synchronization_release_crash_required_objects_owned_by_thread(void)
{
    mangled_ppc("?synchronization_release_crash_required_objects_owned_by_thread@@YAXXZ");

    if (g_synchronization_globals.group_created_mask != 0)
    {
        long thread_index = synchronization_get_current_thread_index();

        for (long index = 0; index < g_synchronization_globals.critical_sections.count(); index++)
        {
            if (TEST_BIT(g_synchronization_globals.group_created_mask, g_synchronization_globals.critical_sections[index].synchronization_group_index) &&
                g_synchronization_globals.critical_sections[index].definition.unknown8)
            {
                critical_section_force_release_if_owned_by_thread(&g_synchronization_globals.critical_section_instances[index], thread_index);
            }
        }
    }
};

void synchronization_enable_lock_enforcement(bool enable)
{
    mangled_ppc("?synchronization_enable_lock_enforcement@@YAX_N@Z");

    for (long thread_index = 0; thread_index < k_synchronization_maximum_registered_threads; thread_index++)
    {
        if (g_synchronization_globals.registered_thread_vector.test_bit(thread_index))
        {
            g_synchronization_globals.lock_trackers[thread_index].set_enforcement_enabled(enable);
        }
    }
};

long synchronization_get_current_thread_index(void)
{
    mangled_ppc("?synchronization_get_current_thread_index@@YAJXZ");

    long thread_index = g_synchronization_thread_index;
    dassert_tag_debug_untracked_jul_11_2011(699, g_synchronization_thread_registered, "you are trying to use the synchronization manager from an unregistered thread");
    assert_tag_debug_untracked_jul_11_2011(700, VALID_INDEX(thread_index, k_synchronization_maximum_registered_threads));

    return thread_index;
};

c_lock_hierarchy * synchronization_get_lock_hierarchy(void)
{
    mangled_ppc("?synchronization_get_lock_hierarchy@@YAPAVc_lock_hierarchy@@XZ");

    assert_tag_debug_untracked_jul_11_2011(708, g_synchronization_globals.initialized);
    dassert_tag_debug_untracked_jul_11_2011(709, !g_synchronization_globals.lock_hierarchy.is_finalized(), "you can't get write access to the lock hierarchy after sync objects are created and the hierarchy is finalized");

    return &g_synchronization_globals.lock_hierarchy;
};

c_lock_hierarchy const * synchronization_get_lock_hierarchy_const(void)
{
    mangled_ppc("?synchronization_get_lock_hierarchy_const@@YAPBVc_lock_hierarchy@@XZ");

    assert_tag_debug_untracked_jul_11_2011(716, g_synchronization_globals.initialized);

    return &g_synchronization_globals.lock_hierarchy;
};

unsigned long synchronization_declare_critical_section(long synchronization_group_index, s_critical_section_definition const * definition)
{
    mangled_ppc("?synchronization_declare_critical_section@@YAKJPBUs_critical_section_definition@@@Z");

    unsigned long synchronization_object_id = k_synchronization_object_id_invalid;
    assert_tag_debug_untracked_jul_11_2011(726, g_synchronization_globals.initialized);
    assert_tag_debug_untracked_jul_11_2011(727, !synchronization_object_group_created(synchronization_group_index));

    if (!g_synchronization_globals.critical_sections.full())
    {
        long object_index = g_synchronization_globals.critical_sections.push();
        unsigned long object_id = SYNCHRONIZATION_OBJECT_ID(synchronization_group_index, _synchronization_object_critical_section, object_index);
        s_critical_section_declaration & critical_section = g_synchronization_globals.critical_sections[object_index];
        critical_section.synchronization_group_index = synchronization_group_index;
        critical_section.definition = *definition;
        critical_section.lock_node_index = create_lock_node_index(synchronization_group_index, object_id, definition->name);
        synchronization_object_id = object_id;
    }

    return synchronization_object_id;
};

unsigned long synchronization_declare_mutex(long synchronization_group_index, s_mutex_definition const * definition)
{
    mangled_ppc("?synchronization_declare_mutex@@YAKJPBUs_mutex_definition@@@Z");

    unsigned long synchronization_object_id = k_synchronization_object_id_invalid;
    assert_tag_debug_untracked_jul_11_2011(751, g_synchronization_globals.initialized);
    assert_tag_debug_untracked_jul_11_2011(752, !synchronization_object_group_created(synchronization_group_index));

    if (!g_synchronization_globals.mutexes.full())
    {
        long object_index = g_synchronization_globals.mutexes.push();
        unsigned long object_id = SYNCHRONIZATION_OBJECT_ID(synchronization_group_index, _synchronization_object_mutex, object_index);
        s_mutex_declaration & mutex = g_synchronization_globals.mutexes[object_index];
        mutex.synchronization_group_index = synchronization_group_index;
        mutex.definition = *definition;
        mutex.lock_node_index = create_lock_node_index(synchronization_group_index, object_id, definition->name);
        synchronization_object_id = object_id;
    }

    return synchronization_object_id;
};

unsigned long synchronization_declare_synchronization_event(long synchronization_group_index, s_synchronization_event_definition const * definition)
{
    mangled_ppc("?synchronization_declare_synchronization_event@@YAKJPBUs_synchronization_event_definition@@@Z");

    unsigned long synchronization_object_id = k_synchronization_object_id_invalid;
    assert_tag_debug_untracked_jul_11_2011(775, g_synchronization_globals.initialized);
    assert_tag_debug_untracked_jul_11_2011(776, !synchronization_object_group_created(synchronization_group_index));

    if (!g_synchronization_globals.events.full())
    {
        long object_index = g_synchronization_globals.events.push();
        s_event_declaration & event = g_synchronization_globals.events[object_index];
        event.synchronization_group_index = synchronization_group_index;
        event.definition = *definition;
        synchronization_object_id = SYNCHRONIZATION_OBJECT_ID(synchronization_group_index, _synchronization_object_event, object_index);
    }

    return synchronization_object_id;
};

unsigned long synchronization_declare_semaphore(long synchronization_group_index, s_semaphore_definition const * definition)
{
    mangled_ppc("?synchronization_declare_semaphore@@YAKJPBUs_semaphore_definition@@@Z");

    unsigned long synchronization_object_id = k_synchronization_object_id_invalid;
    assert_tag_debug_untracked_jul_11_2011(797, g_synchronization_globals.initialized);
    assert_tag_debug_untracked_jul_11_2011(798, !synchronization_object_group_created(synchronization_group_index));

    if (!g_synchronization_globals.semaphores.full())
    {
        long object_index = g_synchronization_globals.semaphores.push();
        unsigned long object_id = SYNCHRONIZATION_OBJECT_ID(synchronization_group_index, _synchronization_object_semaphore, object_index);
        s_semaphore_declaration & semaphore = g_synchronization_globals.semaphores[object_index];
        semaphore.synchronization_group_index = synchronization_group_index;
        semaphore.definition = *definition;
        semaphore.lock_node_index = create_lock_node_index(synchronization_group_index, object_id, definition->name);
        synchronization_object_id = object_id;
    }

    return synchronization_object_id;
};

unsigned long synchronization_declare_busy_wait(long synchronization_group_index, s_busy_wait_definition const * definition)
{
    mangled_ppc("?synchronization_declare_busy_wait@@YAKJPBUs_busy_wait_definition@@@Z");

    unsigned long synchronization_object_id = k_synchronization_object_id_invalid;
    assert_tag_debug_untracked_jul_11_2011(821, g_synchronization_globals.initialized);

    if (!g_synchronization_globals.busy_waits.full())
    {
        long index = g_synchronization_globals.busy_waits.push();
        s_busy_wait_declaration & busy_wait = g_synchronization_globals.busy_waits[index];
        busy_wait.synchronization_group_index = synchronization_group_index;
        busy_wait.definition = *definition;
        synchronization_object_id = SYNCHRONIZATION_OBJECT_ID(synchronization_group_index, _synchronization_object_busy_wait, index);
    }

    return synchronization_object_id;
};

unsigned long synchronization_declare_virtual_guard_block(long synchronization_group_index, s_virtual_guard_block_definition const * definition)
{
    mangled_ppc("?synchronization_declare_virtual_guard_block@@YAKJPBUs_virtual_guard_block_definition@@@Z");

    unsigned long synchronization_object_id = k_synchronization_object_id_invalid;
    assert_tag_debug_untracked_jul_11_2011(844, g_synchronization_globals.initialized);
    assert_tag_debug_untracked_jul_11_2011(845, !synchronization_object_group_created(synchronization_group_index));

    if (!g_synchronization_globals.virtual_guard_blocks.full())
    {
        long object_index = g_synchronization_globals.virtual_guard_blocks.push();
        unsigned long object_id = SYNCHRONIZATION_OBJECT_ID(synchronization_group_index, _synchronization_object_virtual_guard_block, object_index);
        s_virtual_guard_block_declaration & guard_block = g_synchronization_globals.virtual_guard_blocks[object_index];
        guard_block.synchronization_group_index = synchronization_group_index;
        guard_block.definition = *definition;
        guard_block.lock_node_index = create_lock_node_index(synchronization_group_index, object_id, definition->name);
        synchronization_object_id = object_id;
    }

    return synchronization_object_id;
};

char const * synchronization_object_get_name(unsigned long object_id)
{
    mangled_ppc("?synchronization_object_get_name@@YAPBDK@Z");

    char const * name = "<invalid>";
    long object_type = SYNCHRONIZATION_OBJECT_TYPE(object_id);
    long object_index = SYNCHRONIZATION_OBJECT_INDEX(object_id);

    if (g_synchronization_globals.initialized)
    {
        switch (object_type)
        {
        case _synchronization_object_critical_section:
            if (g_synchronization_globals.critical_sections.valid(object_index))
            {
                name = g_synchronization_globals.critical_sections[object_index].definition.name;
            }
            break;
        case _synchronization_object_mutex:
            if (g_synchronization_globals.mutexes.valid(object_index))
            {
                name = g_synchronization_globals.mutexes[object_index].definition.name;
            }
            break;
        case _synchronization_object_event:
            if (g_synchronization_globals.events.valid(object_index))
            {
                name = g_synchronization_globals.events[object_index].definition.name;
            }
            break;
        case _synchronization_object_semaphore:
            if (g_synchronization_globals.semaphores.valid(object_index))
            {
                name = g_synchronization_globals.semaphores[object_index].definition.name;
            }
            break;
        case _synchronization_object_busy_wait:
            if (g_synchronization_globals.busy_waits.valid(object_index))
            {
                name = g_synchronization_globals.busy_waits[object_index].definition.name;
            }
            break;
        case _synchronization_object_virtual_guard_block:
            if (g_synchronization_globals.virtual_guard_blocks.valid(object_index))
            {
                name = g_synchronization_globals.virtual_guard_blocks[object_index].definition.name;
            }
            break;
        }
    }

    return name;
};

long synchronization_object_get_lock_node_index(unsigned long object_id)
{
    mangled_ppc("?synchronization_object_get_lock_node_index@@YAJK@Z");

    long node_index = NONE;
    long object_type = SYNCHRONIZATION_OBJECT_TYPE(object_id);
    long object_index = SYNCHRONIZATION_OBJECT_INDEX(object_id);
    assert_tag_debug_untracked_jul_11_2011(931, g_synchronization_globals.initialized);

    switch (object_type)
    {
    case _synchronization_object_critical_section:
        assert_tag_debug_untracked_jul_11_2011(936, g_synchronization_globals.critical_sections.valid(object_index));
        node_index = g_synchronization_globals.critical_sections[object_index].lock_node_index;
        break;
    case _synchronization_object_mutex:
        assert_tag_debug_untracked_jul_11_2011(941, g_synchronization_globals.mutexes.valid(object_index));
        node_index = g_synchronization_globals.mutexes[object_index].lock_node_index;
        break;
    case _synchronization_object_semaphore:
        assert_tag_debug_untracked_jul_11_2011(946, g_synchronization_globals.semaphores.valid(object_index));
        node_index = g_synchronization_globals.semaphores[object_index].lock_node_index;
        break;
    case _synchronization_object_virtual_guard_block:
        assert_tag_debug_untracked_jul_11_2011(951, g_synchronization_globals.virtual_guard_blocks.valid(object_index));
        node_index = g_synchronization_globals.virtual_guard_blocks[object_index].lock_node_index;
        break;
    }

    return node_index;
};

c_synchronization_object * synchronization_get_object(unsigned long object_id)
{
    mangled_ppc("?synchronization_get_object@@YAPAVc_synchronization_object@@K@Z");

    c_synchronization_object * object = NULL;
    long object_type = SYNCHRONIZATION_OBJECT_TYPE(object_id);
    long object_index = SYNCHRONIZATION_OBJECT_INDEX(object_id);
    assert_tag_debug_untracked_jul_11_2011(966, g_synchronization_globals.initialized);
    assert_tag_debug_untracked_jul_11_2011(967, synchronization_object_group_created(SYNCHRONIZATION_OBJECT_GROUP(object_id)));

    switch (object_type)
    {
    case _synchronization_object_critical_section:
        object = &g_synchronization_globals.critical_section_instances[object_index];
        break;
    case _synchronization_object_mutex:
        object = &g_synchronization_globals.mutex_instances[object_index];
        break;
    case _synchronization_object_event:
        object = &g_synchronization_globals.event_instances[object_index];
        break;
    case _synchronization_object_semaphore:
        object = &g_synchronization_globals.semaphore_instances[object_index];
        break;
    case _synchronization_object_virtual_guard_block:
        object = &g_synchronization_globals.virtual_guard_block_instances[object_index];
        break;
    default:
        dassert_tag_debug_untracked_jul_11_2011(992, false, "unreachable");
        break;
    }

    return object;
};

c_critical_section_instance * synchronization_get_critical_section(unsigned long object_id)
{
    mangled_ppc("?synchronization_get_critical_section@@YAPAVc_critical_section_instance@@K@Z");

    long index = SYNCHRONIZATION_OBJECT_INDEX(object_id);
    assert_tag_debug_untracked_jul_11_2011(1004, g_synchronization_globals.initialized);
    assert_tag_debug_untracked_jul_11_2011(1005, synchronization_object_group_created(SYNCHRONIZATION_OBJECT_GROUP(object_id)));
    assert_tag_debug_untracked_jul_11_2011(1006, SYNCHRONIZATION_OBJECT_TYPE(object_id)==_synchronization_object_critical_section);
    assert_tag_debug_untracked_jul_11_2011(1007, g_synchronization_globals.critical_sections.valid(index));

    return &g_synchronization_globals.critical_section_instances[index];
};

c_synchronization_handle * synchronization_get_mutex(unsigned long object_id)
{
    mangled_ppc("?synchronization_get_mutex@@YAPAVc_synchronization_handle@@K@Z");

    long index = SYNCHRONIZATION_OBJECT_INDEX(object_id);
    assert_tag_debug_untracked_jul_11_2011(1017, g_synchronization_globals.initialized);
    assert_tag_debug_untracked_jul_11_2011(1018, synchronization_object_group_created(SYNCHRONIZATION_OBJECT_GROUP(object_id)));
    assert_tag_debug_untracked_jul_11_2011(1019, SYNCHRONIZATION_OBJECT_TYPE(object_id)==_synchronization_object_mutex);
    assert_tag_debug_untracked_jul_11_2011(1020, g_synchronization_globals.mutexes.valid(index));

    return &g_synchronization_globals.mutex_instances[index];
};

c_synchronization_handle * synchronization_get_synchronization_event(unsigned long object_id)
{
    mangled_ppc("?synchronization_get_synchronization_event@@YAPAVc_synchronization_handle@@K@Z");

    long index = SYNCHRONIZATION_OBJECT_INDEX(object_id);
    assert_tag_debug_untracked_jul_11_2011(1030, g_synchronization_globals.initialized);
    assert_tag_debug_untracked_jul_11_2011(1031, synchronization_object_group_created(SYNCHRONIZATION_OBJECT_GROUP(object_id)));
    assert_tag_debug_untracked_jul_11_2011(1032, SYNCHRONIZATION_OBJECT_TYPE(object_id)==_synchronization_object_event);
    assert_tag_debug_untracked_jul_11_2011(1033, g_synchronization_globals.events.valid(index));

    return &g_synchronization_globals.event_instances[index];
};

c_semaphore_instance * synchronization_get_semaphore(unsigned long object_id)
{
    mangled_ppc("?synchronization_get_semaphore@@YAPAVc_semaphore_instance@@K@Z");

    long index = SYNCHRONIZATION_OBJECT_INDEX(object_id);
    assert_tag_debug_untracked_jul_11_2011(1043, g_synchronization_globals.initialized);
    assert_tag_debug_untracked_jul_11_2011(1044, synchronization_object_group_created(SYNCHRONIZATION_OBJECT_GROUP(object_id)));
    assert_tag_debug_untracked_jul_11_2011(1045, SYNCHRONIZATION_OBJECT_TYPE(object_id)==_synchronization_object_semaphore);
    assert_tag_debug_untracked_jul_11_2011(1046, g_synchronization_globals.semaphores.valid(index));

    return &g_synchronization_globals.semaphore_instances[index];
};

c_synchronization_object * synchronization_get_virtual_guard_block(unsigned long object_id)
{
    mangled_ppc("?synchronization_get_virtual_guard_block@@YAPAVc_synchronization_object@@K@Z");

    long index = SYNCHRONIZATION_OBJECT_INDEX(object_id);
    assert_tag_debug_untracked_jul_11_2011(1056, g_synchronization_globals.initialized);
    assert_tag_debug_untracked_jul_11_2011(1057, synchronization_object_group_created(SYNCHRONIZATION_OBJECT_GROUP(object_id)));
    assert_tag_debug_untracked_jul_11_2011(1058, SYNCHRONIZATION_OBJECT_TYPE(object_id)==_synchronization_object_virtual_guard_block);
    assert_tag_debug_untracked_jul_11_2011(1059, g_synchronization_globals.virtual_guard_blocks.valid(index));

    return &g_synchronization_globals.virtual_guard_block_instances[index];
};

s_synchronization_event_definition const * synchronization_get_synchronization_event_definition(unsigned long object_id)
{
    mangled_ppc("?synchronization_get_synchronization_event_definition@@YAPBUs_synchronization_event_definition@@K@Z");

    long index = SYNCHRONIZATION_OBJECT_INDEX(object_id);
    assert_tag_debug_untracked_jul_11_2011(1069, g_synchronization_globals.initialized);
    assert_tag_debug_untracked_jul_11_2011(1070, SYNCHRONIZATION_OBJECT_TYPE(object_id)==_synchronization_object_event);

    return &g_synchronization_globals.events[index].definition;
};

s_semaphore_definition const * synchronization_get_semaphore_definition(unsigned long object_id)
{
    mangled_ppc("?synchronization_get_semaphore_definition@@YAPBUs_semaphore_definition@@K@Z");

    long index = SYNCHRONIZATION_OBJECT_INDEX(object_id);
    assert_tag_debug_untracked_jul_11_2011(1080, g_synchronization_globals.initialized);
    assert_tag_debug_untracked_jul_11_2011(1081, SYNCHRONIZATION_OBJECT_TYPE(object_id)==_synchronization_object_semaphore);

    return &g_synchronization_globals.semaphores[index].definition;
};

bool wait_for_single_object_internal(void * handle, long timeout_milliseconds)
{
    mangled_ppc("?wait_for_single_object_internal@@YA_NPAXJ@Z");

    bool success = true;
    assert_tag_debug_untracked_jul_11_2011(1093, VALID_HANDLE(handle));

    if (handle)
    {
        unsigned long result = WaitForSingleObjectEx(handle, timeout_milliseconds, FALSE);
        switch (result)
        {
        case WAIT_TIMEOUT:
            success = false;
            break;
        case WAIT_ABANDONED:
            dassert_tag_debug_untracked_jul_11_2011(1111, false, "some thread terminated before releasing a synchronization primative");
            success = true;
            break;
        case WAIT_OBJECT_0:
            success = true;
            break;
        default:
            dassert_tag_debug_untracked_jul_11_2011(1121, false, "unreachable");
            break;
        }
    }

    assert_tag_debug_untracked_jul_11_2011(1126, success || timeout_milliseconds!=INFINITE);

    return success;
};

c_synchronization_block_timer::c_synchronization_block_timer(unsigned long object_id, long timeout_milliseconds)
{
    mangled_ppc("??0c_synchronization_block_timer@@QAA@KJ@Z");

    m_object_id = object_id;
    m_timeout_milliseconds = timeout_milliseconds;
};

c_synchronization_block_timer::~c_synchronization_block_timer(void)
{
    mangled_ppc("??1c_synchronization_block_timer@@QAA@XZ");

    long object_type = SYNCHRONIZATION_OBJECT_TYPE(m_object_id);
    long object_index = SYNCHRONIZATION_OBJECT_INDEX(m_object_id);
};

long create_lock_node_index(long synchronization_group_index, unsigned long object_id, char const * name)
{
    mangled_ppc("?create_lock_node_index@@YAJJKPBD@Z");

    long lock_node_index = NONE;
    if (synchronization_group_index == k_synchronization_group_base)
    {
        lock_node_index = g_synchronization_globals.lock_hierarchy.declare_object(object_id, name);
    }

    return lock_node_index;
};

