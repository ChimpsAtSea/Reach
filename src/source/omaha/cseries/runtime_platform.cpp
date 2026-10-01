#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\cseries\\runtime_platform.cpp"
/* ---------- headers */

#include "omaha\cseries\runtime_platform.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_macros.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

e_runtime_platform_type active_type;
bool g_building_cache_file;
bool g_building_cache_file_cache;
bool g_building_cache_file_for_ship;
bool g_building_cache_file_language_specific_cache;

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// enum e_runtime_platform_type active_type; // "?active_type@@3W4e_runtime_platform_type@@A"
// bool g_building_cache_file; // "?g_building_cache_file@@3_NA"
// bool g_building_cache_file_cache; // "?g_building_cache_file_cache@@3_NA"
// bool g_building_cache_file_for_ship; // "?g_building_cache_file_for_ship@@3_NA"
// bool g_building_cache_file_language_specific_cache; // "?g_building_cache_file_language_specific_cache@@3_NA"

// enum e_runtime_platform_type get_runtime_platform_type(void);
// enum e_runtime_platform_type set_runtime_platform_type(enum e_runtime_platform_type);
// bool runtime_platform_needs_byteswapping(void);
// bool runtime_platform_needs_byteswapping(enum e_runtime_platform_type);
// bool runtime_platform_building_for_cache_file(void);
// void set_runtime_platform_building_for_cache_file(bool);
// bool runtime_platform_building_for_cache_file_cache(void);
// void set_runtime_platform_building_for_cache_file_cache(bool);
// bool runtime_platform_building_cache_file_for_ship(void);
// void set_runtime_platform_building_cache_file_for_ship(bool);
// bool runtime_platform_building_for_cache_file_language_specific_cache(void);
// void set_runtime_platform_building_for_cache_file_language_specific_cache(bool);
// char const * describe_runtime_platform_type(enum e_runtime_platform_type);
// bool runtime_platform_on_target_platform(void);

e_runtime_platform_type get_runtime_platform_type(void)
{
    mangled_ppc("?get_runtime_platform_type@@YA?AW4e_runtime_platform_type@@XZ");

    return active_type;
};

e_runtime_platform_type set_runtime_platform_type(e_runtime_platform_type new_type)
{
    mangled_ppc("?set_runtime_platform_type@@YA?AW4e_runtime_platform_type@@W41@@Z");

    e_runtime_platform_type old_type = active_type;
    active_type = new_type;
    return old_type;
};

bool runtime_platform_needs_byteswapping(void)
{
    mangled_ppc("?runtime_platform_needs_byteswapping@@YA_NXZ");

    return runtime_platform_needs_byteswapping(active_type);
};

bool runtime_platform_needs_byteswapping(e_runtime_platform_type runtime_platform)
{
    mangled_ppc("?runtime_platform_needs_byteswapping@@YA_NW4e_runtime_platform_type@@@Z");

    bool needs_byteswapping = false;
    needs_byteswapping = runtime_platform == _runtime_platform_pc;
    return needs_byteswapping;
};

bool runtime_platform_building_for_cache_file(void)
{
    mangled_ppc("?runtime_platform_building_for_cache_file@@YA_NXZ");

    return g_building_cache_file;
};

void set_runtime_platform_building_for_cache_file(bool building)
{
    mangled_ppc("?set_runtime_platform_building_for_cache_file@@YAX_N@Z");

    g_building_cache_file = building;
};

bool runtime_platform_building_for_cache_file_cache(void)
{
    mangled_ppc("?runtime_platform_building_for_cache_file_cache@@YA_NXZ");

    return g_building_cache_file_cache;
};

void set_runtime_platform_building_for_cache_file_cache(bool building)
{
    mangled_ppc("?set_runtime_platform_building_for_cache_file_cache@@YAX_N@Z");

    g_building_cache_file_cache = building;
};

bool runtime_platform_building_cache_file_for_ship(void)
{
    mangled_ppc("?runtime_platform_building_cache_file_for_ship@@YA_NXZ");

    return g_building_cache_file_for_ship;
};

void set_runtime_platform_building_cache_file_for_ship(bool building)
{
    mangled_ppc("?set_runtime_platform_building_cache_file_for_ship@@YAX_N@Z");

    g_building_cache_file_for_ship = building;
};

bool runtime_platform_building_for_cache_file_language_specific_cache(void)
{
    mangled_ppc("?runtime_platform_building_for_cache_file_language_specific_cache@@YA_NXZ");

    return g_building_cache_file_language_specific_cache;
};

void set_runtime_platform_building_for_cache_file_language_specific_cache(bool building)
{
    mangled_ppc("?set_runtime_platform_building_for_cache_file_language_specific_cache@@YAX_N@Z");

    g_building_cache_file_language_specific_cache = building;
};

char const *describe_runtime_platform_type(e_runtime_platform_type runtime_platform)
{
    mangled_ppc("?describe_runtime_platform_type@@YAPBDW4e_runtime_platform_type@@@Z");

    char const *k_platform_descriptions[NUMBER_OF_RUNTIME_PLATFORMS] = { "xenon", "pc" };
    assert_tag_debug_untracked_jul_11_2011(234, VALID_INDEX(runtime_platform, NUMBEROF(k_platform_descriptions)));

    return k_platform_descriptions[runtime_platform];
};

bool runtime_platform_on_target_platform(void)
{
    mangled_ppc("?runtime_platform_on_target_platform@@YA_NXZ");

    return active_type != _runtime_platform_pc;
};
