#pragma once
#ifndef __RENDER_VIEW_STACK_H__
#define __RENDER_VIEW_STACK_H__

/* ---------- headers */

/* ---------- constants */

/* ---------- definitions */

struct render_camera;

class c_view_stack
{
public:
    static c_view_stack * top(void);
    render_camera const * get_rasterizer_camera(void) const;
};

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __RENDER_VIEW_STACK_H__

