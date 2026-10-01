/* ---------- headers */

#include "omaha\profiler\profiler_tracedump.h"
#include "core\corelib\cseries\cseries_events.h"
#include "omaha\multithreading\threads.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// void trace_next_frame(long);
// void trace_next_frame_to_file(long, char const *);
// void trace_tick(long);
// bool trace_dump_is_trace_enabled(void);
// bool trace_dump_is_trace_enabled_for_thread(enum e_registered_threads);
// void trace_dump_process_thread_start(enum e_registered_threads);
// void trace_dump_process_thread_stop(enum e_registered_threads);

void trace_next_frame(long thread_index)
{
    mangled_ppc("?trace_next_frame@@YAXJ@Z");

    event_wrapped(_event_warning, "trace: tracedumps are not supported on this build");
};

void trace_next_frame_to_file(long thread_index, char const * file_name)
{
    mangled_ppc("?trace_next_frame_to_file@@YAXJPBD@Z");

    event_wrapped(_event_warning, "trace: tracedumps are not supported on this build");
};

void trace_tick(long tick_index)
{
    mangled_ppc("?trace_tick@@YAXJ@Z");

    event_wrapped(_event_warning, "trace: tracedumps are not supported on this build");
};

bool trace_dump_is_trace_enabled(void)
{
    mangled_ppc("?trace_dump_is_trace_enabled@@YA_NXZ");

    return false;
};

bool trace_dump_is_trace_enabled_for_thread(e_registered_threads thread_index)
{
    mangled_ppc("?trace_dump_is_trace_enabled_for_thread@@YA_NW4e_registered_threads@@@Z");

    return false;
};

void trace_dump_process_thread_start(e_registered_threads thread_index)
{
    mangled_ppc("?trace_dump_process_thread_start@@YAXW4e_registered_threads@@@Z");
};

void trace_dump_process_thread_stop(e_registered_threads thread_index)
{
    mangled_ppc("?trace_dump_process_thread_stop@@YAXW4e_registered_threads@@@Z");
};

