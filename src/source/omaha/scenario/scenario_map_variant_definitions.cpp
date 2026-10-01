#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\scenario\\scenario_map_variant_definitions.cpp"
/* ---------- headers */

#include "omaha\scenario\scenario_map_variant_definitions.h"
#include "core\corelib\cseries\cseries_events.h"
#include "omaha\cseries\cseries.h"
#include "omaha\objects\object_definitions.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// struct s_tag_struct_definition map_variant_palette_block_struct_definition; // "?map_variant_palette_block_struct_definition@@3Us_tag_struct_definition@@A"
// struct s_tag_block_definition map_variant_palette_block; // "?map_variant_palette_block@@3Us_tag_block_definition@@A"

// bool postprocess_map_variant_object_variant(long, void *, bool);

bool postprocess_map_variant_object_variant(long tag_index, void * element, bool for_editor)
{
    mangled_ppc("?postprocess_map_variant_object_variant@@YA_NJPAX_N@Z");

    if (!for_editor)
    {
        s_map_variant_object_variant * object_variant = static_cast<s_map_variant_object_variant *>(element);
        if (object_variant->object.index != NONE)
        {
            _object_definition * object_definition = static_cast<_object_definition *>(tag_get(OBJECT_TAG, object_variant->object.index));
            if (object_definition->multiplayer_object.count == 0)
            {
                event_wrapped(_event_error, "map_variant:tag '%s' doesn't have multiplayer properties!  removing it from the map variant palette", tag_get_name(object_variant->object.index));
                tag_reference_clear(&object_variant->object);
            }
        }
    }

    return true;
};

