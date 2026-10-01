/* ---------- headers */

#include "omaha\cseries\progress.h"
#include "omaha\cseries\cseries.h"
#include "baselib\system_time_xenon.h"
#include "core\corelib\cseries\cseries_events.h"
#include "core\corelib\cseries\cseries_macros.h"
#include "core\corelib\cseries\cseries_string.h"
#include "omaha\shell\shell.h"
#include <string.h>

/* ---------- constants */

/* ---------- definitions */

struct s_progress_globals
{
    progress_callbacks default_callbacks; // 0x0
    progress_callbacks custom_callbacks; // 0x10
    bool disable_callbacks; // 0x20
    unsigned long start_milliseconds; // 0x24
    bool currently_valid; // 0x28
    char description[256]; // 0x29
    long last_progress; // 0x12C
    unsigned long last_milliseconds; // 0x130
};
static_assert(sizeof(s_progress_globals) == 0x134, "s_progress_globals");

/* ---------- prototypes */

/* ---------- globals */

static s_progress_globals progress_globals;

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// void progress_set_default_callbacks(struct progress_callbacks const *);
// void progress_set_custom_callbacks(struct progress_callbacks const *);
// void progress_disable_callbacks(bool);
// void progress_new(char const *);
// long progress_update(long, long);
// long progress_update_with_description(long, long, char const *);
// void progress_done(void);

void progress_set_default_callbacks(progress_callbacks const * callbacks)
{
    mangled_ppc("?progress_set_default_callbacks@@YAXPBUprogress_callbacks@@@Z");

    if (callbacks)
    {
        progress_globals.default_callbacks = *callbacks;
    }
    else
    {
        memset(&progress_globals.default_callbacks, 0, sizeof(progress_globals.default_callbacks));
    }
};

void progress_set_custom_callbacks(progress_callbacks const * callbacks)
{
    mangled_ppc("?progress_set_custom_callbacks@@YAXPBUprogress_callbacks@@@Z");

    if (callbacks)
    {
        progress_globals.custom_callbacks = *callbacks;
    }
    else
    {
        memset(&progress_globals.custom_callbacks, 0, sizeof(progress_globals.custom_callbacks));
    }
};

void progress_disable_callbacks(bool disabled)
{
    mangled_ppc("?progress_disable_callbacks@@YAX_N@Z");

    progress_globals.disable_callbacks = disabled;
};

void progress_new(char const * description)
{
    mangled_ppc("?progress_new@@YAXPBD@Z");

    progress_done();
    progress_globals.currently_valid = true;
    progress_globals.start_milliseconds = system_milliseconds();
    csstrnzcpy(progress_globals.description, description, NUMBEROF(progress_globals.description));
    progress_globals.last_progress = NONE;
    progress_globals.last_milliseconds = 0;

    if (!progress_globals.disable_callbacks)
    {
        if (progress_globals.custom_callbacks.new_proc != NULL)
        {
            progress_globals.custom_callbacks.new_proc(progress_globals.description, progress_globals.custom_callbacks.user_data);
        }
        else if (progress_globals.default_callbacks.new_proc != NULL)
        {
            progress_globals.default_callbacks.new_proc(progress_globals.description, progress_globals.default_callbacks.user_data);
        }
    }
};

long progress_update(long current_amount, long total_amount)
{
    mangled_ppc("?progress_update@@YAJJJ@Z");

    return progress_update_with_description(current_amount, total_amount, NULL);
};

long progress_update_with_description(long current_amount, long total_amount, char const * optional_description)
{
    mangled_ppc("?progress_update_with_description@@YAJJJPBD@Z");

    unsigned long milliseconds = system_milliseconds();
    __int64 preciser_current_amount = PIN(current_amount, 0, total_amount);
    __int64 preciser_total_amount = MAX(total_amount, 1);
    long progress = static_cast<long>(100 * preciser_current_amount / preciser_total_amount);

    if (progress_globals.currently_valid)
    {
        if (shell_tool_type() != _shell_tool_command_line || progress >= progress_globals.last_progress + 20 || milliseconds - progress_globals.last_milliseconds > 500)
        {
            progress_globals.last_progress = progress;
            progress_globals.last_milliseconds = milliseconds;

            if (!progress_globals.disable_callbacks)
            {
                if (progress_globals.custom_callbacks.update_proc != NULL)
                {
                    progress_globals.custom_callbacks.update_proc(progress_globals.description, optional_description, progress, progress_globals.custom_callbacks.user_data);
                }
                else if (progress_globals.default_callbacks.update_proc != NULL)
                {
                    progress_globals.default_callbacks.update_proc(progress_globals.description, optional_description, progress, progress_globals.default_callbacks.user_data);
                }
            }
        }
    }

    return progress;
};

void progress_done(void)
{
    mangled_ppc("?progress_done@@YAXXZ");

    if (progress_globals.currently_valid)
    {
        if (!progress_globals.disable_callbacks)
        {
            if (progress_globals.custom_callbacks.done_proc != NULL)
            {
                progress_globals.custom_callbacks.done_proc(progress_globals.description, progress_globals.custom_callbacks.user_data);
            }
            else if (progress_globals.default_callbacks.done_proc != NULL)
            {
                progress_globals.default_callbacks.done_proc(progress_globals.description, progress_globals.default_callbacks.user_data);
            }
        }

        event_wrapped(_event_message, "system:progress: %s, total time: %.2f seconds", progress_globals.description, static_cast<float>(system_milliseconds() - progress_globals.start_milliseconds) / 1000.0f);

        progress_globals.currently_valid = false;
    }
};
