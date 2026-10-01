#pragma once
#ifndef __THREADLIB_UNIT_TESTS_H__
#define __THREADLIB_UNIT_TESTS_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"

/* ---------- constants */

/* ---------- definitions */

struct s_unit_test_function
{
    char const * name;
    void (* function)(void);
};
static_assert(sizeof(s_unit_test_function) == 0x8, "s_unit_test_function");

/* ---------- prototypes */

extern void threadlib_run_unit_tests(void);

/* ---------- globals */

extern s_unit_test_function g_threadlib_unit_test_functions[];

/* ---------- public code */

#endif // __THREADLIB_UNIT_TESTS_H__

