/* ---------- headers */

#include "blamlib\debug_async_log.h"
#include <string.h>
#include "core\corelib\cseries\cseries_events.h"
#include "omaha\cseries\cseries_windows_debug.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// public: void c_debug_async_log::initialize(class c_allocation_interface *, unsigned long);
// public: bool c_debug_async_log::open(char const *);
// public: void c_debug_async_log::write(char const *);
// public: void c_debug_async_log::close(void);
// public: void c_debug_async_log::dispose(class c_allocation_interface *);

void c_debug_async_log::initialize(c_allocation_interface * allocation, unsigned long buffer_size)
{
    mangled_ppc("?initialize@c_debug_async_log@@QAAXPAVc_allocation_interface@@K@Z");

    allocate_storage(allocation, buffer_size);
};

bool c_debug_async_log::open(char const * file_name)
{
    mangled_ppc("?open@c_debug_async_log@@QAA_NPBD@Z");

    close();
    return open_file(make_debug_path(file_name), _async_buffer_file_access_write, _async_buffer_disposition_create_always);
};

void c_debug_async_log::write(char const * string)
{
    mangled_ppc("?write@c_debug_async_log@@QAAXPBD@Z");

    long bytes_written = 0;
    bool fatal_error = false;
    c_async_buffer_set::write(string, strlen(string), &bytes_written, &fatal_error);
    if (bytes_written != static_cast<long>(strlen(string)) || fatal_error)
    {
        event_wrapped(_event_warning, "sound:event:log: sound event logging stopped for some reason!");
    }
};

void c_debug_async_log::close(void)
{
    mangled_ppc("?close@c_debug_async_log@@QAAXXZ");

    close_file();
};

void c_debug_async_log::dispose(c_allocation_interface * allocation)
{
    mangled_ppc("?dispose@c_debug_async_log@@QAAXPAVc_allocation_interface@@@Z");

    release_storage(allocation);
};

