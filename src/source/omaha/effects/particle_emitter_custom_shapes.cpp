/* ---------- headers */

#include "omaha\effects\particle_emitter_custom_shapes.h"
#include "omaha\tag_files\tag_groups.h"
#include "core\corelib\cseries\cseries_string.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// struct s_tag_reference_definition particle_emitter_custom_shape_reference; // "?particle_emitter_custom_shape_reference@@3Us_tag_reference_definition@@A"
// struct s_tag_reference_definition particle_model_reference; // "?particle_model_reference@@3Us_tag_reference_definition@@A"
// struct s_custom_tool_command_definition particle_emitter_custom_points_import_definition; // "?particle_emitter_custom_points_import_definition@@3Us_custom_tool_command_definition@@A"
// struct s_tag_block_definition particle_emitter_custom_points_block; // "?particle_emitter_custom_points_block@@3Us_tag_block_definition@@A"
// struct s_tag_group particle_emitter_custom_points_group; // "?particle_emitter_custom_points_group@@3Us_tag_group@@A"
// struct s_tag_group_legacy_vtable legacy_particle_emitter_custom_points_vtable; // "?legacy_particle_emitter_custom_points_vtable@@3Us_tag_group_legacy_vtable@@A"
// struct s_tag_group_stream_definition legacy_particle_emitter_custom_points_stream_definition; // "?legacy_particle_emitter_custom_points_stream_definition@@3Us_tag_group_stream_definition@@A"
// struct s_tag_group_sync_definition legacy_particle_emitter_custom_points_xsync_declaration; // "?legacy_particle_emitter_custom_points_xsync_declaration@@3Us_tag_group_sync_definition@@A"
// class c_legacy_tag_group_vtable_shim legacy_particle_emitter_custom_points_vtable_shim; // "?legacy_particle_emitter_custom_points_vtable_shim@@3Vc_legacy_tag_group_vtable_shim@@A"

// void particle_emitter_custom_points_import_callback(long, long, char *, long);

void particle_emitter_custom_points_import_callback(long tag_index, long field_index, char * buffer, long buffer_size)
{
    mangled_ppc("?particle_emitter_custom_points_import_callback@@YAXJJPADJ@Z");

    switch (field_index)
    {
    case 0:
        csnzprintf(buffer, buffer_size, "%s", tag_get_name(tag_index));
        break;
    default:
    {
        s_particle_emitter_custom_points * custom_points = s_particle_emitter_custom_points::get(tag_index);
        if (custom_points->source_reference.name == NULL)
        {
            csnzprintf(buffer, buffer_size, "");
        }
        else
        {
            csnzprintf(buffer, buffer_size, "%s", custom_points->source_reference.name);
        }
    }
        break;
    }
};

