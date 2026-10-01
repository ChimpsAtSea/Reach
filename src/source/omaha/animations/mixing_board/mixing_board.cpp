#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\animations\\mixing_board\\mixing_board.cpp"
/* ---------- headers */

#include "omaha\animations\mixing_board\mixing_board.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "omaha\animations\mixing_board\mixing_board_slider.h"
#include "omaha\animations\mixing_board\channels\aiming_channel.h"
#include "omaha\animations\mixing_board\channels\animation_channel.h"
#include "omaha\animations\mixing_board\channels\auxilary_channel.h"
#include "omaha\animations\mixing_board\channels\channel_base.h"
#include "omaha\animations\mixing_board\channels\facial_animation_channel.h"
#include "omaha\animations\mixing_board\channels\pose_blend_channel.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// void reset_mixing_board(class c_animation_manager *, long, class c_mixing_board_definition const *);
// long mixing_board_get_component(long, class c_mixing_board_definition const *, long, long);

void reset_mixing_board(c_animation_manager * animation_manager, long starting_address, c_mixing_board_definition const * definition)
{
    mangled_ppc("?reset_mixing_board@@YAXPAVc_animation_manager@@JPBVc_mixing_board_definition@@@Z");

    assert_tag_debug_untracked_jul_11_2011(15, animation_manager);
    assert_tag_debug_untracked_jul_11_2011(16, starting_address);
    assert_tag_debug_untracked_jul_11_2011(17, definition);

    long total_size = definition->get_total_size();
    if (total_size > 0)
    {
        {
            c_mixing_board_slider * slider;
            c_mixing_board_component_iterator iterator;

            iterator.setup(starting_address, definition, _mixing_board_slider);
            while (iterator.next())
            {
                if (iterator.get(&slider))
                {
                    slider->initialize();
                }
            }
        }

        for (e_mixing_board_component_type component_type = k_mixing_board_first_component_type; component_type < k_total_mixing_board_component_types; component_type++)
        {
            c_mixing_board_component_iterator iterator;

            iterator.setup(starting_address, definition, component_type);
            while (iterator.next())
            {
                c_channel_base * channel;
                if (iterator.get(&channel))
                {
                    switch (component_type)
                    {
                    case _mixing_board_auxilary_channel:
                        static_cast<c_auxilary_channel *>(channel)->initialize();
                        break;
                    case _mixing_board_animation_channel:
                        static_cast<c_animation_channel *>(channel)->initialize();
                        break;
                    case _mixing_board_aiming_channel:
                        static_cast<c_aiming_channel *>(channel)->initialize();
                        break;
                    case _mixing_board_facial_animation_channel:
                        static_cast<c_facial_animation_channel *>(channel)->initialize();
                        break;
                    case _mixing_board_pose_blend_channel:
                        static_cast<c_pose_blend_channel *>(channel)->initialize();
                        break;
                    default:
                        dassert_tag_debug_untracked_jul_11_2011(59, false, "unreachable");
                        break;
                    }
                }
                else
                {
                    break;
                }
            }
        }

        if (definition != NULL && definition->setup_function != NULL)
        {
            definition->setup_function(animation_manager);
        }
    }
};

long mixing_board_get_component(long starting_address, c_mixing_board_definition const * definition, long component_type, long component_index)
{
    mangled_ppc("?mixing_board_get_component@@YAJJPBVc_mixing_board_definition@@JJ@Z");

    assert_tag_debug_untracked_jul_11_2011(132, starting_address);
    assert_tag_debug_untracked_jul_11_2011(133, definition);
    assert_tag_debug_untracked_jul_11_2011(134, definition->validate_component_index(component_type, component_index));

    long offset = definition->get_component_offset(component_type, component_index);
    return starting_address + offset;
};

