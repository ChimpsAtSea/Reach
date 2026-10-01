#pragma once
#ifndef __INPUT_H__
#define __INPUT_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"
#include "omaha\math\integer_math.h"
#include "omaha\input\controllers.h"

/* ---------- constants */

enum e_memory_unit
{
    _memory_unit_hard_drive = 0,
    k_number_of_default_memory_units,
    _memory_unit_controller0_top = k_number_of_default_memory_units,
    _memory_unit_controller0_bottom,
    _memory_unit_controller1_top,
    _memory_unit_controller1_bottom,
    _memory_unit_controller2_top,
    _memory_unit_controller2_bottom,
    _memory_unit_controller3_top,
    _memory_unit_controller3_bottom,
    k_number_of_memory_units,
};

enum
{
    k_number_of_controller_memory_units = 8,
    k_memory_unit_slots_per_gamepad = 2,
};

enum e_gamepad_button
{
    FIRST_GAMEPAD_ANALOG_BUTTON = 0,
    _gamepad_analog_button_left_trigger = FIRST_GAMEPAD_ANALOG_BUTTON,
    _gamepad_analog_button_right_trigger,
    NUMBER_OF_GAMEPAD_ANALOG_BUTTONS,
    FIRST_GAMEPAD_BINARY_BUTTON = NUMBER_OF_GAMEPAD_ANALOG_BUTTONS,
    _gamepad_binary_button_dpad_up = FIRST_GAMEPAD_BINARY_BUTTON,
    _gamepad_binary_button_dpad_down,
    _gamepad_binary_button_dpad_left,
    _gamepad_binary_button_dpad_right,
    _gamepad_binary_button_start,
    _gamepad_binary_button_back,
    _gamepad_binary_button_left_thumb,
    _gamepad_binary_button_right_thumb,
    _gamepad_binary_button_a,
    _gamepad_binary_button_b,
    _gamepad_binary_button_x,
    _gamepad_binary_button_y,
    _gamepad_binary_button_left_bumper,
    _gamepad_binary_button_right_bumper,
    NUMBER_OF_GAMEPAD_BUTTONS,
    NUMBER_OF_GAMEPAD_BINARY_BUTTONS = NUMBER_OF_GAMEPAD_BUTTONS - FIRST_GAMEPAD_BINARY_BUTTON,
};

enum e_input_key_code
{
    _key_escape,
    _key_f1,
    _key_f2,
    _key_f3,
    _key_f4,
    _key_f5,
    _key_f6,
    _key_f7,
    _key_f8,
    _key_f9,
    _key_f10,
    _key_f11,
    _key_f12,
    _key_print_screen,
    _key_scroll_lock,
    _key_pause,
    _key_backquote,
    _key_1,
    _key_2,
    _key_3,
    _key_4,
    _key_5,
    _key_6,
    _key_7,
    _key_8,
    _key_9,
    _key_0,
    _key_dash,
    _key_equal,
    _key_backspace,
    _key_tab,
    _key_q,
    _key_w,
    _key_e,
    _key_r,
    _key_t,
    _key_y,
    _key_u,
    _key_i,
    _key_o,
    _key_p,
    _key_left_bracket,
    _key_right_bracket,
    _key_backslash,
    _key_caps_lock,
    _key_a,
    _key_s,
    _key_d,
    _key_f,
    _key_g,
    _key_h,
    _key_j,
    _key_k,
    _key_l,
    _key_semicolon,
    _key_apostrophe,
    _key_return,
    _key_left_shift,
    _key_z,
    _key_x,
    _key_c,
    _key_v,
    _key_b,
    _key_n,
    _key_m,
    _key_comma,
    _key_period,
    _key_forwardslash,
    _key_right_shift,
    _key_left_control,
    _key_left_windows,
    _key_left_alt,
    _key_space,
    _key_right_alt,
    _key_right_windows,
    _key_menu,
    _key_right_control,
    _key_up_arrow,
    _key_down_arrow,
    _key_left_arrow,
    _key_right_arrow,
    _key_insert,
    _key_home,
    _key_page_up,
    _key_delete,
    _key_end,
    _key_page_down,
    _keypad_num_lock,
    _keypad_divide,
    _keypad_multiply,
    _keypad_0,
    _keypad_1,
    _keypad_2,
    _keypad_3,
    _keypad_4,
    _keypad_5,
    _keypad_6,
    _keypad_7,
    _keypad_8,
    _keypad_9,
    _keypad_subtract,
    _keypad_add,
    _keypad_enter,
    _keypad_decimal,
    _key_shift,
    _key_control,
    _key_windows,
    _key_alt,
    NUMBER_OF_KEYS,
    _key_question_mark = _key_forwardslash,
    _key_tilde = _key_backquote,
    _key_not_a_key = 255,
};

enum
{
    _key_modifier_shift_bit = 0,
    _key_modifier_control_bit,
    _key_modifier_alt_bit,
    NUMBER_OF_KEY_MODIFIER_FLAGS,
};

/* ---------- definitions */

struct key_stroke
{
    unsigned char modifier_flags; // 0x0
    char ascii_code; // 0x1
    short key_code; // 0x2
    bool repeating; // 0x4
};
static_assert(sizeof(key_stroke) == 0x6, "key_stroke");

struct gamepad_state
{
    unsigned char analog_buttons[2]; // 0x0
    unsigned char analog_button_thresholds[2]; // 0x2
    unsigned char button_frames[16]; // 0x4
    unsigned short button_msec[16]; // 0x14
    point2d sticks[2]; // 0x34
};
static_assert(sizeof(gamepad_state) == 0x3C, "gamepad_state");

struct mouse_state;

/* ---------- prototypes */

gamepad_state const * input_get_gamepad_state(short gamepad_index);
mouse_state const * input_get_mouse_state();
bool input_any_controller_button_down(e_gamepad_button button);
bool input_any_controller_button_down_this_frame(e_gamepad_button button);
e_controller_index gamepad_from_memory_unit(e_memory_unit mu);

/* ---------- globals */

/* ---------- public code */

#endif // __INPUT_H__

