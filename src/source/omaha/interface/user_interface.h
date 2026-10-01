#pragma once
#ifndef __USER_INTERFACE_H__
#define __USER_INTERFACE_H__

/* ---------- headers */

/* ---------- constants */

// names from H3; _console_window (4) verified in camera_input_inhibited,
// k_number_of_render_windows (6, one more than H3) verified in c_cui_screen_manager::get_window
enum e_window_index
{
    k_no_window = -1,

    _player_window_first = 0,
    _window0 = _player_window_first,
    _window1,
    _window2,
    _window3,

    k_number_of_player_windows,
    _console_window = k_number_of_player_windows,
    _window5, // $TODO Reach-only window, name unknown

    k_number_of_render_windows,
    k_any_window = 255,
};

/* ---------- definitions */

/* ---------- prototypes */

void user_interface_main_menu_music_initialize_for_saved_game(long game_state_proc_flags);

/* ---------- globals */

/* ---------- public code */

#endif // __USER_INTERFACE_H__

