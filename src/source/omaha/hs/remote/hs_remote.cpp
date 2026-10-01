/* ---------- headers */

#include "omaha\hs\remote\hs_remote.h"
#include "omaha\hs\hs.h"
#include "omaha\networking\tools\remote_command.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// bool hs_process_remote_command(char const *);

bool hs_process_remote_command(char const *command_string)
{
    mangled_ppc("?hs_process_remote_command@@YA_NPBD@Z");

    long result = 0;
    e_hs_type result_type = _hs_type_void;
    bool success = hs_compile_and_evaluate_result(_event_verbose, "remote_command", command_string, false, false, &result, &result_type);
    if (success)
    {
        hs_result_coerce_to_native(&result, &result_type);
        remote_command_send_hs_result(result, result_type);
    }
    return success;
};

