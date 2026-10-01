#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\foundation\\baselib\\multithreading\\threads\\thread_manipulation_xenon.cpp"
/* ---------- headers */

#include "foundation\baselib\multithreading\threads\thread_manipulation_xenon.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_events.h"
#include "core\corelib\cseries\cseries_macros.h"

#include <xtl.h>

/* ---------- constants */

#ifndef VALID_HANDLE
#define VALID_HANDLE(handle) ((handle) != NULL && (handle) != INVALID_HANDLE_VALUE)
#endif

/* ---------- definitions */

// Xenon KPCR (r13), only the fields used here
struct s_xenon_processor_control_region
{
    unsigned char unknown0[0x6C];
    long in_dpc;
    char * stack_base;
    char * stack_limit;
    char * dpc_stack_base;
    char * dpc_stack_limit;
};

/* ---------- prototypes */

// compiler intrinsic (alias __gregister_get): reads a general purpose register
extern "C" unsigned __int64 __GPRGetReg(const int register_index);

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// enum e_thread_xenon_processor thread_get_current_thread_xenon_processor(void);
// void thread_set_xenon_processor(struct s_thread_handle, enum e_thread_xenon_processor);
// long thread_get_total_stack_bytes(void);
// long thread_get_current_used_stack_bytes(void);
// long thread_get_current_remaining_stack_bytes(void);

e_thread_xenon_processor thread_get_current_thread_xenon_processor(void)
{
    mangled_ppc("?thread_get_current_thread_xenon_processor@@YA?AW4e_thread_xenon_processor@@XZ");

    unsigned long processor = GetCurrentProcessorNumber();
    assert_tag_debug_untracked_jul_11_2011(26, VALID_INDEX(processor, k_thread_xenon_processor_count));

    return static_cast<e_thread_xenon_processor>(processor);
};

void thread_set_xenon_processor(s_thread_handle thread_handle, e_thread_xenon_processor processor)
{
    mangled_ppc("?thread_set_xenon_processor@@YAXUs_thread_handle@@W4e_thread_xenon_processor@@@Z");

    void * handle = thread_handle.handle;
    assert_tag_debug_untracked_jul_11_2011(37, VALID_HANDLE(handle));
    assert_tag_debug_untracked_jul_11_2011(38, VALID_INDEX(processor, k_thread_xenon_processor_count));

    unsigned long result = XSetThreadProcessor(handle, processor);
    if (result >= 0)
    {
    }
    else
    {
        event(_event_error, "threads:xenon: XSetThreadProcessor(%p, %d) failed with error 0x%08X", thread_handle.handle, processor, GetLastError());
    }
};

// $TODO nonmatching
long thread_get_total_stack_bytes(void)
{
    mangled_ppc("?thread_get_total_stack_bytes@@YAJXZ");

    char * limit;
    s_xenon_processor_control_region * pcr = reinterpret_cast<s_xenon_processor_control_region *>(__GPRGetReg(13));
    char * stack_start;
    if (pcr->in_dpc == 0)
    {
        limit = pcr->stack_limit;
        stack_start = pcr->stack_base;
    }
    else
    {
        limit = pcr->dpc_stack_limit;
        stack_start = pcr->dpc_stack_base;
    }

    return stack_start - limit;
};

//long thread_get_current_used_stack_bytes(void)
//{
//    mangled_ppc("?thread_get_current_used_stack_bytes@@YAJXZ");
//};

//long thread_get_current_remaining_stack_bytes(void)
//{
//    mangled_ppc("?thread_get_current_remaining_stack_bytes@@YAJXZ");
//};
