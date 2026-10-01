#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\game\\location_name_definitions.cpp"
/* ---------- headers */

#include "omaha\game\location_name_definitions.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_events.h"
#include "core\corelib\cseries\cseries_macros.h"
#include "foundation\baselib\errors\output\output_globals.h"
#include "omaha\cseries\cseries.h"
#include "omaha\game\players.h"
#include "omaha\math\real_math.h"
#include "omaha\objects\multiplayer_game_objects.h"
#include "omaha\objects\object_types.h"
#include "omaha\objects\objects.h"
#include "omaha\scenario\scenario.h"
#include "omaha\scenario\scenario_definitions.h"
#include "omaha\scenario\scenario_named_location_volumes.h"
#include "omaha\tag_files\string_ids.h"
#include "omaha\tag_files\tag_groups.h"
#include "omaha\text\text_group.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// struct s_tag_block_definition location_name_globals_definition_block; // "?location_name_globals_definition_block@@3Us_tag_block_definition@@A"
// struct s_tag_group location_name_globals_definition_group; // "?location_name_globals_definition_group@@3Us_tag_group@@A"
// struct s_tag_reference_definition global_location_name_globals_reference; // "?global_location_name_globals_reference@@3Us_tag_reference_definition@@A"
// struct s_tag_group_legacy_vtable legacy_location_name_globals_definition_vtable; // "?legacy_location_name_globals_definition_vtable@@3Us_tag_group_legacy_vtable@@A"
// struct s_tag_group_stream_definition legacy_location_name_globals_definition_stream_definition; // "?legacy_location_name_globals_definition_stream_definition@@3Us_tag_group_stream_definition@@A"
// struct s_tag_group_sync_definition legacy_location_name_globals_definition_xsync_declaration; // "?legacy_location_name_globals_definition_xsync_declaration@@3Us_tag_group_sync_definition@@A"
// class c_legacy_tag_group_vtable_shim legacy_location_name_globals_definition_vtable_shim; // "?legacy_location_name_globals_definition_vtable_shim@@3Vc_legacy_tag_group_vtable_shim@@A"

// long location_names_get_name_count(void);
// void location_names_get_name_string(long, class c_static_wchar_string<256> *);
// long location_names_get_name_index_from_string_id(long);
// long location_names_get_name(long);
// long location_names_get_name_index_for_player(long);
// long location_names_get_name_index_for_point(union real_point3d const *);
// void location_names_print_hs(void);
// struct s_location_name_globals_tag_definition const * try_and_get_location_name_globals(void);

long location_names_get_name_count(void)
{
    mangled_ppc("?location_names_get_name_count@@YAJXZ");

    s_location_name_globals_tag_definition const * location_name_globals = try_and_get_location_name_globals();
    long name_count = 0;
    if (location_name_globals)
    {
        name_count = location_name_globals->location_names.count;
    }

    return name_count;
};

void location_names_get_name_string(long location_name_index, c_static_wchar_string<256> * string)
{
    mangled_ppc("?location_names_get_name_string@@YAXJPAV?$c_static_wchar_string@$0BAA@@@@Z");

    s_location_name_globals_tag_definition const * location_name_globals = try_and_get_location_name_globals();
    if (location_name_globals && location_name_globals->location_name_string_list.index != NONE)
    {
        string_list_get_normal_string(location_name_globals->location_name_string_list.index, location_name_index, string, NULL);
    }
};

long location_names_get_name_index_from_string_id(long name)
{
    mangled_ppc("?location_names_get_name_index_from_string_id@@YAJJ@Z");

    long location_name_index = NONE;
    if (name != 0 && name != -1)
    {
        s_location_name_globals_tag_definition const * location_name_globals = try_and_get_location_name_globals();
        if (location_name_globals)
        {
            long name_count = location_name_globals->location_names.count;
            for (long name_index = 0; location_name_index == NONE && name_index < name_count; name_index++)
            {
                s_location_name_tag_definition const * location_name = static_cast<s_location_name_tag_definition const *>(tag_block_get_element_with_size(&location_name_globals->location_names, name_index, sizeof(s_location_name_tag_definition)));
                if (name == location_name->name)
                {
                    location_name_index = name_index;
                }
            }

            if (location_name_index == NONE)
            {
                event_wrapped(_event_error, "scenario: location names: cannot find '%s' in the location_globals name list for this scenario", string_id_get_string_const(name));
            }
        }
        else
        {
            event_wrapped(_event_error, "scenario: location names: no location name globals found.");
        }
    }

    if (location_name_index == NONE)
    {
        location_name_index = 0;
    }

    return location_name_index;
};

long location_names_get_name(long location_name_index)
{
    mangled_ppc("?location_names_get_name@@YAJJ@Z");

    long name = NONE;
    s_location_name_globals_tag_definition const * location_name_globals = try_and_get_location_name_globals();
    if (location_name_globals && location_name_index >= 0 && location_name_index < location_name_globals->location_names.count)
    {
        s_location_name_tag_definition const * location_name = static_cast<s_location_name_tag_definition const *>(tag_block_get_element_with_size(&location_name_globals->location_names, location_name_index, sizeof(s_location_name_tag_definition)));
        name = location_name->name;
    }

    return name;
};

// $TODO nonmatching: only the TLS offset of player_data (0x204 in the target) differs; it is resolved at link time
long location_names_get_name_index_for_player(long player_index)
{
    mangled_ppc("?location_names_get_name_index_for_player@@YAJJ@Z");

    long location_name_index = NONE;
    real best_volume = 0.0f;

    c_multiplayer_object_iterator<object_datum> iterator;
    iterator.begin(_object_mask_scenery, 0, 0x1000);
    while (iterator.next())
    {
        s_multiplayer_object_properties * multiplayer_properties = static_cast<s_multiplayer_object_properties *>(object_header_block_get(iterator.get_index(), &iterator.get_datum()->object.multiplayer));
        assert_tag_debug_untracked_jul_11_2011(236, multiplayer_properties);

        s_multiplayer_object_boundary_geometry_data geometry_data;
        multiplayer_object_calculate_boundary_geometry(iterator.get_index(), &geometry_data, false);
        if (player_in_multiplayer_object_boundary(player_index, &geometry_data))
        {
            real volume = 0.0f;
            switch (geometry_data.shape)
            {
            case _shape_sphere:
                volume = (4.0 / 3.0) * k_pi * geometry_data.width_or_radius * geometry_data.width_or_radius * geometry_data.width_or_radius;
                break;
            case _shape_cylinder:
                volume = k_pi * geometry_data.width_or_radius * geometry_data.width_or_radius * (geometry_data.positive_height + geometry_data.negative_height);
                break;
            case _shape_box:
                volume = geometry_data.width_or_radius * geometry_data.box_length * (geometry_data.positive_height + geometry_data.negative_height);
                break;
            default:
                dassert_tag_debug_untracked_jul_11_2011(259, false, "unreachable");
                break;
            }

            if (location_name_index == NONE || volume < best_volume)
            {
                location_name_index = multiplayer_properties->location_name_index;
                best_volume = volume;
            }
        }
    }

    if (location_name_index == NONE && player_index != NONE && static_cast<player_datum *>(datum_get(player_data, player_index))->unit_index != NONE)
    {
        real_point3d unit_origin;
        object_get_origin_interpolated(static_cast<player_datum *>(datum_get(player_data, player_index))->unit_index, &unit_origin);
        location_name_index = named_location_volumes_get_location_name_index_for_point(&unit_origin);
    }

    return location_name_index;
};

long location_names_get_name_index_for_point(real_point3d const * point)
{
    mangled_ppc("?location_names_get_name_index_for_point@@YAJPBTreal_point3d@@@Z");

    long location_name_index = NONE;
    real best_volume = 0.0f;

    c_multiplayer_object_iterator<object_datum> iterator;
    iterator.begin(_object_mask_scenery, 0, 0x1000);
    while (iterator.next())
    {
        s_multiplayer_object_properties * multiplayer_properties = object_try_and_get_multiplayer(iterator.get_index());
        if (multiplayer_properties)
        {
            s_multiplayer_object_boundary_geometry_data geometry_data;
            multiplayer_object_calculate_boundary_geometry(iterator.get_index(), &geometry_data, false);
            if (point_in_multiplayer_object_boundary(point, &geometry_data))
            {
                real volume = 0.0f;
                switch (geometry_data.shape)
                {
                case _shape_sphere:
                    volume = (4.0 / 3.0) * k_pi * geometry_data.width_or_radius * geometry_data.width_or_radius * geometry_data.width_or_radius;
                    break;
                case _shape_cylinder:
                    volume = k_pi * geometry_data.width_or_radius * geometry_data.width_or_radius * (geometry_data.positive_height + geometry_data.negative_height);
                    break;
                case _shape_box:
                    volume = geometry_data.width_or_radius * geometry_data.box_length * (geometry_data.positive_height + geometry_data.negative_height);
                    break;
                default:
                    dassert_tag_debug_untracked_jul_11_2011(320, false, "unreachable");
                    break;
                }

                if (location_name_index == NONE || volume < best_volume)
                {
                    location_name_index = multiplayer_properties->location_name_index;
                    best_volume = volume;
                }
            }
        }
    }

    if (location_name_index == NONE)
    {
        location_name_index = named_location_volumes_get_location_name_index_for_point(point);
    }

    return location_name_index;
};

void location_names_print_hs(void)
{
    mangled_ppc("?location_names_print_hs@@YAXXZ");

    long name_count = location_names_get_name_count();
    for (long location_name_index = 0; location_name_index < name_count; location_name_index++)
    {
        output_message("%i: %s", location_name_index, string_id_get_string_const(location_names_get_name(location_name_index)));
    }
};

s_location_name_globals_tag_definition const * try_and_get_location_name_globals(void)
{
    mangled_ppc("?try_and_get_location_name_globals@@YAPBUs_location_name_globals_tag_definition@@XZ");

    scenario * scenario = global_scenario_get();
    s_location_name_globals_tag_definition const * location_name_globals = NULL;
    if (scenario->location_name_globals.index != NONE)
    {
        location_name_globals = static_cast<s_location_name_globals_tag_definition const *>(tag_get(LOCATION_NAME_GLOBALS_TAG, scenario->location_name_globals.index));
    }

    return location_name_globals;
};

