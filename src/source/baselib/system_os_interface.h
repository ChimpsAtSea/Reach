#pragma once
#ifndef __SYSTEM_OS_INTERFACE_H__
#define __SYSTEM_OS_INTERFACE_H__

/* ---------- headers */

/* ---------- constants */

/* ---------- definitions */

// only _application_exit_code_failure (1) verified (assert_handler_instance.obj)
enum e_application_exit_code
{
    _application_exit_code_success = 0,
    _application_exit_code_failure,

    k_application_exit_code_count
};

/* ---------- prototypes */

extern void system_exit_application(e_application_exit_code exit_code);
extern void system_register_halt_function(void (* const halt_function)());
extern void (* system_get_halt_function())();

/* ---------- globals */

/* ---------- public code */

#endif // __SYSTEM_OS_INTERFACE_H__

