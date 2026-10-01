/* ---------- headers */

#include "baselib\system_time_xenon.h"

#include <xtl.h>

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// unsigned long system_milliseconds(void);

unsigned long system_milliseconds(void)
{
    mangled_ppc("?system_milliseconds@@YAKXZ");

    return GetTickCount();
};

