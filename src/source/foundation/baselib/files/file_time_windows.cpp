#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\foundation\\baselib\\files\\file_time_windows.cpp"
/* ---------- headers */

#include <xtl.h>
#include "foundation\baselib\files\file_time_windows.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_macros.h"
#include "core\corelib\cseries\cseries_memory.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

bool file_time_to_local_system_time(FILETIME const * file_time, SYSTEMTIME * out_local_system_time);
bool local_system_time_to_file_time(SYSTEMTIME const * local_system_time, FILETIME * out_file_time);

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// long file_time_compare(struct s_file_time const *, struct s_file_time const *);
// void file_time_get_current_time(struct s_file_time *);
// bool file_time_unpack(struct s_file_time const *, enum e_file_time_unpack_mode, struct s_file_time_unpacked *);
// bool file_time_pack(struct s_file_time_unpacked const *, enum e_file_time_unpack_mode, struct s_file_time *);
// bool file_time_to_local_system_time(struct _FILETIME const *, struct _SYSTEMTIME *);
// bool local_system_time_to_file_time(struct _SYSTEMTIME const *, struct _FILETIME *);

long file_time_compare(s_file_time const * time1, s_file_time const * time2)
{
    mangled_ppc("?file_time_compare@@YAJPBUs_file_time@@0@Z");
    FILETIME const * file_time1 = reinterpret_cast<FILETIME const *>(time1);
    FILETIME const * file_time2 = reinterpret_cast<FILETIME const *>(time2);
    assert_tag_debug_untracked_jul_11_2011(28, time1!=NULL);
    assert_tag_debug_untracked_jul_11_2011(29, time2!=NULL);
    return CompareFileTime(file_time1, file_time2);
};

void file_time_get_current_time(s_file_time * out_time)
{
    mangled_ppc("?file_time_get_current_time@@YAXPAUs_file_time@@@Z");
    FILETIME file_time;
    assert_tag_debug_untracked_jul_11_2011(40, out_time);
    GetSystemTimeAsFileTime(&file_time);
    csmemcpy(out_time, &file_time, sizeof(file_time));
};

bool file_time_unpack(s_file_time const * time, e_file_time_unpack_mode unpack_mode, s_file_time_unpacked * out_unpacked_time)
{
    mangled_ppc("?file_time_unpack@@YA_NPBUs_file_time@@W4e_file_time_unpack_mode@@PAUs_file_time_unpacked@@@Z");
    bool success;
    SYSTEMTIME system_time;
    {
        FILETIME const * file_time = reinterpret_cast<FILETIME const *>(time);
        success = false;
        assert_tag_debug_untracked_jul_11_2011(55, time);
        assert_tag_debug_untracked_jul_11_2011(56, VALID_INDEX(unpack_mode, k_file_time_unpack_mode_count));
        assert_tag_debug_untracked_jul_11_2011(57, out_unpacked_time);
        csmemset(&system_time, 0, sizeof(system_time));
        if (unpack_mode == _file_time_unpack_mode_utc)
        {
            if (FileTimeToSystemTime(file_time, &system_time))
            {
                success = true;
            }
        }
        else
        {
            success = file_time_to_local_system_time(file_time, &system_time);
        }
        csmemset(out_unpacked_time, 0, sizeof(s_file_time_unpacked));
        if (success)
        {
            out_unpacked_time->year = system_time.wYear;
            out_unpacked_time->month = system_time.wMonth;
            out_unpacked_time->day = system_time.wDay;
            out_unpacked_time->hour = system_time.wHour;
            out_unpacked_time->minute = system_time.wMinute;
            out_unpacked_time->second = system_time.wSecond;
            out_unpacked_time->millisecond = system_time.wMilliseconds;
        }
    }
    return success;
};

bool file_time_pack(s_file_time_unpacked const * unpacked_time, e_file_time_unpack_mode unpack_mode, s_file_time * out_time)
{
    mangled_ppc("?file_time_pack@@YA_NPBUs_file_time_unpacked@@W4e_file_time_unpack_mode@@PAUs_file_time@@@Z");
    SYSTEMTIME system_time;
    FILETIME file_time;
    bool success = true;
    assert_tag_debug_untracked_jul_11_2011(99, unpacked_time);
    assert_tag_debug_untracked_jul_11_2011(100, VALID_INDEX(unpack_mode, k_file_time_unpack_mode_count));
    assert_tag_debug_untracked_jul_11_2011(101, out_time);
    csmemset(&system_time, 0, sizeof(system_time));
    system_time.wYear = unpacked_time->year;
    system_time.wMonth = unpacked_time->month;
    system_time.wDay = unpacked_time->day;
    system_time.wHour = unpacked_time->hour;
    system_time.wMinute = unpacked_time->minute;
    system_time.wSecond = unpacked_time->second;
    system_time.wMilliseconds = unpacked_time->millisecond;
    if (unpack_mode == _file_time_unpack_mode_utc)
    {
        if (SystemTimeToFileTime(&system_time, &file_time))
        {
            success = true;
        }
    }
    else
    {
        success = local_system_time_to_file_time(&system_time, &file_time);
    }
    if (success)
    {
        csmemcpy(out_time, &file_time, sizeof(file_time));
    }
    else
    {
        csmemset(out_time, 0, sizeof(s_file_time));
    }
    return success;
};

bool file_time_to_local_system_time(FILETIME const * file_time, SYSTEMTIME * out_local_system_time)
{
    mangled_ppc("?file_time_to_local_system_time@@YA_NPBU_FILETIME@@PAU_SYSTEMTIME@@@Z");
    FILETIME local_file_time;
    bool success = false;
    assert_tag_debug_untracked_jul_11_2011(150, file_time);
    assert_tag_debug_untracked_jul_11_2011(151, out_local_system_time);
    csmemset(out_local_system_time, 0, sizeof(SYSTEMTIME));
    if (FileTimeToLocalFileTime(file_time, &local_file_time) && FileTimeToSystemTime(&local_file_time, out_local_system_time))
    {
        success = true;
    }
    return success;
};

bool local_system_time_to_file_time(SYSTEMTIME const * local_system_time, FILETIME * out_file_time)
{
    mangled_ppc("?local_system_time_to_file_time@@YA_NPBU_SYSTEMTIME@@PAU_FILETIME@@@Z");
    FILETIME local_file_time;
    bool success = false;
    assert_tag_debug_untracked_jul_11_2011(178, local_system_time);
    assert_tag_debug_untracked_jul_11_2011(179, out_file_time);
    csmemset(out_file_time, 0, sizeof(FILETIME));
    if (SystemTimeToFileTime(local_system_time, &local_file_time) && LocalFileTimeToFileTime(&local_file_time, out_file_time))
    {
        success = true;
    }
    return success;
};
