#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\foundation\\baselib\\files\\file_location_manager.cpp"
/* ---------- headers */

#include "foundation\baselib\files\file_location_manager.h"
#include "foundation\baselib\files\file_location_manager_xenon.h"
#include "foundation\baselib\multithreading\datatypes\initialization_container.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_macros.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

t_initialization_container<s_file_location_globals> g_file_location_globals;

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// public: static long const s_static_array<struct s_file_location, 5>::k_element_count; // "?k_element_count@?$s_static_array@Us_file_location@@$04@@2JB"
// class t_initialization_container<struct s_file_location_globals> g_file_location_globals; // "?g_file_location_globals@@3V?$t_initialization_container@Us_file_location_globals@@@@A"

// void file_locations_initialize(void);
// struct s_file_location_globals const * file_location_globals_get(void);
// bool file_location_available(enum e_file_location, enum e_file_location_usage_mode);
// enum e_file_location_device file_location_get_device_type(enum e_file_location);
// char const * file_location_get_root_absolute_path(enum e_file_location);
// void file_locations_configure(struct s_file_location_globals *);
// void file_location_set_read_only(struct s_file_location *, struct s_file_available_location const *);
// void file_location_set_read_write(struct s_file_location *, struct s_file_available_location const *);
// public: void s_flags<enum e_file_location_usage_mode, unsigned long, 2>::clear(void);
// public: bool s_flags<enum e_file_location_usage_mode, unsigned long, 2>::test(enum e_file_location_usage_mode) const;
// public: void s_flags<enum e_file_location_usage_mode, unsigned long, 2>::set(enum e_file_location_usage_mode, bool);
// ?get@?$t_initialization_container@Us_file_location_globals@@@@QAAPBUs_file_location_globals@@Q6AXPAU2@@Z@Z;
// public: struct s_file_location const & s_static_array<struct s_file_location, 5>::operator[]<enum e_file_location>(enum e_file_location) const;
// public: struct s_file_location & s_static_array<struct s_file_location, 5>::operator[]<long>(long);
// public: static bool s_flags<enum e_file_location_usage_mode, unsigned long, 2>::valid_bit(enum e_file_location_usage_mode);
// public: bool s_flags<enum e_file_location_usage_mode, unsigned long, 2>::valid(void) const;
// private: static unsigned long s_flags<enum e_file_location_usage_mode, unsigned long, 2>::flag_size_type(enum e_file_location_usage_mode);
// public: static bool s_static_array<struct s_file_location, 5>::valid<enum e_file_location>(enum e_file_location);
// public: static bool s_static_array<struct s_file_location, 5>::valid<long>(long);
// private: static unsigned long s_flags<enum e_file_location_usage_mode, unsigned long, 2>::make_mask_with_all_valid_bits_on_size_type(void);
// private: static unsigned long s_flags<enum e_file_location_usage_mode, unsigned long, 2>::make_N_bit_mask_size_type(enum e_file_location_usage_mode);
// public: t_initialization_container<struct s_file_location_globals>::t_initialization_container<struct s_file_location_globals>(void);
// public: t_initialization_container<struct s_file_location_globals>::~t_initialization_container<struct s_file_location_globals>(void);
// void g_file_location_globals::`dynamic atexit destructor'(void);

void file_locations_initialize(void)
{
    mangled_ppc("?file_locations_initialize@@YAXXZ");

    s_file_location_globals const * globals = file_location_globals_get();
};

s_file_location_globals const * file_location_globals_get(void)
{
    mangled_ppc("?file_location_globals_get@@YAPBUs_file_location_globals@@XZ");

    return g_file_location_globals.get(file_locations_configure);
};

bool file_location_available(e_file_location location, e_file_location_usage_mode usage_mode)
{
    mangled_ppc("?file_location_available@@YA_NW4e_file_location@@W4e_file_location_usage_mode@@@Z");

    s_file_location_globals const * globals = file_location_globals_get();
    s_file_location const * file_location = &globals->locations[location];
    bool available = file_location->usage_flags.test(usage_mode);

    return available;
};

e_file_location_device file_location_get_device_type(e_file_location location)
{
    mangled_ppc("?file_location_get_device_type@@YA?AW4e_file_location_device@@W4e_file_location@@@Z");

    s_file_location_globals const * globals = file_location_globals_get();
    e_file_location_device device = globals->locations[location].device;

    return device;
};

char const * file_location_get_root_absolute_path(e_file_location location)
{
    mangled_ppc("?file_location_get_root_absolute_path@@YAPBDW4e_file_location@@@Z");

    s_file_location_globals const * globals = file_location_globals_get();
    s_file_location const * file_location = &globals->locations[location];
    assert_tag_debug_untracked_jul_11_2011(66, file_location->usage_flags.test(_file_location_read));
    char const * root_path = file_location->root_path.get_string();

    return root_path;
};

void file_locations_configure(s_file_location_globals * globals)
{
    mangled_ppc("?file_locations_configure@@YAXPAUs_file_location_globals@@@Z");

    s_file_available_location utility_drive[2];
    unsigned long utility_drive_flags = file_locations_find_utility_drives(NUMBEROF(utility_drive), utility_drive);

    s_file_available_location working_directory_location;
    bool on_devkit;
    bool found_working_directory = file_locations_find_working_directory(&working_directory_location, &on_devkit);

    s_file_available_location media_location;
    bool media_directory_available = file_locations_find_media_directory(&media_location);

    for (long location_index = 0; location_index < k_file_location_count; location_index++)
    {
        s_file_location * file_location = &globals->locations[location_index];
        file_location->usage_flags.clear();

        switch (location_index)
        {
        case _file_location_development_relative:
        {
            if (found_working_directory)
            {
                file_location_set_read_write(file_location, &working_directory_location);
            }
        }
        break;
        case _file_location_1:
        case _file_location_2:
        {
            if (found_working_directory && on_devkit)
            {
                file_location_set_read_write(file_location, &working_directory_location);
            }
            else if (media_directory_available)
            {
                file_location_set_read_only(file_location, &media_location);
            }
        }
        break;
        case _file_location_3:
        {
            if (TEST_BIT(utility_drive_flags, 0))
            {
                file_location_set_read_write(file_location, &utility_drive[0]);
            }
        }
        break;
        case _file_location_4:
        {
            if (TEST_BIT(utility_drive_flags, 1))
            {
                file_location_set_read_write(file_location, &utility_drive[1]);
            }
        }
        break;
        default:
        {
            dassert_tag_debug_untracked_jul_11_2011(137, false, "unreachable");
        }
        break;
        }
    }
};

void file_location_set_read_only(s_file_location * file_location, s_file_available_location const * available_location)
{
    mangled_ppc("?file_location_set_read_only@@YAXPAUs_file_location@@PBUs_file_available_location@@@Z");

    file_location->usage_flags.clear();
    file_location->usage_flags.set(_file_location_read, true);
    file_location->device = available_location->device;
    file_location->root_path.set(available_location->path.get_string());
};

void file_location_set_read_write(s_file_location * file_location, s_file_available_location const * available_location)
{
    mangled_ppc("?file_location_set_read_write@@YAXPAUs_file_location@@PBUs_file_available_location@@@Z");

    file_location->usage_flags.clear();
    file_location->usage_flags.set(_file_location_read, true);
    file_location->usage_flags.set(_file_location_write, true);
    file_location->device = available_location->device;
    file_location->root_path.set(available_location->path.get_string());
};

