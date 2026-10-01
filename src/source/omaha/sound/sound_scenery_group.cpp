/* ---------- headers */

#include "omaha\sound\sound_scenery_group.h"
#include "core\corelib\cseries\cseries_macros.h"
#include "omaha\cseries\cseries.h"
#include "omaha\math\real_math.h"
#include "omaha\objects\object_definitions.h"
#include "omaha\sound\game_sound_definitions.h"
#include "omaha\sound\sound_definitions.h"
#include "omaha\sound\sound_scenery.h"
#include "omaha\tag_files\tag_groups.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

static real k_half_circle = k_pi;

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// struct s_tag_block_definition sound_scenery_block; // "?sound_scenery_block@@3Us_tag_block_definition@@A"
// struct s_tag_group_legacy_vtable legacy_sound_scenery_vtable; // "?legacy_sound_scenery_vtable@@3Us_tag_group_legacy_vtable@@A"
// struct s_tag_group sound_scenery_group; // "?sound_scenery_group@@3Us_tag_group@@A"
// struct s_tag_group_stream_definition legacy_sound_scenery_stream_definition; // "?legacy_sound_scenery_stream_definition@@3Us_tag_group_stream_definition@@A"
// struct s_tag_group_sync_definition legacy_sound_scenery_xsync_declaration; // "?legacy_sound_scenery_xsync_declaration@@3Us_tag_group_sync_definition@@A"
// class c_legacy_tag_group_vtable_shim legacy_sound_scenery_vtable_shim; // "?legacy_sound_scenery_vtable_shim@@3Vc_legacy_tag_group_vtable_shim@@A"

// bool postprocess_sound_scenery_definition(long, bool);

bool postprocess_sound_scenery_definition(long tag_index, bool for_editor)
{
    mangled_ppc("?postprocess_sound_scenery_definition@@YA_NJ_N@Z");

    if (!for_editor)
    {
        s_sound_scenery_definition * definition = static_cast<s_sound_scenery_definition *>(tag_get(SOUND_SCENERY_TAG, tag_index));
        definition->scenery.runtime_minimum_distance = k_real_max;
        definition->scenery.runtime_inner_cone_angle = k_half_circle;
        definition->scenery.runtime_outer_cone_angle = k_half_circle;
        definition->object.bounding_radius = 1.0f;

        for (long attachment_index = 0, attachment_count = definition->object.attachments.count; attachment_index < attachment_count; attachment_index++)
        {
            object_attachment_definition * attachment = static_cast<object_attachment_definition *>(tag_block_get_element_with_size(&definition->object.attachments, attachment_index, sizeof(object_attachment_definition)));
            if (attachment->type.group_tag == SOUND_LOOPING_TAG && attachment->type.index != NONE)
            {
                looping_sound_definition * looping_sound = static_cast<looping_sound_definition *>(tag_get(SOUND_LOOPING_TAG, attachment->type.index));
                definition->scenery.runtime_minimum_distance = CEILING(definition->scenery.runtime_minimum_distance, looping_sound->runtime_distance_bounds.lower);
                definition->scenery.runtime_maximum_distance = MAX(definition->scenery.runtime_maximum_distance, looping_sound->runtime_distance_bounds.upper);
                if (looping_sound->tracks.count != 0)
                {
                    looping_sound_track * track = static_cast<looping_sound_track *>(tag_block_get_element_with_size(&looping_sound->tracks, 0, sizeof(looping_sound_track)));
                    if (track->loop_sound.index != NONE)
                    {
                        sound_definition * sound = static_cast<sound_definition *>(tag_get(SOUND_TAG, track->loop_sound.index));
                        if (!sound_definition_get_playback_parameters(sound)->internal_flags.test(_sound_playback_flag_bit0))
                        {
                            definition->scenery.runtime_inner_cone_angle = sound->playback.inner_cone_angle;
                            definition->scenery.runtime_outer_cone_angle = sound->playback.outer_cone_angle;
                        }
                    }
                }
            }
        }

        definition->scenery.runtime_minimum_distance = CEILING(definition->scenery.runtime_maximum_distance, definition->scenery.runtime_minimum_distance);
    }

    return true;
};
