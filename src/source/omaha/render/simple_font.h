#pragma once
#ifndef __SIMPLE_FONT_H__
#define __SIMPLE_FONT_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"

/* ---------- constants */

/* ---------- definitions */

class c_simple_font_screen_display
{
public:
    c_simple_font_screen_display(void); // $TODO inline in the target (render_debug_auto_graph.obj)
    ~c_simple_font_screen_display(void); // $TODO inline in the target (render_debug_auto_graph.obj)
    bool open_session(float scale);
    void close_session(void);
    long get_max_column(void) const; // $TODO inline in the target
    long get_max_row(void) const; // $TODO inline in the target

protected:
    // $TODO layout
    bool m_session_open; // 0x0
    unsigned char unknown_1[0x1B];
    long m_max_column; // 0x1C
    unsigned char unknown_20[0x408];
};
static_assert(sizeof(c_simple_font_screen_display) == 0x428, "c_simple_font_screen_display");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __SIMPLE_FONT_H__

