#pragma once
#ifndef __FILE_PLATFORM_ERRORS_WINDOWS_H__
#define __FILE_PLATFORM_ERRORS_WINDOWS_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"

/* ---------- constants */

/* ---------- definitions */

struct s_file_platform_error
{
    unsigned long error_code; // GetLastError()
};
static_assert(sizeof(s_file_platform_error) == 0x4, "s_file_platform_error");

/* ---------- prototypes */

void file_platform_get_error(s_file_platform_error * error);
void file_platform_clear_last_error(void);
void file_platform_format_error(s_file_platform_error const * error, char * buffer, long buffer_size);

/* ---------- globals */

/* ---------- public code */

#endif // __FILE_PLATFORM_ERRORS_WINDOWS_H__

