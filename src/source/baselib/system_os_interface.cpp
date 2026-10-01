/* ---------- headers */

#include "baselib\system_os_interface.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

static void (* g_halt_function)() = NULL;

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// ?system_register_halt_function@@YAXQ6AXXZ@Z;
// void (* system_get_halt_function(void))(void);

void system_register_halt_function(void (* const halt_function)())
{
    mangled_ppc("?system_register_halt_function@@YAXQ6AXXZ@Z");

    g_halt_function = halt_function;
};

void (* system_get_halt_function())()
{
    mangled_ppc("?system_get_halt_function@@YAP6AXXZXZ");

    return g_halt_function;
};

