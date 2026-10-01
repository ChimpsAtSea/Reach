#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\blamlib\\animation_statistics.cpp"
/* ---------- headers */

#include "blamlib\animation_statistics.h"
#include "core\corelib\cseries\cseries_events.h"
#include "foundation\baselib\datatypes\static_string.h"
#include "omaha\main\console.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

bool g_animation_statistic_accumulator_enabled;

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// bool g_animation_statistic_accumulator_enabled; // "?g_animation_statistic_accumulator_enabled@@3_NA"

// void animation_statistics_dump(void);
// void animation_statistic_initialize_for_new_map(void);
// void animation_statistic_dispose_from_old_map(void);
// void animation_statistic_initialize(void);
// void animation_statistic_dispose(void);

void animation_statistics_dump(void)
{
    mangled_ppc("?animation_statistics_dump@@YAXXZ");

    event_wrapped(_event_critical, "Animation statistic gathering is not enabled in this build");
};

void animation_statistic_initialize_for_new_map(void)
{
    mangled_ppc("?animation_statistic_initialize_for_new_map@@YAXXZ");
};

void animation_statistic_dispose_from_old_map(void)
{
    mangled_ppc("?animation_statistic_dispose_from_old_map@@YAXXZ");
};

void animation_statistic_initialize(void)
{
    mangled_ppc("?animation_statistic_initialize@@YAXXZ");

    bool accumulator_enabled = false;
    c_static_string<256> value;
    if (console_get_command_slow("g_animation_statistic_accumulator_enabled", &value))
    {
        accumulator_enabled = true;
    }

    event_wrapped(_event_critical, "Animation statistic gathering is not enabled in this build");
};

void animation_statistic_dispose(void)
{
    mangled_ppc("?animation_statistic_dispose@@YAXXZ");

    event_wrapped(_event_critical, "Animation statistic gathering is not enabled in this build");
};

