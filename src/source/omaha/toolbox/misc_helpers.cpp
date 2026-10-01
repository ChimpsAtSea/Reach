#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\toolbox\\misc_helpers.cpp"
/* ---------- headers */

#include "omaha\toolbox\misc_helpers.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_macros.h"

#include <string.h>

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// char const * path_remove_all_parent_directories(char const *);
// char const * path_add_parent_directory(char const *, char const *);
// char const * path_get_name_with_parent_directories(char const *, long);

char const *path_remove_all_parent_directories(char const *original_path)
{
    mangled_ppc("?path_remove_all_parent_directories@@YAPBDPBD@Z");

    assert_tag_debug_untracked_jul_11_2011(250, original_path);

    char const *name_without_path = strrchr(original_path, '\\');
    if (name_without_path != NULL)
    {
        name_without_path++;
    }
    else
    {
        name_without_path = original_path;
    }
    return name_without_path;
};

char const *path_add_parent_directory(char const *original_path, char const *stripped_path)
{
    mangled_ppc("?path_add_parent_directory@@YAPBDPBD0@Z");

    {
        char const *path_end = original_path + strlen(original_path);
        assert_tag_debug_untracked_jul_11_2011(272, IN_RANGE_INCLUSIVE(stripped_path, original_path, path_end));
    }

    char const *parent_path = MAX(stripped_path - 1, original_path);
    while (parent_path > original_path && parent_path[-1] != '\\')
    {
        parent_path--;
    }
    return parent_path;
};

char const *path_get_name_with_parent_directories(char const *original_path, long parent_path_count)
{
    mangled_ppc("?path_get_name_with_parent_directories@@YAPBDPBDJ@Z");

    char const *new_output_path = path_remove_all_parent_directories(original_path);
    while (parent_path_count-- > 0)
    {
        new_output_path = path_add_parent_directory(original_path, new_output_path);
    }
    return new_output_path;
};

