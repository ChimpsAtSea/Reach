/* ---------- headers */

#include "omaha\profiler\profiler_datamine.h"
#include "omaha\profiler\profiler_export_io.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

bool g_profiler_datamine_uploads_enabled;

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// bool g_profiler_datamine_uploads_enabled; // "?g_profiler_datamine_uploads_enabled@@3_NA"

// bool profiler_datamine_active(void);

bool profiler_datamine_active(void)
{
    mangled_ppc("?profiler_datamine_active@@YA_NXZ");

    return profiler_export_io_connected();
};

