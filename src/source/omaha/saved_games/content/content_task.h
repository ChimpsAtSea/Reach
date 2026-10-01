#pragma once
#ifndef __CONTENT_TASK_H__
#define __CONTENT_TASK_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"
#include "baselib\synchronized_value_windows.h"
#include "foundation\threadlib\async\async.h"
#include "omaha\input\controllers.h"
#include "omaha\memory\wrapped_arrays.h"

/* ---------- constants */

// $TODO: enumerators not reversed yet
enum e_content_task_type
{
    _content_task_type_none = 0,
};

enum e_content_task_handle_type
{
    _content_task_handle_type_none = 0,
    _content_task_handle_type_overlapped,
    _content_task_handle_type_async,

    k_content_task_handle_type_count
};

/* ---------- definitions */

class c_overlapped_task;

struct s_content_task_private_data
{
    e_controller_index controller_index; // 0x0
    e_content_task_type type; // 0x4
    e_content_task_handle_type handle_type; // 0x8
    struct
    {
        s_async_task_id task_id; // 0x0
        c_async_completion_flag completion_flag; // 0x4
    } m_async_handle; // 0xC
    c_overlapped_task * overlapped_task; // 0x18
    bool submitted; // 0x1C
    bool succeeded; // 0x1D
    c_synchronized_int32 complete; // 0x20
};
static_assert(sizeof(s_content_task_private_data) == 0x24, "s_content_task_private_data");

class c_content_task
{
public:
    c_content_task(void);
    virtual ~c_content_task(void);

    c_typed_opaque_data<s_content_task_private_data, 36, 4> m_private_data; // 0x4
};
static_assert(sizeof(c_content_task) == 0x2C, "c_content_task");

/* ---------- prototypes */

void content_task_initialize(c_content_task * const task, e_content_task_type type);
void content_task_per_use_initialize(c_content_task * const task);
void content_task_pre_submit(c_content_task * const task, e_controller_index controller_index);
void content_task_post_submit(c_content_task * const task, bool submitted);
void content_task_set_complete(c_content_task * const task, bool succeeded);
void content_task_set_overlapped_handle(c_content_task * const task, c_overlapped_task * const overlapped_task);
bool content_task_async_task_add(c_content_task * const task, e_async_completion (*callback)(void *));
e_content_task_type content_task_get_type(c_content_task const * const task);
bool content_task_in_progress(c_content_task const * const task);
bool content_task_is_complete(c_content_task const * const task);
bool content_task_is_complete_and_succeeded(c_content_task const * const task);
bool content_task_is_complete_and_failed(c_content_task const * const task);
void content_task_block_until_complete(c_content_task * const task);
e_controller_index content_task_get_controller_index(c_content_task const * const task);
void content_task_set_async_handle(c_content_task * const task);

/* ---------- globals */

/* ---------- public code */

#endif // __CONTENT_TASK_H__

