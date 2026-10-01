#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\structures\\detail_object_definitions.cpp"
/* ---------- headers */

#include "omaha\structures\detail_object_definitions.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_events.h"
#include "core\corelib\cseries\cseries_macros.h"
#include "omaha\bitmaps\bitmap_group.h"
#include "omaha\cseries\cseries.h"
#include "omaha\scenario\scenario_definitions.h"
#include "omaha\tag_files\tag_groups.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// struct s_tag_reference_definition global_detail_object_collection_reference; // "?global_detail_object_collection_reference@@3Us_tag_reference_definition@@A"
// struct s_tag_block_definition detail_object_collection_block; // "?detail_object_collection_block@@3Us_tag_block_definition@@A"
// struct s_tag_group_legacy_vtable legacy_detail_object_collection_vtable; // "?legacy_detail_object_collection_vtable@@3Us_tag_group_legacy_vtable@@A"
// struct s_tag_group detail_object_collection_group; // "?detail_object_collection_group@@3Us_tag_group@@A"
// struct s_tag_struct_definition global_detail_object_cells_block_struct_definition; // "?global_detail_object_cells_block_struct_definition@@3Us_tag_struct_definition@@A"
// struct s_tag_block_definition global_detail_object_cells_block; // "?global_detail_object_cells_block@@3Us_tag_block_definition@@A"
// struct s_tag_block_definition global_detail_object_block; // "?global_detail_object_block@@3Us_tag_block_definition@@A"
// struct s_tag_struct_definition global_detail_object_block_struct_definition; // "?global_detail_object_block_struct_definition@@3Us_tag_struct_definition@@A"
// struct s_tag_struct_definition global_detail_object_counts_block_struct_definition; // "?global_detail_object_counts_block_struct_definition@@3Us_tag_struct_definition@@A"
// struct s_tag_block_definition global_detail_object_counts_block; // "?global_detail_object_counts_block@@3Us_tag_block_definition@@A"
// struct s_tag_block_definition global_z_reference_vector_block; // "?global_z_reference_vector_block@@3Us_tag_block_definition@@A"
// struct s_tag_struct_definition global_z_reference_vector_block_struct_definition; // "?global_z_reference_vector_block_struct_definition@@3Us_tag_struct_definition@@A"
// struct s_tag_group_stream_definition legacy_detail_object_collection_stream_definition; // "?legacy_detail_object_collection_stream_definition@@3Us_tag_group_stream_definition@@A"
// struct s_tag_group_sync_definition legacy_detail_object_collection_xsync_declaration; // "?legacy_detail_object_collection_xsync_declaration@@3Us_tag_group_sync_definition@@A"
// class c_legacy_tag_group_vtable_shim legacy_detail_object_collection_vtable_shim; // "?legacy_detail_object_collection_vtable_shim@@3Vc_legacy_tag_group_vtable_shim@@A"

// void postprocess_detail_objects(struct scenario *, struct structure_detail_object_data *);
// bool postprocess_detail_object_collection(long, bool);
// bool postprocess_detail_object_type(struct bitmap_group *, struct detail_object_type_definition *, char const **);

void postprocess_detail_objects(scenario * scenario, structure_detail_object_data * detail_objects)
{
    mangled_ppc("?postprocess_detail_objects@@YAXPAUscenario@@PAUstructure_detail_object_data@@@Z");

    if (detail_objects->z_reference_vectors.count != 0)
    {
        detail_object_collection_definition * collections[MAXIMUM_DETAIL_OBJECT_LAYERS_PER_STRUCTURE] = { 0 };
        short layer_index;
        short cell_index;

        for (layer_index = 0; layer_index < scenario->detail_object_collection_palette.count; layer_index++)
        {
            long collection_index = static_cast<scenario_detail_object_collection_palette_entry *>(tag_block_get_element_with_size(&scenario->detail_object_collection_palette, layer_index, sizeof(scenario_detail_object_collection_palette_entry)))->reference.index;
            assert_tag_debug_untracked_jul_11_2011(29, layer_index<MAXIMUM_DETAIL_OBJECT_LAYERS_PER_STRUCTURE);
            collections[layer_index] = collection_index == NONE ? NULL : static_cast<detail_object_collection_definition *>(tag_get(DETAIL_OBJECT_COLLECTION_TAG, collection_index));
        }

        for (cell_index = 0; cell_index < detail_objects->cells.count; cell_index++)
        {
            detail_object_cell_definition * cell = static_cast<detail_object_cell_definition *>(tag_block_get_element_with_size(&detail_objects->cells, cell_index, sizeof(detail_object_cell_definition)));
            short count = 0;
            for (layer_index = 0; layer_index < scenario->detail_object_collection_palette.count; layer_index++)
            {
                if (TEST_BIT(cell->valid_layers_flags, layer_index) && collections[layer_index])
                {
                    detail_object_z_reference_vector * z_reference_vector = static_cast<detail_object_z_reference_vector *>(tag_block_get_element_with_size(&detail_objects->z_reference_vectors, cell->count_index + count, sizeof(detail_object_z_reference_vector)));
                    z_reference_vector->n[3] += collections[layer_index]->global_z_offset / 8.0f;
                    count++;
                }
            }
        }
    }
};

bool postprocess_detail_object_collection(long tag_index, bool for_editor)
{
    mangled_ppc("?postprocess_detail_object_collection@@YA_NJ_N@Z");

    bool success = true;
    if (!for_editor)
    {
        detail_object_collection_definition * collection = static_cast<detail_object_collection_definition *>(tag_get(DETAIL_OBJECT_COLLECTION_TAG, tag_index));
        if (collection->sprite_plate.index != NONE)
        {
            bitmap_group * bitmap = static_cast<bitmap_group *>(tag_get(BITMAP_GROUP_TAG, collection->sprite_plate.index));
            char const * error_string = NULL;
            short type_index;
            for (type_index = 0; type_index < collection->types.count; type_index++)
            {
                detail_object_type_definition * type = static_cast<detail_object_type_definition *>(tag_block_get_element_with_size(&collection->types, type_index, sizeof(detail_object_type_definition)));
                success = success && postprocess_detail_object_type(bitmap, type, &error_string);
                if (!success && error_string)
                {
                    event_wrapped(_event_warning, "detail_object_type %s: %s", type->name, error_string);
                }
            }
        }
        else
        {
            event_wrapped(_event_warning, "bitmap '%s' does not exist", collection->sprite_plate.name);
            success = false;
        }

        if (!success)
        {
            event_wrapped(_event_warning, "error loading detail_object_collection '%s'", tag_get_name(tag_index));
        }
    }

    return success;
};

bool postprocess_detail_object_type(bitmap_group * bitmap, detail_object_type_definition * type, char const ** error_string)
{
    mangled_ppc("?postprocess_detail_object_type@@YA_NPAUbitmap_group@@PAUdetail_object_type_definition@@PAPBD@Z");

    bool success = true;
    *error_string = NULL;
    if (!VALID_INDEX(type->sequence_index, bitmap->sequences.count))
    {
        success = false;
        *error_string = "type does not reference a valid sequence";
    }
    else
    {
        bitmap_group_sequence * sequence_data = static_cast<bitmap_group_sequence *>(tag_block_get_element_with_size(&bitmap->sequences, type->sequence_index, sizeof(bitmap_group_sequence)));
        type->first_sprite_index = 0;
        for (short bitmap_sequence_index = 0; bitmap_sequence_index < type->sequence_index; bitmap_sequence_index++)
        {
            type->first_sprite_index += static_cast<bitmap_group_sequence *>(tag_block_get_element_with_size(&bitmap->sequences, bitmap_sequence_index, sizeof(bitmap_group_sequence)))->sprites.count;
        }
        type->sprite_count = static_cast<unsigned char>(sequence_data->sprites.count);
    }

    return success;
};

