#pragma once
#ifndef __NEW_CINEMATIC_SH_LIGHTING_H__
#define __NEW_CINEMATIC_SH_LIGHTING_H__

/* ---------- headers */

/* ---------- constants */

/* ---------- definitions */

struct render_lighting;

struct s_cinematic_sh_lighting_interface
{
    static void apply_cinematic_lighting(long object_index, render_lighting * lighting);
    static bool get_final_render_lighting(render_lighting const * const original_cached_lighting, render_lighting const ** final_lighting);
};

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __NEW_CINEMATIC_SH_LIGHTING_H__

