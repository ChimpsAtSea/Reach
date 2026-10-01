#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\foundation\\threadlib\\async\\async.cpp"
/* ---------- headers */

#include "foundation\threadlib\async\async.h"
#include "foundation\threadlib\async\async_profile.h"
#include "foundation\threadlib\async\async_setup.h"
#include "threadlib\async_compare_private.h"
#include "baselib\thread_execution_windows.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_events.h"
#include "core\corelib\cseries\cseries_macros.h"
#include "core\corelib\cseries\cseries_memory.h"
#include "foundation\baselib\multithreading\synchronization\semaphore_windows.h"
#include "foundation\baselib\multithreading\synchronization\virtual_guard_block.h"
#include "omaha\cseries\cseries.h"

/* ---------- constants */

/* ---------- definitions */

class c_category_counter_visitor
{
public:
    c_category_counter_visitor(long category)
    {
        mangled_ppc("??0c_category_counter_visitor@@QAA@J@Z");

        m_category = category;
        m_count = 0;
    }

    void visit(t_thread_safe_list<s_async_task_element>::s_list_element * element)
    {
        mangled_ppc("?visit@c_category_counter_visitor@@QAAXPAUs_list_element@?$t_thread_safe_list@Us_async_task_element@@@@@Z");

        t_thread_safe_list<s_async_task_element>::s_list_element * current = element;
        while (current != NULL)
        {
            if (current->data.category == m_category)
            {
                m_count++;
            }
            current = current->next;
        }
    }

    long m_category;
    long m_count;
};

/* ---------- prototypes */

e_async_completion async_exit_thread_callback(void * task_data);
s_async_task_id async_add_task_to_work_list_ordered(s_async_thread_context * thread_context, t_thread_safe_list<s_async_task_element>::s_list_element * task_element);
s_async_task_id async_add_task_to_work_list_ordered_internal(s_async_thread_context * thread_context, t_thread_safe_list<s_async_task_element>::s_list_element * task_element, bool generate_new_id);
s_async_task_id async_add_task_to_work_list_ordered_with_new_id(s_async_thread_context * thread_context, t_thread_safe_list<s_async_task_element>::s_list_element * task_element);
t_thread_safe_list<s_async_task_element>::s_list_element * async_get_free_task_element_from_context_with_block(s_async_thread_context * thread_context, e_async_block_if_full blocking_behavior, bool * out_blocked);

/* ---------- globals */

s_async_task_id const k_invalid_async_task_id = { -1 };

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// public: static long const s_static_array<long, 32>::k_element_count; // "?k_element_count@?$s_static_array@J$0CA@@@2JB"
// public: static long const s_static_array<struct s_async_task_priority_timings, 32>::k_element_count; // "?k_element_count@?$s_static_array@Us_async_task_priority_timings@@$0CA@@@2JB"
// public: static long const s_static_array<struct t_thread_safe_list<struct s_async_task_element>::s_list_element, 128>::k_element_count; // "?k_element_count@?$s_static_array@Us_list_element@?$t_thread_safe_list@Us_async_task_element@@@@$0IA@@@2JB"
// struct s_async_task_id const k_invalid_async_task_id; // "?k_invalid_async_task_id@@3Us_async_task_id@@B"

// void async_initialize(void);
// void async_request_shutdown(void);
// void async_dispose(void);
// void async_idle(void);
// bool async_category_in_queue(long);
// public: c_category_counter_visitor::c_category_counter_visitor(long);
// bool async_task_change_priority(struct s_async_task_id, long);
// struct s_async_task_id async_task_add_simple_function(long, long, enum e_async_completion (*)(void *), class c_async_completion_flag *);
// struct s_async_task_id async_task_add_sized_task_data_unsafe(long, long, void const *, long, enum e_async_completion (*)(void *), class c_async_completion_flag *, enum e_async_block_if_full);
// void async_yield_begin(class c_async_completion_flag const *);
// public: long c_async_completion_flag::get_internal_data(void) const;
// void async_yield_end(class c_async_completion_flag const *);
// void async_yield_until_done_simple(struct s_async_task_id, class c_async_completion_flag const *);
// public: bool c_async_completion_flag::is_done(void) const;
// long async_get_thread_index_from_task_id(struct s_async_task_id);
// long async_get_local_index_from_task_id(struct s_async_task_id);
// enum e_async_completion async_exit_thread_callback(void *);
// struct s_async_task_id async_add_task_to_work_list_ordered(struct s_async_thread_context *, struct t_thread_safe_list<struct s_async_task_element>::s_list_element *);
// struct s_async_task_id async_add_task_to_work_list_ordered_internal(struct s_async_thread_context *, struct t_thread_safe_list<struct s_async_task_element>::s_list_element *, bool);
// struct s_async_task_id async_build_task_id(long, long, long);
// struct s_async_task_id async_add_task_to_work_list_ordered_with_new_id(struct s_async_thread_context *, struct t_thread_safe_list<struct s_async_task_element>::s_list_element *);
// struct s_async_task_id async_task_add_sized_task_data_with_thread_index_unsafe(long, long, long, void const *, long, enum e_async_completion (*)(void *), class c_async_completion_flag *, enum e_async_block_if_full, bool *);
// public: void c_async_completion_flag::set_internal_data(long);
// public: void c_async_completion_flag::set(long);
// struct t_thread_safe_list<struct s_async_task_element>::s_list_element * async_get_free_task_element_from_context_with_block(struct s_async_thread_context *, enum e_async_block_if_full, bool *);
// public: static long s_static_array<struct t_thread_safe_list<struct s_async_task_element>::s_list_element, 128>::get_count(void);
// public: long t_thread_safe_list<struct s_async_task_element>::size(void);
// public: struct t_thread_safe_list<struct s_async_task_element>::s_list_element * t_thread_safe_list<struct s_async_task_element>::get_and_remove_head_element(void);
// public: void t_thread_safe_list<struct s_async_task_element>::lock(void);
// public: void t_thread_safe_list<struct s_async_task_element>::unlock(void);
// public: bool t_thread_safe_list<struct s_async_task_element>::remove_element_assumes_locked(struct t_thread_safe_list<struct s_async_task_element>::s_list_element *);
// public: void t_thread_safe_list<struct s_async_task_element>::visit_list<class c_category_counter_visitor>(class c_category_counter_visitor *);
// public: void c_category_counter_visitor::visit(struct t_thread_safe_list<struct s_async_task_element>::s_list_element *);
// public: struct t_thread_safe_list<struct s_async_task_element>::s_list_element & s_static_array<struct t_thread_safe_list<struct s_async_task_element>::s_list_element, 128>::operator[]<long>(long);
// public: struct t_thread_safe_list<struct s_async_task_element>::s_list_element & s_static_array<struct t_thread_safe_list<struct s_async_task_element>::s_list_element, 128>::operator[]<int>(int);
// public: void t_thread_safe_list<struct s_async_task_element>::add_element_ordered_assumes_locked<class c_async_task_element_comparer>(struct t_thread_safe_list<struct s_async_task_element>::s_list_element *, class c_async_task_element_comparer &);
// public: static bool s_static_array<struct t_thread_safe_list<struct s_async_task_element>::s_list_element, 128>::valid<long>(long);
// public: static bool s_static_array<struct t_thread_safe_list<struct s_async_task_element>::s_list_element, 128>::valid<int>(int);

void async_initialize(void)
{
    mangled_ppc("?async_initialize@@YAXXZ");

    async_setup_initialize();
};

void async_request_shutdown(void)
{
    mangled_ppc("?async_request_shutdown@@YAXXZ");

    long thread_count = async_setup_get_thread_count();
    for (long thread_index = 0; thread_index < thread_count; thread_index++)
    {
        c_async_completion_flag completion_flag;
        s_async_task_id task_id = async_task_add_sized_task_data_with_thread_index_unsafe(thread_index, 0, 0, NULL, 0, async_exit_thread_callback, &completion_flag, _async_block_if_full, NULL);
        async_yield_until_done_simple(task_id, &completion_flag);
    }
};

void async_dispose(void)
{
    mangled_ppc("?async_dispose@@YAXXZ");

    async_setup_dispose();
};

void async_idle(void)
{
    mangled_ppc("?async_idle@@YAXXZ");

    long thread_count = async_setup_get_thread_count();
    for (long thread_index = 0; thread_index < thread_count; thread_index++)
    {
        s_async_thread_context * thread_context = async_setup_get_context_for_thread(thread_index);
        thread_context->unknown9C2C.set(thread_context->work_list.size());
    }
};

bool async_category_in_queue(long category)
{
    mangled_ppc("?async_category_in_queue@@YA_NJ@Z");

    bool in_queue = false;
    s_async_thread_context * thread_context = async_setup_get_context_for_category(category);
    c_category_counter_visitor category_visitor(category);
    assert_tag_debug_untracked_jul_11_2011(135, thread_context!=NULL);

    thread_context->work_list.visit_list(&category_visitor);
    in_queue = category_visitor.m_count > 0;

    return in_queue;
};

bool async_task_change_priority(s_async_task_id task_id, long priority)
{
    mangled_ppc("?async_task_change_priority@@YA_NUs_async_task_id@@J@Z");

    bool success = false;
    long thread_index = NONE;
    s_async_thread_context * thread_context = NULL;
    assert_tag_debug_untracked_jul_11_2011(152, async_task_id_is_valid(task_id));

    thread_index = async_get_thread_index_from_task_id(task_id);
    thread_context = async_setup_get_context_for_thread(thread_index);
    thread_context->work_list.lock();
    {
        long local_index = async_get_local_index_from_task_id(task_id);
        {
            t_thread_safe_list<s_async_task_element>::s_list_element * task_element = NULL;
            task_element = &thread_context->element_storage[local_index];
            if (task_element->data.task_id.value == task_id.value && thread_context->work_list.remove_element_assumes_locked(task_element))
            {
                task_element->data.priority = priority;
                async_add_task_to_work_list_ordered(thread_context, task_element);
                success = true;
            }
        }
    }
    thread_context->work_list.unlock();

    return success;
};

s_async_task_id async_task_add_simple_function(long priority, long category, e_async_completion (*callback)(void *), c_async_completion_flag * completion_flag)
{
    mangled_ppc("?async_task_add_simple_function@@YA?AUs_async_task_id@@JJP6A?AW4e_async_completion@@PAX@ZPAVc_async_completion_flag@@@Z");

    return async_task_add_sized_task_data_unsafe(priority, category, NULL, 0, callback, completion_flag, _async_block_if_full);
};

s_async_task_id async_task_add_sized_task_data_unsafe(long priority, long category, void const * task_data, long task_data_size, e_async_completion (*callback)(void *), c_async_completion_flag * completion_flag, e_async_block_if_full blocking_behavior)
{
    mangled_ppc("?async_task_add_sized_task_data_unsafe@@YA?AUs_async_task_id@@JJPBXJP6A?AW4e_async_completion@@PAX@ZPAVc_async_completion_flag@@W4e_async_block_if_full@@@Z");

    long thread_index = NONE;
    assert_tag_debug_untracked_jul_11_2011(221, VALID_INDEX(category, k_maximum_async_category));

    thread_index = async_setup_get_thread_index_for_category(category);
    bool blocked;
    s_async_task_id task_id = async_task_add_sized_task_data_with_thread_index_unsafe(thread_index, priority, category, task_data, task_data_size, callback, completion_flag, blocking_behavior, &blocked);
    if (blocked)
    {
        event(_event_error, "async: %s while trying to add a task of category %d with priority %d in async thread %d", blocking_behavior == _async_block_if_full ? "blocked" : "task list full", category, priority, thread_index);
    }

    return task_id;
};

void async_yield_begin(c_async_completion_flag const * completion_flag)
{
    mangled_ppc("?async_yield_begin@@YAXPBVc_async_completion_flag@@@Z");

    long thread_index = NONE;
    s_async_thread_context * thread_context = NULL;
    assert_tag_debug_untracked_jul_11_2011(258, completion_flag);

    thread_index = completion_flag->get_internal_data();
    thread_context = async_setup_get_context_for_thread(thread_index);
    virtual_guard_block_enter(thread_context->guard_block);
};

void async_yield_end(c_async_completion_flag const * completion_flag)
{
    mangled_ppc("?async_yield_end@@YAXPBVc_async_completion_flag@@@Z");

    long thread_index = NONE;
    s_async_thread_context * thread_context = NULL;
    assert_tag_debug_untracked_jul_11_2011(274, completion_flag);

    thread_index = completion_flag->get_internal_data();
    thread_context = async_setup_get_context_for_thread(thread_index);
    virtual_guard_block_leave(thread_context->guard_block);
};

void async_yield_until_done_simple(s_async_task_id task_id, c_async_completion_flag const * completion_flag)
{
    mangled_ppc("?async_yield_until_done_simple@@YAXUs_async_task_id@@PBVc_async_completion_flag@@@Z");

    async_yield_begin(completion_flag);
    while (!completion_flag->is_done())
    {
        thread_switch();
    }
    async_yield_end(completion_flag);
};

long async_get_thread_index_from_task_id(s_async_task_id task_id)
{
    mangled_ppc("?async_get_thread_index_from_task_id@@YAJUs_async_task_id@@@Z");

    long thread_index = (task_id.value >> 8) & 0xFF;
    assert_tag_debug_untracked_jul_11_2011(320, VALID_INDEX(thread_index, async_setup_get_thread_count()));

    return thread_index;
};

long async_get_local_index_from_task_id(s_async_task_id task_id)
{
    mangled_ppc("?async_get_local_index_from_task_id@@YAJUs_async_task_id@@@Z");

    return task_id.value & 0xFF;
};

e_async_completion async_exit_thread_callback(void * task_data)
{
    mangled_ppc("?async_exit_thread_callback@@YA?AW4e_async_completion@@PAX@Z");

    return _async_completion_thread_exit;
};

s_async_task_id async_add_task_to_work_list_ordered(s_async_thread_context * thread_context, t_thread_safe_list<s_async_task_element>::s_list_element * task_element)
{
    mangled_ppc("?async_add_task_to_work_list_ordered@@YA?AUs_async_task_id@@PAUs_async_thread_context@@PAUs_list_element@?$t_thread_safe_list@Us_async_task_element@@@@@Z");

    return async_add_task_to_work_list_ordered_internal(thread_context, task_element, false);
};

s_async_task_id async_add_task_to_work_list_ordered_internal(s_async_thread_context * thread_context, t_thread_safe_list<s_async_task_element>::s_list_element * task_element, bool generate_new_id)
{
    mangled_ppc("?async_add_task_to_work_list_ordered_internal@@YA?AUs_async_task_id@@PAUs_async_thread_context@@PAUs_list_element@?$t_thread_safe_list@Us_async_task_element@@@@_N@Z");

    assert_tag_debug_untracked_jul_11_2011(376, thread_context);
    assert_tag_debug_untracked_jul_11_2011(377, task_element);

    c_async_task_element_comparer comparer(thread_context->thread_index);
    s_async_task_id task_id = k_invalid_async_task_id;

    thread_context->work_list.lock();
    if (generate_new_id)
    {
        long local_task_id;
        {
            long task_counter = async_setup_increment_total_tasks_added();
            local_task_id = task_element - &thread_context->element_storage[0];
            assert_tag_debug_untracked_jul_11_2011(391, VALID_INDEX(local_task_id, thread_context->element_storage.get_count()));

            task_element->data.task_id = async_build_task_id(task_counter, thread_context->thread_index, local_task_id);
        }
    }
    task_id = task_element->data.task_id;
    thread_context->work_list.add_element_ordered_assumes_locked(task_element, comparer);
    thread_context->work_list.unlock();

    semaphore_release_internal(thread_context->work_available_semaphore, NULL);

    return task_id;
};

s_async_task_id async_build_task_id(long task_counter, long thread_index, long local_index)
{
    mangled_ppc("?async_build_task_id@@YA?AUs_async_task_id@@JJJ@Z");

    s_async_task_id task_id = k_invalid_async_task_id;
    assert_tag_debug_untracked_jul_11_2011(308, async_setup_get_encoding_bit_count_for_thread_indices()<=k_async_task_id_thread_index_bits);

    task_id.value = (task_counter << 16) | (thread_index << 8) | local_index;

    return task_id;
};

s_async_task_id async_add_task_to_work_list_ordered_with_new_id(s_async_thread_context * thread_context, t_thread_safe_list<s_async_task_element>::s_list_element * task_element)
{
    mangled_ppc("?async_add_task_to_work_list_ordered_with_new_id@@YA?AUs_async_task_id@@PAUs_async_thread_context@@PAUs_list_element@?$t_thread_safe_list@Us_async_task_element@@@@@Z");

    return async_add_task_to_work_list_ordered_internal(thread_context, task_element, true);
};

s_async_task_id async_task_add_sized_task_data_with_thread_index_unsafe(long thread_index, long priority, long category, void const * task_data, long task_data_size, e_async_completion (*callback)(void *), c_async_completion_flag * completion_flag, e_async_block_if_full blocking_behavior, bool * out_blocked)
{
    mangled_ppc("?async_task_add_sized_task_data_with_thread_index_unsafe@@YA?AUs_async_task_id@@JJJPBXJP6A?AW4e_async_completion@@PAX@ZPAVc_async_completion_flag@@W4e_async_block_if_full@@PA_N@Z");

    s_async_thread_context * thread_context = NULL;
    s_async_task_id task_id = k_invalid_async_task_id;
    t_thread_safe_list<s_async_task_element>::s_list_element * task_element = NULL;
    {
        c_async_profile_block profile_block(async_profile_get_block_name(_async_profile_block_task_add_sized_task_data_unsafe));
        assert_tag_debug_untracked_jul_11_2011(453, (task_data==NULL && task_data_size==0) || (task_data && IN_RANGE_INCLUSIVE(task_data_size, 1, k_maximum_async_task_data_size)));
        assert_tag_debug_untracked_jul_11_2011(454, completion_flag);
        assert_tag_debug_untracked_jul_11_2011(455, VALID_INDEX(category, k_maximum_async_category));
        assert_tag_debug_untracked_jul_11_2011(456, VALID_INDEX(priority, k_maximum_async_priority));

        thread_context = async_setup_get_context_for_thread(thread_index);
        completion_flag->set(0);
        completion_flag->set_internal_data(thread_index);
        task_element = async_get_free_task_element_from_context_with_block(thread_context, blocking_behavior, out_blocked);
        if (task_element)
        {
            csmemset(task_element->data.task_data, 0, sizeof(task_element->data.task_data));
            if (task_data)
            {
                csmemcpy(task_element->data.task_data, task_data, task_data_size);
            }
            task_element->data.completion_flag = completion_flag;
            task_element->data.priority = priority;
            task_element->data.callback = callback;
            task_element->data.category = category;
            task_id = async_add_task_to_work_list_ordered_with_new_id(thread_context, task_element);
        }
        else
        {
            completion_flag->set(1);
        }

        return task_id;
    }
};

t_thread_safe_list<s_async_task_element>::s_list_element * async_get_free_task_element_from_context_with_block(s_async_thread_context * thread_context, e_async_block_if_full blocking_behavior, bool * out_blocked)
{
    mangled_ppc("?async_get_free_task_element_from_context_with_block@@YAPAUs_list_element@?$t_thread_safe_list@Us_async_task_element@@@@PAUs_async_thread_context@@W4e_async_block_if_full@@PA_N@Z");

    t_thread_safe_list<s_async_task_element>::s_list_element * task_element = NULL;
    assert_tag_debug_untracked_jul_11_2011(338, VALID_INDEX(blocking_behavior, k_async_block_if_full_count));

    task_element = thread_context->free_list.get_and_remove_head_element();
    if (out_blocked)
    {
        *out_blocked = task_element == NULL;
    }
    while (task_element == NULL && blocking_behavior == _async_block_if_full)
    {
        thread_context->statistics.unknown4.increment();
        if (thread_context->free_list_blocked_callback)
        {
            thread_context->free_list_blocked_callback();
        }
        thread_switch();
        task_element = thread_context->free_list.get_and_remove_head_element();
    }

    return task_element;
};
