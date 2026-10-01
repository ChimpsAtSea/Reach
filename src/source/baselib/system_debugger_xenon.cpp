/* ---------- headers */

#include "baselib\system_debugger_xenon.h"

#include <xtl.h>
#include <xbdm.h>

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// bool system_is_debugger_present(void);

bool system_is_debugger_present(void)
{
    mangled_ppc("?system_is_debugger_present@@YA_NXZ");

    bool result = false;
    result = DmIsDebuggerPresent() != FALSE;
    return result;
};

