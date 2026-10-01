#ifndef __RENDER_PLAYER_VIEW_H__
#define __RENDER_PLAYER_VIEW_H__
#pragma once

/* ---------- headers */

#include "omaha\rasterizer\rasterizer_projection.h"

/* ---------- constants */

/* ---------- definitions */

// $TODO: layout mostly unrecovered; only verified members are placed
class c_player_view
{
public:
    static c_player_view * get_current(void);

    unsigned char unknown0[0x480]; // 0x0
    s_rasterizer_projection m_rasterizer_projection; // 0x480
};

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __RENDER_PLAYER_VIEW_H__

