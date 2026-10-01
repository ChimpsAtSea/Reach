/* ---------- headers */

#include "omaha\cseries\watch_window.h"
#include "omaha\cseries\cseries.h"
#include "core\corelib\cseries\cseries_macros.h"
#include "core\corelib\cseries\cseries_string.h"
#include "foundation\baselib\datatypes\data_array.h"
#include "omaha\objects\objects.h"
#include "omaha\objects\object_types.h"
#include "omaha\scenario\scenario.h"
#include "omaha\scenario\scenario_definitions.h"
#include "omaha\tag_files\tag_groups.h"

#include <string.h>

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

static char g_watch_window_buffer[512];
static s_watch_object_results g_watch_object_results;

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// void watch_window_initialize(void);
// void watch_window_dispose(void);
// char const * watch_object_describe(long);
// struct s_watch_object_results & watch_object(long);
// bool object_index_valid_for_try_and_get(long);
// unsigned long clear_watch_window_globals(void);
// char const * watch_object_describe_internal(long, char *, long);

void watch_window_initialize()
{
    mangled_ppc("?watch_window_initialize@@YAXXZ");

    watch_object(NONE);
};

// code is identical; objdiff counts the alignment padding and the 8-byte SEH header of watch_object_describe as part of this symbol in our build
void watch_window_dispose()
{
    mangled_ppc("?watch_window_dispose@@YAXXZ");
};

// code is identical; objdiff counts the 8-byte SEH header of watch_object as part of this symbol in our build
char const * watch_object_describe(long object_index)
{
    mangled_ppc("?watch_object_describe@@YAPBDJ@Z");

    clear_watch_window_globals();
    if (object_index_valid_for_try_and_get(object_index))
    {
        __try
        {
            watch_object_describe_internal(object_index, g_watch_window_buffer, NUMBEROF(g_watch_window_buffer));
        }
        __except (clear_watch_window_globals())
        {
        }
    }
    return g_watch_window_buffer;
};

s_watch_object_results & watch_object(long object_index)
{
    mangled_ppc("?watch_object@@YAAAUs_watch_object_results@@J@Z");

    clear_watch_window_globals();
    g_watch_object_results.description = g_watch_window_buffer;
    if (object_index_valid_for_try_and_get(object_index))
    {
        __try
        {
            watch_object_describe(object_index);
            g_watch_object_results.description = g_watch_window_buffer;
            g_watch_object_results.datum = static_cast<object_datum *>(object_try_and_get_and_verify_type(object_index, NONE));
        }
        __except (clear_watch_window_globals())
        {
        }
    }
    return g_watch_object_results;
};

// $TODO nonmatching: only the TLS slot offset differs (target li 0x7C is the linked .tls offset; ours is the unlinked 0)
bool object_index_valid_for_try_and_get(long object_index)
{
    mangled_ppc("?object_index_valid_for_try_and_get@@YA_NJ@Z");

    bool valid = false;
    if (object_index != NONE && object_header_data != NULL)
    {
        long absolute_index = DATUM_INDEX_TO_ABSOLUTE_INDEX(object_index);
        if (absolute_index != object_index)
        {
            valid = true;
        }
    }
    return valid;
};

unsigned long clear_watch_window_globals()
{
    mangled_ppc("?clear_watch_window_globals@@YAKXZ");

    csstrnzcpy(g_watch_window_buffer, "failed to get object information", NUMBEROF(g_watch_window_buffer));
    memset(&g_watch_object_results, 0, sizeof(g_watch_object_results));
    return static_cast<unsigned long>(NONE);
};

char const * watch_object_describe_internal(long object_index, char * buffer, long buffer_length)
{
    mangled_ppc("?watch_object_describe_internal@@YAPBDJPADJ@Z");

    object_datum const * object = static_cast<object_datum const *>(object_try_and_get_and_verify_type(object_index, NONE));
    if (object != NULL)
    {
        char name_buffer[128];
        csstrnzcpy(name_buffer, " ", NUMBEROF(name_buffer));
        if (object->object.name_index != NONE && global_scenario_index_get() != NONE)
        {
            scenario_object_name const * object_name = static_cast<scenario_object_name const *>(tag_block_get_element_with_size(&global_scenario_get()->object_names, object->object.name_index, sizeof(scenario_object_name)));
            csnzprintf(name_buffer, NUMBEROF(name_buffer), "string_id %d", object_name->name);
            csstrnzcat(name_buffer, " ", NUMBEROF(name_buffer));
        }

        {
            char const * tag_name = NULL;
            e_object_type object_type = object->object.object_identifier.get_type();
            tag_name = tag_get_name_safe(object->definition_index);
            csnzprintf(buffer, buffer_length, "%s %s%s", object_type_get_name(object_type), name_buffer, tag_name != NULL ? tag_name_strip_path(tag_name) : "");
        }
    }
    return buffer;
};

