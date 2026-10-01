#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\visibility\\visibility_collection_render.cpp"
/* ---------- headers */

#include "omaha\visibility\visibility_collection_render.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_macros.h"
#include "omaha\cseries\cseries.h"
#include "omaha\game\game_globals.h"
#include "omaha\math\color_math.h"
#include "omaha\math\matrix_math.h"
#include "omaha\math\real_math.h"
#include "omaha\rasterizer\dx9\rasterizer_dx9_dynamic_geometry.h"
#include "omaha\rasterizer\rasterizer_global_definitions.h"
#include "omaha\rasterizer\rasterizer_samplers.h"
#include "omaha\rasterizer\rasterizer_shaders.h"
#include "omaha\rasterizer\rasterizer_states.h"
#include "omaha\rasterizer\rasterizer_surfaces.h"
#include "omaha\render\render_debug.h"
#include "omaha\render\render_debug_structure.h"
#include "omaha\scenario\scenario.h"
#include "omaha\scenario\scenario_definitions.h"
#include "omaha\structures\structure_bsp_definitions.h"
#include "omaha\tag_files\tag_groups.h"
#include "omaha\visibility\visibility.h"
#include "omaha\visibility\visibility_collection.h"
#include "omaha\visibility\visibility_portal_traversal.h"

/* ---------- constants */

long const k_portal_explicit_shader_index = 129; // $TODO: explicit shader name unknown

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// public: static void c_visibility_collection_render::render_structure_cluster_portal(struct structure_bsp const *, short, float);
// public: static void c_visibility_collection_render::render_region_cluster_portals(long, float, bool);
// public: static void c_visibility_collection_render::render_visible_portals(void);
// public: static void c_visibility_collection_render::render_debug_visibility_region(struct s_visibility_region const *);
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

void c_visibility_collection_render::render_structure_cluster_portal(structure_bsp const * bsp, short portal_index, float alpha)
{
    mangled_ppc("?render_structure_cluster_portal@c_visibility_collection_render@@SAXPBUstructure_bsp@@FM@Z");

    argb_color real_color = global_real_argb_color_table[portal_index % global_real_argb_color_table_size];
    real_color.alpha = alpha;
    cluster_portal const * portal = static_cast<cluster_portal const *>(tag_block_get_element_with_size(&bsp->cluster_portals, portal_index, sizeof(cluster_portal)));

    c_rasterizer_states::set_cull_mode(_cull_mode_off);
    c_rasterizer_states::set_scissor_rect(NULL);
    c_rasterizer_states::set_z_buffer_mode(_z_buffer_mode_read);
    c_rasterizer_states::set_alpha_blend_mode(_alpha_blend_alpha_blend);
    c_rasterizer_states::set_alpha_blend_mode(_alpha_blend_alpha_blend);
    c_rasterizer_states::set_color_write_enable(0, 7);

    if (c_rasterizer_shaders::set_explicit_shaders(k_portal_explicit_shader_index, _vertex_type_world, _transfer_vertex_none, _entry_point_default))
    {
        vector4d portal_color = { real_color.red, real_color.green, real_color.blue, 0.2f * c_surface::get_alpha_multiplier(0) };
        c_rasterizer_shaders::set_pixel_shader_constant(2, 1, &portal_color);
        c_rasterizer_dynamic_geometry::draw_worldspace_polygon(static_cast<real_point3d const *>(portal->vertices.address), portal->vertices.count);
    }
};

void c_visibility_collection_render::render_region_cluster_portals(long region_cluster_index, float alpha, bool only_visible_portals)
{
    mangled_ppc("?render_region_cluster_portals@c_visibility_collection_render@@SAXJM_N@Z");

    c_visibility_collection * camera_collection = get_global_camera_collection();
    s_visibility_region const * region = camera_collection->get_region();
    assert_tag_debug_untracked_jul_11_2011(79, region_cluster_index>=0 && region_cluster_index<region->cluster_count);

    visibility_cluster const * cluster = &region->clusters[region_cluster_index];
    structure_bsp const * bsp = global_structure_bsp_get(cluster->cluster_reference.bsp_index);
    structure_cluster const * structure_bsp_cluster = static_cast<structure_cluster const *>(tag_block_get_element_with_size(&bsp->clusters, cluster->cluster_reference.cluster_index, sizeof(structure_cluster)));

    c_rasterizer_globals const * rasterizer_globals = static_cast<c_rasterizer_globals const *>(scenario_get_game_globals()->rasterizer_globals_ref.index != NONE ? tag_get(RASTERIZER_GLOBALS_GROUP_TAG, scenario_get_game_globals()->rasterizer_globals_ref.index) : NULL);
    c_rasterizer_samplers::set_sampler_texture(0, rasterizer_globals->get_default_texture_rasterizer_texture_ref(0));
    c_rasterizer_states::set_z_buffer_mode(_z_buffer_mode_read);
    c_rasterizer_states::set_cull_mode(_cull_mode_off);

    for (long cluster_portal_index = 0; cluster_portal_index < structure_bsp_cluster->portals.count; cluster_portal_index++)
    {
        short portal_index = *static_cast<short const *>(tag_block_get_element_with_size(&structure_bsp_cluster->portals, cluster_portal_index, sizeof(short)));
        if (!only_visible_portals || camera_collection->get_bsp_portal_visible(cluster->cluster_reference.bsp_index, portal_index))
        {
            render_structure_cluster_portal(bsp, portal_index, alpha);
        }
    }

    c_rasterizer_states::set_z_buffer_mode(_z_buffer_mode_write);
    c_rasterizer_states::set_cull_mode(_cull_mode_ccw);
};

void c_visibility_collection_render::render_visible_portals()
{
    mangled_ppc("?render_visible_portals@c_visibility_collection_render@@SAXXZ");

    float alpha = 0.2f;

    if (visibility_debug_portals_3d || visibility_debug_visible_cluster_portals_3d)
    {
        c_visibility_collection * collection = get_global_camera_collection();
        s_visibility_region const * region = collection->get_region();
        for (long region_cluster_index = 0; region_cluster_index < region->cluster_count; region_cluster_index++)
        {
            render_region_cluster_portals(region_cluster_index, alpha, !visibility_debug_visible_cluster_portals_3d);
        }
    }

    if (visibility_debug_all_portals_3d)
    {
        scenario * global_scenario = global_scenario_get();
        short active_structure_bsp_mask = static_cast<short>(global_structure_bsp_active_mask_get());
        for (long structure_bsp_index = 0; structure_bsp_index < global_scenario->structure_bsps.count; structure_bsp_index++)
        {
            if (TEST_BIT(active_structure_bsp_mask, structure_bsp_index))
            {
                long structure_bsp_tag_index = global_structure_bsp_tag_index_get(global_scenario, structure_bsp_index);
                if (structure_bsp_tag_index != NONE)
                {
                    structure_bsp const * bsp = static_cast<structure_bsp const *>(tag_get(STRUCTURE_BSP_TAG, structure_bsp_tag_index));
                    for (long portal_index = 0; portal_index < bsp->cluster_portals.count; portal_index++)
                    {
                        render_structure_cluster_portal(bsp, static_cast<short>(portal_index), alpha);
                    }
                }
            }
        }
    }
};

void c_visibility_collection_render::render_debug_visibility_region(s_visibility_region const * region)
{
    mangled_ppc("?render_debug_visibility_region@c_visibility_collection_render@@SAXPBUs_visibility_region@@@Z");

    if (visibility_debug_region_projections)
    {
        assert_tag_debug_untracked_jul_11_2011(157, VALID_COUNT(region->projection_count, NUMBEROF(region->projections)));
        for (long projection_index = 0; projection_index < region->projection_count; projection_index++)
        {
            visibility_projection const * projection = &region->projections[projection_index];
            long const slice_count = 15;
            long slice_index;

            for (slice_index = 0; slice_index < slice_count; slice_index++)
            {
                float t = static_cast<float>(slice_index) / static_cast<float>(slice_count - 1);
                long point_index;
                real_point3d slice_points[NUMBEROF(projection->convex_hull_points)];
                float z_distance = t * (projection->far_distance - projection->near_distance) + projection->near_distance;

                for (point_index = 0; point_index < projection->convex_hull_point_count; point_index++)
                {
                    real_point3d basis_space_point;
                    basis_space_point.x = projection->convex_hull_points[point_index].x * z_distance;
                    basis_space_point.y = projection->convex_hull_points[point_index].y * z_distance;
                    basis_space_point.z = -z_distance;
                    matrix4x3_transform_point(&projection->basis_to_world, &basis_space_point, &slice_points[point_index]);
                }

                render_debug_polygon_edges(slice_points, static_cast<short>(projection->convex_hull_point_count), global_real_argb_cyan);
            }
        }
    }

    if (visibility_debug_region_volumes)
    {
        for (long volume_index = 0; volume_index < region->volume_count; volume_index++)
        {
            visibility_volume const * volume = &region->volumes[volume_index];
            bool draw_volume = true;
            if (draw_volume)
            {
                render_debug_line(true, &volume->world_vertices[0], &volume->world_vertices[1], global_real_argb_lightblue);
                render_debug_line(true, &volume->world_vertices[1], &volume->world_vertices[3], global_real_argb_lightblue);
                render_debug_line(true, &volume->world_vertices[3], &volume->world_vertices[2], global_real_argb_lightblue);
                render_debug_line(true, &volume->world_vertices[2], &volume->world_vertices[0], global_real_argb_lightblue);
                render_debug_line(true, &volume->world_vertices[0], &volume->world_vertices[4], global_real_argb_lightblue);
                render_debug_line(true, &volume->world_vertices[1], &volume->world_vertices[4], global_real_argb_lightblue);
                render_debug_line(true, &volume->world_vertices[2], &volume->world_vertices[4], global_real_argb_lightblue);
                render_debug_line(true, &volume->world_vertices[3], &volume->world_vertices[4], global_real_argb_lightblue);
            }
        }
    }
};

