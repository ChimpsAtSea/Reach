#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\saved_games\\content\\content_task.cpp"
/* ---------- headers */

#include "omaha\saved_games\content\content_task.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "omaha\cseries\async_spasm.h"
#include "omaha\cseries\async_xoverlapped.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// public: c_content_task::c_content_task(void);
// merged_835C3968;
// public: virtual c_content_task::~c_content_task(void);
// void content_task_initialize(class c_content_task *const, enum e_content_task_type);
// void content_task_per_use_initialize(class c_content_task *const);
// void content_task_pre_submit(class c_content_task *const, enum e_controller_index);
// void content_task_post_submit(class c_content_task *const, bool);
// void content_task_set_complete(class c_content_task *const, bool);
// void content_task_set_overlapped_handle(class c_content_task *const, class c_overlapped_task *const);
// bool content_task_async_task_add(class c_content_task *const, enum e_async_completion (*)(void *));
// enum e_content_task_type content_task_get_type(class c_content_task const *const);
// bool content_task_in_progress(class c_content_task const *const);
// bool content_task_is_complete(class c_content_task const *const);
// bool content_task_is_complete_and_succeeded(class c_content_task const *const);
// bool content_task_is_complete_and_failed(class c_content_task const *const);
// void content_task_block_until_complete(class c_content_task *const);
// enum e_controller_index content_task_get_controller_index(class c_content_task const *const);
// void content_task_set_async_handle(class c_content_task *const);
// public: c_typed_opaque_data<struct s_content_task_private_data, 36, 4>::c_typed_opaque_data<struct s_content_task_private_data, 36, 4>(void);
// public: c_typed_opaque_data<struct s_content_task_private_data, 36, 4>::~c_typed_opaque_data<struct s_content_task_private_data, 36, 4>(void);
// public: struct s_content_task_private_data * c_typed_opaque_data<struct s_content_task_private_data, 36, 4>::construct(void);
// public: void c_typed_opaque_data<struct s_content_task_private_data, 36, 4>::destruct(void);
// public: struct s_content_task_private_data * c_typed_opaque_data<struct s_content_task_private_data, 36, 4>::get(void);
// public: struct s_content_task_private_data const * c_typed_opaque_data<struct s_content_task_private_data, 36, 4>::get_const(void) const;
// public: bool c_typed_opaque_data<struct s_content_task_private_data, 36, 4>::alive(void) const;
// public: s_content_task_private_data::s_content_task_private_data(void);
// public: void * s_content_task_private_data::`scalar deleting destructor'(unsigned int);
// public: s_content_task_private_data::<unnamed-type-m_async_handle>::<unnamed-type-m_async_handle>(void);
// public: s_content_task_private_data::~s_content_task_private_data(void);
// public: s_content_task_private_data::<unnamed-type-m_async_handle>::~<unnamed-type-m_async_handle>(void);
// public: struct s_content_task_private_data * c_opaque_data<struct s_content_task_private_data, 36, 4>::get(void);
// struct s_async_task_id async_task_add<class c_content_task *>(long, class c_content_task *const *, long, enum e_async_completion (*)(void *), class c_async_completion_flag *);
// struct s_async_task_id async_task_add_ex<class c_content_task *>(long, class c_content_task *const *, long, enum e_async_completion (*)(void *), class c_async_completion_flag *, enum e_async_block_if_full);

c_content_task::c_content_task(void)
{
    mangled_ppc("??0c_content_task@@QAA@XZ");

    if (m_private_data.alive())
    {
        m_private_data.destruct();
    }
    m_private_data.construct();
};

//merged_835C3968
//{
//    mangled_ppc("merged_835C3968");
//};

c_content_task::~c_content_task(void)
{
    mangled_ppc("??1c_content_task@@UAA@XZ");

    if (m_private_data.alive())
    {
        m_private_data.destruct();
    }
};

void content_task_initialize(c_content_task * const task, e_content_task_type type)
{
    mangled_ppc("?content_task_initialize@@YAXQAVc_content_task@@W4e_content_task_type@@@Z");

    if (task->m_private_data.alive())
    {
        task->m_private_data.destruct();
    }
    task->m_private_data.construct();
    task->m_private_data.get()->type = type;
    task->m_private_data.get()->handle_type = _content_task_handle_type_none;
    content_task_per_use_initialize(task);
};

void content_task_per_use_initialize(c_content_task * const task)
{
    mangled_ppc("?content_task_per_use_initialize@@YAXQAVc_content_task@@@Z");

    task->m_private_data.get()->m_async_handle.task_id = k_invalid_async_task_id;
    task->m_private_data.get()->overlapped_task = NULL;
    task->m_private_data.get()->submitted = false;
    task->m_private_data.get()->succeeded = false;
    task->m_private_data.get()->complete.set(false);
};

void content_task_pre_submit(c_content_task * const task, e_controller_index controller_index)
{
    mangled_ppc("?content_task_pre_submit@@YAXQAVc_content_task@@W4e_controller_index@@@Z");

    task->m_private_data.get()->controller_index = controller_index;
};

void content_task_post_submit(c_content_task * const task, bool submitted)
{
    mangled_ppc("?content_task_post_submit@@YAXQAVc_content_task@@_N@Z");

    if (submitted)
    {
        task->m_private_data.get()->submitted = true;
    }
};

void content_task_set_complete(c_content_task * const task, bool succeeded)
{
    mangled_ppc("?content_task_set_complete@@YAXQAVc_content_task@@_N@Z");

    task->m_private_data.get()->succeeded = succeeded;
    task->m_private_data.get()->complete.set(true);
};

void content_task_set_overlapped_handle(c_content_task * const task, c_overlapped_task * const overlapped_task)
{
    mangled_ppc("?content_task_set_overlapped_handle@@YAXQAVc_content_task@@QAVc_overlapped_task@@@Z");

    task->m_private_data.get()->handle_type = _content_task_handle_type_overlapped;
    task->m_private_data.get()->overlapped_task = overlapped_task;
};

bool content_task_async_task_add(c_content_task * const task, e_async_completion (*callback)(void *))
{
    mangled_ppc("?content_task_async_task_add@@YA_NQAVc_content_task@@P6A?AW4e_async_completion@@PAX@Z@Z");

    bool result = false;
    task->m_private_data.get()->m_async_handle.task_id = async_task_add(0, &task, 10, callback, &task->m_private_data.get()->m_async_handle.completion_flag);
    if (async_task_id_is_valid(task->m_private_data.get()->m_async_handle.task_id))
    {
        result = true;
        content_task_set_async_handle(task);
    }

    return result;
};

e_content_task_type content_task_get_type(c_content_task const * const task)
{
    mangled_ppc("?content_task_get_type@@YA?AW4e_content_task_type@@QBVc_content_task@@@Z");

    return task->m_private_data.get_const()->type;
};

bool content_task_in_progress(c_content_task const * const task)
{
    mangled_ppc("?content_task_in_progress@@YA_NQBVc_content_task@@@Z");

    return task->m_private_data.get_const()->submitted && !content_task_is_complete(task);
};

bool content_task_is_complete(c_content_task const * const task)
{
    mangled_ppc("?content_task_is_complete@@YA_NQBVc_content_task@@@Z");

    return static_cast<bool>(task->m_private_data.get_const()->complete.peek());
};

bool content_task_is_complete_and_succeeded(c_content_task const * const task)
{
    mangled_ppc("?content_task_is_complete_and_succeeded@@YA_NQBVc_content_task@@@Z");

    return content_task_is_complete(task) && task->m_private_data.get_const()->succeeded;
};

bool content_task_is_complete_and_failed(c_content_task const * const task)
{
    mangled_ppc("?content_task_is_complete_and_failed@@YA_NQBVc_content_task@@@Z");

    return content_task_is_complete(task) && !task->m_private_data.get_const()->succeeded;
};

void content_task_block_until_complete(c_content_task * const task)
{
    mangled_ppc("?content_task_block_until_complete@@YAXQAVc_content_task@@@Z");

    if (content_task_in_progress(task))
    {
        switch (task->m_private_data.get()->handle_type)
        {
        case _content_task_handle_type_overlapped:
        {
            overlapped_task_block_until_finished(task->m_private_data.get()->overlapped_task);
        }
        break;
        case _content_task_handle_type_async:
        {
            async_yield_until_done_internal(&task->m_private_data.get()->m_async_handle.completion_flag, true, false);
        }
        break;
        default:
        {
            dassert_tag_debug_untracked_jul_11_2011(217, false, "unreachable");
        }
        break;
        }
    }
};

e_controller_index content_task_get_controller_index(c_content_task const * const task)
{
    mangled_ppc("?content_task_get_controller_index@@YA?AW4e_controller_index@@QBVc_content_task@@@Z");

    return task->m_private_data.get_const()->controller_index;
};

void content_task_set_async_handle(c_content_task * const task)
{
    mangled_ppc("?content_task_set_async_handle@@YAXQAVc_content_task@@@Z");

    task->m_private_data.get()->handle_type = _content_task_handle_type_async;
};
