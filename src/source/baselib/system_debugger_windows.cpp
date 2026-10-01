/* ---------- headers */

#include "baselib\system_debugger_windows.h"

#include <xtl.h>

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// void system_output_debug_string(char const *);

void system_output_debug_string(char const *string)
{
    mangled_ppc("?system_output_debug_string@@YAXPBD@Z");
    OutputDebugStringA(string);
};

