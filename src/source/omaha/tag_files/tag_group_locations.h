#pragma once
#ifndef __TAG_GROUP_LOCATIONS_H__
#define __TAG_GROUP_LOCATIONS_H__

/* ---------- headers */

/* ---------- constants */

enum e_tag_group_location
{
    _tag_group_location_rasterizer = 0,
    _tag_group_location_shaders,

    k_number_of_tag_group_locations
};

/* ---------- definitions */

/* ---------- prototypes */

extern char const * tag_group_location_get_tag_path(e_tag_group_location location);
extern bool tag_path_is_valid_for_location(e_tag_group_location location, char const * path);

/* ---------- globals */

extern char const * k_tag_group_location_paths[k_number_of_tag_group_locations];

/* ---------- public code */

#endif // __TAG_GROUP_LOCATIONS_H__

