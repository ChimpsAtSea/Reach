#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\SD\Reach\Publishing\Main\shared\engine\source\omaha\tag_files\tag_group_locations.cpp"
/* ---------- headers */

#include "omaha\tag_files\tag_group_locations.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_macros.h"
#include "core\corelib\cseries\cseries_string.h"
#include <string.h>

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

char const * k_tag_group_location_paths[k_number_of_tag_group_locations] =
{
    "rasterizer\\",
    "shaders\\",
};

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// char const **k_tag_group_location_paths; // "?k_tag_group_location_paths@@3PAPBDA"

// char const * tag_group_location_get_tag_path(enum e_tag_group_location);
// bool tag_path_is_valid_for_location(enum e_tag_group_location, char const *);

char const * tag_group_location_get_tag_path(e_tag_group_location location)
{
    mangled_ppc("?tag_group_location_get_tag_path@@YAPBDW4e_tag_group_location@@@Z");

    assert_tag_debug_untracked_jul_11_2011(23, VALID_INDEX(location, NUMBEROF(k_tag_group_location_paths)));

    return k_tag_group_location_paths[location];
};

bool tag_path_is_valid_for_location(e_tag_group_location location, char const * path)
{
    mangled_ppc("?tag_path_is_valid_for_location@@YA_NW4e_tag_group_location@@PBD@Z");

    assert_tag_debug_untracked_jul_11_2011(32, VALID_INDEX(location, NUMBEROF(k_tag_group_location_paths)));

    char const * location_path = tag_group_location_get_tag_path(location);
    bool valid;
    unsigned int location_path_length = strlen(location_path);
    valid = ascii_strnicmp(path, location_path, location_path_length) == 0;

    return valid;
};
