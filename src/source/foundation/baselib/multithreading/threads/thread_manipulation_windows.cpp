#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\foundation\\baselib\\multithreading\\threads\\thread_manipulation_windows.cpp"
/* ---------- headers */

#include "foundation\baselib\multithreading\threads\thread_manipulation_windows.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_events.h"
#include "core\corelib\cseries\cseries_macros.h"
#include "core\corelib\cseries\cseries_memory.h"
#include "foundation\baselib\multithreading\synchronization\synchronization_manager.h"
#include "omaha\cseries\cseries.h"

#include <xtl.h>

/* ---------- constants */

#ifndef VALID_HANDLE
#define VALID_HANDLE(handle) ((handle) != NULL && (handle) != INVALID_HANDLE_VALUE)
#endif

static unsigned long const k_ms_vc_exception = 0x406D1388;
static unsigned long const k_thread_name_info_type = 0x1000;

/* ---------- definitions */

struct THREADNAME_INFO
{
    unsigned long dwType;
    char const * szName;
    unsigned long dwThreadID;
    unsigned long dwFlags;
};
static_assert(sizeof(THREADNAME_INFO) == 0x10, "THREADNAME_INFO");

/* ---------- prototypes */

/* ---------- globals */

s_thread_handle const k_thread_handle_invalid = { INVALID_HANDLE_VALUE };
s_thread_id const k_thread_id_invalid = { static_cast<unsigned long>(NONE) };

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// struct s_thread_handle const k_thread_handle_invalid; // "?k_thread_handle_invalid@@3Us_thread_handle@@B"
// struct s_thread_id const k_thread_id_invalid; // "?k_thread_id_invalid@@3Us_thread_id@@B"

// enum e_thread_priority thread_get_priority(struct s_thread_handle);
// void thread_set_priority(struct s_thread_handle, enum e_thread_priority);
// bool thread_handle_valid(struct s_thread_handle);
// struct s_thread_handle thread_get_current_handle(void);
// bool thread_id_valid(struct s_thread_id);
// struct s_thread_id thread_get_current_id(void);
// ?thread_create@@YA?AUs_thread_handle@@Q6AKPAX@Z0W4e_thread_creation_state@@W4e_thread_creation_inheritance@@IPAUs_thread_id@@@Z;
// void thread_resume(struct s_thread_handle);
// void thread_destroy(struct s_thread_handle);
// void thread_wait(struct s_thread_handle);
// bool thread_wait_timeout(struct s_thread_handle, long);
// void thread_set_current_thread_name_for_platform(char const *);

e_thread_priority thread_get_priority(s_thread_handle thread_handle)
{
    mangled_ppc("?thread_get_priority@@YA?AW4e_thread_priority@@Us_thread_handle@@@Z");

    HANDLE handle = thread_handle.handle;
    e_thread_priority priority = _thread_priority_normal;
    assert_tag_debug_untracked_jul_11_2011(44, VALID_HANDLE(handle));

    long windows_priority = GetThreadPriority(handle);
    if (windows_priority == THREAD_PRIORITY_ERROR_RETURN)
    {
        event(_event_error, "threads: GetThreadPriority failed with error 0x%08X", GetLastError());
    }
    else
    {
        switch (windows_priority)
        {
        case THREAD_PRIORITY_IDLE:
            priority = _thread_priority_idle;
            break;
        case THREAD_PRIORITY_LOWEST:
            priority = _thread_priority_lowest;
            break;
        case THREAD_PRIORITY_BELOW_NORMAL:
            priority = _thread_priority_below_normal;
            break;
        case THREAD_PRIORITY_NORMAL:
            priority = _thread_priority_normal;
            break;
        case THREAD_PRIORITY_ABOVE_NORMAL:
            priority = _thread_priority_above_normal;
            break;
        case THREAD_PRIORITY_HIGHEST:
            priority = _thread_priority_highest;
            break;
        case THREAD_PRIORITY_TIME_CRITICAL:
            priority = _thread_priority_time_critical;
            break;
        default:
            if (windows_priority > 0)
            {
                priority = _thread_priority_above_normal;
            }
            else
            {
                priority = _thread_priority_below_normal;
            }
            break;
        }
    }

    return priority;
};

void thread_set_priority(s_thread_handle thread_handle, e_thread_priority priority)
{
    mangled_ppc("?thread_set_priority@@YAXUs_thread_handle@@W4e_thread_priority@@@Z");

    HANDLE handle = thread_handle.handle;
    long windows_priority = THREAD_PRIORITY_NORMAL;
    assert_tag_debug_untracked_jul_11_2011(101, VALID_HANDLE(handle));

    switch (priority)
    {
    case _thread_priority_idle:
        windows_priority = THREAD_PRIORITY_IDLE;
        break;
    case _thread_priority_lowest:
        windows_priority = THREAD_PRIORITY_LOWEST;
        break;
    case _thread_priority_below_normal:
        windows_priority = THREAD_PRIORITY_BELOW_NORMAL;
        break;
    case _thread_priority_normal:
        windows_priority = THREAD_PRIORITY_NORMAL;
        break;
    case _thread_priority_above_normal:
        windows_priority = THREAD_PRIORITY_ABOVE_NORMAL;
        break;
    case _thread_priority_highest:
        windows_priority = THREAD_PRIORITY_HIGHEST;
        break;
    case _thread_priority_time_critical:
        windows_priority = THREAD_PRIORITY_TIME_CRITICAL;
        break;
    default:
        dassert_tag_debug_untracked_jul_11_2011(127, false, "unreachable");
        break;
    }

    if (SetThreadPriority(handle, windows_priority))
    {
    }
    else
    {
        event(_event_error, "threads: SetThreadPriority failed with error 0x%08X", GetLastError());
    }
};

bool thread_handle_valid(s_thread_handle thread_handle)
{
    mangled_ppc("?thread_handle_valid@@YA_NUs_thread_handle@@@Z");

    return VALID_HANDLE(thread_handle.handle);
};

s_thread_handle thread_get_current_handle(void)
{
    mangled_ppc("?thread_get_current_handle@@YA?AUs_thread_handle@@XZ");

    s_thread_handle handle = { GetCurrentThread() };
    assert_tag_debug_untracked_jul_11_2011(153, thread_handle_valid(handle));

    return handle;
};

bool thread_id_valid(s_thread_id thread_id)
{
    mangled_ppc("?thread_id_valid@@YA_NUs_thread_id@@@Z");

    return thread_id.id != 0 && thread_id.id != NONE;
};

s_thread_id thread_get_current_id(void)
{
    mangled_ppc("?thread_get_current_id@@YA?AUs_thread_id@@XZ");

    s_thread_id thread = { GetCurrentThreadId() };
    assert_tag_debug_untracked_jul_11_2011(170, thread_id_valid(thread));

    return thread;
};

s_thread_handle thread_create(unsigned long (* const thread_function)(void *), void * thread_parameters, e_thread_creation_state creation_state, e_thread_creation_inheritance creation_inheritance, unsigned int stack_size, s_thread_id * out_thread_id)
{
    mangled_ppc("?thread_create@@YA?AUs_thread_handle@@Q6AKPAX@Z0W4e_thread_creation_state@@W4e_thread_creation_inheritance@@IPAUs_thread_id@@@Z");

    HANDLE handle = INVALID_HANDLE_VALUE;
    unsigned long thread_id = static_cast<unsigned long>(NONE);
    LPSECURITY_ATTRIBUTES security_attributes = NULL;
    assert_tag_debug_untracked_jul_11_2011(188, thread_function);
    assert_tag_debug_untracked_jul_11_2011(189, VALID_INDEX(creation_state, k_thread_creation_state_count));

    s_thread_handle thread_handle;
    thread_handle.handle = NULL;

    handle = CreateThread(security_attributes, stack_size, thread_function, thread_parameters, (creation_state == _thread_creation_state_suspended) * CREATE_SUSPENDED, &thread_id);
    if (VALID_HANDLE(handle))
    {
        thread_handle.handle = handle;
    }
    else
    {
        event(_event_error, "threads: CreateThread failed with error 0x%08X", GetLastError());
    }

    if (out_thread_id)
    {
        out_thread_id->id = thread_id;
    }

    return thread_handle;
};

void thread_resume(s_thread_handle thread_handle)
{
    mangled_ppc("?thread_resume@@YAXUs_thread_handle@@@Z");

    HANDLE handle = thread_handle.handle;
    assert_tag_debug_untracked_jul_11_2011(227, VALID_HANDLE(handle));

    unsigned long previous_suspend_count = ResumeThread(handle);
    if (previous_suspend_count > 0)
    {
    }
    else if (previous_suspend_count == 0)
    {
    }
    else
    {
        event(_event_error, "threads: ResumeThread failed(%d) with error 0x%08X", previous_suspend_count, GetLastError());
    }
};

void thread_destroy(s_thread_handle thread_handle)
{
    mangled_ppc("?thread_destroy@@YAXUs_thread_handle@@@Z");

    HANDLE handle = thread_handle.handle;
    assert_tag_debug_untracked_jul_11_2011(248, VALID_HANDLE(handle));

    if (CloseHandle(handle))
    {
    }
    else
    {
        event(_event_error, "threads: thread_destroy failed in CloseHandle with error 0x%08X", GetLastError());
    }
};

void thread_wait(s_thread_handle thread_handle)
{
    mangled_ppc("?thread_wait@@YAXUs_thread_handle@@@Z");

    bool success = wait_for_single_object_internal(thread_handle.handle, INFINITE);
    dassert_tag_debug_untracked_jul_11_2011(265, success, "thread_wait: wait_for_single_object_internal failed");
};

bool thread_wait_timeout(s_thread_handle thread_handle, long timeout)
{
    mangled_ppc("?thread_wait_timeout@@YA_NUs_thread_handle@@J@Z");

    return wait_for_single_object_internal(thread_handle.handle, timeout);
};

void thread_set_current_thread_name_for_platform(char const * name)
{
    mangled_ppc("?thread_set_current_thread_name_for_platform@@YAXPBD@Z");

    assert_tag_debug_untracked_jul_11_2011(282, name);

    THREADNAME_INFO info;
    csmemset(&info, 0, sizeof(info));
    info.dwType = k_thread_name_info_type;
    info.szName = name;
    info.dwThreadID = static_cast<unsigned long>(NONE);

    __try
    {
        RaiseException(k_ms_vc_exception, 0, sizeof(info) / sizeof(unsigned long), reinterpret_cast<ULONG_PTR *>(&info));
    }
    __except (EXCEPTION_CONTINUE_EXECUTION)
    {
    }

    PIXNameThread(name);
};

