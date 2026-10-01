#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\cseries\\cseries_events.cpp"
/* ---------- headers */

#include "omaha\cseries\cseries_events.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_macros.h"
#include "foundation\baselib\datatypes\static_string.h"
#include "foundation\baselib\errors\events\event_globals.h"
#include "foundation\baselib\files\file_path.h"
#include "omaha\tag_files\files.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// struct s_file_reference * create_report_file_reference(struct s_file_reference *, char const *, bool);
// void events_disable_suppression(bool);

// $TODO nonmatching: stack layout only (target orders success@0x50, full_path@0x60, result@0x160, file_path@0x170, path@0x280; declaration order has no effect)
s_file_reference * create_report_file_reference(s_file_reference * reference, char const * name, bool place_in_report_directory)
{
    mangled_ppc("?create_report_file_reference@@YAPAUs_file_reference@@PAU1@PBD_N@Z");

    s_file_reference * result = NULL;
    bool success = false;
    c_file_path file_path;
    s_static_string<256> full_path;

    if (events_build_report_file_path(name, static_cast<e_report_file_location>(!place_in_report_directory), &file_path))
    {
        success = true;
    }
    else
    {
        c_static_string<256> path;
        path.print("reports\\%s", name);
        file_path.set_file_path(_file_location_development_relative, path);
        success = true;
    }

    if (success)
    {
        result = file_reference_create_from_path(reference, file_path.get_full_path(&full_path), false);
        assert_tag_debug_untracked_jul_11_2011(44, result != NULL);

        if (result != NULL)
        {
            file_create_parent_directories_if_not_present(result);
        }
    }

    return result;
};

void events_disable_suppression(bool disable)
{
    mangled_ppc("?events_disable_suppression@@YAX_N@Z");

    events_suppression_enable(!disable);
};
