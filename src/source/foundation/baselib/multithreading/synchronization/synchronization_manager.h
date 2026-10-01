#pragma once
#ifndef __SYNCHRONIZATION_MANAGER_H__
#define __SYNCHRONIZATION_MANAGER_H__

/* ---------- headers */

/* ---------- constants */

enum e_synchronization_object_type
{
    _synchronization_object_none = 0,
    _synchronization_object_critical_section,
    _synchronization_object_mutex,
    _synchronization_object_event,
    _synchronization_object_semaphore,
    _synchronization_object_busy_wait,
    _synchronization_object_virtual_guard_block,

    k_synchronization_object_type_count
};

long const k_synchronization_group_base = 0;
long const k_synchronization_group_count = 2;
long const k_synchronization_maximum_registered_threads = 23;
unsigned long const k_synchronization_object_id_invalid = 0xFFFFFFFF;

#define SYNCHRONIZATION_OBJECT_ID(group_index, object_type, object_index) (((group_index) << 28) | ((object_type) << 24) | (object_index))
#define SYNCHRONIZATION_OBJECT_GROUP(object_id) static_cast<long>(((object_id) >> 28) & 0xF)
#define SYNCHRONIZATION_OBJECT_TYPE(object_id) static_cast<e_synchronization_object_type>(((object_id) >> 24) & 0xF)
#define SYNCHRONIZATION_OBJECT_INDEX(object_id) ((object_id) & 0xFFFFFF)

/* ---------- definitions */

class c_allocation_interface;
class c_lock_hierarchy;
class c_lock_tracker;
class c_synchronization_object;
class c_critical_section_instance;
class c_synchronization_handle;
class c_semaphore_instance;
struct s_critical_section_definition;
struct s_mutex_definition;
struct s_synchronization_event_definition;
struct s_semaphore_definition;
struct s_busy_wait_definition;
struct s_virtual_guard_block_definition;

class c_synchronization_block_timer
{
public:
    c_synchronization_block_timer(unsigned long object_id, long timeout_milliseconds);
    ~c_synchronization_block_timer(void);

private:
    long m_unknown0[2]; // 0x0
    unsigned long m_object_id; // 0x8
    long m_timeout_milliseconds; // 0xC
};

/* ---------- prototypes */

extern void synchronization_manager_initialize(c_allocation_interface * allocator);
extern void synchronization_manager_dispose(void);
extern bool synchronization_manager_initialized(void);
extern bool synchronization_object_group_created(long synchronization_group_index);
extern void synchronization_declare_threads_explicit(long const * thread_indices, long thread_count);
extern void synchronization_declare_threads(long thread_count, long * out_thread_indices);
extern void synchronization_register_thread(long thread_index);
extern void synchronization_unregister_thread(long thread_index);
extern bool synchronization_is_thread_registered(void);
extern long synchronization_get_maximum_declared_threads(void);
extern long synchronization_get_declared_threads(void);
extern long synchronization_get_available_thread_declarations(void);
extern void synchronization_release_objects_owned_by_thread(void);
extern void synchronization_release_crash_required_objects_owned_by_thread(void);
extern void synchronization_enable_lock_enforcement(bool enable);
extern long synchronization_get_current_thread_index(void);
extern c_lock_hierarchy * synchronization_get_lock_hierarchy(void);
extern c_lock_hierarchy const * synchronization_get_lock_hierarchy_const(void);
extern unsigned long synchronization_declare_critical_section(long synchronization_group_index, s_critical_section_definition const * definition);
extern unsigned long synchronization_declare_mutex(long synchronization_group_index, s_mutex_definition const * definition);
extern unsigned long synchronization_declare_synchronization_event(long synchronization_group_index, s_synchronization_event_definition const * definition);
extern unsigned long synchronization_declare_semaphore(long synchronization_group_index, s_semaphore_definition const * definition);
extern unsigned long synchronization_declare_busy_wait(long synchronization_group_index, s_busy_wait_definition const * definition);
extern unsigned long synchronization_declare_virtual_guard_block(long synchronization_group_index, s_virtual_guard_block_definition const * definition);
extern char const * synchronization_object_get_name(unsigned long object_id);
extern long synchronization_object_get_lock_node_index(unsigned long object_id);
extern c_synchronization_object * synchronization_get_object(unsigned long object_id);
extern c_critical_section_instance * synchronization_get_critical_section(unsigned long object_id);
extern c_synchronization_handle * synchronization_get_mutex(unsigned long object_id);
extern c_synchronization_handle * synchronization_get_synchronization_event(unsigned long object_id);
extern c_semaphore_instance * synchronization_get_semaphore(unsigned long object_id);
extern c_synchronization_object * synchronization_get_virtual_guard_block(unsigned long object_id);
extern s_synchronization_event_definition const * synchronization_get_synchronization_event_definition(unsigned long object_id);
extern s_semaphore_definition const * synchronization_get_semaphore_definition(unsigned long object_id);
extern bool wait_for_single_object_internal(void * handle, long timeout_milliseconds);

extern long synchronization_declare_object_group(void);
extern void synchronization_create_object_group(long synchronization_group_index);
extern void synchronization_destroy_object_group(long synchronization_group_index);

/* ---------- globals */

extern __declspec(thread) c_lock_tracker * g_synchronization_lock_tracker;

/* ---------- public code */

#endif // __SYNCHRONIZATION_MANAGER_H__

