/* ---------- headers */

#include "omaha\cutscene\recorded_animation_definitions.h"
#include "core\corelib\cseries\cseries_string.h"
#include "omaha\cseries\cseries.h"
#include "omaha\cutscene\recorded_animation_playback.h"
#include "omaha\cutscene\recorded_animation_playback_v1.h"
#include "omaha\scenario\scenario_definitions.h"
#include "omaha\tag_files\tag_groups.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// struct s_tag_block_definition recorded_animation_block; // "?recorded_animation_block@@3Us_tag_block_definition@@A"
// struct s_tag_struct_definition recorded_animation_block_struct_definition; // "?recorded_animation_block_struct_definition@@3Us_tag_struct_definition@@A"

// void byte_swap_recording(void *, void *, long, bool);
// short scenario_get_animation_by_name(struct scenario const *, char const *);

void byte_swap_recording(void * element, void * data, long data_size, bool for_writing)
{
    mangled_ppc("?byte_swap_recording@@YAXPAX0J_N@Z");

    recorded_animation_definition * animation = static_cast<recorded_animation_definition *>(element);
    switch (animation->version)
    {
    case 1:
    case 2:
    case 3:
        byte_swap_recording_stream_v1(data, data_size, animation->unit_control_data_version);
        break;
    case 4:
        byte_swap_recording_stream(data, data_size, animation->unit_control_data_version);
        break;
    }
};

short scenario_get_animation_by_name(scenario const * scenario, char const * animation_name)
{
    mangled_ppc("?scenario_get_animation_by_name@@YAFPBUscenario@@PBD@Z");

    short index = NONE;
    for (short animation_index = 0; animation_index < scenario->recorded_animations.count; animation_index++)
    {
        recorded_animation_definition * animation = static_cast<recorded_animation_definition *>(tag_block_get_element_with_size(&scenario->recorded_animations, animation_index, sizeof(recorded_animation_definition)));
        if (csstricmp(animation->name, animation_name) == 0)
        {
            index = animation_index;
            break;
        }
    }

    return index;
};

