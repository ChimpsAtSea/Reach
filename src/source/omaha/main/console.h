#pragma once
#ifndef __CONSOLE_H__
#define __CONSOLE_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"
#include "foundation\baselib\datatypes\static_string.h"
#include "omaha\math\color_math.h"
#include "omaha\memory\static_arrays.h"

/* ---------- constants */

enum e_status_line_flags
{
    _status_line_blink_bit = 0,
    _status_line_inhibit_drawing_bit,
    _status_line_left_justify_bit,
    _status_line_draw_once_bit,

    k_status_line_flags_count
};

/* ---------- definitions */

// 0x124 bytes in Reach: g_overlapped_memory_status_line @ 0x860D4258, next static @ 0x860D437C
// ctor is inline in the target (f i, owned by shell_xenon.obj): c_static_string<256> ctor then c_flags ctor at 0x110; body not added yet
struct c_status_line
{
    c_status_line(void);

    c_static_string<256> text; // 0x0
    real_rgb_color color; // 0x100
    real alpha; // 0x10C
    c_flags<e_status_line_flags, unsigned long, k_status_line_flags_count> flags; // 0x110
    bool * in_use; // 0x114
    char const * identifier; // 0x118
    c_status_line * previous; // 0x11C
    c_status_line * next; // 0x120
};
static_assert(sizeof(c_status_line) == 0x124, "c_status_line");

/* ---------- prototypes */

void status_lines_initialize(c_status_line * status_line, bool * in_use, long count);
char const * status_line_printf(c_status_line * status_line, char const * format, ...);
bool console_get_command_slow(char const * command, c_static_string<256> * buffer);

/* ---------- globals */

/* ---------- public code */

#endif // __CONSOLE_H__

