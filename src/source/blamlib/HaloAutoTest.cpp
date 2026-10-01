#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\blamlib\\HaloAutoTest.cpp"
/* ---------- headers */

#include "blamlib\HaloAutoTest.h"
#include "omaha\cseries\cseries_windows_debug.h"
#include "omaha\input\input.h"

#include <xtl.h>

/* ---------- constants */

enum e_hat_mode
{
    _hat_mode_none = 0,
    _hat_mode_write = 3,
    _hat_mode_read,
    _hat_mode_loop,
};

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

static HANDLE g_hat_file_handle;
static long g_hat_mode;

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// void HATInit(void);
// void HATCleanup(void);
// void HATReadMain(void);
// void HATRun(struct gamepad_state *);
// void HATRawRead(struct gamepad_state *);
// void HATRawLoopRead(struct gamepad_state *);
// void HATRawWrite(struct gamepad_state const *);

void HATInit(void)
{
    mangled_ppc("?HATInit@@YAXXZ");

    HATReadMain();
    if (g_hat_mode == _hat_mode_write)
    {
        c_debug_output_path output_path;
        g_hat_file_handle = CreateFileA(output_path.get_path("state.data"), GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_FLAG_SEQUENTIAL_SCAN, NULL);
    }
    else if (g_hat_mode == _hat_mode_read || g_hat_mode == _hat_mode_loop)
    {
        c_debug_output_path output_path;
        g_hat_file_handle = CreateFileA(output_path.get_path("state.data"), GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_FLAG_SEQUENTIAL_SCAN, NULL);
    }
};

void HATCleanup(void)
{
    mangled_ppc("?HATCleanup@@YAXXZ");

    if (g_hat_file_handle)
    {
        CloseHandle(g_hat_file_handle);
    }
};

void HATReadMain(void)
{
    mangled_ppc("?HATReadMain@@YAXXZ");

    c_debug_output_path output_path;
    if (GetFileAttributesA(output_path.get_path("write.xts")) != 0xFFFFFFFF)
    {
        g_hat_mode = _hat_mode_write;
    }
    else if (GetFileAttributesA(output_path.get_path("read.xts")) != 0xFFFFFFFF)
    {
        g_hat_mode = _hat_mode_read;
    }
    else if (GetFileAttributesA(output_path.get_path("loop.xts")) != 0xFFFFFFFF)
    {
        g_hat_mode = _hat_mode_loop;
    }
};

void HATRun(gamepad_state * state)
{
    mangled_ppc("?HATRun@@YAXPAUgamepad_state@@@Z");

    switch (g_hat_mode)
    {
    case _hat_mode_write:
        HATRawWrite(state);
        break;
    case _hat_mode_read:
        HATRawRead(state);
        break;
    case _hat_mode_loop:
        HATRawLoopRead(state);
        break;
    }
};

void HATRawRead(gamepad_state * state)
{
    mangled_ppc("?HATRawRead@@YAXPAUgamepad_state@@@Z");

    DWORD bytes_read = 0;
    ReadFile(g_hat_file_handle, state, sizeof(gamepad_state), &bytes_read, NULL);
};

void HATRawLoopRead(gamepad_state * state)
{
    mangled_ppc("?HATRawLoopRead@@YAXPAUgamepad_state@@@Z");

    DWORD bytes_read = 0;
    ReadFile(g_hat_file_handle, state, sizeof(gamepad_state), &bytes_read, NULL);
    if (bytes_read == 0)
    {
        SetFilePointer(g_hat_file_handle, 0, NULL, FILE_BEGIN);
        ReadFile(g_hat_file_handle, state, sizeof(gamepad_state), &bytes_read, NULL);
    }
};

void HATRawWrite(gamepad_state const * state)
{
    mangled_ppc("?HATRawWrite@@YAXPBUgamepad_state@@@Z");

    DWORD bytes_written = 0;
    WriteFile(g_hat_file_handle, state, sizeof(gamepad_state), &bytes_written, NULL);
};
