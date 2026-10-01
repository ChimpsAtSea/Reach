#ifndef __RASTERIZER_SHADERS_H__
#define __RASTERIZER_SHADERS_H__
#pragma once

/* ---------- headers */

#include "omaha\rasterizer\rasterizer_main.h"
#include "omaha\render_methods\render_method_submit.h"

#include <xtl.h>

/* ---------- constants */

/* ---------- definitions */

class c_rasterizer_vertex_buffer;
union vector4d;

class c_rasterizer_shaders
{
public:
    static bool set_vertex_stream(c_rasterizer_vertex_buffer const * vertex_buffer);
    static void set_vertex_shader_constant(long constant_index, long constant_count, vector4d const * constants);
    static bool set_explicit_shaders(long explicit_shader_index, e_vertex_type vertex_type, e_transfer_vector_vertex_types transfer_vertex_type, e_entry_point entry_point);

    // f i (instance owned by rasterizer_loading_screen.obj)
    static void set_pixel_shader_constant(long constant_index, long constant_count, vector4d const * constants)
    {
        mangled_ppc("?set_pixel_shader_constant@c_rasterizer_shaders@@SAXJJPBTvector4d@@@Z");

        c_rasterizer::get_device()->SetPixelShaderConstantF(constant_index, reinterpret_cast<float const *>(constants), constant_count);
    };
};

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __RASTERIZER_SHADERS_H__

