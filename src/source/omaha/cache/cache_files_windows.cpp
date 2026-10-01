#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\cache\\cache_files_windows.cpp"
/* ---------- headers */

#include <limits.h>
#include "omaha\cache\cache_files_windows.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_macros.h"
#include "core\corelib\cseries\cseries_string.h"
#include "omaha\cache\cache_files.h"
#include "omaha\cseries\cseries_strings.h"
#include "omaha\tag_files\tag_files.h"
#include "omaha\tag_files\tag_groups.h"

/* ---------- constants */

long const k_cache_file_solo_maximum_size = 0x1AE00000;
long const k_cache_file_multiplayer_maximum_size = 0x09400000;
long const k_cache_file_main_menu_maximum_size = 0x06900000;
long const k_cache_file_multiplayer_shared_maximum_size = 0x18000000;
long const k_cache_file_single_player_shared_maximum_size = 0x29E00000;

/* ---------- definitions */

/* ---------- prototypes */

void canonicalize_map_path(char const * source, c_static_string<256> * out_destination);
void copy_and_strip_suffix(char const * source, c_static_string<256> * destination);

/* ---------- globals */

bool g_log_precache_progress = true;
char const * const k_primary_cache_drive_path = "cache0:\\";
char const * const k_secondary_cache_drive_path = "cache1:\\";
char const * k_shared_file_type_names[k_number_of_shared_file_types] =
{
    "mainmenu",
    "shared",
    "campaign"
};
bool display_precache_progress = false;

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// bool g_log_precache_progress; // "?g_log_precache_progress@@3_NA"
// char const *const k_primary_cache_drive_path; // "?k_primary_cache_drive_path@@3PBDB"
// char const *const k_secondary_cache_drive_path; // "?k_secondary_cache_drive_path@@3PBDB"
// char const **k_shared_file_type_names; // "?k_shared_file_type_names@@3PAPBDA"
// bool display_precache_progress; // "?display_precache_progress@@3_NA"

// bool cache_file_map_should_open_directly(char const *);
// long cache_file_round_up_read_size(long);
// class c_static_string<256> cache_file_get_canonical_path(char const *);
// void canonicalize_map_path(char const *, class c_static_string<256> *);
// void copy_and_strip_suffix(char const *, class c_static_string<256> *);
// long cache_file_get_maximum_size(enum e_scenario_type);
// long cache_file_get_absolute_maximum_size(void);
// unsigned long cache_files_get_estimated_dvd_speed(void);
// char const * cache_file_shared_get_file_name(enum e_cache_file_shared_file_type);
// class c_static_string<256> cache_file_shared_get_file_path(enum e_cache_file_shared_file_type);

bool cache_file_map_should_open_directly(char const * map_name)
{
    mangled_ppc("?cache_file_map_should_open_directly@@YA_NPBD@Z");

    return false;
};

long cache_file_round_up_read_size(long size)
{
    mangled_ppc("?cache_file_round_up_read_size@@YAJJ@Z");

    long rounded_size = size;
    if (tag_files_support_async_data() && (size & 0xFFF) != 0)
    {
        rounded_size = (size | 0xFFF) + 1;
    }

    return rounded_size;
};

c_static_string<256> cache_file_get_canonical_path(char const * scenario_path)
{
    mangled_ppc("?cache_file_get_canonical_path@@YA?AV?$c_static_string@$0BAA@@@PBD@Z");

    c_static_string<256> canonical_path;
    canonicalize_map_path(scenario_path, &canonical_path);

    return canonical_path;
};

void canonicalize_map_path(char const * source, c_static_string<256> * out_destination)
{
    mangled_ppc("?canonicalize_map_path@@YAXPBDPAV?$c_static_string@$0BAA@@@@Z");

    char const * stripped_source = tag_name_strip_path(source);
    c_static_string<256> temp_string;
    copy_and_strip_suffix(stripped_source, &temp_string);
    out_destination->print("d:\\maps\\%s.map", temp_string.get_string());
};

void copy_and_strip_suffix(char const * source, c_static_string<256> * destination)
{
    mangled_ppc("?copy_and_strip_suffix@@YAXPBDPAV?$c_static_string@$0BAA@@@@Z");

    char const * source_end = find_string_end(source, ".");
    destination->set_bounded(source, source_end - source);
    csstrnlwr(destination->get_buffer(), NUMBEROF(destination->get_buffer()));
};

long cache_file_get_maximum_size(e_scenario_type scenario_type)
{
    mangled_ppc("?cache_file_get_maximum_size@@YAJW4e_scenario_type@@@Z");

    long maximum_size = 0;
    switch (scenario_type)
    {
    case _scenario_type_multiplayer:
    {
        maximum_size = k_cache_file_multiplayer_maximum_size;
    }
    break;

    case _scenario_type_solo:
    {
        maximum_size = k_cache_file_solo_maximum_size;
    }
    break;

    case _scenario_type_main_menu:
    {
        maximum_size = k_cache_file_main_menu_maximum_size;
    }
    break;

    case _scenario_type_multiplayer_shared:
    {
        maximum_size = k_cache_file_multiplayer_shared_maximum_size;
    }
    break;

    case _scenario_type_single_player_shared:
    {
        maximum_size = k_cache_file_single_player_shared_maximum_size;
    }
    break;

    case _scenario_type_invalid:
    {
        maximum_size = cache_file_get_absolute_maximum_size();
    }
    break;

    default:
    {
        dassert_tag_debug_untracked_jul_11_2011(5208, false, "halt()");
    }
    break;
    }

    return maximum_size;
};

long cache_file_get_absolute_maximum_size(void)
{
    mangled_ppc("?cache_file_get_absolute_maximum_size@@YAJXZ");

    return LONG_MAX;
};

unsigned long cache_files_get_estimated_dvd_speed(void)
{
    mangled_ppc("?cache_files_get_estimated_dvd_speed@@YAKXZ");

    return 4;
};

char const * cache_file_shared_get_file_name(e_cache_file_shared_file_type shared_file_type)
{
    mangled_ppc("?cache_file_shared_get_file_name@@YAPBDW4e_cache_file_shared_file_type@@@Z");

    assert_tag_debug_untracked_jul_11_2011(5230, VALID_INDEX(shared_file_type, k_number_of_shared_file_types));

    return k_shared_file_type_names[shared_file_type];
};

c_static_string<256> cache_file_shared_get_file_path(e_cache_file_shared_file_type shared_file_type)
{
    mangled_ppc("?cache_file_shared_get_file_path@@YA?AV?$c_static_string@$0BAA@@@W4e_cache_file_shared_file_type@@@Z");

    assert_tag_debug_untracked_jul_11_2011(5238, VALID_INDEX(shared_file_type, k_number_of_shared_file_types));

    char const * shared_file_name = cache_file_shared_get_file_name(shared_file_type);

    return cache_file_get_path(shared_file_name);
};

