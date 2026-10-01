/* ---------- headers */

#include "baselib\thread_execution_windows.h"

#include <xtl.h>

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// bool thread_switch(void);
// void thread_sleep(unsigned long);

bool thread_switch(void)
{
    mangled_ppc("?thread_switch@@YA_NXZ");

    bool result = false;
    if (SwitchToThread())
    {
        result = true;
    }

    return result;
};

void thread_sleep(unsigned long milliseconds)
{
    mangled_ppc("?thread_sleep@@YAXK@Z");

    Sleep(milliseconds);
};

