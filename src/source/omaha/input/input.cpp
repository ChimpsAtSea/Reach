#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\input\\input.cpp"
/* ---------- headers */

#include "omaha\input\input.h"
#include "omaha\input\controllers.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_macros.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// bool input_any_controller_button_down(enum e_gamepad_button);
// bool input_any_controller_button_down_this_frame(enum e_gamepad_button);
// enum e_controller_index gamepad_from_memory_unit(enum e_memory_unit);

bool input_any_controller_button_down(e_gamepad_button button)
{
    mangled_ppc("?input_any_controller_button_down@@YA_NW4e_gamepad_button@@@Z");

    bool button_down = false;

    assert_tag_debug_untracked_jul_11_2011(16, (button >= 0) && (button < NUMBER_OF_GAMEPAD_BUTTONS));

    for (e_controller_index controller_index = first_controller(); controller_index != k_no_controller; controller_index = next_controller(controller_index))
    {
        gamepad_state const * gamepad = input_get_gamepad_state(static_cast<short>(controller_index));
        if (gamepad != NULL && gamepad->button_frames[button] != 0)
        {
            button_down = true;
        }
    }

    return button_down;
};

bool input_any_controller_button_down_this_frame(e_gamepad_button button)
{
    mangled_ppc("?input_any_controller_button_down_this_frame@@YA_NW4e_gamepad_button@@@Z");

    bool button_down = false;

    assert_tag_debug_untracked_jul_11_2011(39, (button >= 0) && (button < NUMBER_OF_GAMEPAD_BUTTONS));

    for (e_controller_index controller_index = first_controller(); controller_index != k_no_controller; controller_index = next_controller(controller_index))
    {
        gamepad_state const * gamepad = input_get_gamepad_state(static_cast<short>(controller_index));
        if (gamepad != NULL && gamepad->button_frames[button] == 1)
        {
            button_down = true;
        }
    }

    return button_down;
};

e_controller_index gamepad_from_memory_unit(e_memory_unit mu)
{
    mangled_ppc("?gamepad_from_memory_unit@@YA?AW4e_controller_index@@W4e_memory_unit@@@Z");

    assert_tag_debug_untracked_jul_11_2011(61, mu!=_memory_unit_hard_drive);

    e_controller_index controller_index = static_cast<e_controller_index>((mu - k_number_of_default_memory_units) * k_memory_unit_slots_per_gamepad / k_number_of_controllers);

    assert_tag_debug_untracked_jul_11_2011(63, 0<=controller_index && controller_index<k_number_of_controllers);

    return controller_index;
};

