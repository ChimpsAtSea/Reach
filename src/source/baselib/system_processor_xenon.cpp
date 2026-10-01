/* ---------- headers */

#include "baselib\system_processor_xenon.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// long system_processor_get_physical_count(void);
// long system_processor_get_logical_count(void);

long system_processor_get_physical_count(void)
{
    mangled_ppc("?system_processor_get_physical_count@@YAJXZ");

    return 3;
};

long system_processor_get_logical_count(void)
{
    mangled_ppc("?system_processor_get_logical_count@@YAJXZ");

    return 6;
};

