#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\foundation\\threadlib\\async\\async_setup.cpp"
/* ---------- headers */

#include "foundation\threadlib\async\async_setup.h"
#include "foundation\threadlib\async\async_profile.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_macros.h"
#include "omaha\cseries\cseries.h"

/* ---------- constants */

/* ---------- definitions */

struct s_async_globals
{
    s_static_array<long, k_maximum_async_category> thread_index_for_category;
    s_static_array<s_async_thread_context, k_max_async_thread_count> thread_contexts;
    long max_thread_count;
    c_synchronized_int32 total_tasks_added;
    c_async_profile_interface * profiler;
};
static_assert(sizeof(s_async_globals) == 0x27B7C, "s_async_globals");

/* ---------- prototypes */

/* ---------- globals */

static bool g_async_setup_initialized;
static s_async_globals g_async_globals;

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// public: static long const s_static_array<struct s_async_thread_context, 4>::k_element_count; // "?k_element_count@?$s_static_array@Us_async_thread_context@@$03@@2JB"

// void `vector destructor iterator'(void *, unsigned int, int, void (*)(void *));
// void async_setup_initialize(void);
// void async_setup_dispose(void);
// long async_setup_get_encoding_bit_count_for_thread_indices(void);
// void async_setup_set_thread_count(long);
// long async_setup_get_thread_count(void);
// void async_setup_set_categories_for_thread(long, long const *, long);
// void async_setup_synchronization_for_thread(long, struct s_semaphore, struct s_critical_section, struct s_critical_section, struct s_virtual_guard_block);
// void async_setup_set_thread_work_delay(long, long);
// void async_setup_set_free_list_blocked_callback_for_thread(long, void (*)(void));
// void async_setup_set_profiler(class c_async_profile_interface *);
// void async_setup_set_compare_interface_for_thread(long, struct s_async_task_compare_interface *);
// long async_setup_get_thread_work_delay(long);
// public: long c_interlocked_int32::operator long(void) const;
// public: long c_interlocked_int32::peek(void) const volatile;
// long async_setup_get_thread_index_for_category(long);
// bool async_setup_is_thread_index_valid(long);
// struct s_async_thread_context * async_setup_get_context_for_thread(long);
// struct s_async_thread_context * async_setup_get_context_for_category(long);
// long async_setup_get_total_tasks_added(void);
// long async_setup_increment_total_tasks_added(void);
// class c_async_profile_interface * async_setup_get_registered_profiler(void);
// struct s_async_task_compare_interface * async_setup_get_compare_interface_for_thread(long);
// public: void s_static_array<long, 32>::set_all(long const &);
// public: void s_static_array<long, 32>::set_memory(long);
// bool pointer_is_aligned(void const *, long);
// unsigned long address_from_pointer(void const *);
// bool address_is_aligned(unsigned long, long);
// public: void s_static_array<struct s_async_task_priority_timings, 32>::set_memory(long);
// public: void s_static_array<struct t_thread_safe_list<struct s_async_task_element>::s_list_element, 128>::set_memory(long);
// public: static long s_static_array<struct s_async_thread_context, 4>::get_count(void);
// public: void t_thread_safe_list<struct s_async_task_element>::initialize(struct s_critical_section);
// public: void t_thread_safe_list<struct s_async_task_element>::dispose(void);
// public: void t_thread_safe_list<struct s_async_task_element>::add_element_to_front(struct t_thread_safe_list<struct s_async_task_element>::s_list_element *);
// public: struct s_async_thread_context & s_static_array<struct s_async_thread_context, 4>::operator[]<long>(long);
// public: long & s_static_array<long, 32>::operator[]<long>(long);
// bool operator!=<unsigned long>(unsigned long const &, enum e_none_sentinel const &);
// public: static bool s_static_array<struct s_async_thread_context, 4>::valid<long>(long);
// public: static bool s_static_array<long, 32>::valid<long>(long);
// bool operator==<unsigned long>(unsigned long const &, enum e_none_sentinel const &);
// public: s_async_globals::s_async_globals(void);
// public: s_static_array<struct s_async_thread_context, 4>::s_static_array<struct s_async_thread_context, 4>(void);
// public: s_async_thread_context::s_async_thread_context(void);
// public: c_interlocked_int32::c_interlocked_int32(void);
// public: s_async_thread_internal_statistics::s_async_thread_internal_statistics(void);
// public: t_thread_safe_list<struct s_async_task_element>::t_thread_safe_list<struct s_async_task_element>(void);
// public: s_async_globals::~s_async_globals(void);
// public: s_static_array<struct s_async_thread_context, 4>::~s_static_array<struct s_async_thread_context, 4>(void);
// public: s_async_thread_context::~s_async_thread_context(void);
// public: c_interlocked_int32::~c_interlocked_int32(void);
// public: s_async_thread_internal_statistics::~s_async_thread_internal_statistics(void);
// public: t_thread_safe_list<struct s_async_task_element>::~t_thread_safe_list<struct s_async_task_element>(void);
// void g_async_globals::`dynamic atexit destructor'(void);

void async_setup_initialize(void)
{
    mangled_ppc("?async_setup_initialize@@YAXXZ");

    assert_tag_debug_untracked_jul_11_2011(46, !g_async_setup_initialized);

    g_async_globals.total_tasks_added.set(0);
    g_async_globals.profiler = NULL;
    g_async_globals.thread_index_for_category.set_all(NONE);
    g_async_globals.max_thread_count = NONE;

    for (long thread_index = 0; thread_index < g_async_globals.thread_contexts.get_count(); thread_index++)
    {
        s_async_thread_context * context = &g_async_globals.thread_contexts[thread_index];
        context->work_available_semaphore.object_id = NONE;
        context->unknown9C2C.set(0);
        context->free_list_blocked_callback = NULL;
        context->statistics.unknown4.set(0);
        context->statistics.unknown0 = 0;
        context->statistics.unknown8.set_memory(0);
        context->statistics.unknown88.set_memory(0);
        context->statistics.priority_timings.set_memory(0);
        context->compare_interface.unknown0 = NULL;
        context->compare_interface.unknown8 = NULL;
        context->compare_interface.compare = NULL;
    }

    g_async_setup_initialized = true;
};

void async_setup_dispose(void)
{
    mangled_ppc("?async_setup_dispose@@YAXXZ");

    assert_tag_debug_untracked_jul_11_2011(84, g_async_setup_initialized);

    g_async_globals.thread_index_for_category.set_all(NONE);
    g_async_globals.max_thread_count = NONE;

    for (long thread_index = 0; thread_index < g_async_globals.max_thread_count; thread_index++)
    {
        s_async_thread_context * context = &g_async_globals.thread_contexts[thread_index];
        context->thread_index = thread_index;
        context->free_list.dispose();
        context->work_list.dispose();
        context->free_list_blocked_callback = NULL;
    }

    g_async_setup_initialized = false;
};

long async_setup_get_encoding_bit_count_for_thread_indices(void)
{
    mangled_ppc("?async_setup_get_encoding_bit_count_for_thread_indices@@YAJXZ");

    return 2;
};

void async_setup_set_thread_count(long thread_count)
{
    mangled_ppc("?async_setup_set_thread_count@@YAXJ@Z");

    assert_tag_debug_untracked_jul_11_2011(115, g_async_setup_initialized);
    assert_tag_debug_untracked_jul_11_2011(116, thread_count>0);
    assert_tag_debug_untracked_jul_11_2011(117, thread_count<k_max_async_thread_count);

    g_async_globals.max_thread_count = thread_count;
};

long async_setup_get_thread_count(void)
{
    mangled_ppc("?async_setup_get_thread_count@@YAJXZ");

    assert_tag_debug_untracked_jul_11_2011(127, g_async_setup_initialized);

    return g_async_globals.max_thread_count;
};

void async_setup_set_categories_for_thread(long thread_index, long const * categories, long category_count)
{
    mangled_ppc("?async_setup_set_categories_for_thread@@YAXJPBJJ@Z");

    assert_tag_debug_untracked_jul_11_2011(137, g_async_setup_initialized);
    assert_tag_debug_untracked_jul_11_2011(138, async_setup_is_thread_index_valid(thread_index));
    assert_tag_debug_untracked_jul_11_2011(139, categories!=NULL);
    assert_tag_debug_untracked_jul_11_2011(140, VALID_COUNT(category_count, k_maximum_async_category));

    for (long category_index = 0; category_index < category_count; category_index++)
    {
        long category = categories[category_index];
        g_async_globals.thread_index_for_category[category] = thread_index;
    }
};

void async_setup_synchronization_for_thread(long thread_index, s_semaphore work_available_semaphore, s_critical_section free_list_section, s_critical_section work_list_section, s_virtual_guard_block guard_block)
{
    mangled_ppc("?async_setup_synchronization_for_thread@@YAXJUs_semaphore@@Us_critical_section@@1Us_virtual_guard_block@@@Z");

    s_async_thread_context * context = NULL;

    assert_tag_debug_untracked_jul_11_2011(160, g_async_setup_initialized);
    assert_tag_debug_untracked_jul_11_2011(163, free_list_section.object_id!=work_list_section.object_id);
    assert_tag_debug_untracked_jul_11_2011(166, free_list_section.object_id!=NONE);
    assert_tag_debug_untracked_jul_11_2011(167, work_list_section.object_id!=NONE);
    assert_tag_debug_untracked_jul_11_2011(170, work_available_semaphore.object_id!=NONE);
    assert_tag_debug_untracked_jul_11_2011(173, semaphore_get_initial_count(work_available_semaphore)==0);
    assert_tag_debug_untracked_jul_11_2011(174, semaphore_get_maximum_count(work_available_semaphore)==k_maximum_async_work_items_per_thread);

    context = async_setup_get_context_for_thread(thread_index);
    context->work_available_semaphore = work_available_semaphore;
    context->free_list.initialize(free_list_section);
    context->work_list.initialize(work_list_section);
    context->guard_block = guard_block;
    context->element_storage.set_memory(0);

    for (long element_index = 0; element_index < context->element_storage.get_count(); element_index++)
    {
        context->element_storage[element_index].data.task_id = k_invalid_async_task_id;
        context->free_list.add_element_to_front(&context->element_storage[element_index]);
    }
};

void async_setup_set_thread_work_delay(long thread_index, long work_delay)
{
    mangled_ppc("?async_setup_set_thread_work_delay@@YAXJJ@Z");

    async_setup_get_context_for_thread(thread_index)->work_delay.set(work_delay);
};

void async_setup_set_free_list_blocked_callback_for_thread(long thread_index, void (*callback)(void))
{
    mangled_ppc("?async_setup_set_free_list_blocked_callback_for_thread@@YAXJP6AXXZ@Z");

    s_async_thread_context * context = NULL;

    assert_tag_debug_untracked_jul_11_2011(212, g_async_setup_initialized);

    context = async_setup_get_context_for_thread(thread_index);
    context->free_list_blocked_callback = callback;
};

void async_setup_set_profiler(c_async_profile_interface * profiler)
{
    mangled_ppc("?async_setup_set_profiler@@YAXPAVc_async_profile_interface@@@Z");

    char const * block_names[k_async_profile_block_count] = { NULL };

    assert_tag_debug_untracked_jul_11_2011(224, g_async_setup_initialized);

    g_async_globals.profiler = profiler;

    for (long block_index = 0; block_index < NUMBEROF(block_names); block_index++)
    {
        block_names[block_index] = async_profile_get_block_name(static_cast<e_async_profile_blocks>(block_index));
    }

    profiler->register_profile_blocks(block_names, NUMBEROF(block_names));
};

void async_setup_set_compare_interface_for_thread(long thread_index, s_async_task_compare_interface * compare_interface)
{
    mangled_ppc("?async_setup_set_compare_interface_for_thread@@YAXJPAUs_async_task_compare_interface@@@Z");

    assert_tag_debug_untracked_jul_11_2011(243, g_async_setup_initialized);

    s_async_thread_context * context = async_setup_get_context_for_thread(thread_index);
    if (compare_interface != NULL)
    {
        context->compare_interface = *compare_interface;
    }
    else
    {
        context->compare_interface.unknown0 = NULL;
        context->compare_interface.compare = NULL;
        context->compare_interface.unknown8 = NULL;
    }
};

long async_setup_get_thread_work_delay(long thread_index)
{
    mangled_ppc("?async_setup_get_thread_work_delay@@YAJJ@Z");

    long work_delay = 0;
    work_delay = async_setup_get_context_for_thread(thread_index)->work_delay;

    return work_delay;
};

long async_setup_get_thread_index_for_category(long category)
{
    mangled_ppc("?async_setup_get_thread_index_for_category@@YAJJ@Z");

    long thread_index = NONE;

    assert_tag_debug_untracked_jul_11_2011(278, g_async_setup_initialized);

    thread_index = g_async_globals.thread_index_for_category[category];

    assert_tag_debug_untracked_jul_11_2011(284, VALID_INDEX(thread_index, g_async_globals.max_thread_count));

    return thread_index;
};

bool async_setup_is_thread_index_valid(long thread_index)
{
    mangled_ppc("?async_setup_is_thread_index_valid@@YA_NJ@Z");

    bool valid = false;
    if (g_async_setup_initialized)
    {
        valid = VALID_INDEX(thread_index, k_max_async_thread_count);
        valid = valid && VALID_INDEX(thread_index, g_async_globals.max_thread_count);
    }

    return valid;
};

s_async_thread_context * async_setup_get_context_for_thread(long thread_index)
{
    mangled_ppc("?async_setup_get_context_for_thread@@YAPAUs_async_thread_context@@J@Z");

    assert_tag_debug_untracked_jul_11_2011(306, g_async_setup_initialized);
    assert_tag_debug_untracked_jul_11_2011(307, async_setup_is_thread_index_valid(thread_index));

    return &g_async_globals.thread_contexts[thread_index];
};

s_async_thread_context * async_setup_get_context_for_category(long category)
{
    mangled_ppc("?async_setup_get_context_for_category@@YAPAUs_async_thread_context@@J@Z");

    long thread_index = NONE;
    s_async_thread_context * context = NULL;

    assert_tag_debug_untracked_jul_11_2011(318, g_async_setup_initialized);

    thread_index = async_setup_get_thread_index_for_category(category);
    context = async_setup_get_context_for_thread(thread_index);

    return context;
};

long async_setup_get_total_tasks_added(void)
{
    mangled_ppc("?async_setup_get_total_tasks_added@@YAJXZ");

    assert_tag_debug_untracked_jul_11_2011(329, g_async_setup_initialized);

    return g_async_globals.total_tasks_added.peek();
};

long async_setup_increment_total_tasks_added(void)
{
    mangled_ppc("?async_setup_increment_total_tasks_added@@YAJXZ");

    assert_tag_debug_untracked_jul_11_2011(337, g_async_setup_initialized);

    return g_async_globals.total_tasks_added.add(1);
};

c_async_profile_interface * async_setup_get_registered_profiler(void)
{
    mangled_ppc("?async_setup_get_registered_profiler@@YAPAVc_async_profile_interface@@XZ");

    assert_tag_debug_untracked_jul_11_2011(346, g_async_setup_initialized);

    return g_async_globals.profiler;
};

s_async_task_compare_interface * async_setup_get_compare_interface_for_thread(long thread_index)
{
    mangled_ppc("?async_setup_get_compare_interface_for_thread@@YAPAUs_async_task_compare_interface@@J@Z");

    s_async_thread_context * context = NULL;

    assert_tag_debug_untracked_jul_11_2011(356, g_async_setup_initialized);

    context = async_setup_get_context_for_thread(thread_index);

    return &context->compare_interface;
};
