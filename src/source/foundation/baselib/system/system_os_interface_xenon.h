#pragma once
#ifndef __SYSTEM_OS_INTERFACE_XENON_H__
#define __SYSTEM_OS_INTERFACE_XENON_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"
#include "foundation\baselib\datatypes\static_string.h"

/* ---------- constants */

/* ---------- definitions */

// layout verified from system_get_operating_system_version (csmemset 0x48, fields at 0x0/0x4/0x24/0x28)
struct s_operating_system_version
{
    long system_version;
    s_static_string<32> system_version_string;
    long xtl_version;
    s_static_string<32> xtl_version_string;
};
static_assert(sizeof(s_operating_system_version) == 0x48, "s_operating_system_version");

/* ---------- prototypes */

extern void system_register_exit_function(void (* const exit_function)(void));
extern bool system_get_operating_system_version(s_operating_system_version * out_version);
extern long system_execute_command(char const * command);

/* ---------- globals */

/* ---------- public code */

#endif // __SYSTEM_OS_INTERFACE_XENON_H__

