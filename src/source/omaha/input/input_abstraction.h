#ifndef __INPUT_ABSTRACTION_H__
#define __INPUT_ABSTRACTION_H__
#pragma once

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"
#include "omaha\input\controllers.h"

/* ---------- constants */

/* ---------- definitions */

class c_abstract_button
{
public:
    void latch();
    unsigned char down_frames() const;
    bool latched() const;
    bool access_valid() const;

private:
    unsigned short m_down_msec; // 0x0
    unsigned char m_down_frames; // 0x2
    unsigned char m_flags; // 0x3
    float m_down_amount; // 0x4 $unsure
    long m_button_accessor_index; // 0x8
    long m_button_locked_index; // 0xC
};
static_assert(sizeof(c_abstract_button) == 0x10, "c_abstract_button");

// $TODO: only abstract_gamepad_buttons is known; the rest of the layout is not yet reversed
struct s_game_input_state
{
    c_abstract_button abstract_gamepad_buttons[16]; // 0x0 $unsure count
    unsigned char unknown100[0xD8]; // 0x100 $TODO
};
static_assert(sizeof(s_game_input_state) == 0x1D8, "s_game_input_state");

/* ---------- prototypes */

void input_abstraction_get_input_state(e_controller_index controller_index, s_game_input_state ** input_state);

/* ---------- globals */

/* ---------- public code */

#endif // __INPUT_ABSTRACTION_H__

