#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\foundation\\baselib\\files\\file_errors.cpp"
/* ---------- headers */

#include "foundation\baselib\files\file_errors.h"
#include "baselib\file_interface.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_events.h"
#include "core\corelib\cseries\cseries_macros.h"
#include "foundation\baselib\datatypes\static_string.h"
#include "foundation\baselib\errors\events\event_globals.h"
#include "foundation\baselib\files\file_path.h"
#include "foundation\baselib\files\file_platform_errors_windows.h"
#include "foundation\baselib\files\file_synchronous_io.h"
#include "foundation\baselib\multithreading\primitives\thread_local_storage.h"

/* ---------- constants */

/* ---------- definitions */

struct s_file_error_state
{
    long suppression_level;
};

/* ---------- prototypes */

/* ---------- globals */

static __declspec(thread) s_file_error_state g_file_error_state;

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// void file_errors_suppress_push(void);
// void file_errors_suppress_pop(void);
// bool file_errors_suppressed(void);
// void file_error(char const *, enum e_file_error_mode, struct s_file_accessor const *);
// void file_utility_error(char const *, enum e_file_error_mode, class c_file_path const *, class c_file_path const *);
// public: static long s_static_string<1024>::max_length(void);

void file_errors_suppress_push(void)
{
    mangled_ppc("?file_errors_suppress_push@@YAXXZ");

    TLS_DATA_GET_VALUE_REFERENCE(g_file_error_state).suppression_level++;
};

void file_errors_suppress_pop(void)
{
    mangled_ppc("?file_errors_suppress_pop@@YAXXZ");

    assert_tag_debug_untracked_jul_11_2011(43, TLS_DATA_GET_VALUE_REFERENCE(g_file_error_state).suppression_level>0);
    TLS_DATA_GET_VALUE_REFERENCE(g_file_error_state).suppression_level--;
};

bool file_errors_suppressed(void)
{
    mangled_ppc("?file_errors_suppressed@@YA_NXZ");

    return TLS_DATA_GET_VALUE_REFERENCE(g_file_error_state).suppression_level > 0;
};

void file_error(char const * location, e_file_error_mode error_mode, s_file_accessor const * file)
{
    mangled_ppc("?file_error@@YAXPBDW4e_file_error_mode@@PBUs_file_accessor@@@Z");

    assert_tag_debug_untracked_jul_11_2011(61, location);
    assert_tag_debug_untracked_jul_11_2011(62, file_valid(file));

    s_file_platform_error error;
    file_platform_get_error(&error);

    if (error_mode != _file_error_mode_silent)
    {
        s_static_string<1024> file_string;
        s_static_string<1024> error_string;
        file_string.print("'%s'", file->path.get_string());
        file_platform_format_error(&error, error_string.get_buffer(), error_string.max_length());

        if (!file_errors_suppressed())
        {
            event(_event_warning, "files: %s(%s) error %s", location, file_string.get_string(), error_string.get_string());
        }
        else
        {
            events_internal_error("files: %s(%s) error %s", location, file_string.get_string(), error_string.get_string());
        }
    }

    file_platform_clear_last_error();
};

void file_utility_error(char const * location, e_file_error_mode error_mode, c_file_path const * path, c_file_path const * other_path)
{
    mangled_ppc("?file_utility_error@@YAXPBDW4e_file_error_mode@@PBVc_file_path@@2@Z");

    assert_tag_debug_untracked_jul_11_2011(101, location);
    assert_tag_debug_untracked_jul_11_2011(102, path);

    s_file_platform_error error;
    file_platform_get_error(&error);

    if (error_mode != _file_error_mode_silent)
    {
        s_static_string<1024> file_string;
        s_static_string<256> path_name;
        s_static_string<1024> error_string;
        path->get_full_path(&path_name);

        if (other_path)
        {
            s_static_string<256> other_path_name;
            other_path->get_full_path(&other_path_name);
            file_string.print("'%s', '%s'", path_name.get_string(), other_path_name.get_string());
        }
        else
        {
            file_string.print("'%s'", path_name.get_string());
        }

        file_platform_format_error(&error, error_string.get_buffer(), error_string.max_length());

        if (!file_errors_suppressed())
        {
            event(_event_warning, "files: %s(%s) error %s", location, file_string.get_string(), error_string.get_string());
        }
        else
        {
            events_internal_error("files: %s(%s) error %s", location, file_string.get_string(), error_string.get_string());
        }
    }

    file_platform_clear_last_error();
};
