#ifndef __CUI_SCREEN_MANAGER_H__
#define __CUI_SCREEN_MANAGER_H__
#pragma once

/* ---------- headers */

#include "omaha\memory\static_arrays.h"
#include "omaha\interface\user_interface.h"

/* ---------- constants */

// $TODO names unknown; count (18) from c_flags_no_init<e_cui_screen_category, unsigned long, 18>,
// values 0, 1 (scoreboard), 4, 5, 8 and 14 used by camera_input_inhibited
enum e_cui_screen_category
{
    _cui_screen_category0 = 0,
    _cui_screen_category1,
    _cui_screen_category2,
    _cui_screen_category3,
    _cui_screen_category4,
    _cui_screen_category5,
    _cui_screen_category6,
    _cui_screen_category7,
    _cui_screen_category8,
    _cui_screen_category9,
    _cui_screen_category10,
    _cui_screen_category11,
    _cui_screen_category12,
    _cui_screen_category13,
    _cui_screen_category14,
    _cui_screen_category15,
    _cui_screen_category16,
    _cui_screen_category17,

    k_cui_screen_category_count
};

/* ---------- definitions */

typedef c_flags_no_init<e_cui_screen_category, unsigned long, k_cui_screen_category_count> c_cui_screen_category_flags;

class c_cui_screen_manager
{
public:
    // stride 0x2EC verified in c_cui_screen_manager::get_window
    struct s_window
    {
        unsigned char unknown0[0x94]; // $TODO
        c_cui_screen_category_flags active_category_flags; // 0x94 (get_active_category_flags)
        c_cui_screen_category_flags closing_category_flags; // 0x98 (get_closing_category_flags)
        unsigned char unknown9C[0x2EC - 0x9C]; // $TODO
    };

    // verified f i in camera.obj
    c_cui_screen_category_flags get_active_category_flags(e_window_index window_index) const
    {
        s_window const * window = get_window(window_index);

        return window->active_category_flags;
    };

    // verified f i in camera.obj
    c_cui_screen_category_flags get_closing_category_flags(e_window_index window_index) const
    {
        s_window const * window = get_window(window_index);

        return window->closing_category_flags;
    };

private:
    s_window * get_window(long window_index);
    s_window const * get_window(long window_index) const;

    unsigned char unknown0[0x4]; // $TODO
    s_window m_windows[k_number_of_render_windows]; // 0x4 (get_window)
    // $TODO remaining members and total size unknown
};
static_assert(sizeof(c_cui_screen_manager::s_window) == 0x2EC, "c_cui_screen_manager::s_window");

/* ---------- prototypes */

c_cui_screen_manager * cui_screen_manager_get();

/* ---------- globals */

/* ---------- public code */

#endif // __CUI_SCREEN_MANAGER_H__

