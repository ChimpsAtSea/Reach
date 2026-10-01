/* ---------- headers */

#include "omaha\game\megalogamengine\megalogamengine_sound_definitions.h"
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

// struct s_tag_block_definition megalogamengine_sounds_block; // "?megalogamengine_sounds_block@@3Us_tag_block_definition@@A"
// struct s_tag_group megalogamengine_sounds_group; // "?megalogamengine_sounds_group@@3Us_tag_group@@A"
// struct s_tag_reference_definition global_megalogamengine_sound_group_reference; // "?global_megalogamengine_sound_group_reference@@3Us_tag_reference_definition@@A"
// struct s_tag_group_legacy_vtable legacy_megalogamengine_sounds_vtable; // "?legacy_megalogamengine_sounds_vtable@@3Us_tag_group_legacy_vtable@@A"
// struct s_tag_group_stream_definition legacy_megalogamengine_sounds_stream_definition; // "?legacy_megalogamengine_sounds_stream_definition@@3Us_tag_group_stream_definition@@A"
// struct s_tag_group_sync_definition legacy_megalogamengine_sounds_xsync_declaration; // "?legacy_megalogamengine_sounds_xsync_declaration@@3Us_tag_group_sync_definition@@A"
// class c_legacy_tag_group_vtable_shim legacy_megalogamengine_sounds_vtable_shim; // "?legacy_megalogamengine_sounds_vtable_shim@@3Vc_legacy_tag_group_vtable_shim@@A"

// long megalogamengine_get_sound_definition_index(enum e_megalo_sound);

long megalogamengine_get_sound_definition_index(e_megalo_sound megalo_sound)
{
    mangled_ppc("?megalogamengine_get_sound_definition_index@@YAJW4e_megalo_sound@@@Z");

    long sound_definition_index = NONE;
    if (megalo_sound != _megalo_sound_none)
    {
        s_multiplayer_runtime_globals_definition * runtime_data = scenario_multiplayer_globals_try_and_get_runtime_data();
        if (runtime_data)
        {
            long megalo_sounds_index = runtime_data->megalo_sounds.index;
            if (megalo_sounds_index != NONE)
            {
                s_megalogamengine_sound_group * sound_group = static_cast<s_megalogamengine_sound_group *>(tag_get(k_megalogamengine_sounds_definition_tag, megalo_sounds_index));
                sound_definition_index = sound_group->sounds[megalo_sound].index;
            }
        }
    }

    return sound_definition_index;
};

