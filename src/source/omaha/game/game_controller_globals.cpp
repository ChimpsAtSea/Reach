/* ---------- headers */

#include "omaha\game\game_controller_globals.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// struct s_tag_struct_definition gamepad_stick_info_block_struct_definition; // "?gamepad_stick_info_block_struct_definition@@3Us_tag_struct_definition@@A"
// struct s_tag_block_definition gamepad_stick_info_block; // "?gamepad_stick_info_block@@3Us_tag_block_definition@@A"
// struct s_tag_block_definition controller_input_block; // "?controller_input_block@@3Us_tag_block_definition@@A"
// struct s_tag_struct_definition controller_input_block_struct_definition; // "?controller_input_block_struct_definition@@3Us_tag_struct_definition@@A"
// struct s_tag_block_definition player_control_block; // "?player_control_block@@3Us_tag_block_definition@@A"
// struct s_tag_struct_definition player_control_block_struct_definition; // "?player_control_block_struct_definition@@3Us_tag_struct_definition@@A"

// bool postprocess_gamepad_stick_info_block(long, void *, bool);
// bool postprocess_player_control_block(long, void *, bool);

bool postprocess_gamepad_stick_info_block(long element_index, void * element, bool for_editor)
{
    mangled_ppc("?postprocess_gamepad_stick_info_block@@YA_NJPAX_N@Z");

    if (!for_editor)
    {
        real default_peg_max_angular_velocity = k_2pi;
        s_gamepad_stick_settings * stick_info = static_cast<s_gamepad_stick_settings *>(element);
        if (stick_info->peg_max_angular_velocity < k_real_epsilon)
        {
            stick_info->peg_max_angular_velocity = default_peg_max_angular_velocity;
        }
    }

    return true;
};

bool postprocess_player_control_block(long element_index, void * element, bool for_editor)
{
    mangled_ppc("?postprocess_player_control_block@@YA_NJPAX_N@Z");

    if (!for_editor)
    {
        s_game_globals_player_control * player_control = static_cast<s_game_globals_player_control *>(element);
        if (player_control->minimum_action_hold_time <= 0.0f)
        {
            player_control->minimum_action_hold_time = 0.2333f;
        }
        if (player_control->auto_unzoom_ticks <= 0)
        {
            player_control->auto_unzoom_ticks = 15;
        }
    }

    return true;
};

