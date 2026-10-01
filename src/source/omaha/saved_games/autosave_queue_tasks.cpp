#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\saved_games\\autosave_queue_tasks.cpp"
/* ---------- headers */

#include "omaha\saved_games\autosave_queue_tasks.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_events.h"
#include "core\corelib\cseries\cseries_macros.h"
#include "foundation\baselib\algorithms\qsort.h"
#include "omaha\interface\async\async_helpers.h"
#include "omaha\saved_games\saved_game_files.h"
#include "omaha\shell\shell.h"
#include "omaha\text\unicode.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

static bool item_compare_sort_by_file_modification_date(void const * element_a, void const * element_b, void const * context);
static bool item_compare_sort_by_metadata_display_name(void const * element_a, void const * element_b, void const * context);

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// void autosave_queue_sort_items_by_file_modification_date(struct s_autosave_queue_item *, struct s_autosave_queue_item *);
// void autosave_queue_sort_items_by_metadata_display_name(struct s_autosave_queue_item *, struct s_autosave_queue_item *);
// public: static bool c_autosave_queue_enumerate_async::submit(class c_autosave_queue_enumerate_async *, class c_synchronized_int32*, class c_async_task<enum e_async_completion> *);
// public: c_autosave_queue_enumerate_async::c_autosave_queue_enumerate_async(enum e_content_item_type, struct s_autosave_queue_item *, unsigned int, unsigned int *);
// public: enum e_async_completion c_autosave_queue_enumerate_async::operator()(class c_synchronized_int32*);
// private: enum e_async_completion c_autosave_queue_enumerate_async::start_finding_files(class c_synchronized_int32*);
// private: void c_autosave_queue_enumerate_async::switch_state(enum c_autosave_queue_enumerate_async::e_state);
// private: enum e_async_completion c_autosave_queue_enumerate_async::find_next_file(class c_synchronized_int32*);
// public: void c_saved_game_file_load_metadata_async::reset(void);
// private: enum e_async_completion c_autosave_queue_enumerate_async::read_metadata(class c_synchronized_int32*);
// private: enum e_async_completion c_autosave_queue_enumerate_async::finish_finding_files(class c_synchronized_int32*);
// bool item_compare_sort_by_file_modification_date(void const *, void const *, void const *);
// bool item_compare_sort_by_metadata_display_name(void const *, void const *, void const *);
// class c_async_function1<enum e_async_completion, struct s_async_indirect_function1<class c_autosave_queue_enumerate_async, class c_synchronized_int32*>, class c_synchronized_int32*> async_function_make<class c_autosave_queue_enumerate_async, class c_synchronized_int32*>(class c_autosave_queue_enumerate_async *, class c_synchronized_int32*);
// bool async_function_submit<enum e_async_completion, class c_async_function1<enum e_async_completion, struct s_async_indirect_function1<class c_autosave_queue_enumerate_async, class c_synchronized_int32*>, class c_synchronized_int32*> >(class c_async_function1<enum e_async_completion, struct s_async_indirect_function1<class c_autosave_queue_enumerate_async, class c_synchronized_int32*>, class c_synchronized_int32*> const &, long, long, class c_async_task<enum e_async_completion> *);
// public: s_async_indirect_function1<class c_autosave_queue_enumerate_async, class c_synchronized_int32*>::s_async_indirect_function1<class c_autosave_queue_enumerate_async, class c_synchronized_int32*>(class c_autosave_queue_enumerate_async *);
// public: c_async_function1<enum e_async_completion, struct s_async_indirect_function1<class c_autosave_queue_enumerate_async, class c_synchronized_int32*>, class c_synchronized_int32*>::c_async_function1<enum e_async_completion, struct s_async_indirect_function1<class c_autosave_queue_enumerate_async, class c_synchronized_int32*>, class c_synchronized_int32*>(struct s_async_indirect_function1<class c_autosave_queue_enumerate_async, class c_synchronized_int32*>, class c_synchronized_int32*);
// public: static bool s_async_task_functions::submit<enum e_async_completion, class c_async_function1<enum e_async_completion, struct s_async_indirect_function1<class c_autosave_queue_enumerate_async, class c_synchronized_int32*>, class c_synchronized_int32*> >(class c_async_function1<enum e_async_completion, struct s_async_indirect_function1<class c_autosave_queue_enumerate_async, class c_synchronized_int32*>, class c_synchronized_int32*> const &, long, long, class c_async_task<enum e_async_completion> *);
// public: static enum e_async_completion s_async_callback_context<enum e_async_completion, class c_async_function1<enum e_async_completion, struct s_async_indirect_function1<class c_autosave_queue_enumerate_async, class c_synchronized_int32*>, class c_synchronized_int32*> >::callback(void *);
// public: s_async_callback_context<enum e_async_completion, class c_async_function1<enum e_async_completion, struct s_async_indirect_function1<class c_autosave_queue_enumerate_async, class c_synchronized_int32*>, class c_synchronized_int32*> >::s_async_callback_context<enum e_async_completion, class c_async_function1<enum e_async_completion, struct s_async_indirect_function1<class c_autosave_queue_enumerate_async, class c_synchronized_int32*>, class c_synchronized_int32*> >(class c_async_task<enum e_async_completion> *, class c_async_function1<enum e_async_completion, struct s_async_indirect_function1<class c_autosave_queue_enumerate_async, class c_synchronized_int32*>, class c_synchronized_int32*> const &);
// struct s_async_task_id async_task_add<struct s_async_callback_context<enum e_async_completion, class c_async_function1<enum e_async_completion, struct s_async_indirect_function1<class c_autosave_queue_enumerate_async, class c_synchronized_int32*>, class c_synchronized_int32*> > >(long, struct s_async_callback_context<enum e_async_completion, class c_async_function1<enum e_async_completion, struct s_async_indirect_function1<class c_autosave_queue_enumerate_async, class c_synchronized_int32*>, class c_synchronized_int32*> > const *, long, enum e_async_completion (*)(void *), class c_async_completion_flag *);
// public: enum e_async_completion c_async_function1<enum e_async_completion, struct s_async_indirect_function1<class c_autosave_queue_enumerate_async, class c_synchronized_int32*>, class c_synchronized_int32*>::operator()(void);
// struct s_async_task_id async_task_add_ex<struct s_async_callback_context<enum e_async_completion, class c_async_function1<enum e_async_completion, struct s_async_indirect_function1<class c_autosave_queue_enumerate_async, class c_synchronized_int32*>, class c_synchronized_int32*> > >(long, struct s_async_callback_context<enum e_async_completion, class c_async_function1<enum e_async_completion, struct s_async_indirect_function1<class c_autosave_queue_enumerate_async, class c_synchronized_int32*>, class c_synchronized_int32*> > const *, long, enum e_async_completion (*)(void *), class c_async_completion_flag *, enum e_async_block_if_full);
// public: enum e_async_completion s_async_indirect_function1<class c_autosave_queue_enumerate_async, class c_synchronized_int32*>::operator()(class c_synchronized_int32*);

void autosave_queue_sort_items_by_file_modification_date(s_autosave_queue_item * begin, s_autosave_queue_item * end)
{
    mangled_ppc("?autosave_queue_sort_items_by_file_modification_date@@YAXPAUs_autosave_queue_item@@0@Z");

    assert_tag_debug_untracked_jul_11_2011(27, end >= begin);
    unsigned int item_count = end - begin;
    if (item_count > 1)
    {
        qsort_elements(begin, item_count, sizeof(s_autosave_queue_item), item_compare_sort_by_file_modification_date, NULL);
    }
};

void autosave_queue_sort_items_by_metadata_display_name(s_autosave_queue_item * begin, s_autosave_queue_item * end)
{
    mangled_ppc("?autosave_queue_sort_items_by_metadata_display_name@@YAXPAUs_autosave_queue_item@@0@Z");

    assert_tag_debug_untracked_jul_11_2011(42, end >= begin);
    unsigned int item_count = end - begin;
    if (item_count > 1)
    {
        qsort_elements(begin, item_count, sizeof(s_autosave_queue_item), item_compare_sort_by_metadata_display_name, NULL);
    }
};

bool c_autosave_queue_enumerate_async::submit(c_autosave_queue_enumerate_async * task, c_synchronized_int32 * cancel, c_async_task<e_async_completion> * out_task)
{
    mangled_ppc("?submit@c_autosave_queue_enumerate_async@@SA_NPAV1@PAVc_synchronized_int32@@PAV?$c_async_task@W4e_async_completion@@@@@Z");

    bool success = false;
    if (shell_has_utility_drive())
    {
        success = async_function_submit(async_function_make(task, cancel), 0, 12, out_task);
    }
    return success;
};

c_autosave_queue_enumerate_async::c_autosave_queue_enumerate_async(e_content_item_type content_type, s_autosave_queue_item * out_items, unsigned int out_item_max_count, unsigned int * out_item_count) :
    m_out_items(out_items),
    m_out_item_max_count(out_item_max_count),
    m_out_item_count(out_item_count),
    m_state(_state_start_finding_files),
    m_search_spec(),
    m_load_metadata()
{
    mangled_ppc("??0c_autosave_queue_enumerate_async@@QAA@W4e_content_item_type@@PAUs_autosave_queue_item@@IPAI@Z");

    assert_tag_debug_untracked_jul_11_2011(84, m_out_items);
    assert_tag_debug_untracked_jul_11_2011(85, m_out_item_count);
    char const * extension = saved_game_files_get_extension_for_type(content_type, true);
    file_reference_create_from_path(&m_directory, autosave_queue_get_directory_path(), true);
    m_search_spec.print("*.%s", extension ? extension : "*");
};

e_async_completion c_autosave_queue_enumerate_async::operator()(c_synchronized_int32 * cancel)
{
    mangled_ppc("??Rc_autosave_queue_enumerate_async@@QAA?AW4e_async_completion@@PAVc_synchronized_int32@@@Z");

    e_async_completion result = _async_completion_retry;
    switch (m_state)
    {
    case _state_start_finding_files:
        result = start_finding_files(cancel);
        break;
    case _state_find_next_file:
        result = find_next_file(cancel);
        break;
    case _state_read_metadata:
        result = read_metadata(cancel);
        break;
    case _state_finish_finding_files:
        result = finish_finding_files(cancel);
        break;
    }
    return result;
};

e_async_completion c_autosave_queue_enumerate_async::start_finding_files(c_synchronized_int32 * cancel)
{
    mangled_ppc("?start_finding_files@c_autosave_queue_enumerate_async@@AAA?AW4e_async_completion@@PAVc_synchronized_int32@@@Z");

    e_async_completion result = _async_completion_retry;
    if (!is_canceled(cancel))
    {
        find_files_start_with_search_spec(&m_find_data, 0, &m_directory, m_search_spec.get_string());
        *m_out_item_count = 0;
        switch_state(_state_find_next_file);
    }
    else
    {
        result = _async_completion_done;
    }
    return result;
};

void c_autosave_queue_enumerate_async::switch_state(e_state state)
{
    mangled_ppc("?switch_state@c_autosave_queue_enumerate_async@@AAAXW4e_state@1@@Z");

    m_state = state;
};

e_async_completion c_autosave_queue_enumerate_async::find_next_file(c_synchronized_int32 * cancel)
{
    mangled_ppc("?find_next_file@c_autosave_queue_enumerate_async@@AAA?AW4e_async_completion@@PAVc_synchronized_int32@@@Z");

    if (!is_canceled(cancel) && VALID_INDEX(*m_out_item_count, m_out_item_max_count) && find_files_next(&m_find_data, &m_file, &m_modification_date))
    {
        m_load_metadata.reset();
        switch_state(_state_read_metadata);
    }
    else
    {
        switch_state(_state_finish_finding_files);
    }
    return _async_completion_retry;
};

e_async_completion c_autosave_queue_enumerate_async::read_metadata(c_synchronized_int32 * cancel)
{
    mangled_ppc("?read_metadata@c_autosave_queue_enumerate_async@@AAA?AW4e_async_completion@@PAVc_synchronized_int32@@@Z");

    e_async_pending_bool load_result = m_load_metadata(&m_file, &m_metadata, cancel);
    if (load_result == _async_pending_bool_true)
    {
        s_autosave_queue_item * item = &m_out_items[(*m_out_item_count)++];
        s_static_string<256> path;
        file_reference_get_path(&m_file, path.get_buffer(), sizeof(path));
        file_reference_create_from_path(&item->file, path.get_string(), false);
        item->modification_date = m_modification_date;
        item->size_in_bytes = 0;
        file_get_size(&m_file, &item->size_in_bytes);
        item->metadata = m_metadata;
        switch_state(_state_find_next_file);
    }
    else if (load_result == _async_pending_bool_false)
    {
        if (!is_canceled(cancel))
        {
            s_static_string<256> path;
            event_wrapped(_event_warning, "autosave_queue_enumerate_async:read_metadata: failed to read metadata for \"%s\"; deleting", file_reference_get_path(&m_file, path.get_buffer(), sizeof(path)));
            file_delete(&m_file);
        }
        switch_state(_state_find_next_file);
    }
    return _async_completion_retry;
};

e_async_completion c_autosave_queue_enumerate_async::finish_finding_files(c_synchronized_int32 * cancel)
{
    mangled_ppc("?finish_finding_files@c_autosave_queue_enumerate_async@@AAA?AW4e_async_completion@@PAVc_synchronized_int32@@@Z");

    find_files_end(&m_find_data);
    return _async_completion_done;
};

bool item_compare_sort_by_file_modification_date(void const * element_a, void const * element_b, void const * context)
{
    mangled_ppc("?item_compare_sort_by_file_modification_date@@YA_NPBX00@Z");

    s_autosave_queue_item const * item0 = static_cast<s_autosave_queue_item const *>(element_a);
    s_autosave_queue_item const * item1 = static_cast<s_autosave_queue_item const *>(element_b);
    return file_compare_last_modification_dates(&item0->modification_date, &item1->modification_date) <= 0;
};

bool item_compare_sort_by_metadata_display_name(void const * element_a, void const * element_b, void const * context)
{
    mangled_ppc("?item_compare_sort_by_metadata_display_name@@YA_NPBX00@Z");

    s_autosave_queue_item const * item0 = static_cast<s_autosave_queue_item const *>(element_a);
    s_autosave_queue_item const * item1 = static_cast<s_autosave_queue_item const *>(element_b);
    return ustrncmp(item0->metadata.name, item1->metadata.name, NUMBEROF(item0->metadata.name)) > 0;
};

