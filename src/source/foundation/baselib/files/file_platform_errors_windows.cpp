#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\foundation\\baselib\\files\\file_platform_errors_windows.cpp"
/* ---------- headers */

#include "foundation\baselib\files\file_platform_errors_windows.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_memory.h"
#include "core\corelib\cseries\cseries_string.h"

#include <xtl.h>

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// void file_platform_get_error(struct s_file_platform_error *);
// void file_platform_clear_last_error(void);
// void file_platform_format_error(struct s_file_platform_error const *, char *, long);

void file_platform_get_error(s_file_platform_error * error)
{
    mangled_ppc("?file_platform_get_error@@YAXPAUs_file_platform_error@@@Z");

    csmemset(error, 0, sizeof(s_file_platform_error));
    error->error_code = GetLastError();
};

void file_platform_clear_last_error(void)
{
    mangled_ppc("?file_platform_clear_last_error@@YAXXZ");

    SetLastError(0);
};

void file_platform_format_error(s_file_platform_error const * error, char * buffer, long buffer_size)
{
    mangled_ppc("?file_platform_format_error@@YAXPBUs_file_platform_error@@PADJ@Z");

    assert_tag_debug_untracked_jul_11_2011(39, error);
    csnzprintf(buffer, buffer_size, "0x%08x", error->error_code);
};

