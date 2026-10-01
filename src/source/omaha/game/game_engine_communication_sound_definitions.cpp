/* ---------- headers */

#include "omaha\game\game_engine_communication_sound_definitions.h"
#include "core\corelib\cseries\cseries_events.h"
#include "foundation\baselib\datatypes\static_string.h"
#include "omaha\cseries\cseries.h"
#include "omaha\game\multiplayer_definitions.h"
#include "omaha\tag_files\tag_groups.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// struct s_tag_block_definition communication_sounds_block; // "?communication_sounds_block@@3Us_tag_block_definition@@A"
// struct s_tag_group communication_sounds_group; // "?communication_sounds_group@@3Us_tag_group@@A"
// struct s_tag_reference_definition global_communication_sound_group_reference; // "?global_communication_sound_group_reference@@3Us_tag_reference_definition@@A"
// struct s_tag_group_legacy_vtable legacy_communication_sounds_vtable; // "?legacy_communication_sounds_vtable@@3Us_tag_group_legacy_vtable@@A"
// struct s_tag_group_stream_definition legacy_communication_sounds_stream_definition; // "?legacy_communication_sounds_stream_definition@@3Us_tag_group_stream_definition@@A"
// struct s_tag_group_sync_definition legacy_communication_sounds_xsync_declaration; // "?legacy_communication_sounds_xsync_declaration@@3Us_tag_group_sync_definition@@A"
// class c_legacy_tag_group_vtable_shim legacy_communication_sounds_vtable_shim; // "?legacy_communication_sounds_vtable_shim@@3Vc_legacy_tag_group_vtable_shim@@A"

// long communication_get_sound_definition_index(enum e_communication_sound);
// long communication_get_location_sound_index(class c_static_wchar_string<32> const *);

long communication_get_sound_definition_index(e_communication_sound sound)
{
    mangled_ppc("?communication_get_sound_definition_index@@YAJW4e_communication_sound@@@Z");

    long sound_index = NONE;
    if (sound != _communication_sound_none)
    {
        s_multiplayer_runtime_globals_definition * runtime_data = scenario_multiplayer_globals_try_and_get_runtime_data();
        if (runtime_data != NULL)
        {
            long communication_sounds_index = runtime_data->communication_sounds.index;
            if (communication_sounds_index != NONE)
            {
                s_communication_sound_group * communication_sounds = static_cast<s_communication_sound_group *>(tag_get(COMMUNICATION_SOUNDS_TAG, communication_sounds_index));
                sound_index = communication_sounds->sounds[sound].index;
            }
        }
    }

    return sound_index;
};

long communication_get_location_sound_index(c_static_wchar_string<32> const * location_name)
{
    mangled_ppc("?communication_get_location_sound_index@@YAJPBV?$c_static_wchar_string@$0CA@@@@Z");

    long sound_index = NONE;
    for (long location_index = 0; location_index < k_communication_location_sound_count; location_index++)
    {
        // the target never takes this branch (location name comparison compiled out)
        if (false)
        {
            sound_index = communication_get_sound_definition_index(static_cast<e_communication_sound>(location_index + _communication_sound_first_location));
        }
    }

    if (sound_index == NONE)
    {
        event_wrapped(_event_error, "sound: No voice-over sound to play for location '%S'", location_name->get_string());
    }

    return sound_index;
};

