/* ---------- headers */

#include "omaha\scenario\wind.h"
#include "omaha\cseries\cseries.h"
#include "omaha\cseries\location.h"
#include "omaha\game\game_globals.h"
#include "omaha\scenario\scenario.h"
#include "omaha\scenario\scenario_definitions.h"
#include "omaha\scenario\wind_definitions.h"
#include "omaha\tag_files\tag_groups.h"
#include "omaha\bitmaps\bitmap_group.h"
#include "omaha\rasterizer\rasterizer_global_definitions.h"
#include "omaha\rasterizer\rasterizer_samplers.h"
#include "omaha\rasterizer\rasterizer_shaders.h"
#include "omaha\rasterizer\rasterizer_textures.h"

/* ---------- constants */

// names from H3 (Reach values from the target asm)
long const k_default_texture_smooth_noise_warp = 10;
long const k_wind_noise_sampler_index = 23; // vertex sampler 0
long const k_vs_wind_data = 246;
long const k_vs_wind_data2 = 247;

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// struct s_wind_definition const * get_wind_definition(union real_point3d const *);
// public: static struct s_wind_definition const * s_wind_definition::get(long);
// void setup_wind_constants(struct s_wind_definition const *, struct s_wind_values const *);

s_wind_definition const * get_wind_definition(real_point3d const * position)
{
    mangled_ppc("?get_wind_definition@@YAPBUs_wind_definition@@PBTreal_point3d@@@Z");

    s_wind_definition const * wind_definition = NULL;
    scenario const * scenario = global_scenario_get();
    long wind_tag_index = NONE;
    s_cluster_reference starting_cluster_reference = scenario_cluster_reference_from_point(position);
    if (starting_cluster_reference.bsp_index != NONE)
    {
        scenario_structure_bsp_reference const * structure_ref = static_cast<scenario_structure_bsp_reference const *>(tag_block_get_element_with_size(&scenario->structure_bsps, starting_cluster_reference.bsp_index, sizeof(scenario_structure_bsp_reference)));
        wind_tag_index = structure_ref->wind_reference.index;
    }
    else
    {
        s_game_globals const * game_globals = scenario_get_game_globals();
        wind_tag_index = game_globals->default_wind_settings.index;
    }

    if (wind_tag_index != NONE)
    {
        wind_definition = s_wind_definition::get(wind_tag_index);
    }

    return wind_definition;
};

void setup_wind_constants(s_wind_definition const * wind_definition, s_wind_values const * wind_values)
{
    mangled_ppc("?setup_wind_constants@@YAXPBUs_wind_definition@@PBUs_wind_values@@@Z");

    c_rasterizer_texture_ref noise_texture_ref;
    if (wind_definition != NULL && wind_definition->m_decorator_gust_bitmap.index != NONE)
    {
        bitmap_group_get_bitmap_hardware_format(wind_definition->m_decorator_gust_bitmap.index, 0, &noise_texture_ref);
    }
    else
    {
        c_rasterizer_globals const * rasterizer_globals = static_cast<c_rasterizer_globals const *>(scenario_get_game_globals()->rasterizer_globals_ref.index != NONE ? tag_get(RASTERIZER_GLOBALS_GROUP_TAG, scenario_get_game_globals()->rasterizer_globals_ref.index) : NULL);
        noise_texture_ref = rasterizer_globals->get_default_texture_rasterizer_texture_ref(k_default_texture_smooth_noise_warp);
    }

    c_rasterizer_samplers::set_sampler_texture(k_wind_noise_sampler_index, noise_texture_ref);
    c_rasterizer_samplers::set_sampler_address_mode(k_wind_noise_sampler_index, _sampler_address_wrap);
    c_rasterizer_samplers::set_sampler_filter_mode(k_wind_noise_sampler_index, _sampler_filter_bilinear);
    c_rasterizer_shaders::set_vertex_shader_constant(k_vs_wind_data, 1, &wind_values->wind_data);
    c_rasterizer_shaders::set_vertex_shader_constant(k_vs_wind_data2, 1, &wind_values->wind_data2);
};

