#pragma once
#ifndef __RENDER_METHOD_SUBMIT_H__
#define __RENDER_METHOD_SUBMIT_H__

/* ---------- headers */

#include "omaha\cseries\location.h"

/* ---------- constants */

/* ---------- definitions */

// values from H3 rasterizer_resource_enums.h / rasterizer_constants.h (only verified entries listed)
enum e_vertex_type
{
    _vertex_type_world = 0,
    _vertex_type_screen = 7,
};

enum e_transfer_vector_vertex_types
{
    _transfer_vertex_none = 0,
};

enum e_entry_point
{
    _entry_point_default = 0,
    _entry_point_albedo,
};

class c_render_method;

typedef float (*shader_context_function)(long, long, long);

/* ---------- prototypes */

extern bool render_method_submit(long render_method_tag_index, c_render_method const * render_method, e_vertex_type vertex_type, e_transfer_vector_vertex_types prt_vertex_type, e_entry_point entry_point);
extern void render_method_submit_data(bool valid, long structure_bsp_index, s_cluster_reference lightmap_cluster_reference, long lightmap_instance_index, float cubemap_blend_factor, unsigned long const * change_colors, long context, shader_context_function context_interface);
extern void render_method_submit_valid(bool valid);

/* ---------- globals */

/* ---------- public code */

#endif // __RENDER_METHOD_SUBMIT_H__

