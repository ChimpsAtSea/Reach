#pragma once
#ifndef __INPUT_XINPUT_H__
#define __INPUT_XINPUT_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"
#include "omaha\math\integer_math.h"

/* ---------- constants */

/* ---------- definitions */

struct gamepad_state;
struct _XINPUT_STATE;
struct _XINPUT_VIBRATION;

struct rumble_state
{
    unsigned short left_speed; // 0x0
    unsigned short right_speed; // 0x2
    unsigned short left_trigger_speed; // 0x4
    unsigned short right_trigger_speed; // 0x6
};
static_assert(sizeof(rumble_state) == 0x8, "rumble_state");

struct debug_gamepad_data
{
    point2d sticks[2]; // 0x0
};
static_assert(sizeof(debug_gamepad_data) == 0x8, "debug_gamepad_data");

// XDK xecr (XCR) control unit, used by the XInput wrappers
namespace XCR
{
    namespace ControlUnit
    {
        class Core
        {
        public:
            unsigned long InputGetState(unsigned long user_index, _XINPUT_STATE * state);
            unsigned long InputSetState(unsigned long user_index, _XINPUT_VIBRATION * vibration);
        };
    }

    ControlUnit::Core * XcrGet();
}

/* ---------- prototypes */

bool input_xinput_update_gamepad(unsigned long user_index, unsigned long elapsed_msec, gamepad_state * in_out_gamepad_state, debug_gamepad_data * out_debug_gamepad_data);
void input_xinput_update_rumble_state(unsigned long user_index, rumble_state const * rumble_state, bool suppress);
bool input_xinput_available();
unsigned long input_xinput_get_state(unsigned long user_index, _XINPUT_STATE * state);
unsigned long input_xinput_set_state(unsigned long user_index, _XINPUT_VIBRATION * vibration);

/* ---------- globals */

/* ---------- public code */

#endif // __INPUT_XINPUT_H__

