#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\SD\Reach\Publishing\Main\shared\engine\source\foundation\baselib\system\system_os_interface_xenon.cpp"
/* ---------- headers */

#include <xtl.h>
#include <stdlib.h>
#include "foundation\baselib\system\system_os_interface_xenon.h"
#include "baselib\system_os_interface.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_macros.h"
#include "core\corelib\cseries\cseries_memory.h"
#include "foundation\baselib\datatypes\static_string.h"
#include "omaha\cseries\cseries.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

extern "C" DWORD WINAPI XGetSystemVersion(LPSTR version_string, UINT version_string_length);

long parse_version_string(char const * version_string);

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// ?system_register_exit_function@@YAXQ6AXXZ@Z;
// void system_exit_application(enum e_application_exit_code);
// bool system_get_operating_system_version(struct s_operating_system_version *);
// long system_execute_command(char const *);
// long parse_version_string(char const *);
// public: static long s_static_string<32>::max_length(void);
// public: char (& s_static_string<32>::get_buffer(void))[32];

void system_register_exit_function(void (* const exit_function)(void))
{
    mangled_ppc("?system_register_exit_function@@YAXQ6AXXZ@Z");
};

void system_exit_application(e_application_exit_code exit_code)
{
    mangled_ppc("?system_exit_application@@YAXW4e_application_exit_code@@@Z");

    if (exit_code == _application_exit_code_failure)
    {
        void (* halt_function)() = system_get_halt_function();
        if (halt_function)
        {
            halt_function();
        }
        else
        {
            system_exit_application(static_cast<e_application_exit_code>(2));
        }
    }
    else
    {
        while (true)
        {
        }
    }
};

bool system_get_operating_system_version(s_operating_system_version * out_version)
{
    mangled_ppc("?system_get_operating_system_version@@YA_NPAUs_operating_system_version@@@Z");

    bool success = false;

    assert_tag_debug_untracked_jul_11_2011(62, out_version);
    csmemset(out_version, 0, sizeof(s_operating_system_version));
    out_version->system_version_string.set("UNKNOWN");
    out_version->xtl_version_string.set("UNKNOWN");

    if (XGetSystemVersion(out_version->system_version_string.get_buffer(), s_static_string<32>::max_length()))
    {
        long system_version = parse_version_string(out_version->system_version_string.get_string());
        if (system_version > 0)
        {
            out_version->system_version = system_version;
            success = true;
        }
    }

    if (XDebugGetXTLVersionA(out_version->xtl_version_string.get_buffer(), s_static_string<32>::max_length()))
    {
        long xtl_version = parse_version_string(out_version->xtl_version_string.get_string());
        if (xtl_version > 0)
        {
            out_version->xtl_version = xtl_version;
            success = true;
        }
    }

    return success;
};

long system_execute_command(char const * command)
{
    mangled_ppc("?system_execute_command@@YAJPBD@Z");

    dassert_tag_debug_untracked_jul_11_2011(104, false, "unreachable");

    return -1;
};

long parse_version_string(char const * version_string)
{
    mangled_ppc("?parse_version_string@@YAJPBD@Z");

    long version = 0;
    long part_count;
    long start_index = 0;
    long index = 0;
    part_count = 0;
    s_static_string<256> string;

    string.set(version_string);
    do
    {
        start_index = index + 1;
        index = string.next_index_of(".", start_index);
    } while (++part_count < 3 && index != NONE);

    if (index != NONE)
    {
        string.set_length(index);
        version = atoi(string.get_string() + start_index);
    }

    return version;
};
