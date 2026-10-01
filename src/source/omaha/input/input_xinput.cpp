#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\input\\input_xinput.cpp"
/* ---------- headers */

#include <xtl.h>

#include "omaha\input\input_xinput.h"
#include "omaha\input\input.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_macros.h"
#include "core\corelib\cseries\cseries_memory.h"

/* ---------- constants */

enum
{
    ANALOG_BUTTON_DOWN = 64,
    ANALOG_BUTTON_UP = 32,
};

/* ---------- definitions */

/* ---------- prototypes */

void update_button(unsigned char * frames, unsigned short * msec, bool down, long elapsed_msec);
void update_threshold(unsigned char * threshold, bool down, unsigned char current_value);

/* ---------- globals */

static long const k_xinput_binary_button_masks[NUMBER_OF_GAMEPAD_BINARY_BUTTONS] =
{
    XINPUT_GAMEPAD_DPAD_UP, // _gamepad_binary_button_dpad_up
    XINPUT_GAMEPAD_DPAD_DOWN, // _gamepad_binary_button_dpad_down
    XINPUT_GAMEPAD_DPAD_LEFT, // _gamepad_binary_button_dpad_left
    XINPUT_GAMEPAD_DPAD_RIGHT, // _gamepad_binary_button_dpad_right
    XINPUT_GAMEPAD_START, // _gamepad_binary_button_start
    XINPUT_GAMEPAD_BACK, // _gamepad_binary_button_back
    XINPUT_GAMEPAD_LEFT_THUMB, // _gamepad_binary_button_left_thumb
    XINPUT_GAMEPAD_RIGHT_THUMB, // _gamepad_binary_button_right_thumb
    XINPUT_GAMEPAD_A, // _gamepad_binary_button_a
    XINPUT_GAMEPAD_B, // _gamepad_binary_button_b
    XINPUT_GAMEPAD_X, // _gamepad_binary_button_x
    XINPUT_GAMEPAD_Y, // _gamepad_binary_button_y
    XINPUT_GAMEPAD_LEFT_SHOULDER, // _gamepad_binary_button_left_bumper
    XINPUT_GAMEPAD_RIGHT_SHOULDER, // _gamepad_binary_button_right_bumper
};

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// bool input_xinput_update_gamepad(unsigned long, unsigned long, struct gamepad_state *, struct debug_gamepad_data *);
// void update_button(unsigned char *, unsigned short *, bool, long);
// void update_threshold(unsigned char *, bool, unsigned char);
// void input_xinput_update_rumble_state(unsigned long, struct rumble_state const *, bool);
// bool input_xinput_available(void);
// unsigned long input_xinput_get_state(unsigned long, struct _XINPUT_STATE *);
// unsigned long input_xinput_set_state(unsigned long, struct _XINPUT_VIBRATION *);

bool input_xinput_update_gamepad(unsigned long user_index, unsigned long elapsed_msec, gamepad_state * in_out_gamepad_state, debug_gamepad_data * out_debug_gamepad_data)
{
    mangled_ppc("?input_xinput_update_gamepad@@YA_NKKPAUgamepad_state@@PAUdebug_gamepad_data@@@Z");

    bool result = false;

    if (input_xinput_available())
    {
        unsigned long error;
        XINPUT_STATE xinput_state;
        error = input_xinput_get_state(user_index, &xinput_state);
        if (error == ERROR_SUCCESS)
        {
            gamepad_state * gamepad = in_out_gamepad_state;

            for (short button_index = 0; button_index < NUMBER_OF_GAMEPAD_ANALOG_BUTTONS; button_index++)
            {
                gamepad->analog_buttons[button_index] = button_index ? xinput_state.Gamepad.bRightTrigger : xinput_state.Gamepad.bLeftTrigger;
                bool down = gamepad->analog_buttons[button_index] > gamepad->analog_button_thresholds[button_index];
                update_button(&gamepad->button_frames[button_index], &gamepad->button_msec[button_index], down, elapsed_msec);
                update_threshold(&gamepad->analog_button_thresholds[button_index], down, gamepad->analog_buttons[button_index]);
            }

            for (short button_index = 0; button_index < NUMBER_OF_GAMEPAD_BINARY_BUTTONS; button_index++)
            {
                update_button(&gamepad->button_frames[button_index + FIRST_GAMEPAD_BINARY_BUTTON], &gamepad->button_msec[button_index + FIRST_GAMEPAD_BINARY_BUTTON], (xinput_state.Gamepad.wButtons & k_xinput_binary_button_masks[button_index]) > 0 ? true : false, elapsed_msec);
            }

            gamepad->sticks[0].x = xinput_state.Gamepad.sThumbLX;
            gamepad->sticks[0].y = xinput_state.Gamepad.sThumbLY;
            gamepad->sticks[1].x = xinput_state.Gamepad.sThumbRX;
            gamepad->sticks[1].y = xinput_state.Gamepad.sThumbRY;

            assert_tag_debug_untracked_jul_11_2011(202, out_debug_gamepad_data);
            out_debug_gamepad_data->sticks[0] = gamepad->sticks[0];
            out_debug_gamepad_data->sticks[1] = gamepad->sticks[1];

            result = true;
        }
        else
        {
            memset(in_out_gamepad_state, 0, sizeof(gamepad_state));
        }
    }

    return result;
};

void update_button(unsigned char * frames, unsigned short * msec, bool down, long elapsed_msec)
{
    mangled_ppc("?update_button@@YAXPAEPAG_NJ@Z");

    *frames = static_cast<unsigned char>(down ? MIN(*frames + 1, UNSIGNED_CHAR_MAX) : 0);
    *msec = static_cast<unsigned short>(down ? MIN(*msec + elapsed_msec, UNSIGNED_SHORT_MAX) : 0);
};

void update_threshold(unsigned char * threshold, bool down, unsigned char current_value)
{
    mangled_ppc("?update_threshold@@YAXPAE_NE@Z");

    if (down)
    {
        unsigned char new_threshold = static_cast<unsigned char>(current_value < ANALOG_BUTTON_UP ? 0 : current_value - ANALOG_BUTTON_UP);
        if (new_threshold > *threshold)
        {
            *threshold = new_threshold;
        }
    }
    else
    {
        unsigned char new_threshold = static_cast<unsigned char>(current_value > UNSIGNED_CHAR_MAX - ANALOG_BUTTON_DOWN ? UNSIGNED_CHAR_MAX : current_value + ANALOG_BUTTON_DOWN);
        if (new_threshold < *threshold)
        {
            *threshold = new_threshold;
        }
    }
};

void input_xinput_update_rumble_state(unsigned long user_index, rumble_state const * rumble_state, bool suppress)
{
    mangled_ppc("?input_xinput_update_rumble_state@@YAXKPBUrumble_state@@_N@Z");

    assert_tag_debug_untracked_jul_11_2011(224, rumble_state);

    if (input_xinput_available())
    {
        XINPUT_VIBRATION vibration;
        vibration.wLeftMotorSpeed = static_cast<WORD>(suppress ? 0 : rumble_state->left_speed);
        vibration.wRightMotorSpeed = static_cast<WORD>(suppress ? 0 : rumble_state->right_speed);
        input_xinput_set_state(user_index, &vibration);
    }
};

bool input_xinput_available()
{
    mangled_ppc("?input_xinput_available@@YA_NXZ");

    return true;
};

unsigned long input_xinput_get_state(unsigned long user_index, _XINPUT_STATE * state)
{
    mangled_ppc("?input_xinput_get_state@@YAKKPAU_XINPUT_STATE@@@Z");

    return XCR::XcrGet()->InputGetState(user_index, state);
};

unsigned long input_xinput_set_state(unsigned long user_index, _XINPUT_VIBRATION * vibration)
{
    mangled_ppc("?input_xinput_set_state@@YAKKPAU_XINPUT_VIBRATION@@@Z");

    return XCR::XcrGet()->InputSetState(user_index, vibration);
};

