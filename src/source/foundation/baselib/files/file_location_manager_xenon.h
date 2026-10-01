#pragma once
#ifndef __FILE_LOCATION_MANAGER_XENON_H__
#define __FILE_LOCATION_MANAGER_XENON_H__

/* ---------- headers */

#include "foundation\baselib\files\file_location_manager.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

extern bool file_locations_find_working_directory(s_file_available_location * out_directory, bool * out_is_devkit_drive);
extern bool file_locations_find_media_directory(s_file_available_location * out_directory);
extern unsigned long file_locations_find_utility_drives(long maximum_count, s_file_available_location * out_locations);
extern bool mount_devkit_drive(s_file_available_location * out_directory, bool * out_is_devkit_drive);
extern bool mount_secondary_utility_drive_as_working_directory(s_file_available_location * out_directory);
extern bool mount_mu_as_working_directory(s_file_available_location * out_directory);

/* ---------- globals */

/* ---------- public code */

#endif // __FILE_LOCATION_MANAGER_XENON_H__

