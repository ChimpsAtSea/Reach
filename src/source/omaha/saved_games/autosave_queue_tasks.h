#pragma once
#ifndef __AUTOSAVE_QUEUE_TASKS_H__
#define __AUTOSAVE_QUEUE_TASKS_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"
#include "foundation\baselib\datatypes\static_string.h"
#include "foundation\threadlib\async\async.h"
#include "omaha\saved_games\autosave_queue.h"
#include "omaha\saved_games\content\content_item_metadata.h"
#include "omaha\saved_games\saved_game_file_tasks.h"
#include "omaha\tag_files\files.h"

/* ---------- constants */

/* ---------- definitions */

class c_synchronized_int32;
template<typename t_result> class c_async_task;

// held in c_typed_opaque_data<c_autosave_queue_enumerate_async, 0x994, 4> (autosave_queue_category_bucket_data_component.obj)
class c_autosave_queue_enumerate_async
{
public:
    // defined in autosave_queue.obj (75)
    static unsigned int const k_max_item_count;

    static bool submit(c_autosave_queue_enumerate_async * task, c_synchronized_int32 * cancel, c_async_task<e_async_completion> * out_task);

    c_autosave_queue_enumerate_async(e_content_item_type content_type, s_autosave_queue_item * out_items, unsigned int out_item_max_count, unsigned int * out_item_count);
    e_async_completion operator()(c_synchronized_int32 * cancel);

private:
    enum e_state
    {
        _state_start_finding_files = 0,
        _state_find_next_file,
        _state_read_metadata,
        _state_finish_finding_files,

        k_state_count
    };

    e_async_completion start_finding_files(c_synchronized_int32 * cancel);
    void switch_state(e_state state);
    e_async_completion find_next_file(c_synchronized_int32 * cancel);
    e_async_completion read_metadata(c_synchronized_int32 * cancel);
    e_async_completion finish_finding_files(c_synchronized_int32 * cancel);

    s_autosave_queue_item * m_out_items; // 0x0
    unsigned int m_out_item_max_count; // 0x4
    unsigned int * m_out_item_count; // 0x8
    e_state m_state; // 0xC
    s_file_reference m_directory; // 0x10
    c_static_string<256> m_search_spec; // 0x120
    s_find_file_data m_find_data; // 0x220
    s_file_reference m_file; // 0x5A8
    s_file_last_modification_date m_modification_date; // 0x6B8
    s_content_item_metadata m_metadata; // 0x6C0
    c_saved_game_file_load_metadata_async m_load_metadata; // 0x970
};
static_assert(sizeof(c_autosave_queue_enumerate_async) == 0x974, "c_autosave_queue_enumerate_async");

/* ---------- prototypes */

extern void autosave_queue_sort_items_by_file_modification_date(s_autosave_queue_item * begin, s_autosave_queue_item * end);
extern void autosave_queue_sort_items_by_metadata_display_name(s_autosave_queue_item * begin, s_autosave_queue_item * end);

/* ---------- globals */

/* ---------- public code */

#endif // __AUTOSAVE_QUEUE_TASKS_H__

