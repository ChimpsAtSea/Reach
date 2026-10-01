#pragma once
#ifndef __SCENARIO_NAMED_LOCATION_VOLUMES_H__
#define __SCENARIO_NAMED_LOCATION_VOLUMES_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"
#include "omaha\math\real_math.h"
#include "omaha\tag_files\tag_groups.h"
#include "omaha\tag_files\tag_group_definitions.h"

/* ---------- constants */

enum
{
    k_maximum_points_per_sector = 32,
};

/* ---------- definitions */

// $TODO the target also uses sizeof(s_real_sector_point) in scenario_definitions.obj; move to a shared sector header if one appears
struct s_real_sector_point
{
    real_point3d position; // 0x0
    real_euler_angles2d normal; // 0xC
};
static_assert(sizeof(s_real_sector_point) == 0x14, "s_real_sector_point");

struct s_scenario_named_location_volume
{
    enum
    {
        k_maximum_scenario_named_location_volumes = 128,
    };

    s_tag_block points; // 0x0 s_real_sector_point
    real height; // 0xC
    real sink; // 0x10
    long location_name; // 0x14 string_id
};
static_assert(sizeof(s_scenario_named_location_volume) == 0x18, "s_scenario_named_location_volume");

class c_scenario_named_location_volume_block_vtable :
    public c_tag_struct_vtable_defaults
{
public:
    static bool on_new_proc(void * data)
    {
        mangled_ppc("?on_new_proc@c_scenario_named_location_volume_block_vtable@@SA_NPAX@Z");

        s_scenario_named_location_volume * named_location_volume = static_cast<s_scenario_named_location_volume *>(data);
        named_location_volume->height = 1.0f;
        named_location_volume->sink = 1.0f;
        return true;
    }
};

/* ---------- prototypes */

bool point_in_named_location_volume(s_scenario_named_location_volume const * named_location_volume, real_point3d const * point);
long named_location_volumes_get_location_name_index_for_point(real_point3d const * point);

/* ---------- globals */

extern c_tag_struct_vtable<c_scenario_named_location_volume_block_vtable> scenario_named_location_volume_block_struct_struct_vtable;

/* ---------- public code */

#endif // __SCENARIO_NAMED_LOCATION_VOLUMES_H__

