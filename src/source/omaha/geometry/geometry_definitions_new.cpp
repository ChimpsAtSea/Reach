#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\geometry\\geometry_definitions_new.cpp"
/* ---------- headers */

#include "omaha\geometry\geometry_definitions_new.h"
#include "omaha\geometry\geometry_definitions.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "omaha\scenario\scenario_definitions.h"
#include "omaha\cseries\cseries.h"
#include "core\corelib\cseries\cseries_events.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// struct s_tag_block_definition global_geometry_material_block; // "?global_geometry_material_block@@3Us_tag_block_definition@@A"
// struct s_tag_struct_definition global_geometry_material_block_struct_definition; // "?global_geometry_material_block_struct_definition@@3Us_tag_struct_definition@@A"

// bool mesh_precompress_raw_vertices(struct s_render_geometry *, long, long);
// float geometry_material_get_lightmap_resolution_scale(struct geometry_material const *, struct scenario_lightmap_setting const *);
// unsigned long geometry_material_get_lightmap_translucency_tint_color(struct geometry_material const *);
// unsigned long geometry_material_get_lightmap_additive_transparency(struct geometry_material const *);
// float geometry_material_get_lightmap_analytical_bounce_modifier(struct geometry_material const *);
// float geometry_material_get_lightmap_normal_bounce_modifier(struct geometry_material const *);
// bool geometry_material_get_lightmap_transparency_override(struct geometry_material const *);
// bool geometry_material_get_lightmap_lighting_from_both_sides(struct geometry_material const *);
// bool geometry_material_get_lightmap_ignore_default_resolution_scale(struct geometry_material const *);
// public: void geometry_material::clear_non_render_information(void);
// public: static bool geometry_material::postprocess(long, void *, bool);

// $TODO nonmatching (stack slot order of success/per_mesh_raw_data/compression_info)
bool mesh_precompress_raw_vertices(s_render_geometry * geometry, long mesh_index, long compression_info_index)
{
    mangled_ppc("?mesh_precompress_raw_vertices@@YA_NPAUs_render_geometry@@JJ@Z");

    bool success = true;

    assert_tag_debug_untracked_jul_11_2011(92, geometry);
    assert_tag_debug_untracked_jul_11_2011(93, (mesh_index >= 0) && (mesh_index < geometry->meshes.count));
    assert_tag_debug_untracked_jul_11_2011(94, (compression_info_index >= 0) && (compression_info_index < geometry->compression_infos.count));

    s_per_mesh_raw_data * per_mesh_raw_data = static_cast<s_per_mesh_raw_data *>(tag_block_get_element_with_size(&geometry->per_mesh_temporary, mesh_index, sizeof(s_per_mesh_raw_data)));
    s_compression_info * compression_info = static_cast<s_compression_info *>(tag_block_get_element_with_size(&geometry->compression_infos, compression_info_index, sizeof(s_compression_info)));

    for (long vertex_index = 0; vertex_index < per_mesh_raw_data->raw_vertices.count; vertex_index++)
    {
        s_raw_vertex * vertex = static_cast<s_raw_vertex *>(tag_block_get_element_with_size(&per_mesh_raw_data->raw_vertices, vertex_index, sizeof(s_raw_vertex)));

        if (TEST_BIT(compression_info->compression_flags, _compression_info_compressed_position_bit) &&
            compression_info->position_bounds.x0 < compression_info->position_bounds.x1 &&
            compression_info->position_bounds.y0 < compression_info->position_bounds.y1 &&
            compression_info->position_bounds.z0 < compression_info->position_bounds.z1)
        {
            assert_tag_debug_untracked_jul_11_2011(111, compression_info->position_bounds.x0<compression_info->position_bounds.x1);
            assert_tag_debug_untracked_jul_11_2011(112, compression_info->position_bounds.y0<compression_info->position_bounds.y1);
            assert_tag_debug_untracked_jul_11_2011(113, compression_info->position_bounds.z0<compression_info->position_bounds.z1);

            vertex->position.x = PIN((vertex->position.x - compression_info->position_bounds.x0) / (compression_info->position_bounds.x1 - compression_info->position_bounds.x0), 0.0f, 1.0f);
            vertex->position.y = PIN((vertex->position.y - compression_info->position_bounds.y0) / (compression_info->position_bounds.y1 - compression_info->position_bounds.y0), 0.0f, 1.0f);
            vertex->position.z = PIN((vertex->position.z - compression_info->position_bounds.z0) / (compression_info->position_bounds.z1 - compression_info->position_bounds.z0), 0.0f, 1.0f);
        }

        if (TEST_BIT(compression_info->compression_flags, _compression_info_compressed_texcoord_bit) &&
            compression_info->texcoord_bounds.x0 < compression_info->texcoord_bounds.x1 &&
            compression_info->texcoord_bounds.y0 < compression_info->texcoord_bounds.y1)
        {
            vertex->texcoord.x = PIN((vertex->texcoord.x - compression_info->texcoord_bounds.x0) / (compression_info->texcoord_bounds.x1 - compression_info->texcoord_bounds.x0), 0.0f, 1.0f);
            vertex->texcoord.y = PIN((vertex->texcoord.y - compression_info->texcoord_bounds.y0) / (compression_info->texcoord_bounds.y1 - compression_info->texcoord_bounds.y0), 0.0f, 1.0f);
        }
    }

    return success;
};

real geometry_material_get_lightmap_resolution_scale(geometry_material const * material, scenario_lightmap_setting const * lightmap_setting)
{
    mangled_ppc("?geometry_material_get_lightmap_resolution_scale@@YAMPBUgeometry_material@@PBUscenario_lightmap_setting@@@Z");

    real resolution_scale = 1.0f;

    if (material)
    {
        resolution_scale = material->lightmap_resolution_scale;
        long resolution_bucket_index = static_cast<long>(resolution_scale) - 1;

        if (VALID_INDEX(resolution_bucket_index, scenario_lightmap_setting::k_number_of_lightmap_resolution_buckets))
        {
            resolution_scale = lightmap_setting->lightmap_resolution_scales[resolution_bucket_index];
        }
        else
        {
            resolution_scale = 1.0f;
        }
    }

    if (resolution_scale < k_real_epsilon)
    {
        event_wrapped(_event_warning, "resolution_scale<k_real_epsilon!! you missed material??");
        resolution_scale = MAX(resolution_scale, k_real_epsilon);
    }

    return resolution_scale;
};

unsigned long geometry_material_get_lightmap_translucency_tint_color(geometry_material const * material)
{
    mangled_ppc("?geometry_material_get_lightmap_translucency_tint_color@@YAKPBUgeometry_material@@@Z");

    unsigned long result = 0;

    if (material)
    {
        result = material->lightmap_translucency_tint_color;
    }

    return result;
};

unsigned long geometry_material_get_lightmap_additive_transparency(geometry_material const * material)
{
    mangled_ppc("?geometry_material_get_lightmap_additive_transparency@@YAKPBUgeometry_material@@@Z");

    unsigned long result = 0;

    if (material)
    {
        result = material->lightmap_additive_transparency_color;
    }

    return result;
};

real geometry_material_get_lightmap_analytical_bounce_modifier(geometry_material const * material)
{
    mangled_ppc("?geometry_material_get_lightmap_analytical_bounce_modifier@@YAMPBUgeometry_material@@@Z");

    real result = 1.0f;

    if (material)
    {
        result = material->lightmap_analytical_light_absorb;
    }

    return result;
};

real geometry_material_get_lightmap_normal_bounce_modifier(geometry_material const * material)
{
    mangled_ppc("?geometry_material_get_lightmap_normal_bounce_modifier@@YAMPBUgeometry_material@@@Z");

    real result = 1.0f;

    if (material)
    {
        result = material->lightmap_normal_light_absorb;
    }

    return result;
};

bool geometry_material_get_lightmap_transparency_override(geometry_material const * material)
{
    mangled_ppc("?geometry_material_get_lightmap_transparency_override@@YA_NPBUgeometry_material@@@Z");

    bool result = false;

    if (material)
    {
        result = TEST_BIT(material->lightmap_flags, _geometry_material_lightmap_transparency_override_bit);
    }

    return result;
};

bool geometry_material_get_lightmap_lighting_from_both_sides(geometry_material const * material)
{
    mangled_ppc("?geometry_material_get_lightmap_lighting_from_both_sides@@YA_NPBUgeometry_material@@@Z");

    bool result = false;

    if (material)
    {
        result = TEST_BIT(material->lightmap_flags, _geometry_material_lightmap_lighting_from_both_sides_bit);
    }

    return result;
};

bool geometry_material_get_lightmap_ignore_default_resolution_scale(geometry_material const * material)
{
    mangled_ppc("?geometry_material_get_lightmap_ignore_default_resolution_scale@@YA_NPBUgeometry_material@@@Z");

    bool result = false;

    if (material)
    {
        result = TEST_BIT(material->lightmap_flags, _geometry_material_lightmap_ignore_default_resolution_scale_bit);
    }

    return result;
};

void geometry_material::clear_non_render_information(void)
{
    mangled_ppc("?clear_non_render_information@geometry_material@@QAAXXZ");

    imported_material_index = NONE;
    lightmap_resolution_scale = 0.0f;
    lightmap_additive_transparency_color = 0;
    lightmap_translucency_tint_color = 0;
    lightmap_analytical_light_absorb = 0.0f;
    lightmap_normal_light_absorb = 0.0f;
    lightmap_flags = 0;
    lightmap_chart_group_index = 0;
};

//public: static bool geometry_material::postprocess(long, void *, bool)
//{
//    mangled_ppc("?postprocess@geometry_material@@SA_NJPAX_N@Z");
//};
