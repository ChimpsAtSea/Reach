#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\scenario\\scenario_named_location_volumes.cpp"

/* ---------- headers */

#include "omaha\scenario\scenario_named_location_volumes.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "foundation\baselib\datatypes\static_stack.h"
#include "omaha\cseries\cseries.h"
#include "omaha\game\location_name_definitions.h"
#include "omaha\math\polygon_math.h"
#include "omaha\math\real_math.h"
#include "omaha\scenario\scenario.h"
#include "omaha\scenario\scenario_definitions.h"
#include "omaha\tag_files\tag_groups.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

c_tag_struct_vtable<c_scenario_named_location_volume_block_vtable> scenario_named_location_volume_block_struct_struct_vtable;

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// struct s_tag_block_definition scenario_named_location_volume_block; // "?scenario_named_location_volume_block@@3Us_tag_block_definition@@A"
// struct s_tag_struct_definition scenario_named_location_volume_block_struct; // "?scenario_named_location_volume_block_struct@@3Us_tag_struct_definition@@A"
// class c_tag_struct_vtable<class c_scenario_named_location_volume_block_vtable> scenario_named_location_volume_block_struct_struct_vtable; // "?scenario_named_location_volume_block_struct_struct_vtable@@3V?$c_tag_struct_vtable@Vc_scenario_named_location_volume_block_vtable@@@@A"

// bool point_in_named_location_volume(struct s_scenario_named_location_volume const *, union real_point3d const *);
// long named_location_volumes_get_location_name_index_for_point(union real_point3d const *);
// public: c_tag_struct_vtable<class c_scenario_named_location_volume_block_vtable>::c_tag_struct_vtable<class c_scenario_named_location_volume_block_vtable>(void);
// public: virtual bool c_tag_struct_vtable<class c_scenario_named_location_volume_block_vtable>::has_byte_swap_proc(void) const;
// public: virtual void c_tag_struct_vtable<class c_scenario_named_location_volume_block_vtable>::byte_swap_block_proc(void *) const;
// public: virtual bool c_tag_struct_vtable<class c_scenario_named_location_volume_block_vtable>::has_postprocess_proc(void) const;
// public: virtual bool c_tag_struct_vtable<class c_scenario_named_location_volume_block_vtable>::postprocess_thunk(long, void *, bool) const;
// public: virtual bool c_tag_struct_vtable<class c_scenario_named_location_volume_block_vtable>::has_format_proc(void) const;
// public: virtual char * c_tag_struct_vtable<class c_scenario_named_location_volume_block_vtable>::format_thunk(long, __int64, struct s_tag_block *, long, char *, long) const;
// public: virtual bool c_tag_struct_vtable<class c_scenario_named_location_volume_block_vtable>::has_on_delete_proc(void) const;
// public: virtual void c_tag_struct_vtable<class c_scenario_named_location_volume_block_vtable>::on_delete_thunk(void *) const;
// public: virtual bool c_tag_struct_vtable<class c_scenario_named_location_volume_block_vtable>::has_on_new_proc(void) const;
// public: virtual bool c_tag_struct_vtable<class c_scenario_named_location_volume_block_vtable>::on_new_thunk(void *) const;
// public: virtual bool c_tag_struct_vtable<class c_scenario_named_location_volume_block_vtable>::has_on_copy_proc(void) const;
// public: virtual bool c_tag_struct_vtable<class c_scenario_named_location_volume_block_vtable>::on_copy_thunk(void const *, void *) const;
// public: virtual bool c_tag_struct_vtable<class c_scenario_named_location_volume_block_vtable>::has_write_to_cache_file_proc(void) const;
// public: virtual void c_tag_struct_vtable<class c_scenario_named_location_volume_block_vtable>::write_to_cache_file_thunk(long, struct s_tag_block *, struct s_cache_file_builder_stream_context const *, void **, void **) const;
// public: virtual bool c_tag_struct_vtable<class c_scenario_named_location_volume_block_vtable>::has_block_does_not_exist_in_cache_file_proc(void) const;
// public: virtual bool c_tag_struct_vtable<class c_scenario_named_location_volume_block_vtable>::block_does_not_exist_in_cache_file_thunk(void) const;
// public: virtual bool c_tag_struct_vtable<class c_scenario_named_location_volume_block_vtable>::has_fixup_old_struct_definition(void) const;
// public: virtual struct s_tag_struct_definition * c_tag_struct_vtable<class c_scenario_named_location_volume_block_vtable>::get_fixup_source_definition_thunk(void) const;
// public: virtual bool c_tag_struct_vtable<class c_scenario_named_location_volume_block_vtable>::has_fixup_old_struct_proc(void) const;
// public: virtual bool c_tag_struct_vtable<class c_scenario_named_location_volume_block_vtable>::fixup_old_struct_thunk(class c_basic_buffer<void> &, struct s_tag_struct_definition const *, class c_basic_buffer<void> &, struct s_tag_struct_definition const *, class c_tag_allocator *, bool) const;
// public: virtual bool c_tag_struct_vtable<class c_scenario_named_location_volume_block_vtable>::has_fixup_old_struct_from_disk_proc(void) const;
// public: virtual bool c_tag_struct_vtable<class c_scenario_named_location_volume_block_vtable>::fixup_old_struct_from_disk_thunk(struct s_tag_struct_definition const *, class c_basic_buffer<void> &, struct s_tag_struct_definition const *, class c_basic_buffer<void> &, struct s_tag_struct_definition const *, class c_tag_allocator *, bool) const;
// public: static void s_tag_vtable_has_byte_swap_proc<class c_scenario_named_location_volume_block_vtable>::call(void *);
// public: static bool s_tag_vtable_has_postprocess_proc<class c_scenario_named_location_volume_block_vtable>::call(long, void *, bool);
// public: static char * s_tag_vtable_has_format_proc<class c_scenario_named_location_volume_block_vtable>::call(long, __int64, struct s_tag_block *, long, char *, long);
// public: static void s_tag_vtable_has_on_delete_proc<class c_scenario_named_location_volume_block_vtable>::call(void *);
// public: static bool s_tag_vtable_has_on_new_proc<class c_scenario_named_location_volume_block_vtable>::call(void *);
// public: static bool c_scenario_named_location_volume_block_vtable::on_new_proc(void *);
// public: static bool s_tag_vtable_has_on_copy_proc<class c_scenario_named_location_volume_block_vtable>::call(void const *, void *);
// public: static void s_tag_vtable_has_write_to_cache_file_proc<class c_scenario_named_location_volume_block_vtable>::call(long, struct s_tag_block *, struct s_cache_file_builder_stream_context const *, void **, void **);
// public: static bool s_tag_vtable_has_block_does_not_exist_in_cache_file<class c_scenario_named_location_volume_block_vtable>::call(void);
// public: static struct s_tag_struct_definition * s_tag_vtable_has_get_fixup_source_definition_proc<class c_scenario_named_location_volume_block_vtable>::call(void);
// public: static bool s_tag_vtable_has_fixup_old_struct_proc<class c_scenario_named_location_volume_block_vtable>::call(class c_basic_buffer<void> &, struct s_tag_struct_definition const *, class c_basic_buffer<void> &, struct s_tag_struct_definition const *, class c_tag_allocator *, bool);
// public: static bool s_tag_vtable_has_fixup_old_struct_from_disk_proc<class c_scenario_named_location_volume_block_vtable>::call(struct s_tag_struct_definition const *, class c_basic_buffer<void> &, struct s_tag_struct_definition const *, class c_basic_buffer<void> &, struct s_tag_struct_definition const *, class c_tag_allocator *, bool);

bool point_in_named_location_volume(s_scenario_named_location_volume const * named_location_volume, real_point3d const * point)
{
    mangled_ppc("?point_in_named_location_volume@@YA_NPBUs_scenario_named_location_volume@@PBTreal_point3d@@@Z");

    bool in_volume = false;

    assert_tag_debug_untracked_jul_11_2011(75, named_location_volume);

    real minimum_z = k_real_max;
    real maximum_z = k_real_min;
    c_static_stack<real_point2d, k_maximum_points_per_sector> points;
    points.resize(named_location_volume->points.count);
    for (long point_index = 0; point_index < named_location_volume->points.count; point_index++)
    {
        s_real_sector_point const * sector_point = static_cast<s_real_sector_point const *>(tag_block_get_element_with_size(&named_location_volume->points, point_index, sizeof(s_real_sector_point)));
        minimum_z = real_min(minimum_z, sector_point->position.z);
        maximum_z = real_max(maximum_z, sector_point->position.z);
        points[point_index].x = sector_point->position.x;
        points[point_index].y = sector_point->position.y;
    }

    real_point2d point_flat;
    point_flat.x = point->x;
    point_flat.y = point->y;
    in_volume = point->z <= maximum_z + named_location_volume->height && point->z >= minimum_z - named_location_volume->sink && point_in_polygon2d(&point_flat, points.count(), points.get_elements());

    return in_volume;
};

long named_location_volumes_get_location_name_index_for_point(real_point3d const * point)
{
    mangled_ppc("?named_location_volumes_get_location_name_index_for_point@@YAJPBTreal_point3d@@@Z");

    assert_tag_debug_untracked_jul_11_2011(109, point);

    scenario * global_scenario = global_scenario_get();
    s_scenario_named_location_volume const * volume = NULL;
    long location_name_index = NONE;
    for (long named_location_volume_index = 0; named_location_volume_index < global_scenario->named_location_volumes.count; named_location_volume_index++)
    {
        s_scenario_named_location_volume const * named_location_volume = static_cast<s_scenario_named_location_volume const *>(tag_block_get_element_with_size(&global_scenario->named_location_volumes, named_location_volume_index, sizeof(s_scenario_named_location_volume)));
        if (point_in_named_location_volume(named_location_volume, point))
        {
            volume = named_location_volume;
            break;
        }
    }

    if (volume)
    {
        location_name_index = location_names_get_name_index_from_string_id(volume->location_name);
    }

    return location_name_index;
};
