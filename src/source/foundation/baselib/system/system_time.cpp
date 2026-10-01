#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\foundation\\baselib\\system\\system_time.cpp"
/* ---------- headers */

#include "foundation\baselib\system\system_time.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_macros.h"
#include "core\corelib\cseries\cseries_string.h"
#include "foundation\baselib\files\file_time_windows.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// void system_print_date_and_time(enum e_date_and_time_print_format, char *, long);

void system_print_date_and_time(e_date_and_time_print_format format, char * buffer, long buffer_size)
{
    mangled_ppc("?system_print_date_and_time@@YAXW4e_date_and_time_print_format@@PADJ@Z");

    assert_tag_debug_untracked_jul_11_2011(23, VALID_INDEX(format, k_date_and_time_print_format_count));

    s_file_time current_time;
    s_file_time_unpacked unpacked_time;

    file_time_get_current_time(&current_time);
    if (file_time_unpack(&current_time, _file_time_unpack_mode_local, &unpacked_time))
    {
        if (format == _date_and_time_print_format_filename)
        {
            csnzprintf(buffer, buffer_size, "%02d%02d%02d_%02d%02d%02d",
                unpacked_time.month,
                unpacked_time.day,
                unpacked_time.year % 100,
                unpacked_time.hour,
                unpacked_time.minute,
                unpacked_time.second);
        }
        else
        {
            csnzprintf(buffer, buffer_size, "%02d.%02d.%02d %02d:%02d:%02d.%03d",
                unpacked_time.month,
                unpacked_time.day,
                unpacked_time.year % 100,
                unpacked_time.hour,
                unpacked_time.minute,
                unpacked_time.second,
                unpacked_time.millisecond);
        }
    }
    else
    {
        csstrnzcpy(buffer, "", buffer_size);
    }
};

