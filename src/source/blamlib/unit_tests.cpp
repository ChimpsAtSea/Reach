/* ---------- headers */

#include "blamlib\unit_tests.h"
#include "foundation\baselib\datatypes\static_string.h"
#include "foundation\baselib\errors\output\output_globals.h"
#include "omaha\math\real_math.h"
#include "omaha\memory\static_arrays.h"
#include "omaha\profiler\profiler_stopwatch.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// void unit_test_initialize(void);
// void unit_test_dispose(void);
// void unit_test_update(void);

void unit_test_initialize()
{
    mangled_ppc("?unit_test_initialize@@YAXXZ");

    c_stop_watch stop_watch;
    static_arrays_test();
    real_math_test();

    s_static_string<256> string;
    string.print("unit_test_initialize() took %dms", static_cast<long>(stop_watch.total_elapsed_time_in_seconds() * 1000.0f + real_sgn(stop_watch.total_elapsed_time_in_seconds() * 1000.0f) * 0.5f));
    output_debug_string(string);
};

void unit_test_dispose()
{
    mangled_ppc("?unit_test_dispose@@YAXXZ");
};

void unit_test_update()
{
    mangled_ppc("?unit_test_update@@YAXXZ");
};

