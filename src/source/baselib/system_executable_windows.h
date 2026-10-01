#pragma once
#ifndef __SYSTEM_EXECUTABLE_WINDOWS_H__
#define __SYSTEM_EXECUTABLE_WINDOWS_H__

/* ---------- headers */

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

extern bool system_executable_is_address_constant_and_static(void const volatile * address);

/* ---------- globals */

extern char k_read_only_data_start;
extern char k_read_only_data_end;

/* ---------- public code */

#endif // __SYSTEM_EXECUTABLE_WINDOWS_H__

