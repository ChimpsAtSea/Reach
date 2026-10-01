/* ---------- headers */

#include "omaha\profiler\profiler_counters.h"
#include "core\corelib\cseries\cseries_events.h"
#include "core\corelib\cseries\cseries_macros.h"

#include <xtl.h>

/* ---------- constants */

long long const k_xenon_performance_counter_frequency = 49875000;

/* ---------- definitions */

struct s_profile_globals
{
    long long frequency;
    bool calibrated;
};
static_assert(sizeof(s_profile_globals) == 0x10, "s_profile_globals");

/* ---------- prototypes */

/* ---------- globals */

static s_profile_globals profile_globals;

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// void initialize_performance_counters(void);

void initialize_performance_counters(void)
{
    mangled_ppc("?initialize_performance_counters@@YAXXZ");

    if (!profile_globals.calibrated)
    {
        QueryPerformanceFrequency(reinterpret_cast<LARGE_INTEGER *>(&profile_globals.frequency));
        if (profile_globals.frequency != k_xenon_performance_counter_frequency)
        {
            event_wrapped(_event_warning, "system: QueryPerformanceFrequency returned %d instead of 49875000", profile_globals.frequency);
            profile_globals.frequency = k_xenon_performance_counter_frequency;
        }
    }
    profile_globals.calibrated = true;
};

