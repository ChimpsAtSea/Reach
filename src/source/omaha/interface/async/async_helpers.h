#ifndef __ASYNC_HELPERS_H__
#define __ASYNC_HELPERS_H__
#pragma once

/* ---------- headers */

#include "baselib\synchronized_value_windows.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_macros.h"
#include "foundation\threadlib\async\async.h"

/* ---------- constants */

/* ---------- definitions */

// "f i", owned by online_file_transfer_tracker.obj
class c_async_task_base
{
public:
    bool is_valid(void) const
    {
        return async_task_id_is_valid(m_task_id);
    }

    bool is_complete(void) const
    {
        return is_valid() && m_completion_flag.is_done();
    }

    // public: written directly by s_async_task_functions::submit
    s_async_task_id m_task_id; // 0x0
    c_async_completion_flag m_completion_flag; // 0x4
};
static_assert(sizeof(c_async_task_base) == 0xC, "c_async_task_base");

template<typename t_result>
class c_async_task :
    public c_async_task_base
{
public:
    void set_result(t_result const & result)
    {
        m_result = result;
    }

protected:
    t_result m_result; // 0xC
};

template<typename t_result>
struct s_async_result_traits;

template<>
struct s_async_result_traits<e_async_completion>
{
    static e_async_completion get_completion(e_async_completion result)
    {
        return result;
    }
};

// calls t_class::operator()(t_arg1) on an object
template<typename t_class, typename t_arg1>
struct s_async_indirect_function1
{
    s_async_indirect_function1(t_class * in_function) :
        function(in_function)
    {
        assert_decomp(function, "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\interface/async/async_helpers.h", 551);
    }

    e_async_completion operator()(t_arg1 arg1)
    {
        return (*function)(arg1);
    }

    t_class * function; // 0x0
};

template<typename t_result, typename t_function, typename t_arg1>
class c_async_function1
{
public:
    c_async_function1(t_function function, t_arg1 arg1) :
        m_function(function),
        m_arg1(arg1)
    {
    }

    t_result operator()(void)
    {
        return m_function(m_arg1);
    }

private:
    t_function m_function; // 0x0
    t_arg1 m_arg1;
};

template<typename t_result, typename t_function>
struct s_async_callback_context
{
    s_async_callback_context(c_async_task<t_result> * in_task, t_function const & in_function) :
        task(in_task),
        function(in_function)
    {
    }

    static e_async_completion callback(void * callback_context)
    {
        s_async_callback_context * context = static_cast<s_async_callback_context *>(callback_context);
        t_result value = context->function();
        e_async_completion completion = s_async_result_traits<t_result>::get_completion(value);
        context->task->set_result(value);
        return completion;
    }

    c_async_task<t_result> * task; // 0x0
    t_function function; // 0x4
};

struct s_async_task_functions
{
    template<typename t_result, typename t_function>
    static bool submit(t_function const & function, long priority, long category, c_async_task<t_result> * out_task)
    {
        assert_decomp(out_task, "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\interface/async/async_helpers.h", 248);
        assert_decomp(!out_task->is_valid() || out_task->is_complete(), "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\interface/async/async_helpers.h", 249);

        s_async_callback_context<t_result, t_function> callback_context(out_task, function);
        s_async_task_id task_id = async_task_add(priority, &callback_context, category, s_async_callback_context<t_result, t_function>::callback, &out_task->m_completion_flag);
        out_task->m_task_id = task_id;
        return async_task_id_is_valid(task_id);
    }
};

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

// "f i", owned by network_blf_compress.obj
inline bool is_canceled(c_synchronized_int32 * cancel)
{
    return cancel && cancel->peek();
}

template<typename t_class, typename t_arg1>
c_async_function1<e_async_completion, s_async_indirect_function1<t_class, t_arg1>, t_arg1> async_function_make(t_class * object, t_arg1 arg1)
{
    return c_async_function1<e_async_completion, s_async_indirect_function1<t_class, t_arg1>, t_arg1>(s_async_indirect_function1<t_class, t_arg1>(object), arg1);
}

template<typename t_result, typename t_function>
bool async_function_submit(t_function const & function, long priority, long category, c_async_task<t_result> * out_task)
{
    return s_async_task_functions::submit(function, priority, category, out_task);
}

#endif // __ASYNC_HELPERS_H__

