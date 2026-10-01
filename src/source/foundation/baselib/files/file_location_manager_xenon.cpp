#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\foundation\\baselib\\files\\file_location_manager_xenon.cpp"
/* ---------- headers */

#include "foundation\baselib\files\file_location_manager_xenon.h"
#include "core\corelib\config\version.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_events.h"
#include "core\corelib\cseries\cseries_string.h"
#include "foundation\baselib\datatypes\static_string.h"
#include "foundation\baselib\files\file_location_manager.h"
#include "foundation\baselib\memory\debug_memory\debug_memory_globals.h"
#include <xtl.h>
#include <xbdm.h>

/* ---------- constants */

/* ---------- definitions */

// xbox kernel counted string
struct STRING
{
    unsigned short Length;
    unsigned short MaximumLength;
    char * Buffer;
};

/* ---------- prototypes */

extern "C" long __stdcall ObCreateSymbolicLink(STRING * link_name, STRING * device_name);

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// bool file_locations_find_working_directory(struct s_file_available_location *, bool *);
// bool file_locations_find_media_directory(struct s_file_available_location *);
// unsigned long file_locations_find_utility_drives(long, struct s_file_available_location *);
// bool mount_devkit_drive(struct s_file_available_location *, bool *);
// bool mount_secondary_utility_drive_as_working_directory(struct s_file_available_location *);
// bool mount_mu_as_working_directory(struct s_file_available_location *);
// public: void s_static_string<256>::to_lower(void);

bool file_locations_find_working_directory(s_file_available_location * out_directory, bool * out_is_devkit_drive)
{
    mangled_ppc("?file_locations_find_working_directory@@YA_NPAUs_file_available_location@@PA_N@Z");

    bool result = false;
    bool is_devkit_drive = false;
    if (mount_devkit_drive(out_directory, &is_devkit_drive))
    {
        result = true;
        *out_is_devkit_drive = is_devkit_drive;
    }
    else if (mount_secondary_utility_drive_as_working_directory(out_directory))
    {
        result = true;
        *out_is_devkit_drive = false;
    }
    else if (mount_mu_as_working_directory(out_directory))
    {
        result = true;
        *out_is_devkit_drive = false;
    }

    return result;
};

bool file_locations_find_media_directory(s_file_available_location * out_directory)
{
    mangled_ppc("?file_locations_find_media_directory@@YA_NPAUs_file_available_location@@@Z");

    DWORD license_mask;
    DWORD license_result = XContentGetLicenseMask(&license_mask, NULL);

    assert_tag_debug_untracked_jul_11_2011(81, out_directory);
    out_directory->path.set("d:\\");

    if (license_result == 0)
    {
        e_file_location_device device = static_cast<e_file_location_device>(1);
        XCONTENTDEVICETYPE device_type;
        XContentQueryVolumeDeviceType("GAME", &device_type, NULL);
        switch (device_type)
        {
        case XCONTENTDEVICETYPE_HDD:
            device = static_cast<e_file_location_device>(3);
            break;
        case XCONTENTDEVICETYPE_MU:
            device = static_cast<e_file_location_device>(4);
            break;
        case XCONTENTDEVICETYPE_ODD:
            device = static_cast<e_file_location_device>(2);
            break;
        default:
            device = static_cast<e_file_location_device>(1);
            break;
        }
        out_directory->device = device;
    }
    else
    {
        s_static_string<256> file_system_name;
        if (GetVolumeInformationA(out_directory->path.get_string(), NULL, 0, NULL, NULL, NULL, file_system_name.get_buffer(), file_system_name.max_length()))
        {
            if (strcmp_debug(file_system_name, "GDFX") == 0 || strcmp_debug(file_system_name, "UDFX") == 0)
            {
                out_directory->device = static_cast<e_file_location_device>(2);
            }
            else
            {
                out_directory->device = static_cast<e_file_location_device>(3);
            }
        }
        else
        {
            event(_event_error, "files:location_manager:xenon: GetVolumeInformation failed for '%s', unknown device", out_directory->path.get_string());
            out_directory->device = static_cast<e_file_location_device>(1);
        }
    }

    return true;
};

unsigned long file_locations_find_utility_drives(long maximum_count, s_file_available_location * out_locations)
{
    mangled_ppc("?file_locations_find_utility_drives@@YAKJPAUs_file_available_location@@@Z");

    return 0;
};

bool mount_devkit_drive(s_file_available_location * out_directory, bool * out_is_devkit_drive)
{
    mangled_ppc("?mount_devkit_drive@@YA_NPAUs_file_available_location@@PA_N@Z");

    HRESULT error;
    bool success = false;
    debug_checkpoint_memory("before DmMapDevkitDrive()", __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__, 157);
    error = DmMapDevkitDrive();
    if (error == 0)
    {
        DM_XBE xbe_info;
        error = DmGetXbeInfo("", &xbe_info);
        if (error == XBDM_NOERR)
        {
            char * last_separator = strrchr_debug(xbe_info.LaunchPath, '\\');
            if (last_separator != NULL)
            {
                out_directory->path.set_bounded(xbe_info.LaunchPath, strlen_debug(xbe_info.LaunchPath) - strlen_debug(last_separator) + 1);
                out_directory->path.to_lower();
                if (!out_directory->path.starts_with("e:\\"))
                {
                    out_directory->path.print("e:\\%s\\%d\\", version_get_project_xsync_directory(), version_is_tracked_build() ? version_get_build_number() : 0);
                    *out_is_devkit_drive = false;
                }
                else
                {
                    *out_is_devkit_drive = true;
                }
                out_directory->device = static_cast<e_file_location_device>(3);
                success = true;
            }
            else
            {
                event(_event_error, "files:location_manager:xenon: failed to get devkit directory path from '%s'", xbe_info.LaunchPath);
            }
        }
        else
        {
            event(_event_error, "files:location_manager:xenon: DmGetXbeInfo failed with error %d", error);
        }
    }
    else
    {
        event(_event_error, "files:location_manager:xenon: failed to map devkit drive [error %d]", error);
    }

    return success;
};

bool mount_secondary_utility_drive_as_working_directory(s_file_available_location * out_directory)
{
    mangled_ppc("?mount_secondary_utility_drive_as_working_directory@@YA_NPAUs_file_available_location@@@Z");

    bool success = false;

    return success;
};

bool mount_mu_as_working_directory(s_file_available_location * out_directory)
{
    mangled_ppc("?mount_mu_as_working_directory@@YA_NPAUs_file_available_location@@@Z");

    bool result = false;

    {
        s_static_string<256> device_name;
        s_static_string<256> link_path;
        link_path.set("\\??\\MU:");
        device_name.set("\\Device\\Mu0");

        STRING link_string;
        STRING device_string;
        link_string.Length = static_cast<unsigned short>(link_path.length());
        link_string.MaximumLength = static_cast<unsigned short>(link_path.max_length());
        link_string.Buffer = link_path.get_buffer();
        device_string.Length = static_cast<unsigned short>(device_name.length());
        device_string.MaximumLength = static_cast<unsigned short>(device_name.max_length());
        device_string.Buffer = device_name.get_buffer();

        ObCreateSymbolicLink(&link_string, &device_string);
    }

    event(_event_error, "files:location_manager:xenon: mapping MU as working directory");

    out_directory->path.set("MU:\\");
    out_directory->device = static_cast<e_file_location_device>(4);
    result = true;

    return result;
};
