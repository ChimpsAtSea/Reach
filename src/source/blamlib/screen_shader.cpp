/* ---------- headers */

#include "blamlib\screen_shader.h"
#include "core\corelib\cseries\cseries_string.h"
#include "graphicslib\render_time.h"
#include "omaha\cseries\cseries.h"
#include "omaha\effects\screen_effect.h"
#include "omaha\objects\objects.h"
#include "omaha\main\main_screenshot.h"
#include "omaha\rasterizer\dx9\rasterizer_dx9_dynamic_geometry.h"
#include "omaha\rasterizer\rasterizer_profile.h"
#include "omaha\rasterizer\rasterizer_shaders.h"
#include "omaha\rasterizer\rasterizer_states.h"
#include "omaha\rasterizer\rasterizer_surfaces.h"
#include "omaha\render\render_cameras.h"
#include "omaha\render\render_debug.h"
#include "omaha\render\views\render_player_view.h"
#include "omaha\render\views\render_view.h"
#include "omaha\render\views\render_view_stack.h"
#include "omaha\render_methods\render_method_definitions.h"
#include "omaha\render_methods\render_method_submit.h"
#include "omaha\tag_files\tag_groups.h"

/* ---------- constants */

/* ---------- definitions */

struct s_screen_shader_context
{
    s_screen_effect_shader_sample const * sample;
};

/* ---------- prototypes */

float screen_shader_context_function_callback(long user_data, long function, long function_owner_tag_index);

/* ---------- globals */

bool g_render_debug_screen_shaders;

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// bool g_render_debug_screen_shaders; // "?g_render_debug_screen_shaders@@3_NA"

// void debug_screen_shaders(struct s_screen_effect_shader_sample_result *);
// public: static class c_render_method_shader_screen const * c_render_method_shader_screen::get(long);
// void render_screen_shaders(struct s_screen_effect_shader_sample_result *, long, enum e_surface, enum e_surface, union real_rectangle2d const *);
// float screen_shader_context_function_callback(long, long, long);
// D3DDevice_SetPixelShaderConstantF;
// D3DTag_ShaderConstantMask;
// D3DTag_SubsetMask;
// D3DDevice_SetPixelShaderConstantF1;
// D3DVECTOR4_SetX;
// D3DVECTOR4_SetY;
// D3DVECTOR4_SetZ;
// D3DVECTOR4_SetW;
// D3DTag_Index;
// D3DTagCollection_Set;

void debug_screen_shaders(s_screen_effect_shader_sample_result * result)
{
    mangled_ppc("?debug_screen_shaders@@YAXPAUs_screen_effect_shader_sample_result@@@Z");

    char debug_string[2048];
    char layer_string[256];
    char const * layer_names[3] = { "pre-UI ", "post-UI", "pre-transparents" };

    csnzprintf(debug_string, sizeof(debug_string), "|n|n|n|n|nlayer  index sort  alpha  name|n");
    for (long layer = 0; layer < 3; layer++)
    {
        for (long index = 0; index < result->shader_count; index++)
        {
            c_render_method_shader_screen const * shader = c_render_method_shader_screen::get(result->shaders[index].shader_index);
            if (shader->m_render_layer == layer)
            {
                csnzprintf(layer_string, sizeof(layer_string), "%s %-4d %-5d %1.4f %s|n", layer_names[layer], index, result->shaders[index].sort_order, result->shaders[index].alpha, tag_get_name(result->shaders[index].shader_index));
                csnzappendf(debug_string, sizeof(debug_string), layer_string);
            }
        }
    }
    render_debug_string(debug_string);
};

void render_screen_shaders(s_screen_effect_shader_sample_result * result, long render_layer, e_surface target_surface, e_surface source_surface, real_rectangle2d const * texture_bounds)
{
    mangled_ppc("?render_screen_shaders@@YAXPAUs_screen_effect_shader_sample_result@@JW4e_surface@@1PBTreal_rectangle2d@@@Z");

    if (render_debug_pix_events)
    {
        PIXBeginNamedEvent(g_rasterizer_profile_pix_colors[0], "screen_shaders");
    }
    for (long shader_index = 0; shader_index < result->shader_count; shader_index++)
    {
        c_render_method_shader_screen const * shader = c_render_method_shader_screen::get(result->shaders[shader_index].shader_index);
        if (render_layer == shader->m_render_layer)
        {
            s_screen_shader_context context;
            context.sample = &result->shaders[shader_index];
            if (render_debug_pix_events)
            {
                char const * name = tag_name_strip_path(tag_get_name(result->shaders[shader_index].shader_index));
                if (render_debug_pix_events)
                {
                    PIXBeginNamedEvent(g_rasterizer_profile_pix_colors[0], name);
                }
            }
            if (shader->m_render_flags & 1)
            {
                c_surface::resolve(source_surface, 0);
            }
            if (c_render_method::get_is_transparent(result->shaders[shader_index].shader_index))
            {
                c_rasterizer_states::begin_high_quality_blend();
            }
            else
            {
                c_rasterizer_states::end_high_quality_blend();
            }
            if (render_layer != 2)
            {
                c_surface::set(0, target_surface);
            }
            c_rasterizer_states::set_color_write_enable(0, 7);
            render_method_submit_data(true, NONE, invalid_cluster_reference_get(), NONE, 0.0f, NULL, reinterpret_cast<long>(&context), screen_shader_context_function_callback);

            vector4d resolution;
            resolution.i = static_cast<real>(c_surface::get_surface_width(static_cast<e_surface>(34)));
            resolution.j = static_cast<real>(c_surface::get_surface_height(static_cast<e_surface>(34)));
            resolution.k = -0.4999f;
            resolution.l = -0.4999f;
            c_rasterizer_shaders::set_vertex_shader_constant(250, 1, &resolution);
            c_rasterizer_shaders::set_pixel_shader_constant(202, 1, &resolution);

            vector4d texture_transform;
            texture_transform.i = 1.0f;
            texture_transform.j = 1.0f;
            texture_transform.k = 0.0f;
            texture_transform.l = 0.0f;
            if (texture_bounds != NULL)
            {
                texture_transform.i = 1.0f / (texture_bounds->x1 - texture_bounds->x0);
                texture_transform.j = 1.0f / (texture_bounds->y1 - texture_bounds->y0);
                texture_transform.k = -texture_bounds->x0 * texture_transform.i;
                texture_transform.l = -texture_bounds->y0 * texture_transform.j;
            }
            c_rasterizer_shaders::set_vertex_shader_constant(251, 1, &texture_transform);
            c_rasterizer_shaders::set_pixel_shader_constant(200, 1, &texture_transform);

            vector4d inverse_texture_transform;
            inverse_texture_transform.i = 1.0f / texture_transform.i;
            inverse_texture_transform.j = 1.0f / texture_transform.j;
            inverse_texture_transform.k = -texture_transform.k * inverse_texture_transform.i;
            inverse_texture_transform.l = -texture_transform.l * inverse_texture_transform.j;
            c_rasterizer_shaders::set_pixel_shader_constant(201, 1, &inverse_texture_transform);

            c_player_view * player = c_player_view::get_current();
            XMMATRIX pixel_to_world_constants = player->m_rasterizer_projection.get_pixel_to_world_relative_to(&c_view_stack::top()->get_rasterizer_camera()->position);
            c_rasterizer_shaders::set_pixel_shader_constant(204, 4, reinterpret_cast<vector4d const *>(&pixel_to_world_constants));

            e_entry_point entry_point = static_cast<e_entry_point>(screenshot_in_progress() != false);
            if (render_method_submit(result->shaders[shader_index].shader_index, shader, _vertex_type_screen, _transfer_vertex_none, entry_point))
            {
                c_rasterizer_dynamic_geometry::draw_fullscreen_quad(c_surface::get_surface_width(target_surface), c_surface::get_surface_height(target_surface));
            }
            if (render_debug_pix_events)
            {
                PIXEndNamedEvent();
            }
        }
    }
    if (g_render_debug_screen_shaders && render_layer == 1)
    {
        debug_screen_shaders(result);
    }
    if (render_debug_pix_events)
    {
        PIXEndNamedEvent();
    }
    render_method_submit_valid(false);
};

float screen_shader_context_function_callback(long user_data, long function, long function_owner_tag_index)
{
    mangled_ppc("?screen_shader_context_function_callback@@YAMJJJ@Z");

    s_screen_shader_context * context = reinterpret_cast<s_screen_shader_context *>(user_data);
    float value = context->sample->value;
    switch (function)
    {
    case 437:
        value = g_render_time.wrapped_periods[2];
        break;
    case 440:
        value = context->sample->alpha;
        break;
    case 438:
        value = g_render_time.frame_seconds;
        break;
    case 439:
        break;
    default:
        if (context->sample->object_index != NONE)
        {
            object_get_function_value(context->sample->object_index, function, function_owner_tag_index, &value);
        }
        break;
    }
    return value;
};

// D3DDevice_SetPixelShaderConstantF and the other D3D* functions above are XDK d3d9.h static inlines,
// emitted via c_rasterizer_shaders::set_pixel_shader_constant -> D3DDevice::SetPixelShaderConstantF

