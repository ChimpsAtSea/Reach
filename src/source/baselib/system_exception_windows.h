#pragma once
#ifndef __SYSTEM_EXCEPTION_WINDOWS_H__
#define __SYSTEM_EXCEPTION_WINDOWS_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"

/* ---------- constants */

/* ---------- definitions */

struct s_exception_pointers;

// layout not yet recovered; size from c_thread_base::c_thread_base (csmemset of 0xA70)
struct s_exception_information
{
    unsigned char data[0xA70];
};
static_assert(sizeof(s_exception_information) == 0xA70, "s_exception_information");

/* ---------- prototypes */

extern void system_build_exception_information(s_exception_pointers * exception_pointers, s_exception_information * exception_information);

/* ---------- globals */

/* ---------- public code */

#endif // __SYSTEM_EXCEPTION_WINDOWS_H__

