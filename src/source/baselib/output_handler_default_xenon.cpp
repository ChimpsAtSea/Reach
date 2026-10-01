/* ---------- headers */

#include "baselib\output_handler_default_xenon.h"
#include "baselib\system_debugger_windows.h"
#include "baselib\system_debugger_xenon.h"
#include "foundation\baselib\errors\output\output_handler.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// public: virtual void c_default_output_handler::handle_output_debug(char const *);

void c_default_output_handler::handle_output_debug(char const * debug_string)
{
    mangled_ppc("?handle_output_debug@c_default_output_handler@@UAAXPBD@Z");

    if (system_is_debugger_present())
    {
        system_output_debug_string(debug_string);
    }
};

