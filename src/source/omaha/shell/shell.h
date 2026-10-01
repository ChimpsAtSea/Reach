#pragma once
#ifndef __SHELL_H__
#define __SHELL_H__

/* ---------- headers */

/* ---------- constants */

/* ---------- definitions */

enum e_shell_tool_type
{
    _shell_tool_invalid = 0,
    _shell_tool_interactive,
    _shell_tool_command_line,

    k_shell_tool_count
};

/* ---------- prototypes */

e_shell_tool_type shell_tool_type(void);
extern bool shell_has_utility_drive(void);

/* ---------- globals */

extern bool const g_managed_dll;

/* ---------- public code */

#endif // __SHELL_H__

